#include "BankruptcyEndCondition.hpp"

EndResult BankruptcyEndCondition::check(const BusinessState& state) const {
    if (state.money < 0) {
        return EndResult{true, "Bankrupt: money below zero"};
    }
    if (state.day >= 10) {
        return EndResult{true, "Goal reached: survived 10 days"};
    }
    return EndResult{false, ""};
}
