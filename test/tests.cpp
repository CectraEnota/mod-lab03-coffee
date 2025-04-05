// Copyright 2022 UNN-IASR
#include <gtest/gtest.h>
#include "Automata.h"

class AutomataTest : public ::testing::Test {
 protected:
  Automata machine;

  void SetUp() override {
    machine.on();
  }

  void TearDown() override {
    machine.off();
  }
};

TEST_F(AutomataTest, InitialState) {
  EXPECT_EQ(machine.getState(), WAIT);
  EXPECT_EQ(machine.getBalance(), 0);
}

TEST_F(AutomataTest, TurnOnOff) {
  machine.off();
  EXPECT_EQ(machine.getState(), OFF);

  machine.on();
  EXPECT_EQ(machine.getState(), WAIT);
}

TEST_F(AutomataTest, CoinInsertion) {
  EXPECT_TRUE(machine.coin(20));
  EXPECT_EQ(machine.getState(), ACCEPT);
  EXPECT_EQ(machine.getBalance(), 20);

  EXPECT_TRUE(machine.coin(50));
  EXPECT_EQ(machine.getBalance(), 70);
}

TEST_F(AutomataTest, InvalidCoinInsertion) {
  EXPECT_FALSE(machine.coin(10));  // Меньше минимальной суммы
  EXPECT_EQ(machine.getBalance(), 0);

  machine.off();
  EXPECT_FALSE(machine.coin(20));  // Автомат выключен
}

TEST_F(AutomataTest, GetMenu) {
  const auto& menu = machine.getMenu();
  const auto& prices = machine.getPrices();

  ASSERT_FALSE(menu.empty());
  ASSERT_EQ(menu.size(), prices.size());

  EXPECT_EQ(menu[0], "Чай");
  EXPECT_EQ(prices[0], 30);
}

TEST_F(AutomataTest, SuccessfulChoice) {
  machine.coin(50);
  EXPECT_TRUE(machine.choice(1));  // Чай стоит 30
  EXPECT_EQ(machine.getState(), WAIT);
}

TEST_F(AutomataTest, InsufficientFunds) {
  machine.coin(20);
  EXPECT_FALSE(machine.choice(1));  // Чай стоит 30, не хватает
  EXPECT_EQ(machine.getState(), ACCEPT);
}

TEST_F(AutomataTest, CancelOperation) {
  machine.coin(100);
  EXPECT_EQ(machine.cancel(), 100);
  EXPECT_EQ(machine.getBalance(), 0);
  EXPECT_EQ(machine.getState(), WAIT);
}

TEST_F(AutomataTest, FinishOperation) {
  machine.coin(200);
  machine.choice(3);  // Горячий шоколад стоит 70
  EXPECT_EQ(machine.getBalance(), 0);  // Сдача должна быть возвращена
}

TEST_F(AutomataTest, InvalidChoice) {
  machine.coin(100);
  EXPECT_FALSE(machine.choice(0));  // Неверный номер
  EXPECT_FALSE(machine.choice(100));  // Неверный номер
}

TEST_F(AutomataTest, StateTransitions) {
  EXPECT_EQ(machine.getState(), WAIT);

  machine.coin(20);
  EXPECT_EQ(machine.getState(), ACCEPT);

  machine.coin(20);
  machine.choice(1);
  EXPECT_EQ(machine.getState(), WAIT);
}

TEST_F(AutomataTest, MinimumCoinRequirement) {
  EXPECT_EQ(machine.getMinCoin(), 20);
}
