#pragma once

#include <cstdlib>
#include "Hand.hpp"

// Kedua kelas ini versi dummy sesuai class diagram:
// generateHand() : Hand

// Membuat hand secara acak (nanti: mengocok dan membagi kartu).
class HandGenerator {
public:
    Hand generateHand() {
        Hand hand;
        hand.dummyRank = static_cast<HandRank>(std::rand() % 13);
        return hand;
    }
};

// Hand yang dimainkan pemain (nanti: pemain memilih kartu).
class HandPlayer {
public:
    Hand generateHand() {
        Hand hand;
        hand.dummyRank = static_cast<HandRank>(std::rand() % 13);
        return hand;
    }
};
