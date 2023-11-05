// 6.3 Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.

#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

template <typename T>
struct Comparator {
    bool operator()(const T& lhs, const T& rhs) const {
        return lhs < rhs;
    }
};

template <typename T, typename Comp>
int partition(T* arr, int left, int right, Comp comp) {
    int pivot_idx = rand() % (right - left) + left;
    T pivot = arr[pivot_idx];

    std::swap(arr[right], arr[pivot_idx]);

    int i = left;
    while (comp(arr[i], pivot) && (i < right))
        i++;

    int j = i + 1 > right ? right : i + 1;

    while (j < right) {
        if (comp(arr[j], pivot)) {
            std::swap(arr[i], arr[j]);
            i++;
        }
        j++;
    }
    std::swap(arr[right], arr[i]);
    return i;
}

template <typename T, typename Comp = Comparator<T>>
T kth_element(T* arr, int arr_length, int percentile, Comp comp = Comp()) {
    int left = 0, right = arr_length - 1;

    while (left < right) {
        int mid = partition(arr, left, right, comp);
        if (percentile == mid)
            return arr[mid];
        else if (percentile < mid)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return arr[left];
}

int main() {
    srand(time(NULL));

    int arr_length;
    int* arr;

    std::cin >> arr_length;
    arr = new int[arr_length];
    for (int i = 0; i < arr_length; i++)
        std::cin >> arr[i];

    std::cout << kth_element(arr, arr_length, arr_length * 0.1) << std::endl;

    std::cout << kth_element(arr, arr_length, arr_length * 0.5) << std::endl;

    std::cout << kth_element(arr, arr_length, arr_length * 0.9) << std::endl;

    return 0;
}