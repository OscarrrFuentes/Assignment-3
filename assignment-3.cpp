// PHYS 30762 Programming in C++
// Assignment 3
// Practice with C++ classes and their interactions

#include "detector_class.h"

void particle::print_data()
  {
    std::cout.precision(3);
    std::cout<<"Particle: "<<particle_name<<"\nRest mass: "<<rest_mass<<" MeV\nCharge: "<<charge<<
    " C\nVelocity: "<<velocity<<" m/s\nBeta = "<<beta<<"\n"<<std::endl;
  }

void detector::turn_on()
{
  if(status){std::cout<<"This "<<detector_type<<" is already on"<<std::endl;}
  else{status = true;}
}

void detector::turn_off()
{
  if(!status){std::cout<<"This "<<detector_type<<" is already off"<<std::endl;}
  else{status = false;}
}

void detector::show_particles()
{
  if(!status){std::cout<<"This "<<detector_type<<" is off"<<std::endl;}
  else if(detector_type == "tracker"){std::cout<<particle_count<<" electrons have passed through this tracker"<<std::endl;}
  else if(detector_type == "muon chamber"){std::cout<<particle_count<<" muons have passed through this muon chamber"<<std::endl;}
  else if(detector_type == "calorimeter"){std::cout<<particle_count<<" electrons or muons have passed through this calorimeter"<<std::endl;}
  else{std::cout<<"DETECTOR_TYPE ERROR"<<std::endl;}
}

bool detector::track_particle(particle lepton)
{
  if(!status)
  {
    std::cout<<"This "<<detector_type<<" is off, particle not tracked"<<std::endl;
    return false;
  }
  if(detector_type == "tracker" && (lepton.get_name() == "electron" || lepton.get_name() == "anti-electron"))
  {
    particle_count++;
    std::cout<<"Electron detected"<<std::endl;
    return true;
  }
  else if(detector_type == "muon chamber" && (lepton.get_name() == "muon" || lepton.get_name() == "anti-muon"))
  {
    particle_count++;
    std::cout<<"Muon detected"<<std::endl;
    return true;
  }
  else if(detector_type == "calorimeter" && (lepton.get_name() == "electron" || lepton.get_name() == "anti-electron" || lepton.get_name() == "muon" || lepton.get_name() == "anti-muon"))
  {
    particle_count++;
    std::cout<<"Electron or muon detected"<<std::endl;
    return true;
  }
  return false;
}

void detector::reset()
{
  if(!status){std::cout<<"This "<<detector_type<<" is off"<<std::endl;}
  else if(particle_count>0){particle_count = 0;}
  else{std::cout<<"The count is already at 0"<<std::endl;}
}

//Main Program
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

  // Print out the data from all the particles (put them in a vector)
  for(int i=0;i<particles.size();i++)
  {
    particles[i].print_data();
  }

  // Create the following detectors: a tracker, a calorimeter, a muon chamber
  detector tracker{"tracker"};
  detector muon_chamber{"muon chamber"};
  detector calorimeter{"calorimeter"};

  tracker.show_particles();
  muon_chamber.show_particles();
  calorimeter.show_particles();

  // Pass the list of particles into each detector
  std::cout<<"\nPassing particles through detectors...\n"<<std::endl;
  tracker.turn_on();
  muon_chamber.turn_on();
  calorimeter.turn_on();
  for(auto& single_particle:particles)
  {
    tracker.track_particle(single_particle);
  }
  for(auto& single_particle:particles)
  {
    muon_chamber.track_particle(single_particle);
  }
  for(auto& single_particle:particles)
  {
    calorimeter.track_particle(single_particle);
  }
  std::cout<<"\nAll particles passed through all detectors\n"<<std::endl;
  tracker.turn_off();
  muon_chamber.turn_off();
  calorimeter.turn_off();
  // Print a summary of how many particles were detected
  std::cout<<"\n";
  tracker.show_particles();
  muon_chamber.show_particles();
  calorimeter.show_particles();
  std::cout<<"\n";
  // Show a particle going through a turned off detector
  particle trial_electron{"electron", 0.511, -1, 12736434};
  std::cout<<"\nPassing trial electron through tracker when tracker turned off...\n"<<std::endl;
  tracker.track_particle(trial_electron);
  std::cout<<"\nDone"<<std::endl;
  // Show validation options for changing velocity
  std::cout<<"\nCurrent velocity: "<<trial_electron.get_velocity()<<"\nCurrent beta: "<<trial_electron.get_beta()<<std::endl;
  std::cout<<"Attempted input velocity of '1234567890'"<<std::endl;
  trial_electron.set_velocity("1234567890", false);
  std::cout<<"\nAttempted input velocity of 'abcd'"<<std::endl;
  trial_electron.set_velocity("abcd", false);
  std::cout<<"Attempted input velocity of '360'"<<std::endl;
  trial_electron.set_velocity("360", false);
  std::cout<<"Current velocity: "<<trial_electron.get_velocity()<<"\nCurrent beta: "<<trial_electron.get_beta()<<"\n"<<std::endl;
  return 0;
}