#include "FixedUpgradeRule.hpp"

int FixedUpgradeRule::upgradeCost(const BusinessState& state) const {
    return 20 * (state.upgradeLevel + 1);
}

void FixedUpgradeRule::applyUpgrade(BusinessState& state) const {
    state.upgradeLevel += 1;
}
