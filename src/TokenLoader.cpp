#include "TokenLoader.hpp"

#include <cstdlib> //NULL

#include "JsonParser.hpp"

TokenLoader * TokenLoader::instance = NULL;

TokenLoader * TokenLoader::getInstance()
{
  if(instance == NULL) {
    instance = new TokenLoader();
  }
  return instance;
}

TokenLoader::TokenLoader() {
}
