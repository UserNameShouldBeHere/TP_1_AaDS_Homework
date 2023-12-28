// Реализуйте структуру данных типа “множество строк” на основе динамической хеш - таблицы с открытой адресацией.Хранимые строки непустые и состоят из строчных латинских букв.
// Хеш - функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
// Начальный размер таблицы должен быть равным 8 - ми.Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3 / 4.
// Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
// 1_2.Для разрешения коллизий используйте двойное хеширование.

#include <vector>
#include <fstream>
#include <cmath>
#include <stdint.h>
#include <iostream>
#include <string>
#include <set>

template <class Key> struct Hash;

template<> struct Hash<std::string> {
    size_t operator()(const std::string& value) const {
        size_t hash = 0;
        for (char i : value)
            hash = hash * 13 + i;
        return hash;
    }
};

template <typename Key>
class Node {
private:
    Key key;
    bool empty, had_prev_value;

    template <typename, typename>
    friend class HashTable;

public:
    Node(Key key) : key(key), empty(false), had_prev_value(false) {}
    Node() : empty(true), had_prev_value(false) {}
};

template <typename Key, typename Hasher = Hash<Key>>
class HashTable {
private:
    Node<Key>* array;
    Hasher hasher;
    size_t items_count;
    size_t* BUCKETS_SIZES_LIST;
    size_t buckets_sizes_list_idx;
    const float LOAD_FACTOR = 0.75;

    size_t double_hash(const std::string& value, const size_t i) {
        size_t hash = 0;
        for (char i : value)
            hash = hash * 17 + i;
        hash = hash * 2 - 1;
        return hasher(value) + i * hash;
    }

public:
    HashTable(Hasher hasher = Hash<std::string>()) : hasher(hasher), items_count(0), buckets_sizes_list_idx(0) {
        BUCKETS_SIZES_LIST = new size_t[62];
        for (int i = 0; i < 62; i++) {
            BUCKETS_SIZES_LIST[i] = pow(2, i + 3);
        }

        array = new Node<Key>[BUCKETS_SIZES_LIST[buckets_sizes_list_idx]];
    }

    bool insert(const Key& key) {
        if (find(key))
            return false;

        if (items_count >= BUCKETS_SIZES_LIST[buckets_sizes_list_idx] * LOAD_FACTOR)
            rehash();

        size_t first_deleted_idx;
        size_t current_idx;
        size_t hash_count = 1;
        current_idx = hasher(key) % BUCKETS_SIZES_LIST[buckets_sizes_list_idx];
        first_deleted_idx = current_idx;

        if (array[current_idx].empty) {
            array[current_idx].key = key;
            array[current_idx].empty = false;
            array[current_idx].had_prev_value = false;
            items_count++;
            return true;
        }

        for (int i = 0; i < BUCKETS_SIZES_LIST[buckets_sizes_list_idx]; i++) {
            current_idx = double_hash(key, hash_count++) % BUCKETS_SIZES_LIST[buckets_sizes_list_idx];

            if (current_idx == first_deleted_idx) {
                rehash();
            }
            else if (array[current_idx].empty) {
                array[current_idx].key = key;
                array[current_idx].empty = false;
                array[current_idx].had_prev_value = false;
                items_count++;
                return true;
            }
        }
    }

    bool erase(const Key& key) {
        size_t first_deleted_idx;
        size_t current_idx;
        size_t hash_count = 1;
        current_idx = hasher(key) % BUCKETS_SIZES_LIST[buckets_sizes_list_idx];
        first_deleted_idx = current_idx;

        if (array[current_idx].empty && !array[current_idx].had_prev_value)
            return false;

        if (!array[current_idx].empty && array[current_idx].key == key)
        {
            array[current_idx].had_prev_value = true;
            array[current_idx].empty = true;
            items_count--;
            return true;
        }

        for (int i = 0; i < BUCKETS_SIZES_LIST[buckets_sizes_list_idx]; i++) {
            current_idx = double_hash(key, hash_count++) % BUCKETS_SIZES_LIST[buckets_sizes_list_idx];

            if (current_idx == first_deleted_idx)
                return false;
            else if (array[current_idx].empty && !array[current_idx].had_prev_value)
                return false;
            else if (!array[current_idx].empty && array[current_idx].key == key) {
                array[current_idx].had_prev_value = true;
                array[current_idx].empty = true;
                items_count--;
                return true;
            }
        }

        return false;
    }

    bool find(const Key& key) {
        size_t first_deleted_idx;
        size_t current_idx;
        size_t hash_count = 1;
        current_idx = hasher(key) % BUCKETS_SIZES_LIST[buckets_sizes_list_idx];
        first_deleted_idx = current_idx;

        if (array[current_idx].empty && !array[current_idx].had_prev_value)
            return false;

        if (!array[current_idx].empty && array[current_idx].key == key)
            return true;

        for (int i = 0; i < BUCKETS_SIZES_LIST[buckets_sizes_list_idx]; i++) {
            current_idx = double_hash(key, hash_count++) % BUCKETS_SIZES_LIST[buckets_sizes_list_idx];

            if (current_idx == first_deleted_idx)
                return false;
            else if (array[current_idx].empty && !array[current_idx].had_prev_value)
                return false;
            else if (!array[current_idx].empty && array[current_idx].key == key)
                return true;
        }

        return false;
    }

    void rehash() {
        Node<Key>* new_arr = new Node<Key>[BUCKETS_SIZES_LIST[++buckets_sizes_list_idx]];
        size_t begin_idx, current_idx;
        size_t hash_count;

        for (size_t i = 0; i < BUCKETS_SIZES_LIST[buckets_sizes_list_idx - 1]; i++) {
            if (array[i].empty)
                continue;

            hash_count = 1;
            current_idx = hasher(array[i].key) % BUCKETS_SIZES_LIST[buckets_sizes_list_idx];

            if (new_arr[current_idx].empty) {
                new_arr[current_idx].key = array[i].key;
                new_arr[current_idx].empty = false;
                continue;
            }

            begin_idx = current_idx;
            while (true) {
                current_idx = double_hash(array[i].key, hash_count++) % BUCKETS_SIZES_LIST[buckets_sizes_list_idx];

                if (new_arr[current_idx].empty) {
                    new_arr[current_idx].key = array[i].key;
                    new_arr[current_idx].empty = false;
                    break;
                }
            }
        }

        delete[] array;
        array = new_arr;
    }

    size_t size() { return items_count; }

    void print() {
        std::cout << "| ";
        for (size_t i = 0; i < BUCKETS_SIZES_LIST[buckets_sizes_list_idx]; i++)
            std::cout << array[i].key << " | ";
    }

    ~HashTable() { delete[] array; }
};

int main() {
    HashTable<std::string>* hash_table = new HashTable<std::string>();

    char command;
    std::string value;

    while (std::cin >> command >> value) {
        switch (command) {
        case '+':
            std::cout << (hash_table->insert(value) ? "OK" : "FAIL") << std::endl;
            break;
        case '-':
            std::cout << (hash_table->erase(value) ? "OK" : "FAIL") << std::endl;
            break;
        case '?':
            std::cout << (hash_table->find(value) ? "OK" : "FAIL") << std::endl;
            break;
        }
    }

    delete hash_table;

    return 0;
}