// HandGenerator.h
#pragma once
#include <random>
#include <vector>
#include "Hand.h"

class HandGenerator
{
public:
    HandGenerator();

    // Menghasilkan hand acak tanpa kartu kembar (diambil dari 1 deck 52 kartu).
    Hand generateHand(int handSize = 5);

private:
    std::vector<Card> createDeck() const;
    std::mt19937 rng;
};
