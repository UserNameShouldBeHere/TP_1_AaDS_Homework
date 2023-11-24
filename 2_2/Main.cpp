// Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
// Требуется построить бинарное дерево, заданное наивным порядком вставки.
// Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
// Требования: Рекурсия запрещена.Решение должно поддерживать передачу функции сравнения снаружи.

#include <iostream>
#include <queue>

template <typename T>
class Stack {
private:
    T* arr;
    unsigned int size;
    unsigned int capacity = 8;

public:
    Stack() : size(0) { arr = new T[capacity]; }

    void push_back(T value) {
        if (size + 1 <= capacity) {
            arr[size++] = value;
        }
        else {
            T* tmp_arr = new T[capacity];
            for (unsigned int i = 0; i < capacity; i++)
                tmp_arr[i] = arr[i];
            delete[] arr;
            arr = new T[capacity * 2];
            for (unsigned int i = 0; i < capacity; i++)
                arr[i] = tmp_arr[i];
            delete[] tmp_arr;
            arr[size++] = value;
            capacity *= 2;
        }
    }

    T pop_back() {
        if (!size)
            return NULL;
        return arr[--size];
    }

    unsigned int length() { return size; }

    ~Stack() { delete[] arr; }
};

template <typename T>
struct Comparator {
    bool operator()(const T& lhs, const T& rhs) const {
        return lhs > rhs;
    }
};

template <typename T>
class TreeNode {
private:
    T value;
    TreeNode<T> *left, *right;

    template <typename, typename>
    friend class Tree;

public:
    TreeNode(T value) : value(value), left(nullptr), right(nullptr) {}

    ~TreeNode() { delete left, right; }
};

template <typename T, typename Comp = Comparator<T>>
class Tree {
private:
    TreeNode<T>* root;
    Comp comp;

public:
    Tree(Comp comp = Comparator<T>()) : root(nullptr), comp(comp) {}

    void add(int value) {
        if (root == nullptr)
            root = new TreeNode<T>(value);
        else {
            TreeNode<T>* parent_node = root;
            while (true) {
                if (comp(parent_node->value, value)) {
                    if (parent_node->left == nullptr)
                        break;
                    else
                        parent_node = parent_node->left;
                }
                else {
                    if (parent_node->right == nullptr)
                        break;
                    else
                        parent_node = parent_node->right;
                }
            }
            if (comp(parent_node->value, value))
                parent_node->left = new TreeNode<T>(value);
            else
                parent_node->right = new TreeNode<T>(value);
        }
    }

    void print_in_order() {
        if (root != nullptr) {
            Stack<TreeNode<T>*>* stack = new Stack<TreeNode<T>*>();
            TreeNode<T>* current = root;
            stack->push_back(current);
            while (true) {
                if (current == nullptr || stack->length() == 0)
                    break;

                if (current->left != nullptr) {
                    current = current->left;
                    stack->push_back(current);
                }
                else {
                    if (current->right == nullptr) {
                        while (true) {
                            if (stack->length() == 0)
                                break;

                            current = stack->pop_back();
                            std::cout << current->value << ' ';
                            if (current->right != nullptr)
                                break;
                        }
                        current = current->right;
                    }
                    else {
                        std::cout << current->value << ' ';
                        stack->pop_back();
                        current = current->right;
                    }
                    stack->push_back(current);
                }
            }
        }
    }

    void print_pre_order() {
        if (root != nullptr) {
            Stack<TreeNode<T>*>* stack = new Stack<TreeNode<T>*>();
            TreeNode<T>* current = root;
            stack->push_back(current);
            while (true) {
                if (current != nullptr)
                    std::cout << current->value << ' ';
                else if (current == nullptr || stack->length() == 0)
                    break;

                if (current->left != nullptr) {
                    current = current->left;
                    stack->push_back(current);
                }
                else {
                    if (current->right == nullptr) {
                        while (true) {
                            if (stack->length() == 0)
                                break;

                            current = stack->pop_back();
                            if (current->right != nullptr)
                                break;
                        }
                        current = current->right;
                    }
                    else {
                        stack->pop_back();
                        current = current->right;
                    }
                    stack->push_back(current);
                }
            }
        }
    }

    void print_level_order() {
        if (root != nullptr) {
            std::queue<TreeNode<T>*>* queue = new std::queue<TreeNode<T>*>();
            TreeNode<T>* current = root;
            queue->push(current);
            while (!queue->empty()) {
                current = queue->front();
                queue->pop();
                std::cout << current->value << ' ';
                if (current->left != nullptr)
                    queue->push(current->left);
                if (current->right != nullptr)
                    queue->push(current->right);
            }
        }
    }

    ~Tree() {
        if (root != nullptr) {
            std::queue<TreeNode<T>*>* queue = new std::queue<TreeNode<T>*>();
            Stack<TreeNode<T>*>* stack = new Stack<TreeNode<T>*>();
            TreeNode<T>* current = root;
            queue->push(current);
            while (!queue->empty()) {
                current = queue->front();
                queue->pop();
                stack->push_back(current);
                if (current->left != nullptr)
                    queue->push(current->left);
                if (current->right != nullptr)
                    queue->push(current->right);
            }
            while (stack->length() != 0) {
                TreeNode<T>* tmp = stack->pop_back();
                tmp->left = nullptr;
                tmp->right = nullptr;
                delete tmp;
            }
        }
    }
};

int main() {
    Tree<int>* tree = new Tree<int>();

    int count, tmp;
    std::cin >> count;
    for (int i = 0; i < count; i++) {
        std::cin >> tmp;
        tree->add(tmp);
    }

    tree->print_in_order();

    delete tree;

    return 0;
}