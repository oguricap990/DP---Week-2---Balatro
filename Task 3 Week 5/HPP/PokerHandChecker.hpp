#pragma once

#include <iostream>
#include "Hand.hpp"

// Handler abstrak pada pola Chain of Responsibility.
class PokerHandChecker {
protected:
    PokerHandChecker* nextChecker = nullptr;

    // Dipanggil concrete checker kalau hand tidak cocok dengan dirinya.
    HandRank passToNext(const Hand& hand) {
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        std::cout << "No checker could identify the hand.\n";
        return HandRank::Unknown;
    }

public:
    virtual HandRank check(const Hand& hand) = 0;

    void setNext(PokerHandChecker* next) {
        nextChecker = next;
    }

    virtual ~PokerHandChecker() = default;
};
