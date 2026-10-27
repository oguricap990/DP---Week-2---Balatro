// ChosenHand.cpp
#include "ChosenHand.h"

bool ChosenHand::selectCard(const Hand& hand, int index)
{
    // index harus valid
    if (index < 0 || index >= static_cast<int>(hand.cards.size()))
        return false;

    // tidak boleh melebihi batas kartu yang boleh dimainkan
    if (isFull())
        return false;

    // tidak boleh memilih kartu yang sama dua kali
    for (int selected : selectedIndices)
    {
        if (selected == index)
            return false;
    }

    selectedIndices.push_back(index);
    cards.push_back(hand.cards[index]);
    return true;
}

bool ChosenHand::deselectCard(int index)
{
    for (std::size_t i = 0; i < selectedIndices.size(); ++i)
    {
        if (selectedIndices[i] == index)
        {
            selectedIndices.erase(selectedIndices.begin() + i);
            cards.erase(cards.begin() + i);
            return true;
        }
    }
    return false;
}

void ChosenHand::clear()
{
    cards.clear();
    selectedIndices.clear();
}

const std::vector<Card>& ChosenHand::getCards() const
{
    return cards;
}

std::size_t ChosenHand::size() const
{
    return cards.size();
}

bool ChosenHand::isEmpty() const
{
    return cards.empty();
}

bool ChosenHand::isFull() const
{
    return cards.size() >= MAX_CARDS;
}
