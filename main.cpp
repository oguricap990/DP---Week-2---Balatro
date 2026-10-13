#include <cstdlib>
#include <ctime>
#include <iostream>
#include "GameManager.hpp"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Demo 1: uji chain untuk semua 13 jenis hand
    std::cout << "===== Demo: semua jenis hand =====\n";
    ScoringRule scoring;
    for (int i = 0; i < 13; ++i) {
        Hand hand;
        hand.dummyRank = static_cast<HandRank>(i);
        std::cout << "[" << i + 1 << "] ";
        scoring.scoreHand(hand);
    }

    // Demo 2: jalankan satu sesi game
    std::cout << "\n===== Demo: game session =====\n";
    GameManager game;
    game.runSession();

    return 0;
}
