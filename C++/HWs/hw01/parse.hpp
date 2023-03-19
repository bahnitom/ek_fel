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
    int width;
    std::string align;
} cfg_values_t;

static const char *const MIN_TYPE = "min";

static const char *const MAX_TYPE = "max";

static const char *const WIDTH_TYPE = "width";

static const char *const ALIGN_TYPE = "align";

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
sum_t getSum(std::string text, std::vector<int> numbers);

cfg_values_t getDefaultCfgValues();

cfg_values_t setCfgValues(cfg_values_t allCfgValues, const config_t& cfgValue)

#endif // __PARSE_HPP_