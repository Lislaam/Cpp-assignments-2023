/* PHYS30762 - Assignment 1
This code takes string input, checks for validity and returns the electron transition energy in
the chosen units. The calculation then re-runs, accepting new input, or terminates, depending on
user choice.

Author: Labeebah Islaam 10453447
Date: 15/02/2022 */

#include<iostream>
#include<iomanip>
#include<regex>

double photon_energy(int atomic_num, int initial_quant_num, int final_quant_num, bool units_are_ev) {
	double ans = 13.6 * pow(atomic_num, 2) * (1 / pow(final_quant_num, 2) - 1 /
		pow(initial_quant_num, 2));

	if (units_are_ev == true) {
		return ans;
	}
	else {
		return ans * 1.60218e-19;
	}
}

int check_int_input(std::string input, std::string var_name="value") { 
	// Check for and return positive integer input:
	bool input_ok = false; // Only exit function when input satisfies conditions 
	int num{}; 

	while (input_ok == false) {
		if (std::regex_match(input, std::regex("[^0-9]")) == false) {
			num = std::stoi(input);
			if (num < 0) {
				std::cout << "Input must be positive integer. Re-enter " << var_name << ": ";
				std::cin >> input;
			}
			else {
				input_ok = true;
			}
		}
		else {
			std::cout << "Input must be positive integer. Re-enter " << var_name << ": ";
			std::cin >> input;
		}
	}
	return num;
}

bool check_unit_ev(std::string unit) { 
	// Return true for 'ev', false for 'j', otherwise reprompt for input
	bool input_ok = false;
	bool unit_is_ev{};

	while (input_ok == false) {
		if (std::regex_match(unit, std::regex("^(e|E|ev|eV)$")) == true) {
			unit_is_ev = true;
			input_ok = true;
		}
		else if (std::regex_match(unit, std::regex("^(j|J)$")) == true) {
			unit_is_ev = false;
			input_ok = true;
		}
		else {
			std::cout << "Input must be 'ev' or 'j'. Re-enter units: ";
			std::cin >> unit;
		}
	}
	return unit_is_ev;
}

bool check_repeat(std::string input) {
	// Return true for 'ev', false for 'j', otherwise reprompt for input
	bool input_ok = false;
	bool repeat{};

	while (input_ok == false) {
		if (std::regex_match(input, std::regex("^(y|Y|yes)$")) == true) {
			repeat = true;
			input_ok = true;
		}
		else if (std::regex_match(input, std::regex("^(n|N|no)$")) == true) {
			repeat = false;
			input_ok = true;
		}
		else {
			std::cout << "Invalid input. Repeat calculation? (y/n): ";
			std::cin >> input;
		}
	}
	return repeat;
}

int main()
{
	bool repeat_calc{ true }; // Repeats calculation until terminated by user
	std::string repeat_calc_str;

	while (repeat_calc == true) {
		std::string atomic_str, initial_quant_str, final_quant_str, unit_str; // Vars to hold cin input
		int atomic_num{}, initial_quant_num{}, final_quant_num{};
		bool unit_is_ev;

		std::cout << "Enter the atomic number (integer): ";
		std::cin >> atomic_str;
		atomic_num = check_int_input(atomic_str, "atomic number");

		std::cout << "Enter the inital quantum number (integer): ";
		std::cin >> initial_quant_str;
		initial_quant_num = check_int_input(initial_quant_str, "initial quantum number");
		while (initial_quant_num == 0) { // Special case of ground state electron. No transition allowed
			std::cout << "Error, ground state. Require initial quantum number > 0." << std::endl;
			std::cout << "Re-enter initial quantum number: ";
			std::cin >> initial_quant_str;
			initial_quant_num = check_int_input(initial_quant_str, "initial quantum number");
		}

		std::cout << "Enter the final quantum number (integer): ";
		std::cin >> final_quant_str;
		final_quant_num = check_int_input(final_quant_str, "final quantum number");
		while (final_quant_num >= initial_quant_num) { // Electron state must decrease to get photon
			std::cout << "Error, require final quantum number < initial quantum number." << std::endl;
			std::cout << "Re-enter final quantum number: ";
			std::cin >> final_quant_str;
			final_quant_num = check_int_input(final_quant_str, "final quantum number");
		}

		std::cout << "Enter your desired units ('ev' or 'j'): ";
		std::cin >> unit_str;
		unit_is_ev = check_unit_ev(unit_str);

		std::cout << "The photon energy of this electron transition is " << std::setprecision(3) <<
			photon_energy(atomic_num, initial_quant_num, final_quant_num, unit_is_ev) << " ";
		if (unit_is_ev == true) {
			std::cout << "eV" << std::endl;
		}
		else {
			std::cout << "J" << std::endl;
		}

		std::cout << "Do another calculation? (y/n): ";
		std::cin >> repeat_calc_str;
		repeat_calc = check_repeat(repeat_calc_str);
	}

}
