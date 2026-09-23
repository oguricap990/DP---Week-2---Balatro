#include "RandomInputGenerator.hpp"

RandomInputGenerator::RandomInputGenerator()
    : rng_(std::random_device{}()), dist_(1, 6) {}

TurnInput RandomInputGenerator::generate(int /*round*/) {
    return TurnInput{dist_(rng_)};
}
