#ifndef MOCK_QT_JSON_HPP
#define MOCK_QT_JSON_HPP

#include "QtJson.hpp"
#include "gmock/gmock.h"

class MockQtJson : public QtJson {
 public:
  MOCK_METHOD1(getStringValue, std::string(std::string key));
  MOCK_METHOD1(getIntegerValue, int(std::string key));
  MOCK_METHOD1(getBooleanValue, bool(std::string key));
};

#endif // MOCK_QT_JSON_HPP
