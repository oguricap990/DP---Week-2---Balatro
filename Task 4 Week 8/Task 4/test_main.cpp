// test_main.cpp : pengujian sederhana untuk ketiga soal
#include <iostream>
#include <set>
#include <utility>
#include "HandGenerator.h"
#include "ChosenHand.h"
#include "PokerHandChecker.h"

static int failed = 0;

static void expect(const std::vector<Card>& cards, PokerHand expected)
{
    PokerHandChecker checker;
    PokerHand got = checker.check(cards);
    bool ok = (got == expected);
    if (!ok) ++failed;
    std::cout << (ok ? "[OK]   " : "[FAIL] ") << toString(expected)
              << " -> " << toString(got) << "\n";
}

int main()
{
    // ---- Soal 2: semua jenis hand ----
    expect({{2,'H'},{5,'D'},{9,'C'},{11,'S'},{13,'H'}}, PokerHand::HighCard);
    expect({{9,'H'},{9,'D'},{3,'C'},{11,'S'},{13,'H'}}, PokerHand::Pair);
    expect({{9,'H'},{9,'D'},{3,'C'},{3,'S'},{13,'H'}}, PokerHand::TwoPair);
    expect({{9,'H'},{9,'D'},{9,'C'},{3,'S'},{13,'H'}}, PokerHand::ThreeOfAKind);
    expect({{5,'H'},{6,'D'},{7,'C'},{8,'S'},{9,'H'}},  PokerHand::Straight);
    expect({{14,'H'},{2,'D'},{3,'C'},{4,'S'},{5,'H'}}, PokerHand::Straight); // wheel
    expect({{2,'H'},{5,'H'},{9,'H'},{11,'H'},{13,'H'}},PokerHand::Flush);
    expect({{9,'H'},{9,'D'},{9,'C'},{3,'S'},{3,'H'}},  PokerHand::FullHouse);
    expect({{9,'H'},{9,'D'},{9,'C'},{9,'S'},{3,'H'}},  PokerHand::FourOfAKind);
    expect({{5,'H'},{6,'H'},{7,'H'},{8,'H'},{9,'H'}},  PokerHand::StraightFlush);
    expect({{10,'S'},{11,'S'},{12,'S'},{13,'S'},{14,'S'}}, PokerHand::RoyalFlush);
    expect({{9,'H'},{9,'D'}}, PokerHand::Pair);       // kurang dari 5 kartu
    expect({{2,'H'},{3,'H'},{4,'H'}}, PokerHand::HighCard); // bukan flush/straight
    expect({}, PokerHand::None);

    // ---- Soal 1: ChosenHand ----
    Hand hand;
    hand.cards = {{2,'H'},{3,'H'},{4,'H'},{5,'H'},{6,'H'},{7,'H'},{8,'H'}};
    ChosenHand chosen;
    bool ok = true;
    ok &= chosen.selectCard(hand, 0);
    ok &= !chosen.selectCard(hand, 0);    // duplikat ditolak
    ok &= !chosen.selectCard(hand, 99);   // index salah ditolak
    ok &= chosen.selectCard(hand, 1);
    ok &= chosen.selectCard(hand, 2);
    ok &= chosen.selectCard(hand, 3);
    ok &= chosen.selectCard(hand, 4);
    ok &= chosen.isFull();
    ok &= !chosen.selectCard(hand, 5);    // lebih dari 5 ditolak
    ok &= chosen.deselectCard(2);
    ok &= chosen.size() == 4;
    chosen.clear();
    ok &= chosen.isEmpty();
    std::cout << (ok ? "[OK]   " : "[FAIL] ") << "ChosenHand\n";
    if (!ok) ++failed;

    // ---- Soal 3: HandGenerator acak dan tanpa duplikat ----
    HandGenerator generator;
    std::set<std::string> distinctHands;
    bool noDuplicate = true;
    for (int i = 0; i < 200; ++i)
    {
        Hand h = generator.generateHand();
        std::set<std::pair<int,char>> seen;
        std::string key;
        for (const Card& c : h.cards)
        {
            noDuplicate &= seen.insert({c.rank, c.suit}).second;
            key += std::to_string(c.rank) + c.suit + ",";
        }
        noDuplicate &= (h.cards.size() == 5);
        distinctHands.insert(key);
    }
    bool random = distinctHands.size() > 100;
    std::cout << (noDuplicate ? "[OK]   " : "[FAIL] ") << "tidak ada kartu kembar\n";
    std::cout << (random ? "[OK]   " : "[FAIL] ") << "hand bervariasi: " << distinctHands.size() << "/200 unik\n";
    if (!noDuplicate || !random) ++failed;

    std::cout << (failed == 0 ? "\nSEMUA TEST LULUS\n" : "\nADA TEST GAGAL\n");
    return failed;
}
