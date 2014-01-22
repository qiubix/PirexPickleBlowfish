#ifndef ATTRIBUTES_HPP
#define ATTRIBUTES_HPP

#include <gtest/gtest.h>

#include <map>
#include "Attribute.hpp"

enum AttributeName {
  ARMY,
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
  void removeAttribute(AttributeName name);

private:
  std::map < AttributeName, Attribute*> attributes;

  FRIEND_TEST(BoardTokenTest, testRemoveAttribute);
};

#endif //ATTRIBUTES_HPP
