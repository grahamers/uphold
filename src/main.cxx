#include <iostream>
#include <exception>
#include <stdexcept> 
//#include <sstream>
#include <fstream>

#include "utils.h"

using namespace std;


// Takes an input file with test strings in format  defined in spec. The std::cout is there just
// for readability so results are immediately visible
int main(int argc, char** argv)
{
	if (argc < 2) 
	{
		std::cerr << "Usage: " << argv[0] << " <input test file (tests/tests.txt) > \n";
		return 1;
	}

	const std::string filename = argv[1];
	std::ifstream inputFile(filename);

	if (!inputFile) 
	{
		std::cerr << "Error opening file: " << filename << "\n";
		return 2;
	}

	std::string inputLine;
	while (getline(inputFile, inputLine))
	{
		try
		{
			std::string res = uphold::padInputString(inputLine);
			cout << res << endl;
		}
		catch (const std::invalid_argument& e) 
		{
			std::cerr << "Invalid argument: passed to std::stoi: \"" << inputLine << "\"\n";
		} catch (const std::out_of_range& e) 
		{
			std::cerr << "Out of range value: passed to std::stoi: " << inputLine << "\n";
		}
		catch (const logic_error& le)
		{
			std::cerr << le.what() << inputLine << '\n'; 
		}
		catch (const exception& ex)
		{
			std::cerr << ex.what() << inputLine << '\n'; 
		}
		catch (...)
		{
			std::cerr << "Unknown exception caught, program wll exit \n" ;
			return 3;
		}
	}
	inputFile.close(); // optional, happens automatically at end of scope

	return 0;
}

