// Task 1 - Building a Balatro-Like Run (Core Loop & System Thinking)
// main.cpp hanya merakit komponen; tidak ada logika game di sini.
// Compile: g++ -std=c++17 *.cpp -o main

#include <memory>
#include "RunSession.hpp"
#include "FixedInputGenerator.hpp"
#include "SimpleScoringRule.hpp"
#include "DirectRewardRule.hpp"
#include "ShopSystem.hpp"

using namespace std;

int main() {
    RunSession session(
        make_unique<FixedInputGenerator>(),
        make_unique<SimpleScoringRule>(),
        make_unique<DirectRewardRule>(),
        ShopSystem{});

    session.run();
    return 0;
}
