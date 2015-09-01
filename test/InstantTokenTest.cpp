#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include <cstdlib>
#include "../src/logic/Attribute.hpp"
#include "../src/logic/Field.hpp"
#include "../src/logic/BoardToken.hpp"
#include "../src/logic/InstantToken.hpp"
#include "MockController.hpp"

//TODO: create mocks
class InstantTokenTest : public Test
{
protected:
  BoardToken* createBoardTokenWithToughness();

  Model model;
  Controller controller {&model};
};

BoardToken* InstantTokenTest::createBoardTokenWithToughness() {
  Attribute* toughness = new Attribute("toughness", 2);
  BoardToken* token = new BoardToken(Army::MOLOCH, "soldier");
  token -> addAttribute(TOUGHNESS, toughness);
  return token;
}

TEST_F(InstantTokenTest, shouldCauseBattle) {
  BattleToken battle {Army::MOLOCH, &controller};
  ASSERT_EQ(PAUSE, model.getGameState());
  battle.action();
  EXPECT_EQ(BATTLE, model.getGameState());
};

TEST_F(InstantTokenTest, shouldMoveToken) {
  MovementToken* movement = new MovementToken(Army::MOLOCH, &controller);
  BoardToken* token = new BoardToken(Army::MOLOCH, "soldier");
  Field* field = new Field;
  Field* destination = new Field;
  token -> setField(field);
  movement -> setTokenToMove(token);
  movement -> setDestination(destination);
  movement->action();
  EXPECT_NE(field, token->getField());
  EXPECT_EQ(nullptr, field->getToken());
  EXPECT_EQ(destination, token->getField());
  EXPECT_EQ(token, destination->getToken());
  delete field;
  delete movement;
}

TEST_F(InstantTokenTest, shouldPushToken) {
  PushToken* push = new PushToken(Army::MOLOCH, &controller);
  BoardToken* pusher = new BoardToken(Army::MOLOCH, "soldier");
  BoardToken* pushee = new BoardToken(Army::OUTPOST, "soldier");
  Field* pusherField = new Field;
  Field* pusheeField = new Field;
  Field* destination = new Field;
  pusher -> setField(pusherField);
  pushee -> setField(pusheeField);
  push -> setPushingToken(pusher);
  push -> setPushedToken(pushee);
  push -> setDestination(destination);
  push->action();
  EXPECT_NE(pusheeField, pushee->getField());
  EXPECT_EQ(destination, pushee->getField());
  EXPECT_EQ(pushee, destination->getToken());
  delete pusherField;
  delete pusheeField;
  delete pusher;
  delete pushee;
  delete push;
}

TEST_F(InstantTokenTest, shouldBombStrikeField) {
  BombToken* bomb = new BombToken(Army::MOLOCH, &controller);
  BoardToken* firstToken = createBoardTokenWithToughness();
  BoardToken* secondToken = createBoardTokenWithToughness();
  Field* firstField = new Field;
  Field* secondField = new Field;
  firstField -> addNeighbour(secondField, Side::NORTH);
  firstField -> setToken(firstToken);
  firstToken -> setField(firstField);
  secondField -> addNeighbour(firstField, Side::SOUTH);
  secondField -> setToken(secondToken);
  secondToken -> setField(secondField);

  bomb -> setEpicentrum(firstToken->getField());
  bomb->action();
  EXPECT_EQ(1, firstToken->getAttribute(TOUGHNESS)->getValue());
  EXPECT_EQ(1, secondToken->getAttribute(TOUGHNESS)->getValue());
  delete firstField;
  delete secondField;
  delete bomb;
}

TEST_F(InstantTokenTest, shouldDestroyToken) {
  GrenadeToken* grenade = new GrenadeToken(Army::BORGO, &controller);
  Player* player = new Player(Army::MOLOCH);
  model.addPlayer(player);
  BoardToken* token = new BoardToken(Army::MOLOCH, "soldier");
  Field* field = new Field;
  token -> setField(field);
  field -> setToken(token);
  grenade -> setTokenToDestroy(token);
  grenade->action();
  //FIXME: uncomment this lines
//  ASSERT_FALSE(model -> usedTokens.empty());
//  EXPECT_EQ(token, model -> usedTokens[0]);
  delete token;
  delete grenade;
}

TEST_F(InstantTokenTest, shouldStrikeToken) {
//  Controller* controller = new Controller(new Model);
//  MockController controller;
  SniperToken* sniper = new SniperToken(Army::OUTPOST, &controller);
  BoardToken* token = createBoardTokenWithToughness();
  sniper -> setTokenToStrike(token);
  sniper->action();
//  EXPECT_CALL(controller, strikeToken(token,1))
//      .Times(1);
  EXPECT_EQ(1, token->getAttribute(TOUGHNESS)->getValue());
  delete sniper;
}
