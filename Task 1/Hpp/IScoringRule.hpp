#pragma once
#include "GameTypes.hpp"

class IScoringRule {
public:
    virtual ~IScoringRule() = default;
    virtual int computeBase(const TurnInput& input) const = 0;
};
