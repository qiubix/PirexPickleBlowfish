#ifndef MOCK_BOOST_JSON_HPP
#define MOCK_BOOST_JSON_HPP

#include "BoostJson.hpp"
#include "gmock/gmock.h"

class MockBoostJson : public BoostJson {
 public:
  MOCK_METHOD1(getStringValue, std::string(std::string key));
  MOCK_METHOD1(getIntegerValue, int(std::string key));
  MOCK_METHOD1(getBooleanValue, bool(std::string key));
};

#endif // MOCK_BOOST_JSON_HPP
