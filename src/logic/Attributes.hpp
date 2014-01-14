#ifndef ATTRIBUTES_HPP
#define ATTRIBUTES_HPP

#include <map>
#include "Attribute.hpp"

enum AttributeName {
  INITIATIVE,
  TOUGHNESS,
  MELEE,
  RANGED,
  SHIELD,
  NET,
  MEDIC,
  MOTHER,
  MOBILITY,
  QUARTERMASTER
};

class Attributes {
public:
  Attributes(void);
  ~Attributes(void);

  Attribute* getAttribute(AttributeName name);
  void addAttribute(AttributeName name, Attribute* attribute);

private:
  std::map < AttributeName, Attribute*> attributes;
};

#endif //ATTRIBUTES_HPP
