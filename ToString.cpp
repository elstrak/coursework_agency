#include "ToString.h"

string realtor_to_str(Realtor &realtor) {
    return "(" + 
        string_to_str(realtor.fio) +
        ", " +
        longlong_to_str(realtor.realtor_phone) +
        ", " +
        int_to_str(realtor.commission) +
        ", " +
        int_to_str(realtor.experience) +
 
    ")";
}

string deal_to_str(Deal &deal) {
    return "(" + 
        date_to_str(deal.date) +
        ", " +
        int_to_str(deal.price) +
        ", " +
        longlong_to_str(deal.realtor_phone) +
        ", " +
        string_to_str(deal.address) +
 
    ")";
}

string dealkey_to_str(DealKey &dealkey) {
    return "(" +
        date_to_str(dealkey.date) +
        ", " +
        string_to_str(dealkey.address) +
    ")";
}

string int_to_str(int &num) {
    return std::to_string(num);
}

string string_to_str(string &s) {
    return s;
}

string longlong_to_str(unsigned long long &num) {
    return std::to_string(num);
}

string date_to_str(Date &date) {
    return std::to_string(date.day) + "." + std::to_string(date.month) + "." + std::to_string(date.year);
}
