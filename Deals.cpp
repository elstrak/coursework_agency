#include "Deals.h"
#include <string>
#include "ToString.h"

Deals::Deals(): deal_table(10) {
    this->price_tree = TreeDeals<int, Deal>();
    this->realtor_phone_tree = TreeDeals<unsigned long long, Deal>();
}

void Deals::add(Date date, int price, unsigned long long realtor_phone, string address) {
    Deal deal = { date, price, realtor_phone, address };
    this->price_tree.insert(price, deal);
    this->realtor_phone_tree.insert(realtor_phone, deal);
    this->deal_table.insert({date, address}, deal);
}

void Deals::remove(Date date, string address) {
    Deal deal = this->get(date, address);
    this->price_tree.remove(deal.price, deal);
    this->realtor_phone_tree.remove(deal.realtor_phone, deal);
    this->deal_table.remove({deal.date, deal.address});
}

void Deals::remove_by_realtor_phone(unsigned long long realtor_phone) {
    vector<Deal> deals = get_deals_by_realtor_phone(realtor_phone);
    for (Deal deal: deals) {
        this->remove(
            deal.date, 
            deal.address
        );
    }
}

bool Deals::has(Date date, string address) {
    return this->deal_table.has({date, address});
}

bool Deals::has_realtor(unsigned long long realtor_phone) {
    return this->realtor_phone_tree.has(realtor_phone);
}

Deal Deals::get(Date date, string address) {
    return this->deal_table.get({date, address});
}

vector<Deal> Deals::get_deals_lower_price(int price) {
    return this->price_tree.get_values_lower(price);
}

vector<Deal> Deals::get_deals_by_realtor_phone(unsigned long long realtor_phone) {
    if (this->realtor_phone_tree.has(realtor_phone)) {
        return this->realtor_phone_tree.find(realtor_phone)->chain.to_vector();
    } else {
        return {};
    }
}

vector<Deal> Deals::get_deals(Date date, string address) {
    DealKey key = {date, address};
    if (this->deal_table.has(key)) {
        return {this->deal_table.get(key)};
    } else {
        return {};
    }
}


void Deals::load_file(const string &file_path) {
    vector<Deal> deals = parse_deals_file(file_path);
    for (Deal &deal: deals) {
        this->add(
            deal.date, 
            deal.price, 
            deal.realtor_phone, 
            deal.address
        );
    }
}

void Deals::save_to_file(const string &file_path) {
    ofstream out(file_path);
    vector<Deal> deals = this->to_vector();
    for (int i = 0; i < deals.size(); i++) {
        Deal deal = deals[i];
        out 
            << deal.date.day << "/" << deal.date.month << "/" << deal.date.year << ";"
            << deal.price << ";"
            << deal.realtor_phone << ";"
            << deal.address;
        if (i != (deals.size() - 1)) {  // В конце файла не должен стоять \n
            out << "\n";
        }
    }
    out.close();
}


vector<Deal> Deals::to_vector() {
    return this->realtor_phone_tree.to_vector();
}

string Deals::to_string_price_tree() {
    return this->price_tree.to_string(int_to_str, deal_to_str);
}
string Deals::to_string_realtor_phone_tree() {
    return this->realtor_phone_tree.to_string(longlong_to_str, deal_to_str);
}
    
string Deals::to_string_deal_table() {
    return this->deal_table.to_string();
}


void Deals::clear() {
    this->price_tree.clear();
    this->realtor_phone_tree.clear();
    this->deal_table.clear();
}

