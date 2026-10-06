#include "GameSession.hpp"
#include <iostream>
#include <string>

using namespace std;

GameSession::GameSession(unique_ptr<IIncomeRule> income,
                          unique_ptr<IUpgradeRule> upgrade,
                          unique_ptr<IEndConditionRule> endCondition)
    : income_(move(income)),
      upgrade_(move(upgrade)),
      endCondition_(move(endCondition)) {}

void GameSession::StartGame() {
    cout << "=== TYCOON START ===\n";
    cout << "Starting money: " << state_.money << "\n";

    while (true) {
        cout << "\nDay " << (state_.day + 1) << "\n";

        // 1. Player does X (memutuskan aksi: upgrade atau tidak)
        PlayerAction();

        // 2. System evaluates Y (hitung income hari ini)
        ResolveSystem();

        // 3. Reward/penalty diberikan + Game state updates
        UpdateState();

        // 4. Check win/lose condition
        if (CheckEndCondition()) break;

        // 5. Repeat (loop while berlanjut ke hari berikutnya)
    }

    cout << "\n=== TYCOON END ===\n";
    cout << "Final money: " << state_.money << " | Days survived: " << state_.day << "\n";
}

void GameSession::PlayerAction() {
    int cost = upgrade_->upgradeCost(state_);
    cout << "[ACTION] upgrade offer: level " << (state_.upgradeLevel + 1)
         << " cost " << cost << " | money: " << state_.money << "\n";

    if (state_.money < cost) {
        cout << "[ACTION] not enough money -> skip upgrade\n";
        pendingUpgradeCost_ = 0;
        return;
    }

    int choice = askChoice();
    if (choice == 1) {
        pendingUpgradeCost_ = cost;
        cout << "[ACTION] upgrade purchased (applied at state update)\n";
    } else {
        pendingUpgradeCost_ = 0;
        cout << "[ACTION] skip upgrade\n";
    }
}

void GameSession::ResolveSystem() {
    pendingIncome_ = income_->computeIncome(state_);
    cout << "[SYSTEM] income today: " << pendingIncome_ << "\n";
}

void GameSession::UpdateState() {
    state_.money += pendingIncome_;
    state_.money -= pendingUpgradeCost_;

    if (pendingUpgradeCost_ > 0) {
        upgrade_->applyUpgrade(state_);
        cout << "[STATE] upgrade level now: " << state_.upgradeLevel << "\n";
    }

    state_.day += 1;
    cout << "[STATE] money: " << state_.money << " | day: " << state_.day << "\n";
}

bool GameSession::CheckEndCondition() {
    EndResult result = endCondition_->check(state_);
    if (result.isOver) {
        cout << "[END] " << result.reason << "\n";
    }
    return result.isOver;
}

int GameSession::askChoice() {
    string line;
    while (true) {
        cout << "  1) Buy upgrade   2) Skip\n> ";
        if (!getline(cin, line)) return 2;  // input habis -> skip
        if (line == "1") return 1;
        if (line == "2") return 2;
        cout << "  Invalid choice.\n";
    }
}
