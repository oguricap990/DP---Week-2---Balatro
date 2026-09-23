#pragma once

class IRewardRule {
public:
    virtual ~IRewardRule() = default;
    virtual int computeGain(int baseScore, int round) const = 0;
};
