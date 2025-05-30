#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <vector>

#include "utils.h"

bool test(const std::string& input, const std::string& expected)
{
	try
	{
		std::string res = uphold::padInputString(input);
		if (res == expected)
		{
			return true;
		} 
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << "Invalid argument: passed to std::stoi: \"" << input<< "\"\n";
	} catch (const std::out_of_range& e)
	{
		std::cerr << "Out of range value: passed to std::stoi: " << input<< "\n";
	}
	catch (const std::logic_error& le)
	{
		std::cerr << le.what() << input << '\n';
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << input << '\n';
	}
	catch (...)
	{
		std::cerr << "Unknown exception caught\n" ;
	}

	return false;
}

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cerr << "Usage: " << argv[0] << " <input test file> <expected results file\n";
		return 1;
	}

	const std::string inputFileName = argv[1];
	std::ifstream inputFile(inputFileName);

	if (!inputFile)
	{
		std::cerr << "Error opening file: " << inputFileName << "\n";
		return 2;
	}
	std::vector<std::string> inputs;
	std::string input;
	while (getline(inputFile, input))
	{
		inputs.emplace_back(input);
	}

	inputFile.close();

	const std::string expectedResultsFileName = argv[2];
	std::vector<std::string> expectedResults;
	std::ifstream expectedResultsFile(expectedResultsFileName);
	while (getline(expectedResultsFile, input))
	{
		expectedResults.emplace_back(input);
	}

	uphold::validateInput(inputs, expectedResults);

	for (size_t i{0}; i<inputs.size(); ++i)
	{
		std::string result = (test(inputs[i], expectedResults[i]) ? "PASS" : "FAIL");
		std::cout << result << ": input: " << inputs[i] << ", output: " << expectedResults[i] << "\n";
	}

}
