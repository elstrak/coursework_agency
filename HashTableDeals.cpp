#include "HashTableDeals.h"

unsigned int str_to_hash(const std::string& str) {
    unsigned int charSum = 0;
    for (unsigned char ch: str)
        charSum += ch;
    return charSum;
}

unsigned int roundUp2(unsigned int v) {
    // Находит ближайшее число степени 2, большее или равное v
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

HashTableDeals::HashTableDeals(unsigned int size) {
    this->size = size;
    this->curr_count = 0;
    this->keys = std::vector<DealKey>(this->size);
    this->values = std::vector<Deal>(this->size);
    this->status = std::vector<int>(this->size, 0);
}

unsigned int HashTableDeals::primary_hash(DealKey key) {
    // Получение хеша модульным методом
    unsigned int hash = 0;
    hash += key.date.day;
    hash += key.date.month;
    hash += key.date.year;
    hash += str_to_hash(key.address);
    return hash % this->size;
}

int HashTableDeals::probing(const DealKey &obj, int try_number) {
    // Нахождение результата квадратичного пробирования на шаге try_number
    // Если try_number = 0, то возвращает первичный хеш
    int first_hash = this->primary_hash(obj);
    int addition = (try_number * try_number + try_number) / 2;
    return (first_hash + addition) % roundUp2(this->size);
}

int HashTableDeals::find_free_index(const DealKey &key) {
    // Возвращает индекс свободной ячейки для ключа key
    int hash = this->probing(key, 0);
    int try_number = 1;
    while (this->get_index_status(hash) == 1) {  // Пока происходит коллизия
        hash = this->probing(key, try_number);
        while (hash >= this->size) {  // По квадратичному пробированию хеш может выходить за размеры. В этом случае пропускаем итерацию
            try_number++;
            hash = this->probing(key, try_number);
        }
        try_number++;
    }
    return hash;
}

int HashTableDeals::get_index(const DealKey &key) {
    // Если ключ есть в таблице, то возвращает его индекс в массиве, иначе -1
    int hash = this->probing(key, 0);
    int try_number = 1;
    while (this->get_index_status(hash) != 0) {  // Пока не попали на полностью пустую ячейку
        if (this->keys[hash] == key &&
            this->get_index_status(hash) == 1)  // Если статус 2, то ячейка удалена и не должна быть найдена
            return hash;
        hash = this->probing(key, try_number);
        try_number++;
    }
    return -1;
}

void HashTableDeals::insert(const DealKey &key, const Deal &value, bool check_filling) {
    /*
     * Вставляет значение key и значение value в хеш таблицу
     * Если check_filling = true, то будет проверять, нужно ли увеличивать / уменьшать таблицу
     */

    // Ищем индекс подходящей ячейки
    int index = this->get_index(key);
    if (index == -1)  // Если ключа нет в таблице
        index = find_free_index(key);

    if (this->get_index_status(index) != 1) {  // Если добавляется новый элемент
        this->status[index] = 1;
        this->keys[index] = key;
        this->values[index] = value;
        this->curr_count++;
        if (check_filling) {  // Проверяем заполненность таблицы
            this->check_filling();
        }
    } else {  // Если ключ уже существует
        std::cout << "DealKey is already taken\n";
    }
}

int HashTableDeals::get_index_status(int i) {
    return this->status[i];
}

void HashTableDeals::set_new_size(int new_size) {
    auto old_keys = this->keys;
    auto old_values = this->values;
    auto old_status = this->status;
    int old_max = this->size;

    // Создаём новые массивы таблицы
    this->keys = std::vector<DealKey>(new_size);
    this->values = std::vector<Deal>(new_size);
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

bool HashTableDeals::has(const DealKey &key) {
    return get_index(key) != -1;
}

Deal HashTableDeals::get(const DealKey &key) {
    int index = this->get_index(key);
    if (index == -1) {  // Если ключа нет
        throw std::runtime_error("Error: DealKey does not exist");
    }
    return this->values[index];
}

void HashTableDeals::check_filling() {
    // Проверяет заполненность таблицы.
    // Если заполненность более 70%, то увеличивает таблицу.
    // Если заполненность менее 30%, то уменьшает таблицу.
    double fill_coefficient = double(this->curr_count) / double(this->size);
    if (fill_coefficient < 0.3 && this->size > this->min_size) {
        this->set_new_size(this->size / 2);
    } else if (fill_coefficient > 0.7) {
        this->set_new_size(this->size * 2);
    }
}

void HashTableDeals::remove(const DealKey &key) {
    int index = this->get_index(key);
    if (index == -1) {  // Если ключа нет
        throw std::runtime_error("Error: DealKey does not exist");
    }
    this->status[index] = 2;
    this->curr_count--;
    this->check_filling();
}

int HashTableDeals::get_size() {
    return this->size;
}

int HashTableDeals::get_count() {
    return this->curr_count;
}

std::string HashTableDeals::to_string() {
    std::string result = "";
    for (int i = 0; i < this->get_size(); i++) {
        int status = this->get_index_status(i);
        result += std::to_string(i) +
                  " " +
                  std::to_string(status);

        DealKey key = this->keys[i];
        Deal value = this->values[i];

        // Выводим первичный и вторичные хеши для данного ключа
        if (status != 0) {  // Если ячейка не пустая, выводим значения
            result += " " +
                      dealkey_to_str(key) +
                      " : " +
                      deal_to_str(value) + " ";
            int prim_hash = this->probing(key, 0);
            result += "Первичный хеш: " + std::to_string(prim_hash) + ", ";
            if (prim_hash != i) {  // Если у данного ключа произошла коллизия, то выводим все вторичные хеши
                result += "Вторичные хеши: ";
                int try_count = 1;
                int sec_hash;
                do {
                    sec_hash = this->probing(key, try_count);
                    result += std::to_string(sec_hash) + ", ";
                    try_count++;
                } while (sec_hash != i);
            }
        }
        result += "\n";
    }
    return result;
}


std::vector<Deal> HashTableDeals::get_values() {
    std::vector<Deal> result = {};
    for (int i = 0; i < this->size; i++) {
        if (this->get_index_status(i) == 1) {
            result.push_back(this->values[i]);
        }
    }
    return result;
}


void HashTableDeals::clear() {
    for (int i = 0; i < this->get_size(); i++) {
        this->status[i] = 0;
    }
    this->set_new_size(10);
}
