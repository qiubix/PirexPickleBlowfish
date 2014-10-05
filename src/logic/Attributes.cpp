#include "Attributes.hpp"

Attributes::Attributes(void) {
}

Attributes::~Attributes(void) {
  for (auto it = attributes.begin(); it != attributes.end(); it++) {
    delete it->second;
  }
}

Attribute* Attributes::getAttribute(AttributeName name) {
  auto it = attributes.find(name);
  if (it != attributes.end()) {
    return attributes.at(name);
  }
  else {
    return nullptr;
  }
}

int Attributes::getSize() {
  return attributes.size();
}

void Attributes::addAttribute(AttributeName name, Attribute* attribute) {
  attributes.insert(std::make_pair(name, attribute));
}

void Attributes::removeAttribute(AttributeName name) {
  auto it = attributes.find(name);
  if (it != attributes.end()) {
    attributes.erase(it);
  }
}

bool Attributes::empty(void) {
  return attributes.empty();
}
