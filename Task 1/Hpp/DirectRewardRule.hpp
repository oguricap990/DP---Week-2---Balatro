#pragma once
#include "IRewardRule.hpp"

// Implementasi awal (base system): reward = base score.
class DirectRewardRule : public IRewardRule {
public:
    int computeGain(int baseScore, int round) const override;
};
