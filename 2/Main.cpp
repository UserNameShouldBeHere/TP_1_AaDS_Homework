// 2_1.Дан отсортированный массив целых чисел A[0..n - 1] и массив целых чисел B[0..m - 1].Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, равного или превосходящего B[i]: A[k] >= B[i].Если такого элемента нет, выведите n.n, m ≤ 10000.
// Требования : Время работы поиска k для каждого элемента B[i] : O(log(k)).Внимание!В этой задаче для каждого B[i] сначала нужно определить диапазон для бинарного поиска размером порядка k с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.
// Формат входных данных.
// В первой строчке записаны числа n и m.Во второй и третьей массивы A и B соответственно.

// 2_2.Дан массив целых чисел А[0..n - 1].Известно, что на интервале[0, m] значения массива строго возрастают, а на интервале[m, n - 1] строго убывают.Найти m за O(log m).
// Требования:  Время работы O(log m).Внимание!В этой задаче сначала нужно определить диапазон для бинарного поиска размером порядка m с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.
// 2 ≤ n ≤ 10000.

// 2_3.Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию.A[0..n - 1] и B[0..m - 1].n >> m.Найдите их пересечение.
// Требования: Время работы : O(m* log k), где k - позиция элемента B[m - 1] в массиве A..В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i - 1].Внимание!В этой задаче для каждого B[i] сначала нужно определить диапазон для бинарного поиска размером порядка k с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.
// n, k ≤ 10000.

// 2_4.Дан отсортированный массив различных целых чисел A[0..n - 1] и массив целых чисел B[0..m - 1].Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
// Требования: Время работы поиска для каждого элемента B[i] : O(log(k)).Внимание!В этой задаче для каждого B[i] сначала нужно определить диапазон для бинарного поиска размером порядка k с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.

#include <iostream>
#include <cmath>

// 2.1
unsigned short binary_search_1(int* arr, unsigned short begin, unsigned short end, int key) {
    unsigned short mid;
    while (begin < end) {
        mid = std::round((begin + end) / 2);
        if (arr[mid] >= key) end = mid;
        else begin = mid + 1;
    }
    return end;
}

void find_greater_or_equal(int* arr1, unsigned short arr1_length, int* arr2, unsigned short arr2_length, int* result) {
    unsigned short search_pos, result_pos;
    for (unsigned short i = 0; i < arr2_length; i++) {
        search_pos = 1;
        while (search_pos < arr1_length) {
            if (arr1[search_pos] >= arr2[i]) break;
            search_pos *= 2;
        }
        result_pos = binary_search_1(arr1, search_pos / 2, search_pos >= arr1_length ? arr1_length - 1 : search_pos, arr2[i]);
        result[i] = arr1[result_pos] >= arr2[i] ? result_pos : arr1_length;
    }
}

// 2.2
unsigned short binary_search_2(int* arr, unsigned short begin, unsigned short end) {
    unsigned short mid;
    while (begin < end) {
        mid = std::round((begin + end) / 2);
        if (arr[mid] < arr[mid + 1]) begin = mid + 1;
        else end = mid;
    }
    return end;
}

unsigned short find_increasing_interval_end(int* arr, unsigned short arr_length) {
    unsigned short search_pos = 1;
    while (search_pos < arr_length) {
        if (arr[search_pos] < arr[search_pos - 1]) break;
        search_pos *= 2;
    }
    return binary_search_2(arr, search_pos / 2, search_pos >= arr_length ? arr_length - 1 : search_pos);
}

// 2.3
unsigned short binary_search_3(int* arr, unsigned short begin, unsigned short end, int key) {
    unsigned short mid;
    while (begin < end) {
        mid = std::round((begin + end) / 2);
        if (arr[mid] >= key) end = mid;
        else begin = mid + 1;
    }
    return end;
}

unsigned short find_intersection(int* arr1, unsigned short arr1_length, int* arr2, unsigned short arr2_length, int* result) {
    unsigned short counter = 0;
    unsigned short search_pos = 1, result_pos;
    for (unsigned short i = 0; i < arr2_length; i++) {
        while (search_pos < arr1_length - 1) {
            if (arr1[search_pos] >= arr2[i]) break;
            search_pos *= 2;
        }
        result_pos = binary_search_3(arr1, search_pos / 2, search_pos >= arr1_length ? arr1_length - 1 : search_pos, arr2[i]);
        if (arr1[result_pos] == arr2[i]) {
            result[counter++] = arr2[i];
        }
    }
    return counter;
}

// 2.4
short binary_search_4(int* arr, unsigned int begin, unsigned int end, int key) {
    short mid;
    while (begin < end) {
        mid = (begin + end) / 2;
        if (arr[mid] >= key) end = mid;
        else begin = mid + 1;
    }
    return end;
}

