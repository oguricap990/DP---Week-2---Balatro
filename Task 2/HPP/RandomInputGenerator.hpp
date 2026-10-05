#pragma once
#include <random>
#include "IInputGenerator.hpp"

// Modification 1: pengganti FixedInputGenerator, RunSession tidak diubah.
class RandomInputGenerator : public IInputGenerator {
public:
    RandomInputGenerator();
    TurnInput generate(int round) override;

private:
    std::mt19937 rng_;
    std::uniform_int_distribution<int> dist_;
};
