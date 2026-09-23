#pragma once
#include "IScoringRule.hpp"

class SimpleScoringRule : public IScoringRule {
public:
    int computeBase(const TurnInput& input) const override;
};
