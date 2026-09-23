#pragma once
#include <memory>
#include "GameTypes.hpp"
#include "IInputGenerator.hpp"
#include "IScoringRule.hpp"
#include "IRewardRule.hpp"
#include "ShopSystem.hpp"

// RunSession = INVARIANT.
// Hanya mengatur urutan fase (1..6) dan MEMANGGIL komponen mutable
// lewat interface. Tidak ada logika scoring, reward, atau pembuatan
// input di dalam class ini.
class RunSession {
public:
    RunSession(std::unique_ptr<IInputGenerator> inputGen,
               std::unique_ptr<IScoringRule> scoring,
               std::unique_ptr<IRewardRule> reward,
               ShopSystem shop);

    void run();

private:
    static constexpr int kTotalRounds = 3;

    std::unique_ptr<IInputGenerator> inputGen_;
    std::unique_ptr<IScoringRule> scoring_;
    std::unique_ptr<IRewardRule> reward_;
    ShopSystem shop_;
    RunState state_;
};