void find_nearlest(int* arr1, unsigned int arr1_length, int* arr2, unsigned short arr2_length) {
    int search_pos, result_pos;
    for (short i = 0; i < arr2_length; i++) {
        search_pos = 1;
        while (search_pos < arr1_length && arr1[search_pos] < arr2[i]) {
            search_pos *= 2;
        }
        search_pos = search_pos >= arr1_length ? arr1_length - 1 : search_pos;
        result_pos = binary_search_4(arr1, search_pos / 2, search_pos, arr2[i]);
        if (result_pos > 0) {
            //if (arr2[i] - arr1[result_pos - 1] <= arr1[result_pos] - arr2[i]) {
            //    search_pos = (result_pos - 1) / 2;
            //    while (arr1[result_pos - 1] == arr1[search_pos] && search_pos > 0)
            //        search_pos /= 2;
            //    result_pos = binary_search_4(arr1, search_pos / 10, result_pos - 1, arr1[result_pos - 1]);
            //}
            //if (abs(arr2[i] - arr1[result_pos - 1]) <= abs(arr1[result_pos] - arr2[i]))
            if (2 * arr2[i] - arr1[result_pos] - arr1[result_pos - 1] <= 0)
                result_pos = binary_search_4(arr1, 0, result_pos, arr1[result_pos - 1]);
        }
        std::cout << result_pos << ' ';
    }
}

int main() {
    // 2.1
    //unsigned short arr1_length, arr2_length;
    //int* arr1, * arr2, * result;

    //std::cin >> arr1_length >> arr2_length;
    //arr1 = new int[arr1_length];
    //arr2 = new int[arr2_length];
    //result = new int[arr2_length];
    //for (unsigned short i = 0; i < arr1_length; i++)
    //    std::cin >> arr1[i];
    //for (unsigned short i = 0; i < arr2_length; i++)
    //    std::cin >> arr2[i];

    //find_greater_or_equal(arr1, arr1_length, arr2, arr2_length, result);

    //for (unsigned short i = 0; i < arr2_length; i++)
    //    std::cout << result[i] << ' ';

    //delete[] arr1, arr2, result;

    // 2.2
    //unsigned short arr_length;
    //int* arr;

    //std::cin >> arr_length;
    //arr = new int[arr_length];
    //for (unsigned short i = 0; i < arr_length; i++)
    //    std::cin >> arr[i];

    //std::cout << find_increasing_interval_end(arr, arr_length) << std::endl;

    //delete[] arr;

    // 2.3
    //unsigned short arr1_length, arr2_length;
    //int* arr1, * arr2, * result;

    //std::cin >> arr1_length >> arr2_length;
    //arr1 = new int[arr1_length];
    //arr2 = new int[arr2_length];
    //result = new int[arr2_length];
    //for (unsigned short i = 0; i < arr1_length; i++)
    //    std::cin >> arr1[i];
    //for (unsigned short i = 0; i < arr2_length; i++)
    //    std::cin >> arr2[i];

    //unsigned short result_length = find_intersection(arr1, arr1_length, arr2, arr2_length, result);
    //for (unsigned short i = 0; i < result_length; i++) {
    //    std::cout << result[i] << ' ';
    //}

    //delete[] arr1, arr2, result;

    // 2.4
    //unsigned int arr1_length;
    //unsigned short arr2_length;
    //int* arr1, * arr2, * result;

    //std::cin >> arr1_length;
    //arr1 = new int[arr1_length];
    //for (unsigned int i = 0; i < arr1_length; i++)
    //    std::cin >> arr1[i];
    //std::cin >> arr2_length;
    //arr2 = new int[arr2_length];
    //result = new int[arr2_length];
    //for (unsigned short i = 0; i < arr2_length; i++)
    //    std::cin >> arr2[i];

    //find_nearlest(arr1, arr1_length, arr2, arr2_length, result);

    //for (unsigned short i = 0; i < arr2_length; i++) {
    //    std::cout << result[i] << ' ';
    //}

    //delete[] arr1, arr2, result;
    unsigned int arr1_length;
    unsigned short arr2_length;
    int* arr1, * arr2;

    std::cin >> arr1_length;
    arr1 = new int[arr1_length];
    for (unsigned int i = 0; i < arr1_length; i++)
        std::cin >> arr1[i];
    std::cin >> arr2_length;
    arr2 = new int[arr2_length];
    for (unsigned short i = 0; i < arr2_length; i++)
        std::cin >> arr2[i];

    if (arr1_length == 0) {
        for (int i = 0; i < arr2_length; i++)
            std::cout << 0 << ' ';
    }
    else
        find_nearlest(arr1, arr1_length, arr2, arr2_length);

    delete[] arr1, arr2;

    return 0;
}

//60
//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
//3 3 3 3 3 3 3 3 3 3
//3 3 3 3 3 3 3 3 3 3
//3 3 3 3 3 3 3 3 3 3
//3 3 3 3 3 3 3 3 3 3 3 3 3 5
//3
//2 4 6
//0 16 59

//3
//2 4 6
//3
//2 4 6
//0 1 2

//3
//10 20 30
//4
//8 9 10 32
//0 0 0 2

//60
//2 2 2 2 2 2 2 2 2 2
//2 2 2 2 2 2 2 2 2 2
//2 2 2 2 2 2 2 2 2 2
//2 2 2 2 2 4 4 4 4 4
//4 4 4 4 4 4 4 4 4 4
//4 4 4 4 4 4 4 4 4 4
//1
//3
//0

//3
//10 20 30
//3
//9 15 35
//0 0 2