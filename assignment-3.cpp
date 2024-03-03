// PHYS 30762 Programming in C++
// Assignment 3
// Practice with C++ classes and their interactions

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include "check_input.h"

using std::string;

// Beginning of particle class
class particle
{
private:
  string particle_name;
  double rest_mass;
  int charge;
  double velocity;
  double beta = velocity/light_speed;

public:
  // Constructors
  particle() = default;
  particle(string name, double mass, int construct_charge, double construct_velocity):
  particle_name{name}, rest_mass{mass}, charge{construct_charge}, velocity{construct_velocity}, beta{construct_velocity/light_speed}
  {}
  particle(string name, double mass, int construct_charge, double construct_velocity, bool anti):
  particle_name{name}, rest_mass{mass}, charge{construct_charge}, velocity{construct_velocity}, beta{construct_velocity/light_speed}
  {if(anti){charge=-construct_charge; particle_name="anti-"+name;}}
  // Destructor
  ~particle(){std::cout<<"Destroying "<<particle_name<<std::endl;}

  // Getter functions
  string get_name(){return particle_name;}
  double get_mass(){return rest_mass;}
  int get_charge(){return charge;}
  double get_velocity(){return velocity;}
  double get_beta(){return beta;}

  // Setter functions
  void set_name(std::string new_name){particle_name = check_name(new_name);}
  void set_mass(std::string new_mass){rest_mass = check_mass(new_mass);}
  void set_charge(std::string new_charge){charge=check_charge(new_charge);}
  void set_velocity(std::string new_velocity)
  {
    velocity = check_velocity(new_velocity);
    beta = velocity/light_speed;
  }

  void print_data()
  {
    std::cout.precision(3);
    std::cout<<"Particle: "<<particle_name<<"\nRest mass: "<<rest_mass<<" MeV\nCharge: "<<charge<<
    " C\nVelocity: "<<velocity<<" m/s\nBeta = "<<beta<<"\n"<<std::endl;
  }
};
// End of particle class and associated member functions

// Beginning of detector class
class detector
{
private:
  std::string detector_type;
  int particle_count;
  int anti_particle_count;

public:
  // Constructors:
  detector() = default;
  detector(std::string type):
  detector_type{type}, particle_count{0}, anti_particle_count{0}{};

  // Destructor
  ~detector(){std::cout<<"Destroying "<<detector_type<<std::endl;}

  // Getters
  string get_type(){return detector_type;}

  void show_particles()
  {
    if(detector_type == "tracker"){std::cout<<particle_count<<" electrons and "<<anti_particle_count<<" anti-electrons have passed through this tracker"<<std::endl;}
    else if(detector_type == "muon chamber"){std::cout<<particle_count<<" muons and "<<anti_particle_count<<" anti-muons have passed through this muon chamber"<<std::endl;}
    else if(detector_type == "calorimeter"){std::cout<<particle_count<<" tau particles and "<<anti_particle_count<<" anti-tau particles have passed through this calorimeter"<<std::endl;}
    else{std::cout<<"DETECTOR_TYPE ERROR"<<std::endl;}
  }
  bool track_particle(particle lepton)
  {
    if(detector_type == "tracker")
    {
      if(lepton.get_name() == "electron")
      {
        particle_count++;
        std::cout<<"Electron detected"<<std::endl;
        return true;
      }
      else if(lepton.get_name() == "anti-electron")
      {
        anti_particle_count++;
        std::cout<<"Anti-electron detected"<<std::endl;
        return true;
      }
      return false;
    }
    else if(detector_type == "muon chamber")
    {
      if(lepton.get_name() == "muon")
      {
        particle_count++;
        std::cout<<"Muon detected"<<std::endl;
        return true;
      }
      else if(lepton.get_name() == "anti-muon")
      {
        anti_particle_count++;
        std::cout<<"Anti-muon detected"<<std::endl;
        return true;
      }
      return false;
    }
    else if(detector_type == "calorimeter")
    {
      if(lepton.get_name() == "tau")
      {
        particle_count++;
        std::cout<<"Tau detected"<<std::endl;
        return true;
      }
      else if(lepton.get_name() == "anti-tau")
      {
        anti_particle_count++;
        std::cout<<"Anti-tau detected"<<std::endl;
        return true;
      }
      return false;
    }
    std::cout<<"DETECTER ERROR"<<std::endl;
    return false;
  }
};
// End of detector class

// Main program
int main()
{
  std::vector<particle> particles;
  particles.emplace_back("electron", 0.511, -1, 2.55e8);
  particles.emplace_back("electron", 0.511, -1, 1.01e8);
  particles.emplace_back("muon", 105.7, -1, 500);
  particles.emplace_back("muon", 105.7, -1, 2.98e8);
  particles.emplace_back("muon", 105.7, -1, 3.06e6);
  particles.emplace_back("muon", 105.7, -1, 100);
  particles.emplace_back("tau", 1777, -1, 2.5e8);
  particles.emplace_back("tau", 1777, -1, 2.2e8);
  particles.emplace_back("tau", 1777, -1, 1.5e8);
  particles.emplace_back("electron", 0.511, -1, 2.55e8, true);
  particles.emplace_back("muon", 105.7, -1, 2.55e8, true);
  particles.emplace_back("tau", 1777, -1, 2.55e8, true);

  for(int i=0;i<particles.size();i++)
  {
    particles[i].print_data();
  }

  // Create the following particles: 
  // two electrons, four muons, three taus, one antielectron, one antimuon, one antitau 
  // Use the parameterised constructor

  // Print out the data from all the particles (put them in a vector)
  detector tracker{"tracker"};
  detector muon_chamber{"muon chamber"};
  detector calorimeter{"calorimeter"};

  tracker.show_particles();
  muon_chamber.show_particles();
  calorimeter.show_particles();

  std::cout<<"\nPassing particles through detectors...\n"<<std::endl;

  for(auto& single_particle:particles)
  {
    tracker.track_particle(single_particle);
    muon_chamber.track_particle(single_particle);
    calorimeter.track_particle(single_particle);
  }
  std::cout<<"\n";
  tracker.show_particles();
  muon_chamber.show_particles();
  calorimeter.show_particles();
  std::cout<<"\n";
  // Create the following detectors: a tracker, a calorimeter, a muon chamber

  // Pass the list of particles into each detector

  // Print a summary of how many particles were detected

  return 0;
}