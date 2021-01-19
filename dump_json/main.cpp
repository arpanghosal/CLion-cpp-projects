#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.h"

int main() {
  nlohmann::json j;
  //writing
  std::ofstream o("top_bongs.json");

  std::map<std::string, std::vector<std::string>> map;
  std::vector<std::string> vec;
  std::string amudaage = "twenty seven";
  vec.push_back("Amu da");
  std::string arpanage = "twenty five";
  vec.push_back("Buddha");

  std::vector<std::string> vec1 = vec;

  map.insert(std::pair<std::string, std::vector<std::string>>(arpanage, vec));
  map.insert(std::pair<std::string, std::vector<std::string>>(amudaage, vec1));
  std::map<std::string, std::vector<std::string>>::iterator itr;
  for (itr=map.begin();itr!=map.end();++itr) {
    std::cout << itr->first << std::endl;
    for(auto c : itr->second)
    {
      std::cout << c << std::endl;
    }
    std:: cout<< std::endl;
    //std::cout << itr->second << std::endl;
  }

  for(itr = map.begin(); itr != map.end(); ++itr){
    j["name"] = itr->first; // name = mod name
    j["vec"] = itr->second; // vec = rod name

    o << std::setw(4) << j << std::endl;
  }

  return 0;
}
