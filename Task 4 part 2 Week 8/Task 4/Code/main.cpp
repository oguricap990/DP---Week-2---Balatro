#include <cstring>
#include "GameManager.hpp"

// Jalankan biasa      : ./game        (kartu dipilih otomatis)
// Pilih kartu sendiri : ./game -i
int main(int argc, char** argv) {
    bool interactive = (argc > 1 && std::strcmp(argv[1], "-i") == 0);

    GameManager game(interactive);
    game.runSession();
    return 0;
}
