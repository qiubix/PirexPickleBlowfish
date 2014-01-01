#include "BoardToken.hpp"

//REVIEW: i think we should use NULL or (if we use c++11 because i'm not sure that we checked that so far) nullptr
BoardToken::BoardToken() {
  this->field = 0;
  this->rotation = new Attribute("rotation", NORTH);
  this->attributes.insert(std::make_pair<std::string, Attribute*>(rotation->getName(), rotation));
}

BoardToken::BoardToken(std::map<std::string, Attribute *> attributes) {
  this->attributes = attributes;
  //REVIEW: there is a posibility to fire other constructor in c++? because if it is we can avoid some duplication here
  //or maybe we can delete default constructor because we only need attributes (correct me if i'm wrong)
  this->field = 0;
  //REVIEW: i think that we don't have to pass orientation, rotation or what we will call this to token constructor.
  //by default it will be always default (NORTH) value
  std::map<std::string, Attribute*>::iterator it = attributes.find("rotation");
  if (it != attributes.end()) {
    this->rotation = it->second;
  } else {
    this->rotation = new Attribute("rotation", NORTH);
    this->attributes.insert(std::make_pair<std::string, Attribute*>(rotation->getName(), rotation));
  }
}

Field* BoardToken::getField() {
  return field;
}

void BoardToken::setField(Field* field) {
  this->field = field;
}

Attribute* BoardToken::getAttribute(std::string name) {
  return attributes[name];
}

//REVIEW: we need this method? is there a case in which we modify attributes list?
//for example is there a module which gives new attribute?
//if this method won't be needed the appropriate test should be deleted
void BoardToken::addAttribute(Attribute *attribute) {
  attributes.insert(std::make_pair<std::string, Attribute*>(attribute->getName(), attribute));
}

//REVIEW: wouldn't it be easier to use getAttribute and perform upgrad on it? code would be much more cleaner
void BoardToken::upgradeAttribute(std::string name, int newValue)
{
  attributes.find(name)->second->upgradeAttribute(newValue);
}

//REVIEW: this would be easier if we make orientation separate field as i wrote before
Orientation BoardToken::getRotation() {
  return static_cast<Orientation>(rotation->getUpgradedValue());
}

void BoardToken::setRotation(Orientation rotation) {
  this->rotation->upgradeAttribute(rotation);
}

void BoardToken::rotateClockwise()
{
  int newOrientation = rotation->getUpgradedValue();
  newOrientation = (++newOrientation)%6;
  rotation->upgradeAttribute(static_cast<Orientation>(newOrientation));
}

void BoardToken::rotateAntiClockwise()
{
  int newOrientation = rotation->getUpgradedValue();
  if (--newOrientation == -1) {
    newOrientation = 5;
  }
  rotation->upgradeAttribute(static_cast<Orientation>(newOrientation));
}
