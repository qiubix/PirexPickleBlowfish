#ifndef BOARDTOKEN_HPP
#define BOARDTOKEN_HPP

#include <map>
#include <string>
#include "Token.hpp"
#include "Field.hpp"
#include "Attribute.hpp"

//REVIEW: I suggest naming this enum "Direction" because it is not the only place we'll use it
//REVIEW: REVIEW comment in Token.hpp
//REVIEW: i think that clockwise order would be more intuitive
enum Orientation {
  NORTH,
  NORTH_EAST,
  SOUTH_EAST,
  SOUTH,
  SOUTH_WEST,
  NORTH_WEST
};

class BoardToken : public Token
//REVIEW: i think that writing explicitly "private:" would be easier to read
//REVIEW: i also think that public section should goes first, because that is the API that other classes use so should be visible first
{
  Field* field;
  //REVIEW: i was thinking about wrapping this map into a Attributes class, so it would be on higher level of abstraction
  //and we could add our methods to have clearer API but that's just a proposition
  //REVIEW: i started to think during this review, that maybe having enum with all possible attributes wouldn't be easier in use
  //now we have some duplication, because key in this map is also a field in Attribute class
  //other thing is, that integers are better for keys and better as method arguments but we can discuss it or leave it for now
  std::map <std::string, Attribute*> attributes;
  //REVIEW: i think that rotation is not that kind of attribute to wrap it in Attribute class
  //i mean that other attributes are strictly connected with token and its rotation is more connected with position on board
  //so i think it should be: Orientation (or Direction) rotation or something. i don't know which word is the most suitable.
  Attribute* rotation;
public:
  BoardToken();
  //REVIEW: QUESTION: i'm not sure how map is passed as a method argument, i mean is it passe through value or through refference or what?
  //if by value the copy constructor of std::map is used and i'm not sure it's the best approach but i'm don't have any argument for now :)
  BoardToken(std::map <std::string, Attribute*> attributes);
  //REVIEW: QUESTION: if we have empty parameters list we leave it empty or we type "void"?
  Field* getField();
  void setField(Field* field);
  Attribute* getAttribute(std::string name);
  void addAttribute(Attribute* attribute);
  void upgradeAttribute(std::string name, int newValue);
  Orientation getRotation();
  void setRotation(Orientation rotation);
  //REVIEW: i think we should have method rotateBy(int degrees) that handles the rotation because now we would have to fire this method multiple times to rotate by 180
  void rotateClockwise();
  void rotateAntiClockwise();
  //REVIEW: shouldn't we have destructor to delete atrributes from attributes map? these are pointers we initiate somewhere else (in some builder)
  //but i think we should deallocate them here
};

#endif //BOARDTOKEN_HPP
