// PHYS 30762 Programming in C++
// Assignment 3
// Oscar Fuentes Rebato - Last updated: 08/03/2024
// Practice with C++ classes and their interactions

#include "detector_class.h"

// Implementing all member functions of detector and particle classes
void particle::print_data()
  {
    std::cout.precision(3);
    std::cout<<"Particle: "<<particle_name<<"\nRest mass: "<<rest_mass<<" MeV\nCharge: "<<charge<<
    " C\nVelocity: "<<velocity<<" m/s\nBeta = "<<beta<<"\n"<<std::endl;
  }

void detector::turn_on()
{
  if(status){std::cout<<"This "<<detector_type<<" is already on"<<std::endl;}
  else
  {
    std::cout<<detector_type<<" turned on"<<std::endl;
    status = true;
  }
}

void detector::turn_off()
{
  if(!status){std::cout<<"This "<<detector_type<<" is already off"<<std::endl;}
  else
  {
    std::cout<<detector_type<<" turned off"<<std::endl;
    status = false;
  }
}

void detector::show_particles()
{
  if(!status){std::cout<<"This "<<detector_type<<" is off, cannot display particle count"<<std::endl;}
  else if(detector_type == "tracker"){std::cout<<particle_count<<" electrons have passed through this tracker"<<std::endl;}
  else if(detector_type == "muon chamber"){std::cout<<particle_count<<" muons have passed through this muon chamber"<<std::endl;}
  else if(detector_type == "calorimeter"){std::cout<<particle_count<<" electrons or muons have passed through this calorimeter"<<std::endl;}
  else{std::cout<<"DETECTOR_TYPE ERROR"<<std::endl;}
}

bool detector::track_particle(particle* lepton)
{
  if(!status)
  {
    std::cout<<"This "<<detector_type<<" is off, particle not tracked"<<std::endl;
    return false;
  }
  if(detector_type == "tracker" && ((*lepton).get_name() == "electron" || (*lepton).get_name() == "anti-electron"))
  {
    particle_count++;
    std::cout<<(*lepton).get_name()<<" detected by tracker"<<std::endl;
    return true;
  }
  else if(detector_type == "muon chamber" && ((*lepton).get_name() == "muon" || (*lepton).get_name() == "anti-muon"))
  {
    particle_count++;
    std::cout<<(*lepton).get_name()<<" detected by muon chamber"<<std::endl;
    return true;
  }
  else if(detector_type == "calorimeter" && ((*lepton).get_name() == "electron" || (*lepton).get_name() == "anti-electron" || (*lepton).get_name() == "muon" || (*lepton).get_name() == "anti-muon"))
  {
    particle_count++;
    std::cout<<(*lepton).get_name()<<" detected by calorimeter"<<std::endl;
    return true;
  }
  return false;
}

void detector::reset()
{
  if(!status){std::cout<<"This "<<detector_type<<" is off, can't reset"<<std::endl;}
  else if(particle_count>0){particle_count = 0;}
  else{std::cout<<"The count is already at 0"<<std::endl;}
}

//Main Program
int main()
{
  std::vector<particle*> particles;
  particles.push_back(new particle("electron", 2.55e8));
  particles.push_back(new particle("electron", 1.01e8));
  particles.push_back(new particle("muon", 500));
  particles.push_back(new particle("muon", 2.98e8));
  particles.push_back(new particle("muon", 3.06e6));
  particles.push_back(new particle("muon", 100));
  particles.push_back(new particle("tau", 2.5e8));
  particles.push_back(new particle("tau", 2.2e8));
  particles.push_back(new particle("tau", 1.5e8));
  particles.push_back(new particle("electron", 2.55e8, true));
  particles.push_back(new particle("muon", 2.55e8, true));
  particles.push_back(new particle("tau", 2.55e8, true));

  // Print out the data from all the particles
  for(std::vector<particle*>::iterator single_particle{particles.begin()}; single_particle != particles.end(); single_particle++)
  {
    (**single_particle).print_data();
  }

  // Create the detectors
  detector tracker{"tracker"};
  detector muon_chamber{"muon chamber"};
  detector calorimeter{"calorimeter"};

  // Pass the list of particles into each detector
  std::cout<<"\nPassing particles through detectors...\n"<<std::endl;
  tracker.turn_on();
  muon_chamber.turn_on();
  calorimeter.turn_on();
  for(std::vector<particle*>::iterator single_particle{particles.begin()}; single_particle != particles.end(); single_particle++)
  {
    tracker.track_particle(*single_particle);
    muon_chamber.track_particle(*single_particle);
    calorimeter.track_particle(*single_particle);
  }
  std::cout<<"\nAll particles passed through all detectors\n"<<std::endl;

  // Print a summary of how many particles were detected, turn off detectors and free up memory by deleting the particles
  std::cout<<"\n";
  tracker.show_particles();
  muon_chamber.show_particles();
  calorimeter.show_particles();
  std::cout<<"\n";
  tracker.turn_off();
  muon_chamber.turn_off();
  calorimeter.turn_off();
  std::cout<<"\n";
  std::cout<<"Deleting particles...\n"<<std::endl;
  for(std::vector<particle*>::iterator single_particle{particles.begin()}; single_particle != particles.end(); single_particle++)
  {
    delete *single_particle;
  }

  // Try to show particle count when a detector is off
  std::cout<<"\nShow particle count after turning off:"<<std::endl;
  tracker.show_particles();
  std::cout<<"\n";

  // Show a particle going through a turned off detector
  particle trial_electron{"electron", 12736434};
  std::cout<<"Passing trial electron through tracker when tracker turned off...\n"<<std::endl;
  tracker.track_particle(&trial_electron);

  // Show validation outputs for changing velocity
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