// Task 2 - Develop Your Own Core Loop (Tycoon)
// main.cpp hanya merakit komponen; tidak ada logika game di sini.
// Compile: g++ -std=c++17 *.cpp -o main

#include <memory>
#include "GameSession.hpp"
#include "SimpleIncomeRule.hpp"
#include "FixedUpgradeRule.hpp"
#include "BankruptcyEndCondition.hpp"

using namespace std;

int main() {
    GameSession session(
        make_unique<SimpleIncomeRule>(),
        make_unique<FixedUpgradeRule>(),
        make_unique<BankruptcyEndCondition>());

    session.StartGame();
    return 0;
}
