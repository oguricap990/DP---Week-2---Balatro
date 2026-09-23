#pragma once
#include "GameTypes.hpp"

// Mencetak tawaran shop dan (opsional) menyimpan efek pembelian ke RunState.
// Tidak mengubah money secara langsung; pembayaran terjadi di fase
// Update money pada round berikutnya (di dalam RunSession).
class ShopSystem {
public:
    void run(RunState& state, bool canBuy) const;

private:
    static int askChoice();
};
