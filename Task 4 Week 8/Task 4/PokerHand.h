#pragma once
#include <string>

enum class PokerHand
{
    None,          // belum ada kartu yang dipilih
    HighCard,
    Pair,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush
};

inline std::string toString(PokerHand hand)
{
    switch (hand)
    {
    case PokerHand::None:          return "None";
    case PokerHand::HighCard:      return "High Card";
    case PokerHand::Pair:          return "Pair";
    case PokerHand::TwoPair:       return "Two Pair";
    case PokerHand::ThreeOfAKind:  return "Three of a Kind";
    case PokerHand::Straight:      return "Straight";
    case PokerHand::Flush:         return "Flush";
    case PokerHand::FullHouse:     return "Full House";
    case PokerHand::FourOfAKind:   return "Four of a Kind";
    case PokerHand::StraightFlush: return "Straight Flush";
    case PokerHand::RoyalFlush:    return "Royal Flush";
    }
    return "Unknown";
}
