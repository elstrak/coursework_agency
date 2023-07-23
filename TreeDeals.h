#pragma once
#include "ListDeals.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

template<typename T1, typename T2>
class RBNode {
public:
    T1 val;
    ListDeals<T2> chain;
    int color;  // 0 - чёрный, 1 - красный
    RBNode<T1, T2> *left;
    RBNode<T1, T2> *right;
    RBNode<T1, T2> *parent;

    RBNode(T1 val, T2 val_2, int color, RBNode<T1, T2> *left, RBNode<T1, T2> *right, RBNode<T1, T2> *parent);

    RBNode();

    bool isNull() const;

    bool isRoot() const;

    void add_to_chain(T2 value);
};


/**
 * Конструктор создания узла КЧ-дерева
 */
template<typename T1, typename T2>
RBNode<T1, T2>::RBNode(T1 val, T2 val_2, int color, RBNode<T1, T2> *left, RBNode<T1, T2> *right, RBNode<T1, T2> *parent) {
    this->val = val;
    this->color = color;
    this->left = left;
    this->right = right;
    this->parent = parent;
    this->chain.insert(val_2);
}


/**
 * Конструктор создания null-узла
 */
template<typename T1, typename T2>
RBNode<T1, T2>::RBNode() {
    this->color = 0;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}


/**
 * Возвращает true, если узел является null-узлом КЧ-дерева
 */
template<typename T1, typename T2>
bool RBNode<T1, T2>::isNull() const {
    return (this->left == nullptr && this->right == nullptr);
}


/**
 * Возвращает true, если узел является корнем КЧ-дерева
 */
template<typename T1, typename T2>
bool RBNode<T1, T2>::isRoot() const {
    return this->parent->isNull();
}

/**
 * Добавляет значение value в цепочку узла
 */
template<typename T1, typename T2>
void RBNode<T1, T2>::add_to_chain(T2 value) {
    this->chain.insert(value);
}



/**
 * Красно-чёрное дерево
 */
template<typename T1, typename T2>
class TreeDeals {
public:
    RBNode<T1, T2> *root;

    TreeDeals();

    bool isEmpty();

    void insert(T1 val, T2 val_2);

    RBNode<T1, T2> *find(T1 val) const;

    void remove(T1 val, T2 val_2);

    void clear();

    bool has(T1 val, T2 val_2) const;

    bool has(T1 val) const;

    vector<T2> to_vector();

    string to_string(string (*val1_to_str)(T1&), string (*val2_to_str)(T2&));

    vector<T2> get_values_lower(T1 value);

    vector<T2> get_values_higher(T1 value);

private:
    RBNode<T1, T2> *nullNode;

    void rightRotate(RBNode<T1, T2> *x);

    void leftRotate(RBNode<T1, T2> *x);

    void balanceAdd(RBNode<T1, T2> *z);

    RBNode<T1, T2> *getMaxLeft(RBNode<T1, T2> *node) const;

    RBNode<T1, T2> *getMinRight(RBNode<T1, T2> *node) const;

    void transplant(RBNode<T1, T2> *u, RBNode<T1, T2> *v);

    void balanceRemove(RBNode<T1, T2> *x);

    void _to_vector(RBNode<T1, T2> *curr, vector<T2> &result);

    void
    _to_string(string &result, RBNode<T1, T2> *curr, int indent, string (*val1_to_str)(T1&), string (*val2_to_str)(T2&));

    void get_values_lower(T1 value, RBNode<T1, T2> *curr, vector<T2> &result);

    void get_values_higher(T1 value, RBNode<T1, T2> *curr, vector<T2> &result);

    void _clear(RBNode<T1, T2> *curr);
};


/**
 * Конструктор пустого КЧ-дерева
 */
template<typename T1, typename T2>
TreeDeals<T1, T2>::TreeDeals() {
    this->nullNode = new RBNode<T1, T2>();
    this->root = nullNode;
}

/**
 * Возвращает true, если дерево пустое
 */
template<typename T1, typename T2>
bool TreeDeals<T1, T2>::isEmpty() {
    return this->root == nullNode;
}


/**
 * Делает правый поворот вокруг узла x
 * @param x  Узел, вокруг которого поворачиваем
 */
template<typename T1, typename T2>
void TreeDeals<T1, T2>::rightRotate(RBNode<T1, T2> *x) {
    RBNode<T1, T2> *y;

    y = x->left;
    x->left = y->right;
    if (!y->right->isNull()) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->isRoot()) {
        this->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}


