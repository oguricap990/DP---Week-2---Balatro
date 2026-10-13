#pragma once

#include <iostream>
#include "PokerHandChecker.hpp"

// Semua checker punya pola yang sama:
//   cocok     -> cetak jenis hand, kembalikan HandRank-nya
//   tidak     -> teruskan ke checker berikutnya (passToNext)
//
// Logic asli (cek kartu) belum diimplementasikan sesuai instruksi tugas.
// Sementara, "cocok" ditentukan dari hand.dummyRank.
// TODO: ganti kondisi if(...) dengan pengecekan kartu yang sebenarnya.

class HighCardChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (hand.dummyRank == HandRank::HighCard) {
            std::cout << "Hand: High Card\n";
            return HandRank::HighCard;
        }
        return passToNext(hand);
    }
};

class PairChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (hand.dummyRank == HandRank::Pair) {
            std::cout << "Hand: Pair\n";
            return HandRank::Pair;
        }
        return passToNext(hand);
    }
};

class TwoPairChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (hand.dummyRank == HandRank::TwoPair) {
            std::cout << "Hand: Two Pair\n";
            return HandRank::TwoPair;
        }
        return passToNext(hand);
    }
};

class ThreeOfAKindChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (hand.dummyRank == HandRank::ThreeOfAKind) {
            std::cout << "Hand: Three of a Kind\n";
            return HandRank::ThreeOfAKind;
        }
        return passToNext(hand);
    }
};

class StraightChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (hand.dummyRank == HandRank::Straight) {
            std::cout << "Hand: Straight\n";
            return HandRank::Straight;
        }
        return passToNext(hand);
    }
};

class FlushChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (hand.dummyRank == HandRank::Flush) {
            std::cout << "Hand: Flush\n";
            return HandRank::Flush;
        }
        return passToNext(hand);
    }
};

class FullHouseChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (hand.dummyRank == HandRank::FullHouse) {
            std::cout << "Hand: Full House\n";
            return HandRank::FullHouse;
        }
        return passToNext(hand);
    }
};

class FourOfAKindChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (hand.dummyRank == HandRank::FourOfAKind) {
            std::cout << "Hand: Four of a Kind\n";
            return HandRank::FourOfAKind;
        }
        return passToNext(hand);
    }
};

class StraightFlushChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (hand.dummyRank == HandRank::StraightFlush) {
            std::cout << "Hand: Straight Flush\n";
            return HandRank::StraightFlush;
        }
        return passToNext(hand);
    }
};

class RoyalFlushChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (hand.dummyRank == HandRank::RoyalFlush) {
            std::cout << "Hand: Royal Flush\n";
            return HandRank::RoyalFlush;
        }
        return passToNext(hand);
    }
};

class FiveOfAKindChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (hand.dummyRank == HandRank::FiveOfAKind) {
            std::cout << "Hand: Five of a Kind\n";
            return HandRank::FiveOfAKind;
        }
        return passToNext(hand);
    }
};

class FlushHouseChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (hand.dummyRank == HandRank::FlushHouse) {
            std::cout << "Hand: Flush House\n";
            return HandRank::FlushHouse;
        }
        return passToNext(hand);
    }
};

class FlushFiveChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (hand.dummyRank == HandRank::FlushFive) {
            std::cout << "Hand: Flush Five\n";
            return HandRank::FlushFive;
        }
        return passToNext(hand);
    }
};
