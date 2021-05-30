#ifndef SIGNALS_H
#define SIGNALS_H

#include <array>
#include <cmath>

#define LENGTH 1000
extern float filtavg_K;

void generate(std::array<int, LENGTH> &a);
void addNoise(const std::array<int, LENGTH> in, std::array<int, LENGTH> &out);
void filtrate(const std::array<int, LENGTH> in, std::array<int, LENGTH> &out);

#endif // SIGNALS_H
