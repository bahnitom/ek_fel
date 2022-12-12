import math
import statistics
import sys
from pathlib import Path
from typing import List


def load_numbers(file) -> List[int]:
    with open(file, 'r') as input_file:
        for line in input_file:
            # one line only
            try:
                return list(map(int, line.split()))
            except ValueError as err:
                print("Invalid input")
                sys.exit(100)


def fill_bins(data: List[int]):
    n_intervals = data[0]
    series = data[1:]
    bins = init_bins(n_bins=n_intervals)
    min_num = min(series)
    interval_size = (max(series) - min(series)) / n_intervals
    for x in series:
        bin_number = put_in_bin(x=x, min_num=min_num, interval_size=interval_size)
        # increase count of items in the bin with bin_number
        bins[bin_number] += 1
    return bins


def print_histogram(bins: List[int], data: List[int]):
    """
    Scale and print bins. bins is array of int.
    The values at index i is the number of item in the bin i
    """
    bin_max = max(bins)
    scale_by = 25 / bin_max
    n_intervals = data[0]
    series = data[1:]
    min_number = min(series)
    interval_size = (max(series) - min(series)) / n_intervals
    for bin_number in range(len(bins)):
        n_of_signs = math.floor(scale_by * bins[bin_number])
        lower_bound = round(min_number + bin_number * interval_size, ndigits=1)
        upper_bound = round(min_number + (bin_number + 1) * interval_size, ndigits=1)
        print("%5.1f - %5.1f |%s" % (lower_bound, upper_bound, '=' * n_of_signs))
        # print("bin %2d, (%1d) %5.1f - %5.1f |%s" %
        #       (bin_number, bins[bin_number], lower_bound, upper_bound, '=' * n_of_signs))
        # print(f"bin {bin_number} ({bins[bin_number]}) {lower_bound} - {upper_bound}|{'=' * n_of_signs}")


def init_bins(n_bins: int) -> List[int]:
    """Initialize all bins to 0"""
    return [0] * n_bins


# small number
EPSILON = 0.001


def put_in_bin(x: int, min_num: int, interval_size: float) -> int:
    """
    Main logic here!
    Number of the bin for given x. Bins are numbered from <0, number of interval), i.e
    there number of bins = number of interval
    """
    # min values belong to bin 0
    # eps values means that the interval is right closed
    return 0 if x == min_num else math.floor((x - EPSILON - min_num) / interval_size)


def print_header(data: List[int]):
    # first numer is number of intervals
    n_intervals = data[0]
    # remaking numeraires is the series
    numbers = data[1:]
    median_num = statistics.median(numbers)
    print(f"Median {median_num}")
    print(f"Pocet cisel: {len(numbers)}")
    min_num = min(numbers)
    print(f"Min. hodnota: {min_num}")
    max_num = max(numbers)
    print(f"Max. hodnota: {max_num}")
    interval_size = (max(numbers) - min(numbers)) / n_intervals
    print(f"Pocet intervalu: {n_intervals}")
    print(f"Interval size: {interval_size}")


if __name__ == "__main__":
    f = Path(sys.argv[1])
    input_data = load_numbers(f)
    print_header(data=input_data)
    filled_bins = fill_bins(data=input_data)
    print(f"Histogram:")
    print_histogram(filled_bins, data=input_data)
