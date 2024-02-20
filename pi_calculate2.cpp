//
// Created by Егор Кулин on 18.02.2024.
//
#include <iostream>
#include "BigInteger.h"
#include "BigFloat.h"
#include <thread>
#include <mutex>
#include <chrono>

namespace {
    big_num::BigFloat pi = 0_bf;
    big_num::BigFloat one = 1_bf;
    big_num::BigFloat two = 2_bf;
    big_num::BigFloat four = 4_bf;
    big_num::BigFloat sixteen = 16_bf;
    std::mutex pi_mutex;
    std::vector <big_num::BigFloat> powers_of_16;
}
#define THREADS std::thread::hardware_concurrency()

void calculate_member(int i) {
    big_num::BigFloat member = 0_bf;
    big_num::BigFloat first_mem = (four / big_num::BigFloat(4 * i + 1));
    big_num::BigFloat second_mem = (four / big_num::BigFloat(8 * i + 3));
    big_num::BigFloat third_mem = (two / big_num::BigFloat(4 * i + 2));
    big_num::BigFloat fourth_mem = (one / big_num::BigFloat(8 * i + 7));
    big_num::BigFloat fifth_mem = first_mem + second_mem + third_mem - fourth_mem;
    member += fifth_mem / powers_of_16[i];
    pi += member;

}

int main(int argc, char *argv[]) {
    int precision;
    if (argc >= 2) {
        precision = std::stoi(argv[1]);
    } else {
        precision = 100;
    }
    int precision_new = static_cast<int>(static_cast<double>(precision) * 3.33 / CHUNK_SIZE + 1) * CHUNK_SIZE;
    if (precision < THREADS) {
#undef THREADS
#define THREADS precision
    }
    int precision_per_threads = precision / (THREADS - 1);
    std::vector <std::thread> threads;
    int member_num = 0;
    big_num::BigFloat power = 1_bf;
    for (int i = 0; i < precision + precision_per_threads + 5; i++) {
        powers_of_16.push_back(power);
        power *= sixteen;
    }
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < precision; i++) {
        calculate_member(i);
    }
    if (precision == 2) {
        std::cout << "3.14" << std::endl;
    } else {
        std::cout << (pi / 2_bf).ToString(precision) << std::endl;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;
    std::cout << "Time: " << duration.count() << std::endl;
    return 0;
}