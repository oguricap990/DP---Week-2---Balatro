#pragma once

// ---------------------------------------------------------------
// Data dasar yang dipakai bersama oleh seluruh sistem.
// ---------------------------------------------------------------
struct TurnInput {
    int value;
};

struct RunState {
    int money = 0;
    int bonus = 0;        // efek item shop: tambahan uang tiap round
    int pendingCost = 0;  // biaya item shop, dipotong di fase Update money round berikutnya
};
