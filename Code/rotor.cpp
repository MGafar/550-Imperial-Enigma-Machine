#include "rotor.h"

using namespace std;

Rotor::Rotor(int* config, int elements_count, int starting_position, const char* stream_name)
{
	configuration_elements_count = elements_count;
	configurations = config;
	verify_configurations_file(stream_name);
	relative_position = 0;
	setup_notch_positions();
	setup_starting_position(starting_position);
}

void Rotor::setup_notch_positions()
{
	notch_positions = new int [configuration_elements_count-26];
	
	for (int i = 0; i < configuration_elements_count-26; i++)
	{
		notch_positions[i] = configurations[configurations[configuration_elements_count-1-i]];
	}
}

void Rotor::verify_configurations_file(const char* stream_name)
{
	if(configuration_elements_count <= 25)
	{
		cerr << "Not all inputs mapped in rotor file: " << stream_name << endl;
		throw INVALID_ROTOR_MAPPING;
	}	
}


int Rotor::pass_signal_forward(int input, bool previous_rotor_notch_is_active, bool previous_rotor_has_rotated)
{
	if(previous_rotor_notch_is_active && previous_rotor_has_rotated)
	{
		rotate();
		rotation_state = 1;
	}else
		rotation_state = 0;	

	int temp;

	if(input+relative_position > 25)
		temp = input+relative_position-26;
	else
		temp = input+relative_position;
	
	temp = configurations[temp];

	if(temp-relative_position >= 0)
		return temp-relative_position;

	return temp-relative_position+26;
}

int Rotor::pass_signal_backward(int input)
{
	int temp;

	if(input+relative_position > 25)
		temp = input+relative_position-26;
	else
		temp = input+relative_position;

	for (int i = 0; i < 26; i++)
	{
		if(configurations[i]==temp)
		{
			temp = i;
			break;
		}
	}

	if(temp-relative_position >= 0)
		return temp-relative_position;

	return temp-relative_position+26;
}

void Rotor::rotate()
{	
	if(relative_position < 25)
		relative_position++;
	else
		relative_position = 0;
	
	rotor_notch_state = verify_rotor_notch_status();
}

bool Rotor::verify_rotor_notch_status()
{
	for(int i = 0 ; i < configuration_elements_count-26; i++)
	{
		if (configurations[relative_position] == notch_positions[i])	
			return 1;
	}
	return 0;
}

void Rotor::setup_starting_position(int start_pos)
{
	for(int i = 0; i < start_pos; i++)
	{
		rotate();
	}
}

bool Rotor::rotor_notch_is_active()
{
	return rotor_notch_state;
}

bool Rotor::rotor_has_rotated()
{
	return rotation_state;
}

Rotor::~Rotor()
{
	//cout << "Rotor Destruct"; //Used for verifying if the destructor is being implicitly called
	delete [] notch_positions;	
}
