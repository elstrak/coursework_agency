#include "HashTableRealtors.h"

int num_len(unsigned long long num) {
    // Возвращает количество цифр в числе
    if (num == 0)
        return 1;
    int count = 0;
    while (num != 0) {
        count += 1;
        num /= 10;
    }
    return count;
}

unsigned long long get_middle_digits(unsigned long long number, int digits_count) {
    // Берёт из числа number digits_count средних цифр
    int n = num_len(number);
    int right_offset = (n - digits_count) / 2;  // На сколько средняя часть сдвинута от правой стороны числа
    for (int i = 0; i < right_offset; i++) {  // Убираем right_offset цифр справа
        number /= 10;
    }
    unsigned long long result = 0;
    unsigned long long rank = 1;
    for (int i = 0; i < digits_count; i++) {  // Берём digits_count цифр из number
        unsigned long long digit = number % 10;
        number /= 10;
        result += digit * rank;
        rank *= 10;
    }
    return result;
}

HashTableRealtors::HashTableRealtors(int size) {
    this->size = size;
    this->curr_count = 0;
    this->keys = std::vector<unsigned long long>(this->size);
    this->values = std::vector<Realtor>(this->size);
    this->status = std::vector<int>(this->size, 0);
}

int HashTableRealtors::first_hash_function(unsigned long long key) {
    /**
     * Вычисляет хеш-функцию методом середины квадрата
     * Установить флаг log в true, чтобы выводить в консоль промежуточные шаги
     */
    unsigned long long hash = key;
    unsigned long long hash_sq = hash * hash;
    int mid_dig_count = num_len(hash_sq) / 2;
    if (mid_dig_count == 0) { mid_dig_count = 1; }  // Нельзя, чтобы мы брали 0 цифр
    unsigned long long mid_digits = get_middle_digits(hash_sq, mid_dig_count);
    //std::cout << "h(" << key << ") = " << key << " ^ 2 mod 2^64 = " << hash_sq << " => " << mid_digits << " mod " << this->size << " = " << mid_digits % this->size << "\n";
    return mid_digits % this->size;
}

int HashTableRealtors::second_hash_function(int first_hash, int try_number) {
    // Линейное пробирование
    return (first_hash + try_number) % this->size;
}

void HashTableRealtors::insert(const unsigned long long &key, const Realtor &value, bool check_filling) {
    /*
     * Вставляет значение key и значение value в хеш таблицу
     * Если check_filling = true, то будет проверять, нужно ли увеличивать / уменьшать таблицу
     */
    int index;

    int first_hash = this->first_hash_function(key);
    if (this->get_index_status(first_hash) == 1 && this->keys[first_hash] == key
        || this->get_index_status(first_hash) == 0) {  // Если есть возможность вставить на первичном хеше
        index = first_hash;
    } else {  // Иначе разрешаем коллизию
        index = this->get_index(key);
    }

    if (this->get_index_status(index) == 0) {
        this->curr_count++;
    }
    this->status[index] = 1;
    this->keys[index] = key;
    this->values[index] = value;
    if (check_filling) {  // Проверяем заполненность таблицы
        this->check_filling();
    }
}

int HashTableRealtors::get_index_status(int i) {
    return this->status[i];
}

void HashTableRealtors::set_new_size(int new_size) {
    auto old_keys = this->keys;
    auto old_values = this->values;
    auto old_status = this->status;
    int old_max = this->size;

    // Создаём новые массивы таблицы
    this->keys = std::vector<unsigned long long>(new_size);
    this->values = std::vector<Realtor>(new_size);
    this->status = std::vector<int>(new_size, 0);
    this->size = new_size;
    this->curr_count = 0;

    // Переносим все данные с прошлой таблицы в новую
    for (int i = 0; i < old_max; i++) {
        if (old_status[i] == 1) {  // Добавляем только если ячейка существует
            this->insert(old_keys[i], old_values[i], false);
        }
    }
}

bool HashTableRealtors::has(const unsigned long long &key) {
    int index = this->get_index(key);
    if (this->get_index_status(index) == 1 && this->keys[index] == key) {
        return true;
    }
    return false;
}

