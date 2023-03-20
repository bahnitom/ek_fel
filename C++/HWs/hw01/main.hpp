
#ifndef MAIN_HPP
#define MAIN_HPP

#include "parse.hpp"

int checkTableRows(const cfg_values_t &cfgValues, const std::vector<std::vector<int>> &rows);

int checkConfigValues(const cfg_values_t &cfgValues);

void printTableRows(const cfg_values_t &cfgValues, const std::vector<std::vector<int>> &rows);

#endif