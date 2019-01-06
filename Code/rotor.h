#ifndef ROTOR_H

#include <iostream>
#include "errors.h"

class Rotor
{
	private:
	/* Variables and pointers */
	int configuration_elements_count;
	int* configurations;
	int* notch_positions;
	bool rotor_notch_state;
	bool rotation_state;
	int relative_position;

	/*Helper function used for veryfying the notch of a rotor has been triggered */
	bool verify_rotor_notch_status();

	/*Helper function used in the constructor to setup the rotors to a specified starting position */
	void setup_starting_position(int start_pos);
	
	/*Helper function used for keeping track of the relative position of the rotor*/
	void rotate();
	
	/*Helper function used in constructor to verify the correct number of parameter are present */
	void verify_configurations_file(const char* stream_name);

	/*Helper function used in constructor to store the value of the notch positions*/
	void setup_notch_positions();

	public:
	/*Constructor used to setup a rotor by verifying the config files, setting up the array of notches
	  and assigning the relative position*/
	Rotor(int* config, int elements_count, int starting_position, const char* stream_name);

	/*Function used to output a signal when the rotor is mapped forwards. The function uses parameters
	  from preceeding rotors to identify if it should rotate*/
	int pass_signal_forward(int input, bool previous_rotor_notch_is_active, bool previous_rotor_has_rotated);

	/*Function used to output a signal when the rotor is mapped backwards.*/
	int pass_signal_backward(int input);
	
	/*Function used for verifying if the rotor has rotated into a position where the notch activates
	  the next rotor's rotation.*/
	bool rotor_notch_is_active();

	/*Getter function used to give the user access to verify if the rotor has rotated*/
	bool rotor_has_rotated();

	/*Destructor*/
	~Rotor();
};

#define ROTOR_H
#endif
