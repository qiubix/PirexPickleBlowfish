#include "Field.hpp"

Field::Field() {
  //REVIEW: i think we should use NULL or (if we use c++11 because i'm not sure that we checked that so far) nullptr
  token = 0;
}

Token* Field::getToken() {
  return token;
}
