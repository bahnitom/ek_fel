
#ifndef MAIN_HPP
#define MAIN_HPP

#include "parse.hpp"

static const int OUT_OFF_RANGE_ERROR = 100;

static const int INVALID_INPUT_ERROR = 101;

static const int INVALID_CONFIG_ERROR = 102;

static const int CELL_IS_TOO_SHORT_ERROR = 103;

static const char *const OUT_OFF_RANGE_MSG = "Out of range\n";

static const char *const INVALID_CONFIG_MSG = "Invalid configuration\n";

static const char *const INVALID_INPUT_MSG = "Invalid input\n";

static const char *const CELL_IS_TOO_SHORT_MSG = "Cell is too short\n";

int checkTableRows(const cfg_values_t &cfgValues, const std::vector<std::vector<int>> &rows);

int checkConfigValues(const cfg_values_t &cfgValues);

void printTableRows(const cfg_values_t &cfgValues, const std::vector<std::vector<int>> &rows);

int loadData(const cfg_values_t &cfgValues, std::vector<std::vector<int>> *values);

#endif