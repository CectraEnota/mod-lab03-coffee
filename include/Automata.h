#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <vector>
#include <string>

enum STATES {
    OFF,
    WAIT,
    ACCEPT,
    CHECK,
    COOK
};
class Automata {
private:
    int cash;
    std::vector<std::string> menu;
    std::vector<int> prices;
    STATES state;
    const int MIN_COIN = 20;
public:
    Automata();
    void on();
    void off();
    bool coin(int amount);
    const std::vector<std::string>& getMenu() const;
    const std::vector<int>& getPrices() const;
    STATES getState() const;
    bool choice(int drink);
    bool check(int drink) const;
    int cancel();
    void cook(int drink);
    int finish();
    int getBalance() const;
    int getMinCoin() const;
};
#endif
