// ChosenHand.h
// Soal 1: class untuk kartu yang DIPILIH pemain dari Hand.
#pragma once
#include <cstddef>
#include <vector>
#include "Card.h"
#include "Hand.h"

class ChosenHand
{
public:
    static const std::size_t MAX_CARDS = 5;

    // Pilih kartu dari hand berdasarkan index (0-based).
    // Return false jika index salah, kartu sudah dipilih, atau sudah penuh.
    bool selectCard(const Hand& hand, int index);

    // Batalkan pilihan kartu dari hand berdasarkan index di hand.
    // Return false jika kartu itu memang belum dipilih.
    bool deselectCard(int index);

    // Kosongkan semua pilihan.
    void clear();

    const std::vector<Card>& getCards() const;
    std::size_t size() const;
    bool isEmpty() const;
    bool isFull() const;

private:
    std::vector<Card> cards;
    std::vector<int>  selectedIndices; // index asal kartu di Hand, mencegah pilih kartu yang sama 2x
};
