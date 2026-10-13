#pragma once

// Urutan dari lemah ke kuat (dipakai untuk konversi skor).
enum class HandRank {
    HighCard,
    Pair,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush,
    FiveOfAKind,
    FlushHouse,
    FlushFive,
    Unknown // rantai habis, tidak ada checker yang cocok
};

// Hand versi dummy.
// Tugas ini tidak butuh logic asli, jadi Hand hanya membawa "jenis hand"
// buatan supaya alur chain bisa didemokan.
// TODO (nanti): ganti dengan daftar kartu (rank + suit) yang sebenarnya.
struct Hand {
    HandRank dummyRank = HandRank::HighCard;
};
