#ifndef REFLECTOR_H

#include <iostream>
#include "errors.h"

class Reflector
{
	private:
	/*Variables*/
	int configuration_elements_count;
	int* configurations;

	/*Helper function used in constructor to verify the number of parameters in "configurations" array*/
	void verify_configurations_file(const char* stream_name);

	public:
	/*Constructor*/
	Reflector(int* config, int elements_count, const char* stream_name);

	/*Function used to return an output from its corresponding input pair*/
	int pass_signal(int input);
};

#define REFLECTOR_H
#endif
