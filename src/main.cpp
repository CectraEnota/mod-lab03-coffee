// Copyright 2022 UNN-IASR
#include "Automata.h"

#include <iostream>
#include <string>

void DisplayMenu(const Automata& machine) {
  const auto& menu = machine.getMenu();
  const auto& prices = machine.getPrices();

  std::cout << "----- МЕНЮ -----" << std::endl;
  for (size_t i = 0; i < menu.size(); ++i) {
    std::cout << i + 1 << ". " << menu[i] << " - " << prices[i] << " руб."
              << std::endl;
  }
  std::cout << "----------------" << std::endl;
}

void DisplayState(const Automata& machine) {
  switch (machine.getState()) {
    case OFF:    std::cout << "Состояние: Выключен" << std::endl; break;
    case WAIT:   std::cout << "Состояние: Ожидание" << std::endl; break;
    case ACCEPT: std::cout << "Состояние: Приём денег" << std::endl; break;
    case CHECK:  std::cout << "Состояние: Проверка" << std::endl; break;
    case COOK:   std::cout << "Состояние: Приготовление" << std::endl; break;
  }
  std::cout << "Баланс: " << machine.getBalance() << " руб." << std::endl;
  std::cout << "Минимальная сумма: " << machine.getMinCoin() << " руб."
            << std::endl;
}

int main() {
  setlocale(LC_ALL, "Russian");
  Automata machine;

  machine.on();
  DisplayState(machine);

  std::cout << "\nВносим 20 рублей: ";
  if (machine.coin(20)) {
    std::cout << "Успешно\n";
    DisplayState(machine);
    DisplayMenu(machine);

    std::cout << "\nПытаемся выбрать чай (1): ";
    if (!machine.choice(1)) {
      std::cout << "Недостаточно средств! Нужно еще "
                << machine.getPrices()[0] - machine.getBalance() << " руб.\n";
    }
    DisplayState(machine);

    std::cout << "\nПытаемся добавить 10 рублей: ";
    if (!machine.coin(10)) {
      std::cout << "Ошибка: минимальная сумма - " << machine.getMinCoin()
                << " руб.\n";
    }

    std::cout << "\nДобавляем 20 рублей: ";
    machine.coin(20);
    std::cout << "Теперь баланс: " << machine.getBalance() << " руб.\n";

    std::cout << "\nСнова выбираем чай (1): ";
    if (machine.choice(1)) {
      std::cout << "Напиток готов! Сдача: " << machine.getBalance()
                << " руб.\n";
    }
    DisplayState(machine);
  }
  machine.off();

  return 0;
}