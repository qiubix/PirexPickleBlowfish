#ifndef ATTRIBUTES_HPP
#define ATTRIBUTES_HPP

#include <map>
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
};

#endif //ATTRIBUTES_HPP
