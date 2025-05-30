#include "utils.h"
#include <stdexcept>
#include <sstream>  

#include <iostream>  

namespace uphold
{



   void validateInput(const std::string& input)
   {
      if (!input.size())
      {
         throw std::logic_error("empty input string");
      }
   }

   void validateInput(const std::vector<std::string>& inputs, 
         const std::vector<std::string>& expectedResults)
   {
      if (inputs.size() != expectedResults.size())
      {
         throw std::logic_error("inputs file must be same size as expected results, check input files");
      }
   }

   auto extractPaddingSeprator(const std::string& input)
   {
      auto separatorPos = input.rfind(",");

      if (std::string::npos == separatorPos)
      {
         throw std::logic_error("Invalid input: \"" + input + "\"");
      }

      return separatorPos;
   }

   auto extractParameters(const std::string& input) -> parseParameters
   {
      validateInput(input);
      auto separatorPos = extractPaddingSeprator(input);
      auto paddingString = std::string(input.data() + separatorPos + 1, input.size()); 
      auto padding = std::stoi(paddingString);
      return {separatorPos  , padding};
   }

   bool isNonNumeric(unsigned char curr)
   {
      if (std::isalpha(curr) || std::ispunct(curr) || std::isspace(curr))
      {
         return true;
      }

      return false;
   }

   bool isNumeric(unsigned char curr)
   {
      return std::isdigit(curr);
   }

   /* 
   when iterating over the input string, this function is called to handle number padding. The
   start index of the number is stored and used to construct a string that will be appended 
   AFTER the calculated padding.

   paddingEnd is used to determine how many consecutive numbers are in string.
   based on how many consecutive numbers are present, we use paddingEnd to obtain the
   number of consecutive numbers are present. We then create a "paddingString" which has
   the correct padding.
   the start and stopIndex variables hold where the numbers are. The final ostringstream
   has the paddingString streamed into it, follwed by the "numbers" string.

   @Duncan: If I had more time, Id come up with a smarter alternative. I have a feeling there
   is a C++ addition to stl that would handle this in 5 lines but I dont have time to check it
   out and I'm not using chatGPT to tell me if there is one. Regex could possibly do it too
   but they are notoriously difficult to debug sometimes.
   */

   void padNumbers(const std::string& input, 
         size_t& index,  
         char& curr, 
         int padding, 
         const std::string_view stringToParse, 
         std::ostringstream& oss)
   {
      size_t start{index};
      auto numbersStart {index};
      auto paddingEnd{numbersStart};
      auto stopIndex{0};

      while ( index < stringToParse.size() && isNumeric(static_cast<unsigned char>(curr)))
      {
         paddingEnd+=1;
         curr = stringToParse[index+=1];
      }

      stopIndex = index;
      index = index - 1;
      int consecutiveNumbers = paddingEnd - numbersStart;

      std::string paddingString("");
      if (padding > consecutiveNumbers)
      {
         paddingString.resize(padding - consecutiveNumbers, '0');
      }
      oss << paddingString;
      std::string numbers = input.substr(start  , stopIndex  - start);
      oss << numbers;
   }


   std::string padInputString(const std::string& input)
   {
      parseParameters params = extractParameters(input);
      auto parseStringEndPos {params.first};
      auto padding {params.second};
      std::string paddingString(params.second, '0');
      std::string_view stringToParse(input.data(), parseStringEndPos);

      std::ostringstream oss;

      for (size_t index{0}; index < stringToParse.size(); ++index)
      {
         char curr = input[index];
         if ( isNumeric(curr))
         {
            padNumbers(input, index, curr, padding, stringToParse, oss);
         }
         else if (isNonNumeric(curr)) 
         {
            oss << curr;
         }
         else
         {
            throw std::logic_error("invalid characters found in input: " + input );
         }
      }
      return oss.str();
   }


}
