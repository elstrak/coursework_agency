#include "Database.h"

Database::Database() {
    this->realtors = Realtors();
    this->deals = Deals();
}

/**
 * SUCCESS - добавление успешно
 * DUPLICATE - запись уже есть в БД
 */
AddResult Database::add_realtor(string fio, unsigned long long realtor_phone, int commission, int experience) {
    if (this->realtors.has(realtor_phone)) {
        return AddResult::DUPLICATE;
    } else {
        this->realtors.add(fio, realtor_phone, commission, experience);
        return AddResult::SUCCESS;
    }
}

/**
 * SUCCESS - Успех. Добавление успешно
 * DUPLICATE - Такая запись уже существует
 * NO_LINKED_REALTOR - Нет такого риэлтора
 */
AddResult Database::add_deal(Date date, int price, unsigned long long realtor_phone, string address) {
    if (this->deals.has(date, address)) {
        return AddResult::DUPLICATE;
    }
    if (this->realtors.has(realtor_phone)) {
        this->deals.add(date, price, realtor_phone, address);
        return AddResult::SUCCESS;
    } else {
        return AddResult::NO_LINKED_REALTOR;
    }
}

/**
 * check_linked_data - если True, то если найдёт связанные записи, сообщит об этом и не будет удалять. Если False, то удалит все связанные записи
 * SUCCESS - Успех. Удаление успешно
 * NOT_FOUND - Запись не найдена
 * LINKED_DEALS - Есть связанные сделки
 */
RemoveResult Database::remove_realtor(unsigned long long realtor_phone, bool check_linked_data) {
    if (this->realtors.has(realtor_phone)) {
        if (this->deals.has_realtor(realtor_phone)) {  // Есть связанные данные в другом справочнике
            if (check_linked_data) {
                return RemoveResult::LINKED_DEALS;
            } else {
                this->deals.remove_by_realtor_phone(realtor_phone);
                return RemoveResult::SUCCESS;
            }
        } else {
            this->realtors.remove(realtor_phone);
            return RemoveResult::SUCCESS;
        }
    } else {
        return RemoveResult::NOT_FOUND;
    }
}

/**
 * SUCCESS - удаление успешно
 * NOT_FOUND - запись не найдена
 */
RemoveResult Database::remove_deal(Date date, string address) {
    if (this->deals.has(date, address)) {
        this->deals.remove(date, address);
        return RemoveResult::SUCCESS;
    } else {
        return RemoveResult::NOT_FOUND;
    }
}

void Database::load_realtors_file(const string &file_path) {
    this->realtors.clear();  // Обнуляем справочник, чтобы значения не добавлялись к прошлым
    this->realtors.load_file(file_path);
}

void Database::load_deals_file(const string &file_path) {
    this->deals.clear();  // Обнуляем справочник, чтобы значения не добавлялись к прошлым
    this->deals.load_file(file_path);
}

void Database::save_realtors_to_file(const string &file_path) {
    this->realtors.save_to_file(file_path);
}

void Database::save_deals_to_file(const string &file_path) {
    this->deals.save_to_file(file_path);
}

string Database::to_string_realtors_realtor_phone_table() {
    return this->realtors.to_string_realtor_phone_table();
}
string Database::to_string_realtors_experience_tree() {
    return this->realtors.to_string_experience_tree();
}


string Database::to_string_deals_realtor_phone_tree() {
    return this->deals.to_string_realtor_phone_tree();
}

string Database::to_string_deals_table() {
    return this->deals.to_string_deal_table();
}

vector<ReportData> Database::search(int experience, int price) {
    vector<ReportData> result = {};
    vector<Deal> deals = this->deals.get_deals_lower_price(price);
    for (Deal &deal: deals) {
        Realtor realtor = this->realtors.get_realtor_by_realtor_phone(deal.realtor_phone);
        if (realtor.experience >= experience) {
            ReportData info = {
                realtor.fio,
                realtor.realtor_phone,
                realtor.experience,
                deal.date,
                deal.price,
                deal.address
            };
            result.push_back(info);
        }
    }
    return result;
}

/**
 * Производит поиск по параметрам и переводит его в красивую форму в строке
 */
string Database::search_to_string(int experience, int price) {
    string result = "";
    vector<ReportData> search_result = this->search(experience, price);
    for (ReportData &info: search_result) {
        result += "";
    }
    return result;
}

vector<Realtor> Database::find_realtors_by_realtor_phone(unsigned long long realtor_phone) {
    if (this->realtors.has(realtor_phone)) {
        return {this->realtors.get_realtor_by_realtor_phone(realtor_phone)};
    } else {
        return {};
    }
}

vector<Realtor> Database::find_realtors_higher_experience(int experience) {
    return this->realtors.get_realtors_higher_experience(experience);
}


vector<Deal> Database::find_deals_lower_price(int price) {
    return this->deals.get_deals_lower_price(price);
}

vector<Deal> Database::find_deals_by_realtor_phone(unsigned long long realtor_phone) {
    return this->deals.get_deals_by_realtor_phone(realtor_phone);
}

vector<Deal> Database::find_deals_by_key(Date date, string address) {
    return this->deals.get_deals(date, address);
}

vector<Realtor> Database::get_all_realtors() {
    return this->realtors.to_vector();
}

vector<Deal> Database::get_all_deals() {
    return this->deals.to_vector();
}