/**
 * Делает левый поворот вокруг узла x
 * @param x  Узел, вокруг которого поворачиваем
 */
template<typename T1, typename T2>
void TreeDeals<T1, T2>::leftRotate(RBNode<T1, T2> *x) {
    RBNode<T1, T2> *y;

    y = x->right;
    x->right = y->left;
    if (!y->left->isNull()) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->isRoot()) {
        this->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}


/**
 * Добавляет в дерево узел со значением val
 * @param val  Значение, которое хотим добавить
 */
template<typename T1, typename T2>
void TreeDeals<T1, T2>::insert(T1 val, T2 val_2) {
    RBNode<T1, T2> *z = new RBNode<T1, T2>(val, val_2, 1, nullNode, nullNode, nullNode);
    RBNode<T1, T2> *y = nullNode;
    RBNode<T1, T2> *x = this->root;
    while (x != nullNode) {
        y = x;
        if (z->val < x->val) {
            x = x->left;
        } else if (z->val > x->val) {
            x = x->right;
        } else {  // Если дубликат
            x->add_to_chain(val_2);
            return;
        }
    }
    z->parent = y;
    if (y == nullNode) {
        this->root = z;
    } else if (z->val < y->val) {
        y->left = z;
    } else {
        y->right = z;
    }
    balanceAdd(z);
}


/**
 * Балансирует дерево после добавления узла
 * @param node  Узел, вокруг которого балансируем
 */
template<typename T1, typename T2>
void TreeDeals<T1, T2>::balanceAdd(RBNode<T1, T2> *z) {
    while (z->parent->color == 1) {
        if (z->parent == z->parent->parent->left) {
            RBNode<T1, T2> *y = z->parent->parent->right;
            if (y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                rightRotate(z->parent->parent);
            }
        } else {
            RBNode<T1, T2> *y = z->parent->parent->left;
            if (y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                leftRotate(z->parent->parent);
            }
        }
    }
    this->root->color = 0;
}


/**
 * Ищет узел со значением val. Если такого нет, то возвращает null-узел
 * @param val  Значение, которое ищем
 * @return  Указатель на узел, если такой имеется, и null-узел, если значения val в дереве нет
 */
