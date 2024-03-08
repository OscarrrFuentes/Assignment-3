// PHYS 30762 Programming in C++
// Assignment 3 Particle Class
// Oscar Fuentes Rebato - Last updated: 08/03/2024
// Practice with C++ classes and their interactions

#ifndef particle_class
#define particle_class

#include "check_input.h"

// Beginning of particle class
class particle
{
private:
  std::string particle_name;
  double rest_mass;
  int charge;
  double velocity;
  double beta = velocity/light_speed;

public:
  // Constructors (with the option to add another argument to make it an anti-particle)
  particle() = default;
  particle(std::string name, double construct_velocity):
  particle_name{check_name(name, false)}, rest_mass{0.511}, charge{-1}, velocity{check_velocity(std::to_string(construct_velocity), false)}, beta{construct_velocity/light_speed}
  {
    // Initially assumes electron mass, if it is a different particle set to their respective masses
    if(name == "muon"){rest_mass = 106;}
    else if(name == "tau"){rest_mass = 1777;}
  }
  // Overload the parametrized constructor to allow for a bool which is true/false for anti-particle/particle
  particle(std::string name, double construct_velocity, bool anti):
  particle_name{name}, rest_mass{0.511}, charge{-1}, velocity{construct_velocity}, beta{construct_velocity/light_speed}
  {
    if(anti)
    {
      charge=1;
      particle_name="anti-"+name;
    }
    if(name == "muon"){rest_mass = 106;}
    else if(name == "tau"){rest_mass = 1777;}
  }
  // Destructor
  ~particle(){std::cout<<"Destroying "<<particle_name<<std::endl;}

  // Getter functions
  std::string get_name(){return particle_name;}
  double get_mass(){return rest_mass;}
  int get_charge(){return charge;}
  double get_velocity(){return velocity;}
  double get_beta(){return beta;}

  // Setter functions
  void set_name(std::string new_name, bool input_status){particle_name = check_name(new_name, input_status);}
  void set_mass(std::string new_mass, bool input_status){rest_mass = check_mass(new_mass, input_status);}
  void set_charge(std::string new_charge, bool input_status){charge=check_charge(new_charge, input_status);}
  void set_velocity(std::string new_velocity, bool input_status)
  {
    velocity = check_velocity(new_velocity, input_status);
    beta = velocity/light_speed;
  }

  // Declare member functions, implemented in assignment_3.cpp
  void print_data();
};

#endif //particle