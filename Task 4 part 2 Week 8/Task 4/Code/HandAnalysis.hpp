#pragma once
#include <algorithm>
#include <cstddef>
#include <functional>
#include <map>
#include <vector>
#include "Card.hpp"

// Menganalisis kartu SATU kali, supaya tiap checker cukup bertanya
// "apakah ini flush?", "berapa kartu kembar terbanyak?", dst.
class HandAnalysis {
public:
    static constexpr std::size_t FULL_HAND = 5; // flush/straight hanya berlaku untuk 5 kartu

    explicit HandAnalysis(const std::vector<Card>& cards) : size_(cards.size()) {
        std::map<int, int> rankCount;
        for (const Card& c : cards) rankCount[c.rank]++;

        for (const auto& e : rankCount) counts_.push_back(e.second);
        std::sort(counts_.begin(), counts_.end(), std::greater<int>());

        if (rankCount.empty()) return;
        lowest_ = rankCount.begin()->first;

        if (size_ == FULL_HAND) {
            flush_ = std::all_of(cards.begin(), cards.end(),
                                 [&](const Card& c) { return c.suit == cards[0].suit; });

            if (rankCount.size() == FULL_HAND) { // 5 rank berbeda
                int highest = rankCount.rbegin()->first;
                bool normal = (highest - lowest_ == 4);
                bool wheel  = (lowest_ == 2 && highest == 14 && (++rankCount.begin())->first == 3
                               && (++++rankCount.begin())->first == 4
                               && (++++++rankCount.begin())->first == 5); // A 2 3 4 5
                straight_ = normal || wheel;
            }
        }
    }

    std::size_t size()        const { return size_; }
    int  topCount()           const { return counts_.empty() ? 0 : counts_[0]; }
    int  secondCount()        const { return counts_.size() < 2 ? 0 : counts_[1]; }
    bool isFlush()            const { return flush_; }
    bool isStraight()         const { return straight_; }
    int  lowestRank()         const { return lowest_; }

private:
    std::size_t      size_;
    std::vector<int> counts_;   // jumlah kemunculan tiap rank, besar -> kecil
    bool flush_    = false;
    bool straight_ = false;
    int  lowest_   = 0;
};
