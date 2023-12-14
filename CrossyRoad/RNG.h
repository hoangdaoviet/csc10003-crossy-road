#pragma once
#include <cstdlib>
#include <random>

int rig(int low, int high) {
    std::mt19937 seed(std::random_device{}());
    std::uniform_int_distribution<int> dist(low, high);
    return dist(seed);
}

float rfg(float low, float high) {
    std::mt19937 seed(std::random_device{}());
    std::uniform_real_distribution<float> dist(low, high);
    return dist(seed);
}