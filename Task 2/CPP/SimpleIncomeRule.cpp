#include "SimpleIncomeRule.hpp"

int SimpleIncomeRule::computeIncome(const BusinessState& state) const {
    return 10 * (1 + state.upgradeLevel);
}
