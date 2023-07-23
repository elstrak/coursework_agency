#pragma once

#include "TreeRealtors.h"
#include "HashTableRealtors.h"
#include "Parser.h"

using namespace std;


class Realtors {
public:
    Realtors();

    void load_file(const string &file_path);

    void save_to_file(const string &file_path);

    void add(string fio, unsigned long long realtor_phone, int commission, int experience);

    void remove(unsigned long long realtor_phone);

    bool has(unsigned long long realtor_phone);

    Realtor get_realtor_by_realtor_phone(unsigned long long realtor_phone);

    vector<Realtor> get_realtors_higher_experience(int experience);

    vector<Realtor> to_vector();

    string to_string_realtor_phone_table();

    string to_string_experience_tree();

    void clear();

private:
    HashTableRealtors realtor_phone_table;
    TreeRealtors<int, Realtor> experience_tree;
};
