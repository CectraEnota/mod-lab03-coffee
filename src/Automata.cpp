#include "Automata.h"
#include <iostream>
#include <fstream>

Automata::Automata() : cash(0), state(OFF) {
    menu = { "Чай", "Латте", "Горячий шоколад", "Капучино", "Эспрессо", "Раф" };
    prices = { 30, 130, 70, 135, 100, 150 };
}

void Automata::on() {
    if (state == OFF) {
        state = WAIT;
    }
}

void Automata::off() {
    state = OFF;
    cash = 0;
}

bool Automata::coin(int amount) {
    if (state == WAIT || state == ACCEPT) {
        state = ACCEPT;
        cash += amount;
        return true;
    }
    return false;
}

const std::vector<std::string>& Automata::getMenu() const {
    return menu;
}

const std::vector<int>& Automata::getPrices() const {
    return prices;
}

STATES Automata::getState() const {
    return state;
}

int Automata::getBalance() const {
    return cash;
}

bool Automata::choice(int drink) {
    if (state == ACCEPT && drink > 0 && drink <= static_cast<int>(menu.size())) {
        if (check(drink)) {
            state = CHECK;
            cook(drink);
            return true;
        }
    }
    return false;
}

bool Automata::check(int drink) const {
    return cash >= prices[drink - 1];
}

int Automata::cancel() {
    int comeback = 0;
    if (state == ACCEPT || state == CHECK) {
        state = WAIT;
        comeback = cash;
        cash = 0;
    }
    return comeback;
}

void Automata::cook(int drink) {
    if (state == CHECK) {
        state = COOK;
        cash -= prices[drink - 1];
        finish();
    }
}

int Automata::finish() {
    int change = cash;
    state = WAIT;
    cash = 0;
    return change;
}

int Automata::getMinCoin() const {
    return MIN_COIN;
}