#ifndef BOOSTJSON_H
#define BOOSTJSON_H

#include "Json.hpp"

#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;

class BoostJson : public Json, public ptree
{
public:
  BoostJson();
  ~BoostJson();

  template<typename T>
  void addKey(std::string name, T value);
};

#endif // BOOSTJSON_H
