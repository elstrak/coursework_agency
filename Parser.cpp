#include "Parser.h"

using namespace std;

vector<string> split(const string &s, const string &delim) {
    // Разбивает строку по разделителю delim
    vector<string> result = {};
    unsigned int start = 0;
    unsigned int end = s.find(delim);
    while (end != -1) {
        result.push_back(
                s.substr(start, end - start)
        );
        start = end + delim.size();
        end = s.find(delim, start);
    }
    result.push_back(s.substr(start, end - start));
    return result;
}


vector<Realtor> parse_realtors_file(const string &file_path) {
    string delimiter = ";";  // Разделитель, по которому разделяем файл
    vector<Realtor> result = {};
    ifstream inp(file_path);
    if (!inp) {  // Проверяем существование файла
        throw runtime_error("Error: File not exist");
    }
    string line;
    vector<string> split_line;
    while (getline(inp, line)) {  // Построчно читаем файл
        split_line = split(line, delimiter);
        Realtor realtor;
        realtor.fio = split_line[0];
        realtor.realtor_phone = stoull(split_line[1]);
        realtor.commission = stoi(split_line[2]);
        realtor.experience = stoi(split_line[3]);
        result.push_back(realtor);
    }
    inp.close();
    return result;
}

vector<Deal> parse_deals_file(const string &file_path) {
    string delimiter = ";";  // Разделитель, по которому разделяем файл
    vector<Deal> result = {};
    ifstream inp(file_path);
    if (!inp) {  // Проверяем существование файла
        throw runtime_error("Error: File not exist");
    }
    string line;
    vector<string> split_line;
    while (getline(inp, line)) {  // Построчно читаем файл
        split_line = split(line, delimiter);
        Deal deal;

        auto split_date = split(split_line[0], "/");
        deal.date = {
            stoi(split_date[0]),
            stoi(split_date[1]),
            stoi(split_date[2]),
        };

        deal.price = stoi(split_line[1]);
        deal.realtor_phone = stoull(split_line[2]);
        deal.address = split_line[3];
        result.push_back(deal);
    }
    inp.close();
    return result;
}
