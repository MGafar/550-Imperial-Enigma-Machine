#ifndef PLUGBOARD_H

#include <iostream>
#include "errors.h"

class Plugboard
{
	private:
	/*variables*/
	int configuration_elements_count;
	int* configurations;

	/*Helper function used in the constructor to verify there is a correct number of parameters*/
	void verify_configurations_file(const char* stream_name);

	public:
	/*Constructor which takes in an array of configurations, the number of elements in the array and
	  the stream which the configurations were collected from*/
	Plugboard(int* config, int elements_count, const char* stream_name);

	/*Function used to return an output from its corresponding input pair*/
	int pass_signal(int input);
};

#define PLUGBOARD_H
#endif
