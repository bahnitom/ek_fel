#ifndef _PARSE_HPP_
#define _PARSE_HPP_

#include <string>
#include <vector>

/**
 * Header file for parsing inputs and printing out the header and lines
 */

/** 
 *  @brief Configuration struct 
 */
typedef struct{
    std::string type;       /**< Type of the config as string  */
    std::string value;      /**< Value after '=' char  */
    bool valid;             /**< true if this configuration is valid  */
}config_t;

/** 
 *  @brief Sum struct
 */
typedef struct{
    int value;              /**< Sum of the cells  */
    bool valid;             /**< true if this sum is valid  */
    int width;              /**< Width of the text  */
}sum_t;

typedef struct {
    int min;
    int max;
    // to avoid g++ compilation errors width must be that type
    long unsigned int width;
    std::string align;
} cfg_values_t;

static const std::string MIN_TYPE = "min";

static const std::string MAX_TYPE = "max";

static const std::string WIDTH_TYPE = "width";

static const std::string ALIGN_TYPE = "align";

static const std::string CONFIG_PREFIX = "config";

static const std::string CONFIG_PREFIX_DOT = CONFIG_PREFIX + ".";

static const std::string EQUAL_SIGN = "=";

/**
 *  @brief Parse input string to parse input configuration
 * 
 *  @param text Input string for parsing (one line)
 *  @retval Configuration struct (config_t) with parsed values
 * 
 */
config_t getConfig(std::string text);

/** 
 *  @brief Parse sum cell and return value and its validity
 * 
 *  @param text Text for parsing in format SUM(FROM:TO)
 *  @param numbers Vector of numbers which can be summed
 *  @retval sum_t struct with the value, text width and valid information
 * 
 */
sum_t getSum(const std::string& text, std::vector<int> numbers);

cfg_values_t getDefaultCfgValues();

cfg_values_t setCfgValues(cfg_values_t allCfgValues, const config_t& cfgValue);

void printCfgValue(const std::string& type, const std::string& value);

void printConfigValues(const cfg_values_t& cfgValues);

#endif // __PARSE_HPP_