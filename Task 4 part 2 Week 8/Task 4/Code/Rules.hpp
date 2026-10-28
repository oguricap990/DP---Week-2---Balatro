#pragma once
#include "ChosenHand.hpp"
#include "Hand.hpp"
#include "HandCheckers.hpp"

// ScoringRule menyusun chain checker dari hand terkuat ke terlemah,
// lalu mengubah hasilnya menjadi skor.
class ScoringRule {
private:
    FlushFiveChecker      flushFive;
    FlushHouseChecker     flushHouse;
    FiveOfAKindChecker    fiveOfAKind;
    RoyalFlushChecker     royalFlush;
    StraightFlushChecker  straightFlush;
    FourOfAKindChecker    fourOfAKind;
    FullHouseChecker      fullHouse;
    FlushChecker          flush;
    StraightChecker       straight;
    ThreeOfAKindChecker   threeOfAKind;
    TwoPairChecker        twoPair;
    PairChecker           pair;
    HighCardChecker       highCard;

    PokerHandChecker* head;

public:
    ScoringRule() {
        flushFive.setNext(&flushHouse);
        flushHouse.setNext(&fiveOfAKind);
        fiveOfAKind.setNext(&royalFlush);
        royalFlush.setNext(&straightFlush);
        straightFlush.setNext(&fourOfAKind);
        fourOfAKind.setNext(&fullHouse);
        fullHouse.setNext(&flush);
        flush.setNext(&straight);
        straight.setNext(&threeOfAKind);
        threeOfAKind.setNext(&twoPair);
        twoPair.setNext(&pair);
        pair.setNext(&highCard);

        head = &flushFive;
    }

    // Chain berisi pointer ke anggota sendiri, jadi tidak boleh disalin.
    ScoringRule(const ScoringRule&) = delete;
    ScoringRule& operator=(const ScoringRule&) = delete;

    HandRank evaluate(const Hand& hand) { return head->check(hand); }

    int scoreHand(const Hand& hand)         { return convertRankToScore(evaluate(hand)); }
    int scoreHand(const ChosenHand& chosen) { return scoreHand(chosen.toHand()); }

    int convertRankToScore(HandRank rank) {
        if (rank == HandRank::Unknown) return 0;
        return (static_cast<int>(rank) + 1) * 10;
    }
};

// Menentukan apakah skor cukup untuk mengalahkan blind.
class BlindRule {
public:
    bool checkBlind(int score) {
        const int target = 60; // nilai dummy
        return score >= target;
    }
};

// Menghitung uang yang didapat.
class RewardRule {
public:
    int earnMoney(bool win, int score) {
        if (!win) return 0;
        return 3 + score / 10; // rumus dummy
    }
};
