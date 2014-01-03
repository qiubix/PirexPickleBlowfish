#ifndef JSON_HPP
#define JSON_HPP

#include <string>

class Json
{
public:
  Json(void) {}
  virtual ~Json(void) {}

  template<typename T>
  void addKey(std::string name, T value);
};

#endif // JSON_HPP
