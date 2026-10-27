// PokerHandChecker.cpp
#include "PokerHandChecker.h"
#include <algorithm>
#include <map>

PokerHand PokerHandChecker::check(const ChosenHand& chosenHand) const
{
    return check(chosenHand.getCards());
}

PokerHand PokerHandChecker::check(const std::vector<Card>& cards) const
{
    if (cards.empty())
        return PokerHand::None;

    // 1. Hitung berapa kali tiap rank muncul, lalu urutkan jumlahnya dari besar ke kecil.
    //    Contoh Full House (K K K 5 5)  -> counts = {3, 2}
    //    Contoh Two Pair   (K K 5 5 9)  -> counts = {2, 2, 1}
    std::map<int, int> rankCount;
    for (const Card& card : cards)
        rankCount[card.rank]++;

    std::vector<int> counts;
    for (const auto& entry : rankCount)
        counts.push_back(entry.second);
    std::sort(counts.begin(), counts.end(), std::greater<int>());

    // 2. Flush dan Straight hanya berlaku jika ada 5 kartu.
    const bool flush    = isFlush(cards);
    const bool straight = isStraight(cards);

    if (straight && flush)
    {
        int minRank = 100;
        for (const Card& card : cards)
            minRank = std::min(minRank, card.rank);

        // 10 J Q K A satu jenis = Royal Flush
        if (minRank == 10)
            return PokerHand::RoyalFlush;
        return PokerHand::StraightFlush;
    }

    // 3. Kombinasi berdasarkan jumlah rank yang sama (urutan dari yang tertinggi).
    if (counts[0] == 4)
        return PokerHand::FourOfAKind;

    if (counts[0] == 3 && counts.size() > 1 && counts[1] == 2)
        return PokerHand::FullHouse;

    if (flush)
        return PokerHand::Flush;

    if (straight)
        return PokerHand::Straight;

    if (counts[0] == 3)
        return PokerHand::ThreeOfAKind;

    if (counts[0] == 2 && counts.size() > 1 && counts[1] == 2)
        return PokerHand::TwoPair;

    if (counts[0] == 2)
        return PokerHand::Pair;

    return PokerHand::HighCard;
}

bool PokerHandChecker::isFlush(const std::vector<Card>& cards) const
{
    if (cards.size() != 5)
        return false;

    for (const Card& card : cards)
    {
        if (card.suit != cards[0].suit)
            return false;
    }
    return true;
}

bool PokerHandChecker::isStraight(const std::vector<Card>& cards) const
{
    if (cards.size() != 5)
        return false;

    std::vector<int> ranks;
    for (const Card& card : cards)
        ranks.push_back(card.rank);
    std::sort(ranks.begin(), ranks.end());

    // Rank tidak boleh ada yang sama
    for (std::size_t i = 1; i < ranks.size(); ++i)
    {
        if (ranks[i] == ranks[i - 1])
            return false;
    }

    // Kasus biasa: 5 angka berurutan (contoh 6 7 8 9 10)
    if (ranks[4] - ranks[0] == 4)
        return true;

    // Kasus khusus: A 2 3 4 5 (Ace dianggap bernilai 1)
    if (ranks[0] == 2 && ranks[1] == 3 && ranks[2] == 4 && ranks[3] == 5 && ranks[4] == 14)
        return true;

    return false;
}
