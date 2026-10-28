#pragma once
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include "ChosenHand.hpp"
#include "Hand.hpp"

// Tugas 3: hand acak, tanpa kartu kembar (diambil dari 1 deck 52 kartu).
class HandGenerator {
public:
    HandGenerator() : rng(std::random_device{}()) {}

    Hand generateHand(int handSize = 5) {
        std::cout << "Generating hand...\n";

        std::vector<Card> deck = createDeck();
        std::shuffle(deck.begin(), deck.end(), rng);

        handSize = std::max(0, std::min(handSize, static_cast<int>(deck.size())));

        Hand hand;
        hand.cards.assign(deck.begin(), deck.begin() + handSize);
        return hand;
    }

private:
    std::vector<Card> createDeck() const {
        const char suits[] = { 'H', 'D', 'C', 'S' };
        std::vector<Card> deck;
        for (char suit : suits)
            for (int rank = 2; rank <= 14; ++rank)
                deck.push_back({ rank, suit });
        return deck; // 52 kartu
    }

    std::mt19937 rng;
};

// Pemain memilih kartu dari hand -> hasilnya ChosenHand.
// interactive = true : pemain mengetik nomor kartu.
// interactive = false: dipilih acak otomatis (untuk demo / testing).
class HandPlayer {
public:
    explicit HandPlayer(bool interactive = false)
        : interactive(interactive), rng(std::random_device{}()) {}

    ChosenHand playHand(const Hand& hand) {
        std::cout << "Your hand:\n";
        for (std::size_t i = 0; i < hand.cards.size(); ++i)
            std::cout << "  [" << i + 1 << "] " << toString(hand.cards[i]) << "\n";

        ChosenHand chosen;
        if (interactive) selectInteractively(hand, chosen);
        if (chosen.isEmpty()) selectRandomly(hand, chosen); // non-interaktif, atau input kosong/EOF

        std::cout << "Played:";
        for (const Card& c : chosen.getCards()) std::cout << " " << toString(c);
        std::cout << "\n";
        return chosen;
    }

private:
    void selectInteractively(const Hand& hand, ChosenHand& chosen) {
        std::cout << "Pilih 1-" << ChosenHand::MAX_CARDS
                  << " kartu (ketik nomor, pisah spasi): ";
        std::string line;
        if (!std::getline(std::cin, line)) return;

        std::istringstream in(line);
        int n;
        while (in >> n) {
            if (!chosen.selectCard(hand, n - 1))
                std::cout << "  (kartu " << n << " ditolak)\n";
        }
    }

    void selectRandomly(const Hand& hand, ChosenHand& chosen) {
        std::vector<int> indices(hand.cards.size());
        std::iota(indices.begin(), indices.end(), 0);
        std::shuffle(indices.begin(), indices.end(), rng);
        for (int index : indices) {
            if (!chosen.selectCard(hand, index)) break; // berhenti saat sudah penuh
        }
    }

    bool         interactive;
    std::mt19937 rng;
};
