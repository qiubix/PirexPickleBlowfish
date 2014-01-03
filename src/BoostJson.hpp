#ifndef BOOSTJSON_H
#define BOOSTJSON_H

#include "Json.hpp"

#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;

class BoostJson : public Json, public ptree
{
public:
  BoostJson();
  virtual ~BoostJson();

  virtual std::string getStringValue(std::string key);
  virtual int getIntegerValue(std::string key);
  virtual bool getBooleanValue(std::string key);

  virtual void addStringValue(std::string key, std::string value);
  virtual void addIntegerValue(std::string key, int value);
  virtual void addBooleanValue(std::string key, bool value);
};

#endif // BOOSTJSON_H
