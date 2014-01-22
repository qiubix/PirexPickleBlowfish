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

  //REVIEW: why just don't make public method getSize(), because you make this test private just to use std::map size() method.
  //adding this method to public interface would help also in other tests (while testing adding for example)
  FRIEND_TEST(BoardTokenTest, testRemoveAttribute);
};

#endif //ATTRIBUTES_HPP
