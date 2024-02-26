// PHYS 30762 Programming in C++
// Assignment 3
// Practice with C++ classes and their interactions

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include "check_input.h"

using std::string;

const double light_speed{2.99792458e8};
// Beginning of particle class
class particle
{
private:
  string particle_name;
  double rest_mass;
  int charge;
  double velocity;
  double beta = velocity/light_speed;
  //...other data members (see slides on BB)

public:
  // Constructors
  // Here you need a default constructor, and a parameterised constructor
  particle() = default;
  particle(string name, double mass, int construct_charge, double construct_velocity):
  particle_name{name}, rest_mass{mass}, charge{construct_charge}, velocity{construct_velocity}, beta{construct_velocity/light_speed}
  {}
  // Destructor
  ~particle(){std::cout<<"Destroying "<<particle_name<<std::endl;}

  // Getter functions (accessors) to
  string get_name(){return particle_name;}
  double get_mass(){return rest_mass;}
  int get_charge(){return charge;}
  double get_velocity(){return velocity;}
  double get_beta(){return beta;}
  // This should include function returning beta value 

  // Setter functions, to change value of data members
  void set_name(std::string new_name) {if(check_string(new_name)){particle_name = new_name;}}
  void set_mass(std::string new_mass) {if(check_double(new_mass)){rest_mass = stod(new_mass);}}
  void set_charge(std::string new_charge) {if(check_int(new_charge)){charge=stoi(new_charge);}}
  void set_velocity(std::string new_velocity)
  {
    if (check_double(new_velocity))
    {
      velocity = stod(new_velocity);
      beta = stod(new_velocity)/light_speed;
    }
  }
  // Make sure you check input validity before changing something
  // Hint: you can use the input checking functions you used in assignment 1

  // Function to print info about a particle
  void print_data();
};

// Implementation of print_data function goes here
void particle::print_data()
{
  std::cout.precision(3);
  std::cout<<"Particle: "<<particle_name<<"\nRest mass: "<<rest_mass<<" MeV\nCharge: "<<charge<<
  " C\nVelocity: "<<velocity<<" m/s\nBeta = "<<beta<<"\n"<<std::endl;
}
// End of particle class and associated member functions

// Beginning of detector class

// Functionalities needed, in addition to constructor/destructor/setters/getters (see slides on BB):
// - write a function that takes a particle 
//   and returns a bool and a print-out on whether this type of detector detected the particle
//   depending on the detector/particle combination (see slides on BB)
// - have data members that keep track of how many particles were detected by this particular detector, 
//   and of which type
// - write a function (accessor) that prints how many particles passed through this detector

// End of detector class

// Main program
int main()
{
  particle electron("electron", 0.511, -1, 2.55e8);
  electron.print_data();
  std::string new_mass;
  std::cout<<"Input new mass";
  std::cin>>new_mass;
  electron.set_mass(new_mass);
  electron.print_data();
  // Create the following particles: 
  // two electrons, four muons, three taus, one antielectron, one antimuon, one antitau 
  // Use the parameterised constructor

  // Print out the data from all the particles (put them in a vector)

  // Create the following detectors: a tracker, a calorimeter, a muon chamber

  // Pass the list of particles into each detector

  // Print a summary of how many particles were detected

  return 0;
}