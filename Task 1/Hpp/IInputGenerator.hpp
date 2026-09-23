#pragma once
#include "GameTypes.hpp"

class IInputGenerator {
public:
    virtual ~IInputGenerator() = default;
    virtual TurnInput generate(int round) = 0;
};
