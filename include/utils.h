#pragma once

#include <utility>
#include <string>
#include <vector>
#include <string_view>

namespace uphold
{



//  holds the index of last char in input string to parse 
// and the padding value ('X' in spec)
using parseParameters = std::pair<size_t, int>;

// depending on input rules we *could* check for incorrect
// input. For example, if the string to pad size is > 10,000 
// this is a basic check
void validateInput(const std::string& input);


// used to verify that the test input files have same line count
void validateInput(const std::vector<std::string>& inputs, 
                   const std::vector<std::string>& expectedResults);



// search for the ',' in input string (searches from end, not front)
auto extractPaddingSeprator(const std::string& input);



// validates the input and calculates "parseParameters" above
auto extractParameters(const std::string& input) -> parseParameters;

// is paramater not value between 0 ... 9
bool isNonNumeric(unsigned char curr);

// is paramater between 0 ... 9 
bool isNumeric(unsigned char curr);


//where the real work is done. based on input and index will
// put the padded string result into ostringstream
void padNumbers(const std::string& input, 
                size_t& index, 
                char& curr, 
                int padding, 
                const std::string_view stringToParse, 
                std::ostringstream& oss);

// entry point for padding input string. Iterates over test string and
// pads via utility functions above as needed
std::string padInputString(const std::string& input);
}
