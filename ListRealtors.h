#pragma once

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
struct NodeRealtors {
    T data;
    NodeRealtors *next;
    NodeRealtors *prev;
};

// Двусвязный список со вставкой в начало
template<typename T>
class ListRealtors {
public:

    ListRealtors();

    ~ListRealtors();

    void insert(T val);

    void remove(T val);

    string to_string(string (*val_to_str)(T&));

    bool isEmpty();

    bool has(T val);

    vector<T> to_vector();

    int size();

private:

    NodeRealtors<T> *head;

    NodeRealtors<T> *search(T val);
};

template<typename T>
ListRealtors<T>::ListRealtors() {
    head = nullptr;
}

template<typename T>
ListRealtors<T>::~ListRealtors() {
//    NodeRealtors<T> *curr = this->head;
//    while (curr != nullptr) {
//        NodeRealtors<T> *tmp = curr->next;
//        delete curr;
//        curr = tmp;
//    }
}

template<typename T>
void ListRealtors<T>::insert(T val) {
    auto *elem = new NodeRealtors<T>;
    elem->next = this->head;
    elem->prev = nullptr;
    elem->data = val;
    if (!this->isEmpty()) {
        this->head->prev = elem;
    }
    this->head = elem;
}

template<typename T>
bool ListRealtors<T>::isEmpty() {
    return this->head == nullptr;
}

template<typename T>
NodeRealtors<T> *ListRealtors<T>::search(T val) {
    // Возвращает указатель на узел со значением val. Если такого нет, то возвращает nullptr
    NodeRealtors<T> *curr = this->head;
    while (curr != nullptr) {
        if (curr->data == val)
            return curr;
        curr = curr->next;
    }
    return nullptr;
}

template<typename T>
void ListRealtors<T>::remove(T val) {
    // Удаляет из списка значение val. Возвращает исключение, если значение отсутствует в списке
    if (this->isEmpty())
        throw runtime_error("Error: Removing from empty list");

    if (head->data == val) {  // Удаляем голову
        NodeRealtors<T> *tmp = head->next;
        delete head;
        head = tmp;
        return;
    }

    NodeRealtors<T> *node = this->search(val);
    if (node != nullptr) {
        node->prev->next = node->next;
        if (node->next != nullptr) {
            node->next->prev = node->prev;
        }
        delete node;
    } else {
        throw runtime_error("Error: Removing non-existing value from list");
    }
}

template<typename T>
bool ListRealtors<T>::has(T val) {
    return this->search(val) != nullptr;
}

template<typename T>
vector<T> ListRealtors<T>::to_vector() {
    vector<T> result = {};
    auto curr = this->head;
    while (curr != nullptr) {
        result.push_back(curr->data);
        curr = curr->next;
    }
    return result;
}

template<typename T>
int ListRealtors<T>::size() {
    return this->to_vector().size();
}

template<typename T>
string ListRealtors<T>::to_string(string (*val_to_str)(T&)) {
    string result = "";
    for (T item: this->to_vector()) {
        result += val_to_str(item) + " <-> ";
    }
    return result;
}
