#ifndef ENIGMA_H

#include <fstream>
#include <sstream>
#include <cstring>
#include "errors.h"
#include "rotor.h"
#include "plugboard.h"
#include "reflector.h"

const int MAX_WORD_LENGTH = 256;

class Enigma
{
	private:
	/*variables*/
	int arguments;
	int* configurations;
	char* file_string;
	int configuration_elements_count;

	/*Components*/
	Plugboard* myPlugboard;
	Reflector* myReflector;
	Rotor** rotor;
	
	/*Function used for getting integer tokens from an input string and for each new token it collects
	  its index will be verified, the tokens will be verified to be numeric characters, and if the token
	  is repeated within the first 26 tokens then a corresponding error will be thrown*/
	int* get_configurations(const char* my_stream, int mapping_error, const char* message_tweak);
	
	/*Helper function used for getting a string from a stream*/
	char* get_file_string(const char* my_stream);

	/*Helper function used for counting tokens in a string. The delimiter used was space.*/
	int find_elements_count(char* file_string);
	
	public:
	/*Constructor used to setup an Enigma machine by instantiating a reflector, a plugboard, and an array
	  of rotors (if there are any)*/
	Enigma(int argc, char** argv);
	
	/*Encrypt function which takes in an integer signal and propagates through the enigma machine to encrypt it*/
	int encrypt(int signal);
	
	/*Destructor used for deleting the dynamically allocated objects and arrays (includes the reflector, the plugboard,
	  and an array of rotors (if there are any)*/
	~Enigma();
};

#define ENIGMA_H
#endif
