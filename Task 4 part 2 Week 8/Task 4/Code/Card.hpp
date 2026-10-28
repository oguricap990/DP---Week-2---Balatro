#pragma once
#include <string>

// rank: 2..10, 11 = Jack, 12 = Queen, 13 = King, 14 = Ace
// suit: 'H' = Hearts, 'D' = Diamonds, 'C' = Clubs, 'S' = Spades
struct Card {
    int  rank;
    char suit;
};

inline std::string toString(const Card& card) {
    std::string r;
    switch (card.rank) {
        case 11: r = "J"; break;
        case 12: r = "Q"; break;
        case 13: r = "K"; break;
        case 14: r = "A"; break;
        default: r = std::to_string(card.rank);
    }
    return r + card.suit;
}
