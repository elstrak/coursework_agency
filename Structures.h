#pragma once

#include <string>

using namespace std;


struct Date {
    int day;
    int month;
    int year;

    bool operator==(const Date &other) const;

    bool operator!=(const Date &other) const;
};


struct Realtor {
    string fio;
    unsigned long long realtor_phone;
    int commission;
    int experience;
    
    bool operator==(const Realtor &other) const;

    bool operator!=(const Realtor &other) const;
};

struct Deal {
    Date date;
    int price;
    unsigned long long realtor_phone;
    string address;

    bool operator==(const Deal &other) const;

    bool operator!=(const Deal &other) const;
};

struct ReportData {
    string fio;
    unsigned long long realtor_phone;
    int experience;
    Date date;
    int price;
    string address;
};

struct DealKey {
    Date date;
    string address;

    bool operator==(const DealKey &other) const;

    bool operator!=(const DealKey &other) const;
};

enum class AddResult {
    SUCCESS, DUPLICATE, NO_LINKED_REALTOR, PHONE_EXIST
};

enum class RemoveResult {
    SUCCESS, NOT_FOUND, LINKED_DEALS
};



