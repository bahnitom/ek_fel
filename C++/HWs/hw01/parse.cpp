
#include <string>
#include <regex>
#include <vector>
#include "parse.hpp"
/**
 * according to assignment config section follows pattern
 * 1. starts with config.
 * 2. allowed values are min, max, width, align
 * so the regexp can be narrowed to
 * config\.(min|max|width|align)=(\d+|left|right)
 * which simplifies these functions +2b
 * @param text
 * @return
 */
config_t getConfig(std::string text){
    config_t config;
    std::regex regexConfig(R"((\w+).(\w+)=([\w-]+))");
    std::smatch fn_match;
    config.valid = false;

    if(std::regex_search(text, fn_match, regexConfig)){
        if(fn_match[1].compare(CONFIG_PREFIX) == 0){
            config.type = fn_match[2];
            config.value = fn_match[3];
            config.valid = true;
        }
        else{
            config.type = "not config";
        }
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
sum_t getSum(std::string text, std::vector<int> numbers){
    sum_t sum;
    std::regex regexConfig(R"((\w+)\((\w):(\w)\))");
    std::smatch fn_match;
    sum.valid = false;
    sum.value = 0;

    if(std::regex_search(text, fn_match, regexConfig)){
        if(fn_match[1].compare("SUM") == 0){
            std::string temp = fn_match[2];
            int from = temp[0] - 'A';
            temp = fn_match[3];
            int to = temp[0] - 'A';

            if(to < (int)numbers.size()){
                for(int i=from; i<=to; i++){
                    sum.value += numbers[i];
                }
                sum.valid = true;
                sum.width = std::to_string(sum.value).size();
            }
            else{
                sum.valid = false;
            }
        }
    }
    return sum;
}

cfg_values_t getDefaultCfgValues(){
    cfg_values_t cfgValues;
    cfgValues.min = -99;
    cfgValues.max = 100;
    cfgValues.width = 3;
    cfgValues.align = "left";
    return cfgValues;
}

cfg_values_t setCfgValues(cfg_values_t allCfgValues, const config_t& cfgValue) {
    if (cfgValue.type == MIN_TYPE) {
        allCfgValues.min = std::stoi(cfgValue.value);
    }
    if (cfgValue.type == MAX_TYPE) {
        allCfgValues.max = std::stoi(cfgValue.value);
    }
    if (cfgValue.type == WIDTH_TYPE) {
        // width is long unsigned int and width <= 0 is invalid
        if (std::stoi(cfgValue.value) > 0) {
            allCfgValues.width = std::stoi(cfgValue.value);
        } else {
            allCfgValues.width = 0;
        }
    }
    if (cfgValue.type == ALIGN_TYPE) {
        allCfgValues.align = cfgValue.value;
    }
    return allCfgValues;
}

void printCfgValue(const std::string& type, const std::string& value) {
    std::cout << CONFIG_PREFIX_DOT + type + EQUAL_SIGN + value;
    std::cout << "\n";
}


void printCfgValues(const cfg_values_t& cfgValues) {
    printCfgValue(MIN_TYPE, std::to_string(cfgValues.min));
    printCfgValue(MAX_TYPE, std::to_string(cfgValues.max));
    printCfgValue(WIDTH_TYPE, std::to_string(cfgValues.width));
    printCfgValue(ALIGN_TYPE, cfgValues.align);
    std::cout << "\n";
}