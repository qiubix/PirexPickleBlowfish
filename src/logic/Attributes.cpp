#include "Attributes.hpp"

Attributes::Attributes(void) {
}

Attributes::~Attributes(void) {
  std::map<AttributeName, Attribute*>::iterator iterator;
  for(iterator = attributes.begin(); iterator != attributes.end(); iterator++) {
    delete iterator->second;
  }
}

Attribute* Attributes::getAttribute(AttributeName name) {
  std::map<AttributeName, Attribute*>::iterator it = attributes.find(name);
  if(it != attributes.end()) {
    return attributes.at(name);
  }
  else {
    return NULL;
  }
}

int Attributes::getSize() {
  return attributes.size();
}

void Attributes::addAttribute(AttributeName name, Attribute* attribute) {
  attributes.insert(std::make_pair(name, attribute));
//  attributes.insert(std::make_pair<AttributeName, Attribute*>(name, attribute));
}

void Attributes::removeAttribute(AttributeName name) {
  std::map <AttributeName, Attribute*>::iterator it;
  it = attributes.find(name);
  if (it == attributes.end()) {
    return;
  } else {
		attributes.erase(attributes.find(name));
  }
}

bool Attributes::empty(void) {
  return attributes.empty();
}
