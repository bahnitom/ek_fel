#!/usr/bin/python3
import collections
import os
import subprocess
import sys
from pathlib import Path
from typing import List

CmdOutput = collections.namedtuple('CmdOutput', ['ret_code', 's_out', 's_err'])

CLANG_OPTIONS = ["-pedantic", "-Wall", "-Werror", "-std=c99", "-O3", "-lm"]
VALGRIND_OPTIONS = ["--leak-check=full", "--leak-resolution=med", "--track-origins=yes", "--vgdb=no"]


def list_files(folder: Path, ends_with: str = '.txt') -> List[Path]:
    # traverse root directory, and list directories as dirs and files as files
    file_type_files: List[Path] = []
    for root, dirs, files in os.walk(folder):
        for file in files:
            if file.endswith(ends_with):
                l_f = Path(root, file)
                file_type_files.append(l_f)
    return file_type_files


def run_cmd(cmd: List[str], stdin_path: Path = None) -> CmdOutput:
    m = f"Running cmd line: {cmd} < {stdin_path}"
    print(m)
    test_data = open(stdin_path) if stdin_path else subprocess.DEVNULL
    p = subprocess.run(cmd, stdin=test_data, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return_code = p.returncode
    std_out = p.stdout.decode('utf-8').strip()
    std_err = p.stderr.decode('utf-8').strip()
    if std_err and len(std_err) > 0:
        print(f"{'=' * 5} std err {'=' * 5}")
        sys.stderr.write(std_err)
    return CmdOutput(ret_code=return_code, s_out=std_out, s_err=std_err)


def compile_project(folder: Path, files: List[str], output_file: Path) -> CmdOutput:
    print(f"\n{'=' * 5} Compile project {'=' * 5}")
    # project files as list of strings
    prj_files: List[str] = [str(Path(folder, f)) for f in files]
    clang_cmd = ['clang'] + CLANG_OPTIONS
    cmd: List[str] = clang_cmd + prj_files + ['-o', output_file]
    return run_cmd(cmd=cmd)


def read_test_files(folder: Path):
    print(f"\n{'=' * 5} Read test files {'=' * 5}")
    in_files: List[Path] = list_files(folder, ends_with='.in')
    out_files: List[Path] = list_files(folder, ends_with='.out')
    err_files: List[Path] = list_files(folder, ends_with='.err')
    print(f"{len(in_files)} in files, {len(out_files)} out files, {len(err_files)} err files")
    return in_files, out_files, err_files


def run_tests(test_files, bin_file: Path):
    print(f"\n{'=' * 5} Functional test {'=' * 5}")
    for in_file in sorted(test_files):
        test_cmd = [f"./{bin_file}"]
        cmd_out: CmdOutput = run_cmd(test_cmd, stdin_path=in_file)
        # out files contain new line
        test_out = cmd_out.s_out + "\n"
        # get name of out file
        o_f = str(in_file).replace('in', 'out')
        o_f_path = Path(o_f)
        if o_f_path.is_file():
            out_file_stream = open(o_f_path)
            expected_out = out_file_stream.read()
            test_passed = test_out == expected_out
            if not test_passed:
                print(f"FAILED return code = {cmd_out.ret_code}, std_err:{cmd_out.s_err}")
                print(f"actual output:\n{test_out.encode('utf-8')}")
                print(f"expected output:\n{expected_out.encode('utf-8')}")
            else:
                print(f"PASSED, return code = {cmd_out.ret_code}, std_err:{cmd_out.s_err}")
        else:
            print(f"expected output file {o_f_path} does not exist")


def run_mem_test(test_files, bin_file):
    # valgrind $VALGRIND_OPTIONS ./$OUTPUT_FILE < $test_file
    print(f"\n{'=' * 5} Memory test {'=' * 5}")
    valgrind_cmd = ['valgrind'] + VALGRIND_OPTIONS + [f"./{bin_file}"]
    for test_file in sorted(test_files):
        cmd_out: CmdOutput = run_cmd(cmd=valgrind_cmd, stdin_path=test_file)
        print(f"\n")


MAIN_C = ['main.c']

if __name__ == "__main__":
    # folder with main.c and other project files
    # and data sub folder with in/out/err test files
    project_folder: Path = Path(sys.argv[1])
    # all project file, if there is only one main.c is default
    project_files: List[str] = sys.argv[2:] if len(sys.argv) > 2 else MAIN_C
    # path to complied bin file
    project_bin_file = Path(project_folder, 'data', f"main_{project_folder}")
    if project_bin_file.is_file():
        # delete binary file
        print(f"remove {project_bin_file}")
        os.remove(project_bin_file)
    r_c, s_o, s_e = compile_project(folder=project_folder, files=project_files, output_file=project_bin_file)
    if not project_bin_file.is_file():
        # compilation error
        print(f"compilation error. {project_bin_file} does not exist")
        sys.exit(2)
    in_f, out_f, err_f = read_test_files(project_folder)
    run_tests(test_files=in_f, bin_file=project_bin_file)
    run_mem_test(test_files=in_f, bin_file=project_bin_file)