Realtor HashTableRealtors::get(const unsigned long long &key) {
    int index = this->get_index(key);
    if (this->get_index_status(index) == 1 && this->keys[index] == key) {
        return this->values[index];
    }
    throw std::runtime_error("Error: key does not exist");
}

void HashTableRealtors::check_filling() {
    // Проверяет заполненность таблицы.
    // Если заполненность более 75%, то увеличивает таблицу.
    // Если заполненность менее 25%, то уменьшает таблицу.
    double fill_coefficient = double(this->curr_count) / double(this->size);
    if (fill_coefficient < 0.25 && this->size > this->min_size) {
        this->set_new_size(this->size / 2);
    } else if (fill_coefficient > 0.75) {
        this->set_new_size(this->size * 2);
    }
}

void HashTableRealtors::remove(const unsigned long long &key) {
    int index;

    int first_hash = this->first_hash_function(key);
    if (this->get_index_status(first_hash) == 1 && this->keys[first_hash] == key) {  // Если есть возможность удалить на первичном хеше
        index = first_hash;
    } else {  // Иначе разрешаем коллизию
        index = this->get_index(key);
    }

    if (this->get_index_status(index) == 1 && this->keys[index] == key) {
        this->status[index] = 2;
        this->curr_count--;
        this->check_filling();
        return;
    }
    throw std::runtime_error("Error: key does not exist");
}

int HashTableRealtors::get_size() {
    return this->size;
}

int HashTableRealtors::get_count() {
    return this->curr_count;
}

int HashTableRealtors::get_index(const unsigned long long &key) {
    // Возвращает индекс, куда нужно вставлять ключ
    // Если ключ уже есть, то вернёт индекс ключа
    // Если ключа нет и при коллизии встретился удалённый ключ, то вернёт первый встреченный удалённый индекс
    // Если удалённых ключей нет, то вернёт индекс свободной ячейки
    int first_hash = this->first_hash_function(key);
    int hash = first_hash;
    int status_2_index = -1;  // Индекс первой встреченной ячейки со статусом 2 (удалённая)
    int try_number = 1;
    while (this->get_index_status(hash) != 0) {
        if (this->get_index_status(hash) == 2 && status_2_index == -1) {
            status_2_index = hash;
        } else if (this->get_index_status(hash) == 1 && this->keys[hash] == key) {
            return hash;
        }
        hash = this->second_hash_function(first_hash, try_number);
        try_number++;
    }
    if (status_2_index != -1) {
        return status_2_index;
    } else {
        return hash;
    }
}

void HashTableRealtors::clear() {
    for (int i = 0; i < this->get_size(); i++) {
        this->status[i] = 0;
    }
    this->set_new_size(10);
}

std::string HashTableRealtors::to_string() {
    std::string result = "";
    for (int i = 0; i < this->get_size(); i++) {
        int status = this->get_index_status(i);
        result += std::to_string(i) +
                  " " +
                  std::to_string(status);

        unsigned long long key = this->keys[i];
        Realtor value = this->values[i];

        // Выводим первичный и вторичные хеши для данного ключа
        if (status != 0) {  // Если ячейка не пустая, выводим значения
            result += " " +
                      std::to_string(key) +
                      " : " +
                      realtor_to_str(value) + " ";
            int prim_hash = this->first_hash_function(key);
            result += "Первичный хеш: " + std::to_string(prim_hash) + ", ";
            if (prim_hash != i) {  // Если у данного ключа произошла коллизия, то выводим все вторичные хеши
                result += "Вторичные хеши: ";
                int try_count = 1;
                int sec_hash;
                do {
                    sec_hash = this->second_hash_function(prim_hash, try_count);
                    result += std::to_string(sec_hash) + ", ";
                    try_count++;
                } while (sec_hash != i);
            }
        }
        result += "\n";
    }
    return result;
}


std::vector<Realtor> HashTableRealtors::get_values() {
    std::vector<Realtor> result = {};
    for (int i = 0; i < this->size; i++) {
        if (this->get_index_status(i) == 1) {
            result.push_back(this->values[i]);
        }
    }
    return result;
}
