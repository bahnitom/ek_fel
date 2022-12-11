import math
import statistics
import sys
from pathlib import Path
from typing import List


def load_numbers(file) -> List[int]:
    with open(file, 'r') as input_file:
        for line in input_file:
            # one line only
            return list(map(int, line.split()))


def load_input_file(file: Path) -> List[str]:
    with open(file, mode='r') as input_file:
        return [line.strip() for line in input_file.readlines()]


def fill_bins(input_data: List[int]):
    n_intervals = input_data[0]
    print(f"Pocet intervalu {n_intervals}")
    numbers = input_data[1:]
    print(f"Pocet cisel {len(numbers)}")
    interval_size = (max(numbers) - min(numbers)) / n_intervals
    print(f"Interval size {interval_size}")
    min_num = min(numbers)
    print(f"min= {min_num}")
    max_num = max(numbers)
    print(f"max= {max_num}")
    median_num = statistics.median(numbers)
    print(f"median= {median_num}")
    #  0..n
    bins_count = 0
    for i in range(n_intervals + 1):
        k = min(numbers) + i + interval_size
        bins_count += 1
        print(f"bin {bins_count} : interval {i} upper bound = {round(k, ndigits=1)}")
    bins = get_bins(n_bins=bins_count)
    for x_i in numbers:
        b = put_in_bin(x=x_i, min_num=min_num, interval_size=interval_size)
        bins[b] += 1
        # print(f"{x_i}: bin({x_i}) = {b}")
    return bins


def print_bins(bins: List[int]):
    bin_max = max(bins)
    scale_by = 25 / bin_max
    for b in range(len(bins)):
        n_of_signs = math.ceil(scale_by * bins[b])
        print(f"in bin {b + 1} | {'=' * n_of_signs} {n_of_signs}")


def get_bins(n_bins: int) -> List[int]:
    return [0] * n_bins


def put_in_bin(x: int, min_num: int, interval_size: float) -> int:
    return math.floor((x - min_num) / interval_size)


if __name__ == "__main__":
    f = Path(sys.argv[1])
    i_f = load_numbers(f)
    filled_bins = fill_bins(input_data=i_f)
    print_bins(filled_bins)
