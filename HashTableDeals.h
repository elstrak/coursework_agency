#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include "Structures.h"
#include "ToString.h"
#include <vector>

unsigned int str_to_hash(const std::string& str);

unsigned int roundUp2(unsigned int v);

class HashTableDeals {
private:
    int min_size = 8;  // Минимально возможный размер таблицы. Не будет уменьшаться меньше этого значения
    std::vector<DealKey> keys;
    std::vector<Deal> values;
    std::vector<int> status;  // 0 - пусто, 1 - занято, 2 - удалено
    int size;  // Размер массива. Всегда является степенью двойки
    int curr_count;  // Текущее количество элементов в таблице

    unsigned int primary_hash(DealKey key);

    int probing(const DealKey &obj, int try_number);

    int find_free_index(const DealKey &key);

    void set_new_size(int new_size);

    int get_index(const DealKey &key);

    int get_index_status(int i);

    void check_filling();

public:
    HashTableDeals(unsigned int size);

    void insert(const DealKey &key, const Deal &value, bool check_filling = true);

    Deal get(const DealKey &key);

    bool has(const DealKey &key);

    void remove(const DealKey &key);

    int get_size();

    int get_count();

    std::string to_string();

    std::vector<Deal> get_values();

    void clear();
};




