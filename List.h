#pragma once

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
struct Node {
    T data;
    Node *next;
};

template<typename T>
class List {
public:

    List();

    ~List();

    void insert(T val);

    void remove(T val);

    string to_string(string (*val_to_str)(T&));

    bool isEmpty();

    bool has(T val);

    vector<T> to_vector();

    int size();

private:

    Node<T> *head;

    Node<T> *search(T val);
};

template<typename T>
List<T>::List() {
    head = nullptr;
}

template<typename T>
List<T>::~List() {
//    Node<T> *curr = this->head;
//    while (curr != nullptr) {
//        Node<T> *tmp = curr->next;
//        delete curr;
//        curr = tmp;
//    }
}

template<typename T>
void List<T>::insert(T val) {
    // Добавление в начало
    auto new_node = new Node<T>;
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
bool List<T>::isEmpty() {
    return this->head == nullptr;
}

template<typename T>
Node<T> *List<T>::search(T val) {
    // Возвращает указатель на узел со значением val. Если такого нет, то возвращает nullptr
    Node<T> *curr = this->head;
    while (curr != nullptr) {
        if (curr->data == val)
            return curr;
        curr = curr->next;
    }
    return nullptr;
}

template<typename T>
void List<T>::remove(T val) {
    // Удаляет из списка значение val. Возвращает исключение, если значение отсутствует в списке
    if (this->isEmpty())
        throw runtime_error("Error: Removing from empty list");

    if (head->data == val) {  // Если удаляем голову
        Node<T> *tmp = head->next;
        delete head;
        head = tmp;
        return;
    }

    Node<T> *curr = head;
    while (curr->next != nullptr) {
        if (curr->next->data == val) {  // Когда нашли узел
            Node<T> *temp = curr->next->next;
            delete curr->next;
            curr->next = temp;
            return;
        }
        curr = curr->next;
    }
    throw runtime_error("Error: Removing non-existing value from list");
}

template<typename T>
bool List<T>::has(T val) {
    return this->search(val) != nullptr;
}

template<typename T>
vector<T> List<T>::to_vector() {
    vector<T> result = {};
    auto curr = this->head;
    while (curr != nullptr) {
        result.push_back(curr->data);
        curr = curr->next;
    }
    return result;
}

template<typename T>
int List<T>::size() {
    return this->to_vector().size();
}

template<typename T>
string List<T>::to_string(string (*val_to_str)(T&)) {
    string result = "";
    for (T item: this->to_vector()) {
        result += val_to_str(item) + " -> ";
    }
    return result;
}