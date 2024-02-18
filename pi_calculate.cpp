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
    std::mutex pi_mutex;
    std::vector <big_num::BigFloat> powers_of_16;
}
#define THREADS std::thread::hardware_concurrency()

void calculate_member(int first_, int second_) {
    big_num::BigFloat member = 0_bf;
    for (int i = first_; i < second_; i++) {
        member += (4_bf / (4 * i + 1) + 4_bf / (8 * i + 3) + 2_bf / (4 * i + 2) - 1_bf / (8 * i + 7)) / powers_of_16[i];
    }
    std::lock_guard <std::mutex> lock(pi_mutex);
    pi += member;
}

int main(int argc, char *argv[]) {
    int precision = std::stoi(argv[1]);
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
        power *= 16_bf;
    }
    for (int i = 0; i < THREADS; i++) {
        threads[i].join();
    }
    std::cout << pi / 2_bf << std::endl;
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;
    std::cout << "Time: " << duration.count() << std::endl;
    return 0;
}