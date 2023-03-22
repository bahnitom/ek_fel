#include <iostream>
#include <string>
#include <vector>
#include "main.hpp"
#include "parse.cpp"

using namespace std;

void handleError(const error_with_msg_t &e_w_m) {
    std::cout << e_w_m.message;
    exit(e_w_m.code);
}


/**
 * Iterates over all values in table (2d array = vector of vectors)
 * and checks if the number fit the cell i.e. width of the cell is <= length of all numbers
 * @param cfgValues test configuration
 * @param rows 2d array of numbers
 * @return 103 in case some of the numbers does not fit into cell
 */
int checkTableRows(const cfg_values_t &cfgValues, const std::vector<std::vector<int>> &rows) {
    std::string number_str;
    for (const auto &row: rows) {
        for (int number: row) {
            if (number < cfgValues.min or number > cfgValues.max) {
                handleError(OUT_OFF_RANGE);
            }
            number_str = std::to_string(number);
            if (number_str.length() > cfgValues.width) {
                handleError(CELL_IS_TOO_SHORT);
            }
        }
    }
    return 0;
}

void checkConfigValues(const cfg_values_t &cfgValues) {
    // width is long unsigned int and width is set to 0 if not > 0
    if (cfgValues.min > cfgValues.max or cfgValues.width == 0) {
        handleError(INVALID_CONFIG);
    }
}

/**
 * @return Length of longest row
 */
std::vector<int>::size_type maxRowLength(const std::vector<std::vector<int>> &rows) {
    std::vector<int>::size_type max = 0;
    for (const auto &row: rows) {
        max = row.size() > max ? row.size() : max;
    }
    return max;
}

/**
 * Load and validate data
 * @param cfgValues configuration of the test
 * @param values load data to this 2d array
 * @return 2d array of loaded data
 */
void loadData(const cfg_values_t &cfgValues, std::vector<std::vector<int>> *values) {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::vector<int> row;
        std::string cell;
        int number;

        while (std::getline(ss, cell, ';')) {
            try {   // if loaded cell is number
                number = std::stoi(cell);
                if ((number < cfgValues.min) || (number > cfgValues.max)) { // if number is out of range
                    handleError(OUT_OFF_RANGE);
                }
                if (std::to_string(number).length() > cfgValues.width) {
                    handleError(CELL_IS_TOO_SHORT);
                }
                row.push_back(number);
            }
            catch (const std::exception &e) { // if there is a text (SUM?)
                if (cell.find("SUM") != 0) { // something different from number or word SUM
                    handleError(INVALID_INPUT);
                }
                int sum = getSum(line, row).value;
                row.push_back(sum);
            }
        }
        values->push_back(row);
    }
}

void printTableRows(const cfg_values_t &cfgValues, const std::vector<std::vector<int>> &rows) {
    std::string number_str;
    std::vector<int>::size_type max_row_length = maxRowLength(rows);
    long unsigned int line_length = max_row_length * (cfgValues.width + 2);
    std::string line(line_length, '-'); // repeat character n times
    for (const auto &row: rows) {
        std::cout << line << std::endl;
        std::string r = "|";
        for (int number: row) {
            number_str = std::to_string(number);
            r.append(" " + number_str + " |");
        }
        std::cout << r << std::endl;
    }
    std::cout << line << std::endl;
}

void print_table(const cfg_values_t &all_cfg_values, const vector<std::vector<int>> &values) {
    std::vector<int>::size_type max_row_length = maxRowLength(values);
    for (size_t a = 0; a < max_row_length + 1; a++) {
        cout << "+";
        for (size_t b = 0; b < all_cfg_values.width + 2; b++) {
            cout << "-";
        }
    }
    cout << "+\n";
    cout << "|" << string(all_cfg_values.width + 2, 32);

    for (size_t j = 0; j < max_row_length; j++) {
        cout << "| ";
        if (all_cfg_values.align == "right") {
            cout << string(all_cfg_values.width - 1, 32);
            cout << char(j + 65);
        } else {
            cout << char(j + 65);
            cout << string(all_cfg_values.width - 1, 32);
        }
        cout << " ";
    }
    cout << "|";
    cout << endl;

    for (size_t a = 0; a < max_row_length + 1; a++) {
        cout << "+";
        for (size_t b = 0; b < all_cfg_values.width + 2; b++) {
            cout << "-";
        }
    }
    cout << "+\n";

    for (size_t i = 0; i < values.size(); i++) {
        cout << "| ";
        if (all_cfg_values.align == "right") {
            cout << string(all_cfg_values.width - 1, 32);
            cout << i + 1;
        } else {
            cout << i + 1;
            cout << string(all_cfg_values.width - 1, 32);
        }
        cout << " ";

        for (size_t j = 0; j < values[i].size(); j++) {
            cout << "| ";
            int a = values[i][j];
            stringstream ss;
            ss << a;
            int numberOfChars = ss.str().length();
            if (all_cfg_values.align == "right") {
                cout << string(all_cfg_values.width - numberOfChars, 32);
                cout << values[i][j];
            } else {
                cout << values[i][j];
                cout << string(all_cfg_values.width - numberOfChars, 32);
            }
            cout << " ";
        }
        cout << "|";
        for (size_t j = values[i].size(); j < max_row_length; j++) {
            cout << string(all_cfg_values.width + 2, 32) << "|";
        }
        cout << endl;
        for (size_t a = 0; a < max_row_length + 1; a++) {
            cout << "+";
            for (size_t b = 0; b < all_cfg_values.width + 2; b++) {
                cout << "-";
            }
        }
        cout << "+\n";
    }
}

int main() {
    // variable for decoded config
    config_t config;
    std::string line;
    cfg_values_t allCfgValues = getDefaultCfgValues();
    do {
        std::getline(std::cin, line);
        config = getConfig(line);
        if (config.valid) {
            allCfgValues = setCfgValues(allCfgValues, config);
        }
    } while (config.valid);
    checkConfigValues(allCfgValues);
    printConfigValues(allCfgValues);
    std::vector<std::vector<int>> values;
    loadData(allCfgValues, &values);
//    printTableRows(allCfgValues, values);
    print_table(allCfgValues, values);
    return 0;
}