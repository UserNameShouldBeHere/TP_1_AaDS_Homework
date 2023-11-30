// 4_2.ѕор€дковые статистики.ƒано число N и N строк. ажда€ строка содержит команду добавлени€ или удалени€ натуральных чисел, а также запрос на получение k - ой пор€дковой статистики.
//  оманда добавлени€ числа A задаетс€ положительным числом A, команда удалени€ числа A задаетс€ отрицательным числом У - AФ.«апрос на получение k - ой пор€дковой статистики задаетс€ числом k.
// “ребовани€: скорость выполнени€ запроса - O(log n).

#include <stdint.h>
#include <iostream>
#include <vector>

template <typename T>
struct Comparator {
    int operator()(const T& lhs, const T& rhs) const {
        if (lhs > rhs)
            return 1;
        if (lhs < rhs)
            return -1;
        return 0;
    }
};

template <typename Key, typename Value, typename Comp=Comparator<Key>>
class AVLTree {
private:
    class TreeNode {
    private:
        Key key;
        Value value;
        uint8_t height;
        TreeNode* left, *right;

        template<typename, typename, typename>
        friend class AVLTree;

        void order_statistics(std::vector<Value>* vect) {
            if (left != nullptr)
                left->order_statistics(vect);
            vect->push_back(value);
            if (right != nullptr)
                right->order_statistics(vect);
        }

    public:
        TreeNode(Key key, Value value) : key(key), value(value), height(1), left(nullptr), right(nullptr) {}

        void print(uint8_t depth) {
            for (int i = 0; i < depth; i++)
                std::cout << "==|";
            std::cout << value << std::endl;
            if (left != nullptr)
                left->print(depth + 1);
            if (right != nullptr)
                right->print(depth + 1);
        }

        Value kth_order_statistics(int order_number) {
            std::vector<Value> vect;

            order_statistics(&vect);

            if (order_number < 0 || order_number >= vect.size())
                return NULL;

            return vect[order_number];
        }

        ~TreeNode() {
            delete left, right;
        }
    };

    TreeNode* root;
    Comp comp;

    uint8_t height(TreeNode* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    TreeNode* insert_aux(const Key& key, const Value& value, TreeNode* node) {
        if (node == nullptr)
            return new TreeNode(key, value);

        switch (comp(key, node->key)) {
        case 1:
            node->right = insert_aux(key, value, node->right);
            break;
        case -1:
            node->left = insert_aux(key, value, node->left);
            break;
        }

        return balance(node);
    }

    std::pair<TreeNode*, TreeNode*> find_and_remove_min_node(std::pair<TreeNode*, TreeNode*> nodes) {
        if (!(nodes.first)->left) {
            return std::pair<TreeNode*, TreeNode*>((nodes.first)->right, (nodes.first));
        }

        std::pair<TreeNode*, TreeNode*> tmp = find_and_remove_min_node(std::pair<TreeNode*, TreeNode*>((nodes.first)->left, nodes.second));
        (nodes.first)->left = tmp.first;
        return std::pair<TreeNode*, TreeNode*>(balance(nodes.first), tmp.second);
    }

    TreeNode* erase_aux(const Key& key, TreeNode* node) {
        if (node == nullptr)
            return node;

        switch (comp(key, node->key)) {
        case 1:
            node->right = erase_aux(key, node->right);
            break;
        case -1:
            node->left = erase_aux(key, node->left);
            break;
        case 0:
            if (node->left == nullptr || node->right == nullptr) {
                TreeNode* tmp = node->left == nullptr ? node->right : node->left;

                if (tmp == nullptr) {
                    delete node;
                    return nullptr;
                }
                else {
                    node->left = nullptr;
                    node->right = nullptr;
                    delete node;
                    node = tmp;
                    return node;
                }
            }
            else {
                TreeNode* left = node->left;
                TreeNode* right = node->right;
                std::pair<TreeNode*, TreeNode*> nodes = find_and_remove_min_node(std::pair<TreeNode*, TreeNode*>(right, nullptr));
                TreeNode* min_node = nodes.second;
                right = nodes.first;

                min_node->left = left;
                min_node->right = right;

                node->left = nullptr;
                node->right = nullptr;
                delete node;

                return balance(min_node);
            }
        }
        
        return balance(node);
    }

    int balance_factor(TreeNode* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    void fix_height(TreeNode* node) {
        node->height = std::max(height(node->left), height(node->right)) + 1;
    }

    TreeNode* rotate_right(TreeNode* node) {
        TreeNode* tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        return tmp;
    }

    TreeNode* rotate_left(TreeNode* node) {
        TreeNode* tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        return tmp;
    }

    TreeNode* balance(TreeNode* node) {
        fix_height(node);

        int bf = balance_factor(node);
        if (bf > 1) {
            if (balance_factor(node->right) < 0) {
                node->right = rotate_right(node->right);
            }
            return rotate_left(node);
        }
        else if (bf < -1) {
            if (balance_factor(node->left) > 0) {
                node->left = rotate_left(node->left);
            }
            return rotate_right(node);
        }

        return node;
    }

public:
    AVLTree(Comp comp=Comparator<Key>()) : comp(comp), root(nullptr) {}

    void insert(const Key& key, const Value& value) {
        root = insert_aux(key, value, root);
    }

    void print() {
        root->print(0);
        std::cout << std::endl;
    }

    void erase(const Key& key) {
        root = erase_aux(key, root);
    }

    Value kth_order_statistics(int order_number) {
        if (root == nullptr)
            return NULL;
        return root->kth_order_statistics(order_number);
    }

    ~AVLTree() { delete root; }
};

int main() {
    AVLTree<int, int>* tree = new AVLTree<int, int>();
    int count, value, order_number;

    std::cin >> count;

    for (int i = 0; i < count; i++) {
        std::cin >> value >> order_number;
        if (value >= 0) {
            tree->insert(value, value);
        }
        else {
            tree->erase(-value);
        }
        std::cout << tree->kth_order_statistics(order_number) << std::endl;
    }

    // tree->print();

    delete tree;

    return 0;
}