#pragma once

#include <iostream>
#include "HandSource.hpp"
#include "Rules.hpp"

class GameManager {
private:
    HandGenerator handGenerator;
    HandPlayer    handPlayer;
    ScoringRule   scoringRule;
    BlindRule     blindRule;
    RewardRule    rewardRule;

public:
    void runSession() {
        std::cout << "--- Dealt hand ---\n";
        Hand dealt = handGenerator.generateHand();
        int dealtScore = scoringRule.scoreHand(dealt);
        std::cout << "Score: " << dealtScore << "\n\n";

        std::cout << "--- Player hand ---\n";
        Hand played = handPlayer.generateHand();
        int score = scoringRule.scoreHand(played);
        std::cout << "Score: " << score << "\n";

        bool win = blindRule.checkBlind(score);
        int money = rewardRule.earnMoney(win, score);

        std::cout << (win ? "Blind cleared!" : "Blind failed.")
                  << " Money earned: " << money << "\n";
    }
};
