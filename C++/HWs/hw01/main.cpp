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

void printRow();

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

    if (all_cfg_values.min > all_cfg_values.max || all_cfg_values.width < 1){
        std::cerr << "Invalid configuration" << std::endl;
        return INVALID_CONFIGURATION;
    }

    std::vector<std::vector<int>> values;

    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::vector<int> row;
        std::string cell;
        int number;

        while (std::getline(ss, cell, ';')) {
            try {   // if loaded cell is number
                number = std::stoi(cell);
                // if number is out of range
                if ((number < all_cfg_values.min) || (number > all_cfg_values.max)) {
                    std::cerr << "Out of range" << std::endl;
                    return OUT_OF_RANGE;
                }
                row.push_back(number);
            }
//            catch (const char * str){
//                std::cerr << "Invalid input" << std::endl;
//                return INVALID_INPUT;
//            }
            catch (const std::exception &e) { // if there is a text (SUM?)
                if (cell.find("SUM") != 0) { // something different then number or word SUM
                    std::cerr << "Invalid input" << std::endl;
                    return INVALID_INPUT;
                }
                //todo check if SUM is valid
                int sum = getSum(line, row).value;
                row.push_back(sum);
            }
        }
        if (static_cast<int>(row.size()) > maxRow){
            maxRow = static_cast<int>(row.size());
        }
        values.push_back(row);
    }
    printCfgValues(all_cfg_values);
    std::cout << "\n";
    // print out the config - TODO /*config printim na radku 18*/

    // print table
    for (std::size_t a = 0; a < maxRow + 1; a++) {
        std::cout << "+";
        for (std::size_t b = 0; b < all_cfg_values.width + 2; b++) {
            std::cout << "-";
        }
    }
    std::cout << "+\n";

    std::cout << "|" << string (all_cfg_values.width+2, 32);



    for (std::size_t j = 0; j < maxRow; j++) {
        std::cout << "| ";
        if(all_cfg_values.align == "right"){
            std::cout<< string(all_cfg_values.width -1, 32);
            std::cout<< char(j + 65);
        }
        else{
            std::cout<< char(j + 65);
            std::cout<< string(all_cfg_values.width -1, 32);
        }
        std::cout << " ";
    }
    std::cout << "|";
    std::cout << std::endl;

    for (std::size_t a = 0; a < maxRow + 1; a++) {
        std::cout << "+";
        for (std::size_t b = 0; b < all_cfg_values.width + 2; b++) {
            std::cout << "-";
        }
    }


    std::cout << "+\n";


    for (std::size_t i = 0; i < values.size(); i++) {
        std::cout << "| ";
        if(all_cfg_values.align == "right"){
            std::cout<< string(all_cfg_values.width -1, 32);
            std::cout<< i + 1;
        }
        else{
            std::cout<< i + 1;
            std::cout<< string(all_cfg_values.width -1, 32);
        }
        std::cout << " ";

        for (std::size_t j = 0; j < values[i].size(); j++) {
            std::cout << "| ";
            int a = values[i][j];
            stringstream ss;
            ss << a;
            int numberOfChars = ss.str().length();
            if(all_cfg_values.align == "right"){
                std::cout<< string(all_cfg_values.width - numberOfChars, 32);
                std::cout<< values[i][j];
            }
            else{
                std::cout<< values[i][j];
                std::cout<< string(all_cfg_values.width - numberOfChars, 32);
            }
            std::cout << " ";
        }
        std::cout << "|";
        for (std::size_t j = values[i].size(); j < maxRow; j++) {
            std::cout << string(all_cfg_values.width + 2, 32) << "|";
        }
        std::cout << std::endl;
        for (std::size_t a = 0; a < maxRow + 1; a++) {
            std::cout << "+";
            for (std::size_t b = 0; b < all_cfg_values.width + 2; b++) {
                std::cout << "-";
            }
        }
        std::cout << "+\n";
    }
    return 0;
}