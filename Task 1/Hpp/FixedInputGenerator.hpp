#pragma once
#include "IInputGenerator.hpp"

// Implementasi awal (base system): selalu menghasilkan input tetap.
class FixedInputGenerator : public IInputGenerator {
public:
    TurnInput generate(int round) override;
};
