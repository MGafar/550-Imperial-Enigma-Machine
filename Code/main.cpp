#include <iostream>
#include "enigma.h"
#include "errors.h"

using namespace std;

int main(int argc, char** argv) 
{
	
	char input;
	char output;
	
	try
	{
		Enigma myEnigma(argc, argv);		
	
		while (cin >> ws >> input)
		{
			if(input < 'A' || input > 'Z')
				{
					cerr << input << " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
					throw INVALID_INPUT_CHARACTER;
				}
		
			input = input - 'A';
			output = (myEnigma.encrypt(input) + 'A');
			cout << output;
		}

	}catch (int error_code)
	{
		return error_code;
	}

	return NO_ERROR;
}
