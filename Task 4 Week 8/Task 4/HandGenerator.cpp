// HandGenerator.cpp
// Soal 3: kartu di hand sekarang acak, bukan lagi 10-14 Hearts yang tetap.
#include "HandGenerator.h"
#include <algorithm>
#include <iostream>

HandGenerator::HandGenerator()
    : rng(std::random_device{}())   // seed acak, jadi tiap game hasilnya berbeda
{
}

std::vector<Card> HandGenerator::createDeck() const
{
    const char suits[] = { 'H', 'D', 'C', 'S' };

    std::vector<Card> deck;
    for (char suit : suits)
    {
        for (int rank = 2; rank <= 14; ++rank)
            deck.push_back({ rank, suit });
    }
    return deck; // 52 kartu
}

Hand HandGenerator::generateHand(int handSize)
{
    std::cout << "Generating hand...\n";

    std::vector<Card> deck = createDeck();
    std::shuffle(deck.begin(), deck.end(), rng);

    if (handSize > static_cast<int>(deck.size()))
        handSize = static_cast<int>(deck.size());
    if (handSize < 0)
        handSize = 0;

    Hand hand;
    hand.cards.assign(deck.begin(), deck.begin() + handSize);
    return hand;
}
