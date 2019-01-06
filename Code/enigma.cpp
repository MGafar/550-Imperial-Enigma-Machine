#include "enigma.h"

using namespace std;

Enigma::Enigma(int argc, char** argv)
{
	arguments = argc;

	if(argc < 3 || argc == 4)
	{
		cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?" << endl;
		throw INSUFFICIENT_NUMBER_OF_PARAMETERS;
	}
		
	int* config = get_configurations(argv[1], IMPOSSIBLE_PLUGBOARD_CONFIGURATION, "in plugboard");
	myPlugboard = new Plugboard(config, configuration_elements_count, argv[1]);

	config = get_configurations(argv[2], INVALID_REFLECTOR_MAPPING, "in reflector");	
	myReflector = new Reflector(config, configuration_elements_count, argv[2]);

	if (argc >= 4)
	{
		int* rotors_start_pos = get_configurations((argv[argc-1]), 0, "in rotor positions");
	
		if(configuration_elements_count < argc-4)
		{
			for(int i = 0; i < ((argc-4)-configuration_elements_count); i++)
			{
				cerr << "No starting position for rotor " << i << " in rotor position file: " << (argv[argc-1]) << endl;
			}
			throw NO_ROTOR_STARTING_POSITION;
		}
		
		rotor = new Rotor *[argc-4];

		for(int i = 0; i < argc-4; i++)
		{
			config = get_configurations((argv[argc-2-i]), INVALID_ROTOR_MAPPING, "for mapping in rotor");
			rotor[i] = new Rotor(config, configuration_elements_count, rotors_start_pos[argc-5-i], (argv[argc-2-i]));
		}
	}
}

int Enigma::encrypt(int signal)
{
	signal = myPlugboard->pass_signal(signal);
	
	if (arguments > 3)
	{
		signal = rotor[0]->pass_signal_forward(signal, 1, 1);
		
		for(int i = 1; i < arguments-4; i++)
		{
			signal = rotor[i]->pass_signal_forward(signal, rotor[i-1]->rotor_notch_is_active(), rotor[i-1]->rotor_has_rotated());
		}
	}

	signal = myReflector->pass_signal(signal);

	if (arguments > 3)
	{
		for(int i = (arguments-5); i >= 0; i--)
		{
			signal = rotor[i]->pass_signal_backward(signal);
		}
	}

	signal = myPlugboard->pass_signal(signal);
	
	return signal;
}

char* Enigma::get_file_string(const char* my_stream)
{
	ifstream input_stream;
	input_stream.open(my_stream);

	if(input_stream.fail())
	{
		cerr << "Unable to open stream: " << my_stream << endl;
		throw ERROR_OPENING_CONFIGURATION_FILE;
	}

	file_string = new char [MAX_WORD_LENGTH];
	input_stream.getline(file_string, MAX_WORD_LENGTH);
	input_stream.close();
		
	return file_string;
}

int Enigma::find_elements_count(char* file_string)
{
	configuration_elements_count = 0;

	for(int i=0; file_string[i] != '\0'; i++)
	{
		if(file_string[i] == ' ' && file_string[i+1] != ' ' && file_string[i+1] != '\0')
			configuration_elements_count++;	
	}

	if(file_string[0] != ' ' && file_string[0] != '\0')
		configuration_elements_count++;
		
	return configuration_elements_count;
}

int* Enigma::get_configurations(const char* my_stream, int mapping_error, const char* message_tweak)
{
	file_string = get_file_string(my_stream);
	configuration_elements_count = find_elements_count(file_string);
	
	stringstream stream(file_string);
	int config;
	
	configurations = new int[configuration_elements_count];

	for(int i = 0; i < configuration_elements_count; i++)
	{
		stream >> config;
		
		if(stream.fail())
		{
			cerr << "Non-numeric character " << message_tweak << " file " << my_stream << endl;;
			throw NON_NUMERIC_CHARACTER;
		}
			
		if (config < 0 || config > 25)
		{
			cerr << "The number " << config << " found in " << my_stream << " is not a valid index" << endl;
			throw INVALID_INDEX;
		}
			
		configurations[i] = config;
		stringstream convert(file_string);
		
		for(int m = 0; m < i && i < 26; m++)
		{
			if((configurations[m] == configurations[i]) && m != i && mapping_error != 0)
			{
				cerr << "Invalid mapping of input " << i << " to output " << configurations[m];
				cerr << " (output " << configurations[m] << " is already mapped to from input ";
				cerr << m << ")" << endl;
				throw mapping_error;
			}
		}
	}
	return configurations;
}

Enigma::~Enigma()
{
	delete myPlugboard;
	delete myReflector;

	if (arguments > 3)
	{
		for(int i = 0; i < arguments-4; i++)
			delete rotor[i];

		delete [] rotor;
	}

	delete [] file_string;
	delete [] configurations;
	//cout << "Enigma Destruct"; //Used for verifying if the destructor is being implicitly called
}
