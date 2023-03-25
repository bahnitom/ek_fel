
#ifndef MAIN_HPP
#define MAIN_HPP

#include "parse.hpp"

typedef struct {
    int code;
    std::string message;
} error_with_msg_t;


int checkTableRows(const cfg_values_t &cfgValues, const std::vector<std::vector<int>> &rows);

void checkConfigValues(const cfg_values_t &cfgValues);

void printTableRows(const cfg_values_t &cfgValues, const std::vector<std::vector<int>> &rows);

void loadData(const cfg_values_t &cfgValues, std::vector<std::vector<int>>& values);

void handleError(const error_with_msg_t &e_w_m);


static const error_with_msg_t OUT_OFF_RANGE = {100, "Out of range\n"};
static const error_with_msg_t INVALID_INPUT = {101, "Invalid input\n"};
static const error_with_msg_t INVALID_CONFIG = {102, "Invalid configuration\n"};
static const error_with_msg_t CELL_IS_TOO_SHORT = {103, "Cell is too short\n"};

#endif