template<typename T1, typename T2>
RBNode<T1, T2> *TreeDeals<T1, T2>::find(T1 val) const {
    RBNode<T1, T2> *curr = this->root;
    while (val != curr->val and !curr->isNull()) {
        if (val < curr->val) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return curr;
}


/**
 * У узла node находит максимальный узел слева
 * @param node  Узел, у которого ищем максимальный слева
 * @return  Указатель на максимальный слева узел
 */
template<typename T1, typename T2>
RBNode<T1, T2> *TreeDeals<T1, T2>::getMaxLeft(RBNode<T1, T2> *node) const {
    RBNode<T1, T2> *curr = node->left;
    while (curr->right != nullNode) {
        curr = curr->right;
    }
    return curr;
}


/**
 * У узла node находит минимальный узел справа
 * @param node  Узел, у которого ищем минимальный справа
 * @return  Указатель на минимальный справа узел
 */
template<typename T1, typename T2>
RBNode<T1, T2> *TreeDeals<T1, T2>::getMinRight(RBNode<T1, T2> *node) const {
    RBNode<T1, T2> *curr = node->right;
    while (curr->left != nullNode) {
        curr = curr->left;
    }
    return curr;
}


/**
 * Заменяет в дереве узел u на узел v
 * @param u  Узел, который заменяем
 * @param v  Узел, на который заменяем
 */
template<typename T1, typename T2>
void TreeDeals<T1, T2>::transplant(RBNode<T1, T2> *u, RBNode<T1, T2> *v) {
    if (u->isRoot()) {
        this->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}


/**
 * Удаляет узел со значением value из дерева
 * Если узлов с таким значением в дереве несколько, то уменьшает счётчик таких узлов
 * @param value  Значение, которое удаляем
 */
template<typename T1, typename T2>
void TreeDeals<T1, T2>::remove(T1 value, T2 val_2) {
    RBNode<T1, T2> *z = this->find(value);
    if (z->isNull() || !z->chain.has(val_2)) {  // Если такого значения нет в дереве
        throw runtime_error("Error: removing non-existing value from tree");
    }
    if (z->chain.size() > 1) {  // Если у узла есть дубликаты
        z->chain.remove(val_2);
        return;
    }
    if (z->isRoot() && z->left->isNull() && z->right->isNull()) {
        this->root = nullNode;
        return;
    }

    RBNode<T1, T2> *y = z;
    RBNode<T1, T2> *x;
    int yOriginalColor = y->color;
    if (z->left->isNull()) {
        x = z->right;
        this->transplant(z, z->right);
    } else if (z->right->isNull()) {
        x = z->left;
        this->transplant(z, z->left);
    } else {

        // Замена на максимальный слева
//        y = this->getMaxLeft(z);
//        yOriginalColor = y->color;
//        x = y->left;
//        if (y->parent == z) {
//            x->parent = y;
//        } else {
//            transplant(y, y->left);
//            y->left = z->left;
//            y->left->parent = y;
//        }
//        transplant(z, y);
//        y->right = z->right;
//        y->right->parent = y;
//        y->color = z->color;

        // Замена на минимальный справа
        y = this->getMinRight(z);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (yOriginalColor == 0) {
        balanceRemove(x);
    }
}


/**
 * Балансирует дерево после удаления узла
 * @param x  Узел, начиная с которого балансируем дерево
 */
template<typename T1, typename T2>
void TreeDeals<T1, T2>::balanceRemove(RBNode<T1, T2> *x) {
    while (!x->isRoot() and x->color == 0) {
        if (x == x->parent->left) {  // Узел слева
            RBNode<T1, T2> *w = x->parent->right;
            if (w->color == 1) {
                w->color = 0;
                x->parent->color = 1;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == 0 and w->right->color == 0) {
                w->color = 1;
                x = x->parent;
            } else {
                if (w->right->color == 0) {
                    w->left->color = 0;
                    w->color = 1;
                    this->rightRotate(w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = 0;
                w->right->color = 0;
                this->leftRotate(x->parent);
                x = this->root;
            }
        } else {  // Узел справа
            RBNode<T1, T2> *w = x->parent->left;
            if (w->color == 1) {
                w->color = 0;
                x->parent->color = 1;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->left->color == 0 and w->right->color == 0) {
                w->color = 1;
                x = x->parent;
            } else {
                if (w->left->color == 0) {
                    w->right->color = 0;
                    w->color = 1;
                    this->leftRotate(w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = 0;
                w->left->color = 0;
                this->rightRotate(x->parent);
                x = this->root;
            }
        }
    }
    x->color = 0;
}


/**
 * Очищает дерево
 */
template<typename T1, typename T2>
void TreeDeals<T1, T2>::clear() {
    this->_clear(this->root);
    this->root = nullNode;
}


/**
 * Возвращает true, если в дереве есть значение val, val_2
 * @param val Значение, которое ищем
 * @param val_2 Второе значение, которое ищем
 * @return Есть ли значение в дереве
 */
template<typename T1, typename T2>
bool TreeDeals<T1, T2>::has(T1 val, T2 val_2) const {
    auto found_node = this->find(val);
    return (!found_node->isNull() && found_node->chain.has(val_2));
}

template<typename T1, typename T2>
bool TreeDeals<T1, T2>::has(T1 val) const {
    auto found_node = this->find(val);
    return !found_node->isNull();
}

/**
 * Возвращает вектор значений данного дерева
 * @return Вектор значений дерева
 */
template<typename T1, typename T2>
vector<T2> TreeDeals<T1, T2>::to_vector() {
    vector<T2> result = {};
    this->_to_vector(this->root, result);
    return result;
}

/**
 * Рекурсивно обходит дерево, засовывая значения узлов в вектор vect
 * @param curr Текущий узел обхода
 * @param vect Вектор, куда складываются значения пройденных узлов
 */
template<typename T1, typename T2>
void TreeDeals<T1, T2>::_to_vector(RBNode<T1, T2> *curr, vector<T2> &result) {
    if (curr->isNull()) {
        return;
    }
    _to_vector(curr->left, result);
    for (T2 &chain_item: curr->chain.to_vector()) {
        result.push_back(chain_item);
    }
    _to_vector(curr->right, result);
}

/**
 * Переводит дерево в строку
 * @param val1_to_str Функция, переводящая первое значение T1 в строку
 * @param val2_to_str Функция, переводящая второе значение T2 в строку
 * @return Дерево в виде строки
 */
template<typename T1, typename T2>
string TreeDeals<T1, T2>::to_string(string (*val1_to_str)(T1&), string (*val2_to_str)(T2&)) {
    string result = "";
    this->_to_string(result, this->root, 0, val1_to_str, val2_to_str);
    return result;
}

/**
 * Рекурсивно обходит дерево и добавляет значение узла curr к строке result с отступом indent
 * @param result Итоговая строка, к которой добавится данный узел curr
 * @param curr Текущий рассматриваемый узел
 * @param indent Отступ от начала
 * @param val1_to_str Функция, переводящая первое значение T1 в строку
 * @param val2_to_str Функция, переводящая второе значение T2 в строку
 */
template<typename T1, typename T2>
void TreeDeals<T1, T2>::_to_string(string &result, RBNode<T1, T2> *curr, int indent, string (*val1_to_str)(T1&),
                                string (*val2_to_str)(T2&)) {
    if (!curr->isNull()) {
        _to_string(result, curr->right, indent + 5, val1_to_str, val2_to_str);
        for (int i = 0; i < indent; i++)
            result += " ";
        string color = "Red";
        if (curr->color == 0) {
            color = "Black";
        }
        result += color + " " +
                  val1_to_str(curr->val) + ": " +
                  curr->chain.to_string(val2_to_str);
        result += "\n";
        _to_string(result, curr->left, indent + 5, val1_to_str, val2_to_str);
    }
}


/**
 * Рекурсивно обходит дерево и все значения узлов с ключом меньше или равно value сохраняет в result
 * @param target Значение, по которому ищем узлы
 * @param curr Текущий рассматриваемый узел
 * @param result Итоговый вектор, куда сохранятся подходящие узлы
 */
template<typename T1, typename T2>
void TreeDeals<T1, T2>::get_values_lower(T1 value, RBNode<T1, T2> *curr, vector<T2> &result) {
	if (curr->isNull()) return;
    if (curr->val > value) {  // Если узел не подходит под условие
        get_values_lower(value, curr->left, result);  // Смотрим на узел поменьше
    } else {
        get_values_lower(value, curr->left, result);
        for (T2 chain_item: curr->chain.to_vector()) {  // Добавляем значения в ответ
            result.push_back(chain_item);
        }
        get_values_lower(value, curr->right, result);
    }
}

/**
 * Рекурсивно обходит дерево и все значения узлов с ключом больше или равно value сохраняет в result
 * @param target Значение, по которому ищем узлы
 * @param curr Текущий рассматриваемый узел
 * @param result Итоговый вектор, куда сохранятся подходящие узлы
 */
template<typename T1, typename T2>
void TreeDeals<T1, T2>::get_values_higher(T1 value, RBNode<T1, T2> *curr, vector<T2> &result) {
	if (curr->isNull()) return;
    if (curr->val < value) {  // Если узел не подходит под условие
        get_values_higher(value, curr->right, result);  // Смотрим на узел побольше
    } else {
        get_values_higher(value, curr->left, result);
        for (T2 chain_item: curr->chain.to_vector()) {  // Добавляем значения в ответ
            result.push_back(chain_item);
        }
        get_values_higher(value, curr->right, result);
    }
}

/**
 * Возвращает все значения, у которых ключ меньше или равен value
 * @param value Значение, по которому ищем узлы
 * @return Вектор всех подходящих вторых значений
 */
template<typename T1, typename T2>
vector<T2> TreeDeals<T1, T2>::get_values_lower(T1 value) {
	vector<T2> result = {};
	this->get_values_lower(value, this->root, result);
	return result;
}

/**
 * Возвращает все значения, у которых ключ больше или равен value
 * @param value Значение, по которому ищем узлы
 * @return Вектор всех подходящих вторых значений
 */
template<typename T1, typename T2>
vector<T2> TreeDeals<T1, T2>::get_values_higher(T1 value) {
	vector<T2> result = {};
	this->get_values_higher(value, this->root, result);
	return result;
}

/**
 * Рекурсивно проходит по всем узлам и удаляет их
 * @param curr Текущий узел
 */
template<typename T1, typename T2>
void TreeDeals<T1, T2>::_clear(RBNode<T1, T2> *curr) {
    if (curr->isNull()) return;
    _clear(curr->left);
    _clear(curr->right);
    delete curr;
}


