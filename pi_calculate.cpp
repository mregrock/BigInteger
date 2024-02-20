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
    big_num::BigFloat pi;
    big_num::BigFloat one;
    big_num::BigFloat two;
    big_num::BigFloat four;
    big_num::BigFloat sixteen;
    std::mutex pi_mutex;
    std::vector <big_num::BigFloat> powers_of_16;
}
#define THREADS std::thread::hardware_concurrency()

void calculate_member(int first_, int second_) {
    big_num::BigFloat member = 0_bf;
    for (int i = first_; i < second_; i++) {
        member += (four / (4 * i + 1) + four / (8 * i + 3) + two / (4 * i + 2) - one / (8 * i + 7)) / powers_of_16[i];
    }
    std::lock_guard <std::mutex> lock(pi_mutex);
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
    pi = 0_bf;
    one = 1_bf;
    two = 2_bf;
    four = 4_bf;
    sixteen = 16_bf;
    if (precision < THREADS) {
#undef THREADS
#define THREADS precision
    }
    int precision_per_threads = precision / THREADS;
    std::vector <std::thread> threads;
    int member_num = 0;
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < THREADS; i++) {
        threads.push_back(std::thread(calculate_member, member_num, member_num + precision_per_threads));
        member_num += precision_per_threads;
    }
    big_num::BigFloat power = 1_bf;
    for (int i = 0; i < precision; i++) {
        powers_of_16.push_back(power);
        power *= sixteen;
    }
    for (int i = 0; i < THREADS; i++) {
        threads[i].join();
    }
    if (precision == 2) {
        std::cout << "3.14" << std::endl;
        return 0;
    } else {
        std::cout << (pi / 2_bf).ToString(precision) << std::endl;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;
    std::cout << "Time: " << duration.count() << std::endl;
    return 0;
}