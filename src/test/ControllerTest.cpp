#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "logic/Controller.hpp"
#include "logic/Model.hpp"

class ControllerTest : public Test
{
protected:
  ControllerTest(void) {
    model = new Model;
    controller = new Controller(model);
  }
  ~ControllerTest(void) {
    delete controller;
  }
  Controller* controller;
  Model* model;

  virtual void SetUp(void) {}
  virtual void TearDown(void) {}
};

TEST_F(ControllerTest, shouldSetGameState) {
  GameState currentState = model->getGameState();
  EXPECT_EQ(PAUSE, currentState);
  controller->setGameState(GAME);
  currentState = model->getGameState();
  EXPECT_EQ(GAME, currentState);
}

//TEST_F(ControllerTest, shouldResetGame) {
//  controller->reset();
//  EXPECT_EQ(PAUSE, model->getGameState());
//  EXPECT_TRUE(model->usedTokens.empty());
//  EXPECT_TRUE(model->players.empty());
//}
