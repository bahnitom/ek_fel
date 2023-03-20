#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <iomanip>
#include "main.hpp"
#include "parse.cpp"

/**
 * Iterates over all values in table (2d array = vector of vectors)
 * and checks if the number fit the cell i.e. width of the cell is <= length of all numbers
 * @param cfgValues test configuration
 * @param rows 2d array of numbers
 * @return 103 in case some of the numbers does not fit into cell
 */
int checkTableRows(const cfg_values_t& cfgValues, const std::vector<std::vector<int>>& rows) {
    std::string number_str;
    for (const auto & row : rows) {
        for (int number: row) {
            if (number < cfgValues.min or number > cfgValues.max) {
                std::cout << "Out of range";
                return 100;
            }
            number_str = std::to_string(number);
            if (number_str.length() > cfgValues.width) {
                std::cout << "Cell is too short";
                return 103;
            }
        }
    }
    return 0;
}

int checkConfigValues(const cfg_values_t& cfgValues) {
    if (cfgValues.min > cfgValues.max) {
        std::cout << "Invalid configuration";
        return 102;
    }
    if (cfgValues.width < 0) {
        std::cout << "Invalid configuration";
        return 102;
    }
    return 0;
}

int main() {
    // variable for decoded config
    config_t config;
    std::string line;
    int ret_code;
    cfg_values_t allCfgValues = getDefaultCfgValues();
    do {
        std::getline(std::cin, line);
        config = getConfig(line);
        if (config.valid) {
            allCfgValues = setCfgValues(allCfgValues, config);
        }
    } while (config.valid);

    ret_code = checkConfigValues(allCfgValues);
    if (ret_code != 0) {
        return ret_code;
    }

    printCfgValues(allCfgValues);

    std::cout << "\n";

    std::vector<std::vector<int>> values;

    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::vector<int> row;
        std::string cell;
        int number;

        while (std::getline(ss, cell, ';')) {
            try {   // if loaded cell is number
                number = std::stoi(cell);
                //std::cout << number;
                row.push_back(number);
            }
            catch (const std::exception &e) { // if there is a text (SUM?)
                int sum = getSum(line, row).value;
                row.push_back(sum);
            }
        }
        values.push_back(row);
    }
    ret_code = checkTableRows(allCfgValues, values);
    if (ret_code != 0) {
        return ret_code;
    }

    // print table
    for (std::size_t a = 0; a < 5; a++) {
        std::cout << "+";
        for (std::size_t b = 0; b < 5; b++) {
            std::cout << "-";
        }
    }
    std::cout << "+\n";
    for (std::size_t i = 0; i < values.size(); i++) {
        for (std::size_t j = 0; j < values[i].size(); j++) {
            std::cout << "|   " << values[i][j];
        }
        std::cout << std::endl;
    }
    return 0;
}