#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "Structures.h"

using namespace std;

vector<string> split(const string &s, const string &delim);

vector<Realtor> parse_realtors_file(const string &file_path);

vector<Deal> parse_deals_file(const string &file_path);