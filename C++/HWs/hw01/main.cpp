#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <iomanip>
#include "main.hpp"
#include "parse.cpp"

using namespace std;

// macros
#define OUT_OF_RANGE 100
#define INVALID_INPUT 101
#define INVALID_CONFIGURATION 102
#define CELL_TOO_SHORT 103

void print_table(const cfg_values_t &all_cfg_values, int maxRow, const vector<std::vector<int>> &values);

int error(int type_of_error);

int main() {
    // variable for decoded config
    config_t config;
    std::string line;
    cfg_values_t all_cfg_values = get_default_cfg_values();
    int maxRow = -1;
    do {
        std::getline(std::cin, line);
        config = getConfig(line);
        if (config.valid) {
            all_cfg_values = set_cfg_values(all_cfg_values, config);
        }
    } while (config.valid);

    int maxNumberLen = all_cfg_values.max;
    stringstream string_stream_1;
    string_stream_1 << maxNumberLen;
    int numberOfMax = string_stream_1.str().length();

    std::vector<std::vector<int>> values;

    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::vector<int> row;
        std::string cell;
        int number;

        while (std::getline(ss, cell, ';')) {
            try {   // if loaded cell is number
                number = std::stoi(cell);
                if ((number < all_cfg_values.min) || (number > all_cfg_values.max)) { // if number is out of range
                    error(1);
                }
                row.push_back(number);
            }
            catch (const std::exception &e) { // if there is a text (SUM?)
                if (cell.find("SUM") != 0) { // something different then number or word SUM
                     error(2);
                }
                // todo check if SUM is valid
                int sum = getSum(line, row).value;
                row.push_back(sum);
            }
        }
        if (static_cast<int>(row.size()) > maxRow) {
            maxRow = static_cast<int>(row.size());
        }
        values.push_back(row);
    }
    if (all_cfg_values.min > all_cfg_values.max || all_cfg_values.width < 1) { // min > max or width is negative number
        error(3);
    }
    if (all_cfg_values.width < numberOfMax) { // cell is too small for the number
        error(4);
    }

    printCfgValues(all_cfg_values); //printing config
    std::cout << "\n";

    print_table(all_cfg_values, maxRow, values); // print table
    return 0;
}

void print_table(const cfg_values_t &all_cfg_values, int maxRow, const vector<std::vector<int>> &values) {
    for (size_t a = 0; a < maxRow + 1; a++) {
        cout << "+";
        for (size_t b = 0; b < all_cfg_values.width + 2; b++) {
            cout << "-";
        }
    }
    cout << "+\n";
    cout << "|" << string(all_cfg_values.width + 2, 32);

    for (size_t j = 0; j < maxRow; j++) {
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

    for (size_t a = 0; a < maxRow + 1; a++) {
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
        for (size_t j = values[i].size(); j < maxRow; j++) {
            cout << string(all_cfg_values.width + 2, 32) << "|";
        }
        cout << endl;
        for (size_t a = 0; a < maxRow + 1; a++) {
            cout << "+";
            for (size_t b = 0; b < all_cfg_values.width + 2; b++) {
                cout << "-";
            }
        }
        cout << "+\n";
    }
}

int error(int type_of_error) {
    switch (type_of_error) {
        case 1:
            std::cerr << "Out of range" << std::endl;
//            return OUT_OF_RANGE;
            exit(OUT_OF_RANGE);
        case 2:
            std::cerr << "Invalid input" << std::endl;
//            return INVALID_INPUT;
            exit(INVALID_INPUT);
        case 3:
            std::cerr << "Invalid configuration" << std::endl;
//            return INVALID_CONFIGURATION;
            exit(INVALID_CONFIGURATION);
        case 4:
            std::cerr << "Cell too short" << std::endl;
//            return CELL_TOO_SHORT;
            exit(CELL_TOO_SHORT);
        default:
            std::cerr << "Different error" << std::endl;
            exit(-1);
    }

}