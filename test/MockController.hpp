#ifndef MOCK_CONTROLLER_HPP
#define MOCK_CONTROLLER_HPP

#include "gmock/gmock.h"
#include "../src/logic/Controller.hpp"

class MockController : public Controller
{
public:
  MOCK_METHOD2(strikeToken, void(BoardToken* token,int strength));
};

#endif // MOCK_CONTROLLER_HPP
