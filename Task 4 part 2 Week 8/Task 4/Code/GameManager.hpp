#pragma once
#include <iostream>
#include "HandSource.hpp"
#include "Rules.hpp"

// Facade: main() cukup memanggil runSession(); urutan langkah disembunyikan di sini.
class GameManager {
private:
    static constexpr int HAND_SIZE = 8; // dibagi 8 kartu, pemain memilih maksimal 5

    HandGenerator handGenerator;
    HandPlayer    handPlayer;
    ScoringRule   scoringRule;
    BlindRule     blindRule;
    RewardRule    rewardRule;

public:
    explicit GameManager(bool interactive = false) : handPlayer(interactive) {}

    void runSession() {
        std::cout << "=== Run Started ===\n";

        // Step 1: bagi kartu (acak)
        Hand dealt = handGenerator.generateHand(HAND_SIZE);

        // Step 2: pemain memilih kartu yang dimainkan
        ChosenHand chosen = handPlayer.playHand(dealt);

        // Step 3: chain checker menentukan jenis hand -> skor
        int score = scoringRule.scoreHand(chosen);
        std::cout << "Score: " << score << "\n";

        // Step 4: menang / kalah melawan blind
        bool win = blindRule.checkBlind(score);

        // Step 5: hitung reward
        int money = rewardRule.earnMoney(win, score);

        std::cout << (win ? "Blind cleared!" : "Blind failed.")
                  << " Money gained: " << money << "\n";
        std::cout << "=== Run Ended ===\n";
    }
};
