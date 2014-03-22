#ifndef ATTRIBUTES_HPP
#define ATTRIBUTES_HPP

#include <map>
#include <gtest/gtest.h>
#include "Attribute.hpp"
#include "AttributeName.hpp"

class Attributes {
public:
  Attributes(void);
  ~Attributes(void);

  //getters
  Attribute* getAttribute(AttributeName name);
  int getSize(void);

  void addAttribute(AttributeName name, Attribute* attribute);
  void removeAttribute(AttributeName name);
  bool empty(void);

private:
  std::map < AttributeName, Attribute*> attributes;
  
  FRIEND_TEST(AttributesTest, shouldRemoveAttribute);
};

#endif //ATTRIBUTES_HPP
