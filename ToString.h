#pragma once

#include <string>
#include "Structures.h"

/**
 * Функции для перевода разных структур в строку
 * Используются при переводе деревьев и хеш-таблиц в строку
 */

string realtor_to_str(Realtor &realtor);

string deal_to_str(Deal &deal);

string dealkey_to_str(DealKey &dealkey);

string date_to_str(Date &date);

string int_to_str(int &num);

string string_to_str(string &s);

string longlong_to_str(unsigned long long &num);
