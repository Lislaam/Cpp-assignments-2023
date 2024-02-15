// 10453447_assignment_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<vector>
#include <algorithm>

const double SOLAR_MASS = 1.989e30;
const std::vector<std::string> allowed_hubble{"E0", "E1", "E2", "E3", "E4", "E5", "E6", "E7", "S0", "Sa", "Sb",
                                                "Sc", "SBa", "SBb", "SCc", "Irr"};

class Galaxy {
private:
    std::string hubble_type;
    double redshift{};
    double mass_total{};
    double mass_stellar_frac{};
    std::vector<Galaxy> satellites{};

public:
    Galaxy() = default; // Default (0) constructor
    Galaxy(std::string in_hubble_type, double in_redshift, double in_mass_total, double in_mass_stellar_frac) :
        hubble_type{in_hubble_type}, redshift{in_redshift}, mass_total{in_mass_total}, // Parameterised constructor
        mass_stellar_frac{ in_mass_stellar_frac } { }
    ~Galaxy() {} // Destructor
   
    // Getters and Setters for every variable:
    void set_hubble_type(const std::string in_hubble_type) { hubble_type = in_hubble_type; }
    void set_redshift(const double in_redshift) { redshift = in_redshift; }
    void set_mass_total(const double in_mass_total) { mass_total = in_mass_total; }
    void set_mass_stellar_frac(const double in_mass_stellar_frac) { mass_stellar_frac = in_mass_stellar_frac; }

    std::string get_hubble_type() const { return hubble_type; }
    double get_redshift() const { return redshift; }
    double get_mass_total() const { return mass_total; }
    double get_mass_stellar_frac() const { return mass_stellar_frac; }

    // Member functions:
    void print_parameters() const; // Declaring a function in the scope

    double stellar_mass() const {
        std::cout << "The stellar mass of this galaxy is " << mass_stellar_frac * mass_total * SOLAR_MASS;
        std::cout << " kg" << "\n" << std::endl;
        return mass_stellar_frac * mass_total * SOLAR_MASS;
    }

    void add_satellite(Galaxy satellite) { // Not const; function must change a class variable.
        satellites.push_back(satellite);
    }

    void check_input() { // This function is allowed to change class parameters
        if (std::find(allowed_hubble.begin(), allowed_hubble.end(), hubble_type) != allowed_hubble.end() == false) {
            std::cout << "Invalid Hubble type. Use E0 to E7, S0, Sa, Sb, Sc, SBa, SBb, SBc or Irr. ";
            std::cout << "Setting Hubble type to SBc." << std::endl;
            hubble_type = "SBc";
        }
        if ((0 < redshift || redshift > 10)) {
            std::cout << "Redshift must be double in range [0, 10]. ";
            std::cout << "Setting redshift to 0." << std::endl;
            redshift = 0;
        }
        if (10e7 < mass_total || mass_total > 10e12) {
            std::cout << "Total mass must be in range [10^7, 10^12] solar masses. ";
            std::cout << "Setting total mass to 1.2e9" << std::endl;
            mass_total = 1.2e9;
        }
        if ((0 < mass_stellar_frac || mass_stellar_frac > 0.05)) {
            std::cout << "Stellar mass fraction must be in range [0, 0.05]. ";
            std::cout << "Setting stellar mass fraction to 0.03" << std::endl;
            mass_stellar_frac = 0.03;
        }
    }
};

void Galaxy::print_parameters() const { // Defining the function out of the scope
    std::cout << "\nGalaxy parameters -\n" << "Hubble type: " << hubble_type << "\nRedshift: " << redshift;
    std::cout << "\nTotal Mass: " << mass_total * SOLAR_MASS << " kg" << "\nStellar Mass Fraction: ";
    std::cout << mass_stellar_frac << std::endl;

    // Satellite information
    std::cout << "There are " << satellites.size() << " satellites." << std::endl;
    if (satellites.size() != 0) {
        std::cout << "\nSatellite parameters -\n" << "Hubble type: " << hubble_type << "\nRedshift: " << redshift;
        std::cout << "\nTotal Mass: " << mass_total << " kg" << "\nStellar Mass Fraction: " << mass_stellar_frac << std::endl;
    }
}


int main() {
    std::vector<Galaxy> universe;

    universe.push_back(Galaxy()); // Adding a default galaxy
    universe.push_back(Galaxy({"Bad", 0.02, 234, 33})); // Adding a galaxy with bad parameters
    universe.push_back(Galaxy({"E2", 5, 10e5, 0.01})); // A good galaxy. I will add a satellite here.

    for (auto iterate = std::begin(universe); iterate != std::end(universe); iterate++) {
        iterate -> check_input();
        iterate -> print_parameters();
        iterate -> stellar_mass();
    }

    universe[2].add_satellite({"E2", 0, 10e6, 0.03}); // Adding satellite to existing galaxy
    universe[2].print_parameters(); // Reprinting the galaxy to show the new satellite


    return 0;
}
