#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include "Structures.h"
#include "ToString.h"
#include <vector>

class HashTableRealtors {
private:
    int min_size = 8;  // Минимально возможный размер таблицы. Не будет уменьшаться меньше этого значения
    std::vector<unsigned long long> keys;
    std::vector<Realtor> values;
    std::vector<int> status;  // 0 - пусто, 1 - занято, 2 - удалено
    int size;  // Размер массива
    int curr_count;  // Текущее количество элементов в таблице

    int second_hash_function(int first_hash, int try_number);

    void set_new_size(int new_size);

    int get_index_status(int i);

    void check_filling();

    int get_index(const unsigned long long & key);

public:
    HashTableRealtors(int size);

    void insert(const unsigned long long &key, const Realtor &value, bool check_filling = true);

    void remove(const unsigned long long &key);

    Realtor get(const unsigned long long &key);

    bool has(const unsigned long long &key);

    int get_size();

    int get_count();

    int first_hash_function(unsigned long long key);

    void clear();

    std::string to_string();

    std::vector<Realtor> get_values();
};

int num_len(unsigned long long num);

unsigned long long get_middle_digits(unsigned long long number, int digits_count);

