// PokerHandChecker.h
// Soal 2: checker untuk menentukan jenis poker hand dari kartu yang dipilih.
#pragma once
#include <vector>
#include "Card.h"
#include "ChosenHand.h"
#include "PokerHand.h"

class PokerHandChecker
{
public:
    PokerHand check(const ChosenHand& chosenHand) const;
    PokerHand check(const std::vector<Card>& cards) const;

private:
    bool isFlush(const std::vector<Card>& cards) const;
    bool isStraight(const std::vector<Card>& cards) const;
};
