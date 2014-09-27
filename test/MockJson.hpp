#ifndef MOCK_JSON_HPP
#define MOCK_JSON_HPP

#include "gmock/gmock.h"
#include "../src/setup/Json.hpp"

#include <string>
#include <vector>

class MockJson : public Json
{
public:
  MOCK_METHOD1(getIntegerValue, int(std::string));
  MOCK_METHOD0(getKeys, std::vector<std::string>());
};

#endif // MOCK_JSON_HPP
