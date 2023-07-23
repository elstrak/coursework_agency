#pragma once

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
struct NodeDeals {
    T data;
    NodeDeals *next;
};

// Односвязный список со вставкой в начало
template<typename T>
class ListDeals {
public:

    ListDeals();

    ~ListDeals();

    void insert(T val);

    void remove(T val);

    string to_string(string (*val_to_str)(T&));

    bool isEmpty();

    bool has(T val);

    vector<T> to_vector();

    int size();

private:

    NodeDeals<T> *head;

    NodeDeals<T> *search(T val);
};

template<typename T>
ListDeals<T>::ListDeals() {
    head = nullptr;
}

template<typename T>
ListDeals<T>::~ListDeals() {
//    NodeDeals<T> *curr = this->head;
//    while (curr != nullptr) {
//        NodeDeals<T> *tmp = curr->next;
//        delete curr;
//        curr = tmp;
//    }
}

template<typename T>
void ListDeals<T>::insert(T val) {
    // Добавление в начало
    auto new_node = new NodeDeals<T>;
    new_node->data = val;
    new_node->next = nullptr;

    if (this->isEmpty())
        this->head = new_node;
    else {
        new_node->next = this->head;
        this->head = new_node;
    }
}

template<typename T>
bool ListDeals<T>::isEmpty() {
    return this->head == nullptr;
}

template<typename T>
NodeDeals<T> *ListDeals<T>::search(T val) {
    // Возвращает указатель на узел со значением val. Если такого нет, то возвращает nullptr
    NodeDeals<T> *curr = this->head;
    while (curr != nullptr) {
        if (curr->data == val)
            return curr;
        curr = curr->next;
    }
    return nullptr;
}

template<typename T>
void ListDeals<T>::remove(T val) {
    // Удаляет из списка значение val. Возвращает исключение, если значение отсутствует в списке
    if (this->isEmpty())
        throw runtime_error("Error: Removing from empty list");

    if (head->data == val) {  // Если удаляем голову
        NodeDeals<T> *tmp = head->next;
        delete head;
        head = tmp;
        return;
    }

    NodeDeals<T> *curr = head;
    while (curr->next != nullptr) {
        if (curr->next->data == val) {  // Когда нашли узел
            NodeDeals<T> *temp = curr->next->next;
            delete curr->next;
            curr->next = temp;
            return;
        }
        curr = curr->next;
    }
    throw runtime_error("Error: Removing non-existing value from list");
}

template<typename T>
bool ListDeals<T>::has(T val) {
    return this->search(val) != nullptr;
}

template<typename T>
vector<T> ListDeals<T>::to_vector() {
    vector<T> result = {};
    auto curr = this->head;
    while (curr != nullptr) {
        result.push_back(curr->data);
        curr = curr->next;
    }
    return result;
}

template<typename T>
int ListDeals<T>::size() {
    return this->to_vector().size();
}

template<typename T>
string ListDeals<T>::to_string(string (*val_to_str)(T&)) {
    string result = "";
    for (T item: this->to_vector()) {
        result += val_to_str(item) + " -> ";
    }
    return result;
}
