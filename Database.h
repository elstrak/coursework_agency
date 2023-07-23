#pragma once

#include "Realtors.h"
#include "Deals.h"
#include <string>

class Database {
public:
    Database();

    void load_realtors_file(const string &file_path);

    void load_deals_file(const string &file_path);

    void save_realtors_to_file(const string &file_path);

    void save_deals_to_file(const string &file_path);

    AddResult add_realtor(string fio, unsigned long long realtor_phone, int commission, int experience);

    AddResult add_deal(Date date, int price, unsigned long long realtor_phone, string address);

    RemoveResult remove_realtor(unsigned long long realtor_phone, bool check_linked_data);

    RemoveResult remove_deal(Date date, string address);

    vector<Realtor> get_all_realtors();

    vector<Deal> get_all_deals();

    string to_string_realtors_realtor_phone_table();
    string to_string_realtors_experience_tree();

    string to_string_deals_price_tree();
    string to_string_deals_realtor_phone_tree();
    string to_string_deals_table();

    // Задачи поиска:

    vector<ReportData> search(int experience, int price);

    string search_to_string(int experience, int price);

    vector<Realtor> find_realtors_by_realtor_phone(unsigned long long realtor_phone);
    vector<Realtor> find_realtors_higher_experience(int experience);

    vector<Deal> find_deals_lower_price(int price);
    vector<Deal> find_deals_by_realtor_phone(unsigned long long realtor_phone);
    vector<Deal> find_deals_by_key(Date date, string address);

private:
    Realtors realtors;
    Deals deals;
};
