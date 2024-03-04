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
  particle(std::string name, double mass, int construct_charge, double construct_velocity):
  particle_name{name}, rest_mass{mass}, charge{construct_charge}, velocity{construct_velocity}, beta{construct_velocity/light_speed}
  {}
  particle(std::string name, double mass, int construct_charge, double construct_velocity, bool anti):
  particle_name{name}, rest_mass{mass}, charge{construct_charge}, velocity{construct_velocity}, beta{construct_velocity/light_speed}
  {if(anti){charge=-construct_charge; particle_name="anti-"+name;}}
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

  void print_data();
};
// End of particle class and associated member functions

#endif //particle