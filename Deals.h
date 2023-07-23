#pragma once

#include <string>
#include "TreeDeals.h"
#include "HashTableDeals.h"
#include "Parser.h"

using namespace std;

class Deals {
public:
    Deals();

    void load_file(const string &file_path);

    void save_to_file(const string &file_path);

    void add(Date date, int price, unsigned long long realtor_phone, string address);

    void remove(Date date, string address);

    void remove_by_realtor_phone(unsigned long long realtor_phone);

    bool has(Date date, string address);

    bool has_realtor(unsigned long long realtor_phone);

    Deal get(Date date, string address);

    vector<Deal> get_deals_lower_price(int price);
    vector<Deal> get_deals_by_realtor_phone(unsigned long long realtor_phone);
    vector<Deal> get_deals(Date date, string address);

    vector<Deal> to_vector();

    string to_string_price_tree();
    string to_string_realtor_phone_tree();
    string to_string_deal_table();

    void clear();

private:
    TreeDeals<int, Deal> price_tree;
    TreeDeals<unsigned long long, Deal> realtor_phone_tree;
    HashTableDeals deal_table;
};
