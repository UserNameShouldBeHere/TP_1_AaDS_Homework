// 4.1 Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.
// Требования: время работы O(N * logK). Ограничение на размер кучи O(K).

#include <iostream>
#include <algorithm>

// 4.1
template <typename T>
struct Comparator {
    bool operator()(const T& lhs, const T& rhs) const {
        return lhs.number() < rhs.number();
    }
};

class Node {
private:
    int value;
    int arr_index;
public:
    Node() {}
    Node(int value, int arr_index) : value(value), arr_index(arr_index) {}

    int number() const { return value; }
    int arr() const { return arr_index; }
};

template <typename T>
class Array {
private:
    int size;
    int capacity;
    T* arr;
public:
    Array() : size(0), capacity(8) { arr = new T[capacity]; }

    void push_back(T value) {
        if (size >= capacity) {
            T* tmp_arr = new T[capacity];
            for (int i = 0; i < size; i++)
                tmp_arr[i] = arr[i];
            delete[] arr;
            arr = new T[capacity * 2];
            for (int i = 0; i < size; i++)
                arr[i] = tmp_arr[i];
            delete[] tmp_arr;
            capacity *= 2;
        }

        arr[size++] = value;
    }

    T pop() {
        if (size == 0)
            throw "Index out of range";

        size--;
        return arr[size];
    }

    void reverse_and_squeeze() {
        T* tmp_arr = new T[size];
        for (int i = 0; i < size; i++)
            tmp_arr[i] = arr[i];
        delete[] arr;
        arr = new T[size];
        for (int i = 0; i < size; i++)
            arr[i] = tmp_arr[size - 1 - i];
        delete[] tmp_arr;
    }

    unsigned int length() { return size; }

    ~Array() { delete[] arr; }
};

template <typename T, typename Comp=Comparator<T>>
class Heap
{
private:
    unsigned int size, capacity;
    T* arr;
    Comp comp;

    void sift_down(int i)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < size && comp(arr[left], arr[i]))
            smallest = left;

        if (right < size && comp(arr[right], arr[smallest]))
            smallest = right;

        if (smallest != i)
        {
            std::swap(arr[i], arr[smallest]);
            sift_down(smallest);
        }
    }

    void sift_up(int i)
    {
        int parent = (i - 1) / 2;

        if (i && comp(arr[i], arr[parent]))
        {
            std::swap(arr[i], arr[parent]);
            sift_up(parent);
        }
    }

public:
    Heap(Comp comp=Comparator<T>()) : size(0), capacity(8), comp(comp) { arr = new T[capacity]; }

    unsigned int length() { return size; }

    bool is_empty() { return size == 0; }

    void push(T value)
    {
        if (size >= capacity) {
            T* tmp_arr = new T[capacity];
            for (int i = 0; i < size; i++)
                tmp_arr[i] = arr[i];
            delete[] arr;
            arr = new T[capacity * 2];
            for (int i = 0; i < size; i++)
                arr[i] = tmp_arr[i];
            delete[] tmp_arr;
            capacity *= 2;
        }

        arr[size++] = value;
        sift_up(size - 1);
    }

    T pop()
    {
        if (size == 0)
            throw "Index out of range";

        T result = arr[0];

        std::swap(arr[0], arr[size - 1]);
        size--;

        sift_down(0);

        return result;
    }

    ~Heap() { delete[] arr; }
};

int main()
{
    unsigned int arrs_count, arr_length, number, total_count = 0;
    Array<Node>* arrs;
    Heap<Node>* heap = new Heap<Node>();

    std::cin >> arrs_count;
    arrs = new Array<Node>[arrs_count];
    for (int i = 0; i < arrs_count; i++) {
        std::cin >> arr_length;
        for (int j = 0; j < arr_length; j++) {
            std::cin >> number;
            arrs[i].push_back(Node(number, i));
        }
        arrs[i].reverse_and_squeeze();
        total_count += arr_length;
    }

    for (int i = 0; i < arrs_count; i++)
        heap->push(arrs[i].pop());
    while (total_count != 0) {
        Node node = heap->pop();
        if (arrs[node.arr()].length() != 0)
            heap->push(arrs[node.arr()].pop());
        std::cout << node.number() << " ";
        total_count--;
    }

    delete heap;
    delete[] arrs;

    return 0;
}