#!/home/toba/miniconda3/envs/pycpt/bin/python
import collections
import os
import subprocess
import sys
from pathlib import Path
from typing import List, Tuple

import typer

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


def run_cmd(cmd: List[str], stdin_path: Path = None, msg: str = None) -> CmdOutput:
    m = f"Running {cmd} < {stdin_path}"
    typer.echo(m)
    test_data = open(stdin_path) if stdin_path else subprocess.DEVNULL
    p = subprocess.Popen(cmd, stdin=test_data, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    p.wait()
    return_code = p.returncode
    std_out = p.stdout.read().decode('utf-8').strip()
    std_err = p.stderr.read().decode('utf-8').strip()
    m = msg if msg else str(cmd)
    if std_err and len(std_err) > 0:
        typer.echo(f"{m} : stderr = {std_err}")
    return CmdOutput(ret_code=return_code, s_out=std_out, s_err=std_err)


def compile_project(folder: Path, files: List[str], output_file: Path) -> CmdOutput:
    # clang -pedantic -Wall -Werror -std=c99 -O3 -lm $COMPILE_FILES -o $OUTPUT_FILE
    project_files = [Path(folder, f) for f in files]
    # get correct paths
    compile_files_list: List[str] = [str(file) for file in project_files]
    clang_cmd = ['clang'] + CLANG_OPTIONS
    cmd: List[str] = clang_cmd + compile_files_list + ['-o', output_file]
    return run_cmd(cmd=cmd)


def read_test_files(folder: Path):
    in_files: List[Path] = list_files(folder, ends_with='.in')
    out_files: List[Path] = list_files(folder, ends_with='.out')
    err_files: List[Path] = list_files(folder, ends_with='.err')
    typer.echo(f"{len(in_files)} in files, {len(out_files)} out files, {len(err_files)} err files")
    return in_files, out_files, err_files


def run_tests(test_files, bin_file: Path):
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
                typer.echo(f"FAILED return code = {cmd_out.ret_code}, std_err:{cmd_out.s_err}")
                typer.echo(f"actual output:\n{test_out.encode('utf-8')}")
                typer.echo(f"expected output:\n{expected_out.encode('utf-8')}")
            else:
                typer.echo(f"PASSED, return code = {cmd_out.ret_code}, std_err:{cmd_out.s_err}")
        else:
            typer.echo(f"expected output file {o_f_path} does not exist")


def run_mem_test(test_files, bin_file):
    # valgrind $VALGRIND_OPTIONS ./$OUTPUT_FILE < $test_file
    valgrind_cmd = ['valgrind'] + VALGRIND_OPTIONS + [f"./{bin_file}"]
    for test_file in sorted(test_files):
        typer.echo(f"\n")
        cmd: List[str] = valgrind_cmd + [test_file]
        cmd_out: CmdOutput = run_cmd(cmd=cmd, stdin_path=test_file)
        # typer.echo(f"Valgrind std out:\n {cmd_out.s_out}")


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
        typer.echo(f"remove {project_bin_file}")
        os.remove(project_bin_file)
    r_c, s_o, s_e = compile_project(folder=project_folder, files=project_files, output_file=project_bin_file)
    if not project_bin_file.is_file():
        # compilation error
        typer.echo(f"compilation error. {project_bin_file} does not exist")
        sys.exit(2)
    in_f, out_f, err_f = read_test_files(project_folder)
    run_tests(test_files=in_f, bin_file=project_bin_file)
    run_mem_test(test_files=in_f, bin_file=project_bin_file)
