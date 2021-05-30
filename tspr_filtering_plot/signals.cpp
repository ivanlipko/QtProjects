#include "signals.h"

/*
 * Генерация исходного чистого сигнала.
 * Лучше использовать несколько синусоид или прямоугольный сигнал.
*/
void generate(std::array<int, LENGTH> &a){
    for(unsigned int i=0; i < a.size(); i++){
//        a[i] = sin(i) + sin(2*i);
        // a[i] = sin(0.1 * i) + sin(2.0*i+0.5);
        a[i] = 500.0 * sin(0.01*i) + 500.0 * sin(0.05*i);
    }
}

/*
 * Добавляем шум
 * Чаще всего это аддитивный (additive -- добавить) шум. Но можно и скачкообразные шумы использовать
*/
void addNoise(const std::array<int, LENGTH> in, std::array<int, LENGTH> &out){
    for(unsigned int i=0; i < in.size(); i++){
        out[i] = in[i] + rand() % 150 - 75;
    }
}

// Алгоритм фильтрации: экспоненциальное
float filtavg_K = 0.9;
float filtavg(float in){
    static float val = 0;
    val = filtavg_K*val + (1.0-filtavg_K)*in;
    return val;
}


/*  Фильтрация всего массива данных
*/
void filtrate(const std::array<int, LENGTH> in, std::array<int, LENGTH> &out){
    for(unsigned int i=0; i < in.size(); i++){
        out[i] = filtavg(in[i]);
    }
}

