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
  int anti_particle_count;

public:
  // Constructors:
  detector() = default;
  detector(std::string type):
  detector_type{type}, status{false}, particle_count{0}, anti_particle_count{0}{};

  // Destructor
  ~detector(){std::cout<<"Destroying "<<detector_type<<std::endl;}

  // Getters
  std::string get_type(){return detector_type;}

  // Declaring member functions
  void turn_on();
  void turn_off();
  void show_particles();
  bool track_particle(particle*);
  void reset();
};

#endif // detector_class