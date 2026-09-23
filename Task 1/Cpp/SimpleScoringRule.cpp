#include "SimpleScoringRule.hpp"

int SimpleScoringRule::computeBase(const TurnInput& input) const {
    return input.value;
}
