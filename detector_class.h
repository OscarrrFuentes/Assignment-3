// PHYS 30762 Programming in C++
// Assignment 3 Detector Class
// Oscar Fuentes Rebato - Last updated: 08/03/2024
// Practice with C++ classes and their interactions

#ifndef detector_class
#define detector_class

#include "particle_class.h"

// Beginning of detector class
class detector
{
private:
  std::string detector_type;
  bool status; // true/false => on/off
  int particle_count;

public:
  // Constructors:
  detector() = default;
  detector(std::string type):
  detector_type{type}, status{false}, particle_count{0}{};

  // Destructor
  ~detector(){std::cout<<"Destroying "<<detector_type<<std::endl;}

  // Getters
  std::string get_type(){return detector_type;}
  double get_particles(){return particle_count;}
  double get_status(){return status;}

  // Declare member functions, implemented in assignment_3.cpp
  void turn_on();
  void turn_off();
  void show_particles(); // This is essentially a print_data() function as it shows all the data members
  bool track_particle(particle*);
  void reset();
};

#endif // detector_class