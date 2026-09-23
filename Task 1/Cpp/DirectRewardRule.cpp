#include "DirectRewardRule.hpp"

int DirectRewardRule::computeGain(int baseScore, int /*round*/) const {
    return baseScore;
}
