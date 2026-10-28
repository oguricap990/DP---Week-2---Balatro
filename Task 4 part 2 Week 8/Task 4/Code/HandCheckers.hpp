#pragma once
#include <iostream>
#include "HandAnalysis.hpp"
#include "PokerHandChecker.hpp"

// Tugas 2: logic checker.
// Pola yang sama di semua checker (cocok -> cetak & kembalikan rank, tidak -> passToNext)
// ditaruh SEKALI di RankChecker (Template Method). Tiap checker cukup menjawab matches().
class RankChecker : public PokerHandChecker {
    HandRank    rank;
    const char* name;
protected:
    RankChecker(HandRank r, const char* n) : rank(r), name(n) {}
    virtual bool matches(const HandAnalysis& a) const = 0;

public:
    HandRank check(const Hand& hand) override {
        HandAnalysis analysis(hand.cards);
        if (matches(analysis)) {
            std::cout << "Hand: " << name << "\n";
            return rank;
        }
        return passToNext(hand);
    }
};

// Urutan chain (di Rules.hpp) dari terkuat ke terlemah, jadi tiap checker
// tidak perlu mengecualikan hand yang lebih kuat.

class FlushFiveChecker : public RankChecker {
public:
    FlushFiveChecker() : RankChecker(HandRank::FlushFive, "Flush Five") {}
protected:
    bool matches(const HandAnalysis& a) const override { return a.topCount() == 5 && a.isFlush(); }
};

class FlushHouseChecker : public RankChecker {
public:
    FlushHouseChecker() : RankChecker(HandRank::FlushHouse, "Flush House") {}
protected:
    bool matches(const HandAnalysis& a) const override {
        return a.topCount() == 3 && a.secondCount() == 2 && a.isFlush();
    }
};

class FiveOfAKindChecker : public RankChecker {
public:
    FiveOfAKindChecker() : RankChecker(HandRank::FiveOfAKind, "Five of a Kind") {}
protected:
    bool matches(const HandAnalysis& a) const override { return a.topCount() == 5; }
};

class RoyalFlushChecker : public RankChecker {
public:
    RoyalFlushChecker() : RankChecker(HandRank::RoyalFlush, "Royal Flush") {}
protected:
    // 10 J Q K A satu jenis
    bool matches(const HandAnalysis& a) const override {
        return a.isStraight() && a.isFlush() && a.lowestRank() == 10;
    }
};

class StraightFlushChecker : public RankChecker {
public:
    StraightFlushChecker() : RankChecker(HandRank::StraightFlush, "Straight Flush") {}
protected:
    bool matches(const HandAnalysis& a) const override { return a.isStraight() && a.isFlush(); }
};

class FourOfAKindChecker : public RankChecker {
public:
    FourOfAKindChecker() : RankChecker(HandRank::FourOfAKind, "Four of a Kind") {}
protected:
    bool matches(const HandAnalysis& a) const override { return a.topCount() == 4; }
};

class FullHouseChecker : public RankChecker {
public:
    FullHouseChecker() : RankChecker(HandRank::FullHouse, "Full House") {}
protected:
    bool matches(const HandAnalysis& a) const override {
        return a.topCount() == 3 && a.secondCount() == 2;
    }
};

class FlushChecker : public RankChecker {
public:
    FlushChecker() : RankChecker(HandRank::Flush, "Flush") {}
protected:
    bool matches(const HandAnalysis& a) const override { return a.isFlush(); }
};

class StraightChecker : public RankChecker {
public:
    StraightChecker() : RankChecker(HandRank::Straight, "Straight") {}
protected:
    bool matches(const HandAnalysis& a) const override { return a.isStraight(); }
};

class ThreeOfAKindChecker : public RankChecker {
public:
    ThreeOfAKindChecker() : RankChecker(HandRank::ThreeOfAKind, "Three of a Kind") {}
protected:
    bool matches(const HandAnalysis& a) const override { return a.topCount() == 3; }
};

class TwoPairChecker : public RankChecker {
public:
    TwoPairChecker() : RankChecker(HandRank::TwoPair, "Two Pair") {}
protected:
    bool matches(const HandAnalysis& a) const override {
        return a.topCount() == 2 && a.secondCount() == 2;
    }
};

class PairChecker : public RankChecker {
public:
    PairChecker() : RankChecker(HandRank::Pair, "Pair") {}
protected:
    bool matches(const HandAnalysis& a) const override { return a.topCount() == 2; }
};

class HighCardChecker : public RankChecker {
public:
    HighCardChecker() : RankChecker(HandRank::HighCard, "High Card") {}
protected:
    // Penampung terakhir: cocok untuk hand apa pun yang punya kartu.
    // Hand kosong tidak cocok -> HandRank::Unknown.
    bool matches(const HandAnalysis& a) const override { return a.size() > 0; }
};
