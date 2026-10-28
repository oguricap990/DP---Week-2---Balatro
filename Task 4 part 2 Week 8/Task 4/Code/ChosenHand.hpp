#pragma once
#include <cstddef>
#include <vector>
#include "Card.hpp"
#include "Hand.hpp"

// Tugas 1: kartu yang DIPILIH pemain dari Hand (maksimal 5).
class ChosenHand {
public:
    static constexpr std::size_t MAX_CARDS = 5;

    // Pilih kartu dari hand berdasarkan index (0-based).
    // false jika index salah, kartu sudah dipilih, atau sudah penuh.
    bool selectCard(const Hand& hand, int index) {
        if (index < 0 || index >= static_cast<int>(hand.cards.size())) return false;
        if (isFull()) return false;
        for (int selected : selectedIndices) {
            if (selected == index) return false;
        }
        selectedIndices.push_back(index);
        cards.push_back(hand.cards[index]);
        return true;
    }

    // Batalkan pilihan berdasarkan index kartu di hand.
    bool deselectCard(int index) {
        for (std::size_t i = 0; i < selectedIndices.size(); ++i) {
            if (selectedIndices[i] == index) {
                selectedIndices.erase(selectedIndices.begin() + i);
                cards.erase(cards.begin() + i);
                return true;
            }
        }
        return false;
    }

    void clear() { cards.clear(); selectedIndices.clear(); }

    const std::vector<Card>& getCards() const { return cards; }
    std::size_t size()    const { return cards.size(); }
    bool        isEmpty() const { return cards.empty(); }
    bool        isFull()  const { return cards.size() >= MAX_CARDS; }

    // Jembatan ke rantai checker, yang bekerja dengan Hand.
    Hand toHand() const { Hand h; h.cards = cards; return h; }

private:
    std::vector<Card> cards;
    std::vector<int>  selectedIndices; // index asal di Hand, mencegah pilih kartu yang sama 2x
};
