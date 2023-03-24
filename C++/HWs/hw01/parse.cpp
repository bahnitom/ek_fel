#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "parse.hpp"

/**
 * according to assignment config section follows pattern
 * 1. starts with config.
 * 2. allowed values are min, max, width, align, stretch, header
 * so the regexp can be narrowed to
 * config\.(min|max|width|align|stretch|header)=([-+]?\d+|left|right)
 * where [-+]? means 0 or 1 sign,  \d+ at least one number
 * @param text
 * @return
 */
config_t getConfig(const std::string &text) {
    config_t config;
    std::regex regexConfig(R"(config\.(min|max|width|align|stretch|header)=([-+]?\d+|left|right))");
    std::smatch fn_match;
    config.valid = false;

    if (std::regex_search(text, fn_match, regexConfig)) {
        config.type = fn_match[1];
        config.value = fn_match[2];
        config.valid = true;
    } else {
        config.valid = false;
    }
    return config;
}

/**
 * Only regexp
 * SUM\(([A-Z]):([A-Z])\) is valid according to assignment
 * @param text
 * @param numbers
 * @return
 */
sum_t getSum(const std::string &text, std::vector<int> numbers) {
    sum_t sum;
    std::regex regexConfig(R"(SUM\(([A-Z]):([A-Z])\))");
    std::smatch fn_match;
    sum.valid = false;
    sum.value = 0;

    if (std::regex_search(text, fn_match, regexConfig)) {
        std::string temp = fn_match[1];
        int from = temp[0] - 'A';
        temp = fn_match[2];
        int to = temp[0] - 'A';

        if (to < (int) numbers.size()) {
            for (int i = from; i <= to; i++) {
                sum.value += numbers[i];
            }
            sum.valid = true;
            sum.width = std::to_string(sum.value).size();
        } else {
            sum.valid = false;
        }
    }
    return sum;
}

cfg_values_t get_default_cfg_values() {
    cfg_values_t config_val;
    config_val.min = -99;
    config_val.max = 100;
    config_val.width = 3;
    config_val.align = "left";
    config_val.stretch = -1;
    config_val.header = 1;
    return config_val;
}

cfg_values_t set_cfg_values(cfg_values_t allCfgValues, const config_t &cfgValue) {
    if (cfgValue.type == MIN_TYPE) {
        allCfgValues.min = std::stoi(cfgValue.value);
    }
    if (cfgValue.type == MAX_TYPE) {
        allCfgValues.max = std::stoi(cfgValue.value);
    }
    if (cfgValue.type == WIDTH_TYPE) {
        allCfgValues.width = std::stoi(cfgValue.value);
    }
    if (cfgValue.type == ALIGN_TYPE) {
        allCfgValues.align = cfgValue.value;
    }
    if (cfgValue.type == STRETCH_TYPE) {
        allCfgValues.stretch = std::stoi(cfgValue.value);
    }
    if (cfgValue.type == HEADER_TYPE) {
        allCfgValues.header = std::stoi(cfgValue.value);
    }
    return allCfgValues;
}

void printCfgValue(const std::string &type, const std::string &value) {
    std::cout << CONFIG_PREFIX_DOT + type + EQUAL_SIGN + value;
    std::cout << "\n";
}


void printCfgValues(const cfg_values_t &cfgValues) {
    printCfgValue(MIN_TYPE, std::to_string(cfgValues.min));
    printCfgValue(MAX_TYPE, std::to_string(cfgValues.max));
    printCfgValue(WIDTH_TYPE, std::to_string(cfgValues.width));
    printCfgValue(ALIGN_TYPE, cfgValues.align);
}