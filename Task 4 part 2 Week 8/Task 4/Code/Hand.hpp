#pragma once
#include <vector>
#include "Card.hpp"

// Urutan dari lemah ke kuat (dipakai untuk konversi skor).
enum class HandRank {
    HighCard,
    Pair,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush,
    FiveOfAKind,
    FlushHouse,
    FlushFive,
    Unknown // rantai habis / tidak ada kartu: tidak ada checker yang cocok
};

// Kumpulan kartu. Dipakai untuk hand hasil bagi (HandGenerator)
// maupun kartu yang dimainkan (lewat ChosenHand::toHand()).
struct Hand {
    std::vector<Card> cards;
};
