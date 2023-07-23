#include "Realtors.h"
#include <fstream>
#include "ToString.h"


Realtors::Realtors(): realtor_phone_table(10) {
    this->experience_tree = TreeRealtors<int, Realtor>();
}

void Realtors::add(string fio, unsigned long long realtor_phone, int commission, int experience) {
    Realtor realtor = { fio, realtor_phone, commission, experience };
    this->realtor_phone_table.insert(realtor_phone, realtor);
    this->experience_tree.insert(experience, realtor);
}

void Realtors::remove(unsigned long long realtor_phone) {
    Realtor realtor = this->get_realtor_by_realtor_phone(realtor_phone);
    this->realtor_phone_table.remove(realtor_phone);
    this->experience_tree.remove(realtor.experience, realtor);
}

void Realtors::load_file(const string &file_path) {
    vector<Realtor> realtors = parse_realtors_file(file_path);
    for (Realtor &realtor: realtors) {
        this->add(
            realtor.fio, 
            realtor.realtor_phone, 
            realtor.commission, 
            realtor.experience
        );
    }
}

void Realtors::save_to_file(const string &file_path) {
    ofstream out(file_path);
    vector<Realtor> realtors = this->to_vector();
    for (int i = 0; i < realtors.size(); i++) {
        Realtor realtor = realtors[i];
        out 
            << realtor.fio << ";"
            << realtor.realtor_phone << ";"
            << realtor.commission << ";"
            << realtor.experience;
        if (i != (realtors.size() - 1)) {  // В конце файла не должен стоять \n
            out << "\n";
        }
    }
    out.close();
}

bool Realtors::has(unsigned long long realtor_phone) {
    return this->realtor_phone_table.has(realtor_phone);
}

Realtor Realtors::get_realtor_by_realtor_phone(unsigned long long realtor_phone) {
    return this->realtor_phone_table.get(realtor_phone);
}

vector<Realtor> Realtors::get_realtors_higher_experience(int experience) {
    return this->experience_tree.get_values_higher(experience);
}

vector<Realtor> Realtors::to_vector() {
    return this->realtor_phone_table.get_values();
}

string Realtors::to_string_realtor_phone_table() {
    return this->realtor_phone_table.to_string();
}

string Realtors::to_string_experience_tree() {
    return this->experience_tree.to_string(int_to_str, realtor_to_str);
}
    

void Realtors::clear() {
    this->realtor_phone_table.clear();
    this->experience_tree.clear();
}



