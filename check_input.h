
#ifndef check_input
#define check_input


#include<iostream>
#include<string>
#include<vector>
#include<cmath>

bool check_string(std::string input)
{
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
  for(const auto& chara:input)
  {
    if(!std::isdigit(chara) && chara != '.')
    {
      std::cin.clear();
      std::cout<<"That was not a valid input, please try again"<<std::endl;
      return false;
    }
  }
  return true;
}

bool check_int(std::string input)
{
  for(const auto& chara:input)
  {
    if(!std::isdigit(chara))
    {
      std::cin.clear();
      std::cout<<"That was not a valid input, please try again"<<std::endl;
      return false;
    }
  }
  return true;
}

#endif  //check_input