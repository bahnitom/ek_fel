# read a file from std in
# cmd line arguments
#  -s sort output
#      1 = sort increasing by frequency
#      2 = sort alphabetically
#      other values ignored with warning "Warning: Chybna hodnota parametru -s!\n"
#  split text to words and remove punctuation
#  list of all unique word and their counts
#  20 chars for each word <space> word_count
#  count all words, number is considered as word
#  find most and least frequent words. if more than one keep the order as in text
#  exit code is always 0
#  output ends by \n
#  check the value of arg -l (positive int)
import argparse
import string
from pathlib import Path
from typing import List, Set


def parse_args() -> argparse.ArgumentParser:
    arg_parser = argparse.ArgumentParser(description='Read output from FE test')
    arg_parser.add_argument("-s", type=int, default=None,
                            help="Sorting 1 = sort increasing by frequency, 2 = sort alphabetically")
    arg_parser.add_argument("-c", action='store_true', help="Case sensitive (default False")
    arg_parser.add_argument("-l", default=None, type=int, help="Max length of words. 0 = suppress output")
    arg_parser.add_argument("-f", type=Path, metavar='filepath', help="Path of file to read")
    return arg_parser


def load_input_file(file: Path) -> List[str]:
    with open(file, mode='r') as input_file:
        # s.translate(str.maketrans('', '', string.punctuation)) remove punctuation
        lines = [line.translate(str.maketrans('', '', string.punctuation)) for line in input_file.readlines()]
        tmp_list: List[List[str]] = [line.split() for line in lines]
        all_words = []
        for word_list in tmp_list:
            all_words += word_list
        return all_words


def unique_words(case_aware_words: List[str]):
    seen = set()
    result = []
    for item in case_aware_words:
        if item not in seen:
            seen.add(item)
            result.append(item)
    return result


def word_count(case_aware_words: List[str], unique_word: str) -> int:
    count = 0
    for w in case_aware_words:
        if w == unique_word:
            count += 1
    return count


# case-sensitive
# python hw09.py -f ./data/pub00.in -c
# case-insensitive
# python hw09.py -f ./data/pub00.in
if __name__ == '__main__':
    parser = parse_args()
    args = parser.parse_args()
    sorting = args.s
    case_sensitive: bool = args.c
    print(f"sorting : {sorting}, case sensitive: {case_sensitive}")
    # MUST be kept untouched it is in original order
    initial_order_words: List[str] = load_input_file(Path(args.f))
    case_aware_words = initial_order_words if case_sensitive else [w.lower() for w in initial_order_words]
    print(f'all words count {len(initial_order_words)}')
    unique_w = unique_words(case_aware_words=case_aware_words)
    print(f'unique words count {len(unique_w)}, case sensitive : {case_sensitive}')
    word_counts = {u_w: word_count(case_aware_words=case_aware_words, unique_word=u_w) for u_w in unique_w}
    print('Seznam slov:')
    for k, v in word_counts.items():
        print("%-20s %d" % (k, v))
    print("%-20s %d" % ('Pocet slov:', len(unique_w)))
    print("%-20s %d" % ('Nejcastejsi:', len(unique_w)))
    print("%-20s %d" % ('Nejmene caste:', len(unique_w)))
