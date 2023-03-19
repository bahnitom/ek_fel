#include <iostream>
#include <string>
#include <vector>
#include "parse.cpp"

int main(){  
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

    printCfgValues(allCfgValues);

    std::cout << "\n";

    std::vector<std::vector<int>> values;

    while(std::getline(std::cin, line)){
        std::stringstream ss(line);
        std::vector<int> row;
        std::string cell;
        int number;

        while (std::getline(ss,cell, ';')) {
            try {   // if loaded cell is number
                number = std::stoi(cell);
                //std::cout << number;
				row.push_back(number);
            }
            catch(const std::exception& e){ // if there is a text (SUM?)
                int sum = getSum(line, row).value;
                row.push_back(sum);
            }
        }   
        values.push_back(row);     
    }
    // print out the config - TODO /*config printim na radku 18*/
    
	// print table
    for (std::size_t i = 0; i < values.size(); i++){
        std::cout << "+----+-----+-----+" << std::endl;
        for (std::size_t j = 0; j < values[i].size(); j++){
            std::cout << "| " << values[i][j] << " |";
        }
        std::cout << std::endl;
    }
    return 0;
}