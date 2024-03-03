
#ifndef check_input
#define check_input

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include <cctype>

const double light_speed{2.99792458e8};
bool check_string(std::string input)
{
  if(input.size() == 0)
  {
    std::cout<<"That was not a valid input, please try again: ";
    return false;
  }
  for(const auto& chara:input)
  {
    if(!std::isalpha(chara))
    {
      std::cin.clear();
      std::cout<<"That was not a valid input, please try again"<<std::endl;
      return false;
    }
  }
  return true;
}

bool check_double(std::string input)
{
  if(input.size() == 0)
  {
    std::cout<<"That was not a valid input, please try again: ";
    return false;
  }
  for(const auto& chara:input)
  {
    if(!std::isdigit(chara) && chara != '.' && chara != '-')
    {
      std::cin.clear();
      std::cout<<"That was not a valid input, please try again:"<<std::endl;
      return false;
    }
  }
  return true;
}

bool check_int(std::string input)
{
  if(input.size() == 0)
  {
    std::cout<<"That was not a valid input, please try again: ";
    return false;
  }
  for(const auto& chara:input)
  {
    if(!std::isdigit(chara) && chara != '-')
    {
      std::cout<<"That was not a valid input, please try again: ";
      return false;
    }
  }
  return true;
}

double check_mass(std::string mass)
{
  if(check_double(mass))
  {
    if(std::stod(mass) <= 0)
    {
      std::cin.clear();
      std::cout<<"The mass has to be greater than 0, please try again: ";
      std::getline(std::cin, mass);
      return check_mass(mass);
    }
    return std::stod(mass);
  }
  std::cin.clear();
  std::getline(std::cin, mass);
  return check_mass(mass);
}

double check_velocity(std::string velocity_input)
{
  if(check_double(velocity_input))
  {
    if(std::stod(velocity_input)<=-light_speed || std::stod(velocity_input)>light_speed)
    {
      std::cin.clear();
      std::cout<<"The magnitude of the velocity can't be greater than the speed of light, please input again: ";
      std::getline(std::cin, velocity_input);
      return check_velocity(velocity_input);
    }
    return std::stod(velocity_input);
  }
  std::cin.clear();
  std::getline(std::cin, velocity_input);
  return check_velocity(velocity_input);
}

int check_charge(std::string charge)
{
  if(check_int(charge))
  {
    if(std::stoi(charge)!=-1 && std::stoi(charge)!=1)
    {
      std::cin.clear();
      std::cout<<"The charge of a particle can only be +1 or -1, please input again: ";
      std::getline(std::cin, charge);
      return check_charge(charge);
    }
    return std::stoi(charge);
  }
  std::cin.clear();
  if(charge[0] == '+'){ std::cout<<"Please be aware that '+1' is also not a valid input, only input 1"<<std::endl;}
  std::getline(std::cin, charge);
  return check_charge(charge);
}

std::string check_name(std::string name)
{
  for(int i{}; i<(name).length();i++)
  {
    name[i] = tolower(name[i]);
  }
  if(name!="electron" && name!="muon" && name!="tau" )
  {
    std::cin.clear();
    std::cout<<"That lepton does not exist, please try again: ";
    std::getline(std::cin, name);
    return check_name(name);
  }
  return name;
}

#endif  //check_input