// 4.1 Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.
// Требования: время работы O(N * logK). Ограничение на размер кучи O(K).

#include <iostream>
#include <vector>
#include <algorithm>

// 4.1
template <typename T>
struct Comparator {
    bool operator()(const T& lhs, const T& rhs) const {
        return lhs < rhs;
    }
};

template <typename T, typename Comp=Comparator<T>>
class Heap
{
private:
    unsigned int size, capacity;
    int* arr;
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
    Heap(Comp comp=Comparator<T>()) : size(0), capacity(8), comp(comp) { arr = new int[capacity]; }

    unsigned int length() { return size; }

    bool is_empty() { return size == 0; }

    void push(int key)
    {
        if (size >= capacity) {
            int* tmp_arr = new int[capacity];
            for (int i = 0; i < size; i++)
                tmp_arr[i] = arr[i];
            delete[] arr;
            arr = new int[capacity * 2];
            for (int i = 0; i < size; i++)
                arr[i] = tmp_arr[i];
            delete[] tmp_arr;
            capacity *= 2;
        }

        arr[size++] = key;
        sift_up(size - 1);
    }

    int pop()
    {
        if (size == 0)
            throw "Index out of range";

        int result = arr[0];

        std::swap(arr[0], arr[size - 1]);
        size--;

        sift_down(0);

        return result;
    }

    ~Heap() { delete[] arr; }
};

int main()
{
    Heap<int> heap;

    int total_arrs_count, arr_length, tmp;
    std::cin >> total_arrs_count;
    for (int i = 0; i < total_arrs_count; i++) {
        std::cin >> arr_length;
        for (int j = 0; j < arr_length; j++) {
            std::cin >> tmp;
            heap.push(tmp);
        }
    }

    unsigned int count = heap.length();
    for (int i = 0; i < count; i++)
        std::cout << heap.pop() << " ";

    return 0;
}