# read a file from std in
# cmd line arguments
#  -s sort output
#      1 = sort increasing by frequency
#      2 = sort alphabetically
#      other values ignored with warning "Warning: Chybna hodnota parametru -s!\n"
#  split text to words and remove punctuation
#  list of all unique word
#  20 chars for each word space count
#  count all words, number is considered as word
#  find most and least frequent words. if more than one keep the order as in text
#  exit code is always 0
#  output ends by \n
#  check the value of arg -l (positive int)
import argparse
import string
from pathlib import Path
from typing import List


def parse_args() -> argparse.ArgumentParser:
    arg_parser = argparse.ArgumentParser(description='Read output from FE test')
    arg_parser.add_argument("-s", type=int, default=None,
                            help="Sorting 1 = sort increasing by frequency, 2 = sort alphabetically")
    arg_parser.add_argument("-c", default=None, help="Case sensitive")
    arg_parser.add_argument("-l", default=None, type=int, help="Max length of words. 0 = suppress output")
    arg_parser.add_argument("-f", type=Path, metavar='filepath', help="Path of file to read")
    return arg_parser


def load_input_file(file: Path) -> List[List[str]]:
    with open(file, mode='r') as input_file:
        # s.translate(str.maketrans('', '', string.punctuation)) remove punctuation
        lines = [line.translate(str.maketrans('', '', string.punctuation)) for line in input_file.readlines()]
        return [line.split() for line in lines]


if __name__ == '__main__':
    parser = parse_args()
    args = parser.parse_args()
    sorting = args.s
    print(f"sorting : {sorting}")
    text = load_input_file(Path(args.f))
    for words in text:
        print(words)
