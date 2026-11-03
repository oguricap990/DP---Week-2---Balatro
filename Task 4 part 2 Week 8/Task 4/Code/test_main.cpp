// Pengujian: rantai checker (13 jenis hand), ChosenHand, HandGenerator, dan satu sesi game.
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include "GameManager.hpp"

static int failed = 0;

static void report(bool ok, const std::string& name) {
    if (!ok) ++failed;
    std::cout << (ok ? "[OK]   " : "[FAIL] ") << name << "\n";
}

static void expect(ScoringRule& rule, const std::vector<Card>& cards, HandRank expected, const std::string& name) {
    Hand h; h.cards = cards;
    report(rule.evaluate(h) == expected, name);
}

int main() {
    ScoringRule rule;

    // ---- Tugas 2: semua jenis hand ----
    expect(rule, {{2,'H'},{5,'D'},{9,'C'},{11,'S'},{13,'H'}},   HandRank::HighCard,     "High Card");
    expect(rule, {{9,'H'},{9,'D'},{3,'C'},{11,'S'},{13,'H'}},   HandRank::Pair,         "Pair");
    expect(rule, {{9,'H'},{9,'D'},{3,'C'},{3,'S'},{13,'H'}},    HandRank::TwoPair,      "Two Pair");
    expect(rule, {{9,'H'},{9,'D'},{9,'C'},{3,'S'},{13,'H'}},    HandRank::ThreeOfAKind, "Three of a Kind");
    expect(rule, {{5,'H'},{6,'D'},{7,'C'},{8,'S'},{9,'H'}},     HandRank::Straight,     "Straight");
    expect(rule, {{14,'H'},{2,'D'},{3,'C'},{4,'S'},{5,'H'}},    HandRank::Straight,     "Straight (wheel A-2-3-4-5)");
    expect(rule, {{2,'H'},{5,'H'},{9,'H'},{11,'H'},{13,'H'}},   HandRank::Flush,        "Flush");
    expect(rule, {{9,'H'},{9,'D'},{9,'C'},{3,'S'},{3,'H'}},     HandRank::FullHouse,    "Full House");
    expect(rule, {{9,'H'},{9,'D'},{9,'C'},{9,'S'},{3,'H'}},     HandRank::FourOfAKind,  "Four of a Kind");
    expect(rule, {{5,'H'},{6,'H'},{7,'H'},{8,'H'},{9,'H'}},     HandRank::StraightFlush,"Straight Flush");
    expect(rule, {{14,'H'},{2,'H'},{3,'H'},{4,'H'},{5,'H'}},    HandRank::StraightFlush,"Straight Flush (wheel, bukan Royal)");
    expect(rule, {{10,'S'},{11,'S'},{12,'S'},{13,'S'},{14,'S'}},HandRank::RoyalFlush,   "Royal Flush");
    expect(rule, {{9,'H'},{9,'D'},{9,'C'},{9,'S'},{9,'H'}},     HandRank::FiveOfAKind,  "Five of a Kind");
    expect(rule, {{9,'H'},{9,'H'},{9,'H'},{3,'H'},{3,'H'}},     HandRank::FlushHouse,   "Flush House");
    expect(rule, {{9,'H'},{9,'H'},{9,'H'},{9,'H'},{9,'H'}},     HandRank::FlushFive,    "Flush Five");
    expect(rule, {{9,'H'},{9,'D'}},                             HandRank::Pair,         "Pair (kurang dari 5 kartu)");
    expect(rule, {{2,'H'},{3,'H'},{4,'H'}},                     HandRank::HighCard,     "3 kartu satu suit = bukan Flush");
    expect(rule, {},                                            HandRank::Unknown,      "Hand kosong");

    // ---- Tugas 1: ChosenHand ----
    Hand hand;
    hand.cards = {{2,'H'},{3,'H'},{4,'H'},{5,'H'},{6,'H'},{7,'H'},{8,'H'}};
    ChosenHand chosen;
    bool ok = true;
    ok &= chosen.selectCard(hand, 0);
    ok &= !chosen.selectCard(hand, 0);   // duplikat ditolak
    ok &= !chosen.selectCard(hand, 99);  // index salah ditolak
    ok &= chosen.selectCard(hand, 1);
    ok &= chosen.selectCard(hand, 2);
    ok &= chosen.selectCard(hand, 3);
    ok &= chosen.selectCard(hand, 4);
    ok &= chosen.isFull();
    ok &= !chosen.selectCard(hand, 5);   // lebih dari 5 ditolak
    ok &= chosen.deselectCard(2);
    ok &= chosen.size() == 4;
    chosen.clear();
    ok &= chosen.isEmpty();
    report(ok, "ChosenHand");

    // ---- Tugas 3: HandGenerator acak dan tanpa duplikat ----
    HandGenerator generator;
    std::set<std::string> distinctHands;
    bool noDuplicate = true;
    for (int i = 0; i < 200; ++i) {
        Hand h = generator.generateHand();
        std::set<std::pair<int,char>> seen;
        std::string key;
        for (const Card& c : h.cards) {
            noDuplicate &= seen.insert({c.rank, c.suit}).second;
            key += toString(c) + ",";
        }
        noDuplicate &= (h.cards.size() == 5);
        distinctHands.insert(key);
    }
    report(noDuplicate, "tidak ada kartu kembar");
    report(distinctHands.size() > 100, "hand bervariasi: " + std::to_string(distinctHands.size()) + "/200 unik");

    // ---- Integrasi: satu sesi penuh tidak crash ----
    GameManager game;
    game.runSession();
    report(true, "GameManager::runSession selesai");

    std::cout << (failed == 0 ? "\nSEMUA TEST LULUS\n" : "\nADA TEST GAGAL\n");
    return failed;
}
