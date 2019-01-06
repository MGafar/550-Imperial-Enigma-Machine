#include "reflector.h"

using namespace std;

Reflector::Reflector(int* config, int elements_count, const char* stream_name)
{
	configuration_elements_count = elements_count;
	configurations = config;
	verify_configurations_file(stream_name);
}

void Reflector::verify_configurations_file(const char* stream_name)
{
	if(configuration_elements_count % 2)
	{
		cerr << "Incorrect (odd) number of parameters in reflector file " << stream_name << endl;
		throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
	} 
	
	if (configuration_elements_count < 26)
	{
		cerr << "Insufficient number of mappings in reflector file: " << stream_name << endl;
		throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
	} 
	
	if (configuration_elements_count > 26)
	{
		cerr << "There are " << configuration_elements_count << "parameters in reflector file: " << stream_name << endl;
		cerr << endl << "The expected number is 13 pairs (26 parameters)";
		throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
	}
}

int Reflector::pass_signal(int input)
{
	for (int i = 0; i < configuration_elements_count; i++)
	{
		if(configurations[i] == input)
		{
			if (i==0 || (i % 2) == 0)
				return configurations[i+1];
			else
				return configurations[i-1];
		} 
	}
	return input;
}

