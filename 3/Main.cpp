//  3_1.Реализовать очередь с динамическим зацикленным буфером(на основе динамического массива).
//  Требования: Очередь должна быть реализована в виде класса.

// 3_2.Реализовать дек с динамическим зацикленным буфером(на основе динамического массива).
// Требования: Дек должен быть реализован в виде класса.

// 3_3.Реализовать очередь с помощью двух стеков.
// Требования: Очередь должна быть реализована в виде класса.Стек тоже должен быть реализован в виде класса.

#include <iostream>

// 3.1
class Queue_1 {
private:
    int* arr;
    unsigned int begin_idx, end_idx;
    unsigned int size;
    unsigned int capacity = 8;

public:
    Queue_1() : begin_idx(0), end_idx(0), size(0) { arr = new int[capacity]; }

    void push_back(unsigned int value) {
        if (size == 0) {
            begin_idx = 0;
            end_idx = 0;
            arr[end_idx] = value;
            size++;
        }
        else if (size + 1 < capacity) {
            if (end_idx + 1 < capacity) {
                end_idx++;
                arr[end_idx] = value;
                size++;
            }
            else {
                end_idx = 0;
                arr[end_idx] = value;
                size++;
            }
        }
        else {
            int* tmp_arr = new int[capacity];
            if (end_idx > begin_idx) {
                for (int i = 0; i <= capacity; i++)
                    tmp_arr[i] = arr[i];
            }
            else {
                for (int i = 0; i < capacity - begin_idx; i++)
                    tmp_arr[i] = arr[begin_idx + i];
                for (int i = 0; i <= end_idx; i++)
                    tmp_arr[capacity - begin_idx + i] = arr[i];
            }
            delete[] arr;
            arr = new int[capacity * 2];
            for (int i = 0; i < capacity; i++)
                arr[i] = tmp_arr[i];
            delete[] tmp_arr;
            begin_idx = 0;
            end_idx = capacity;
            arr[end_idx] = value;
            capacity *= 2;
            size++;
        }

        //if (size == 0) {
        //    begin_idx = 0;
        //    end_idx = 0;
        //    arr[0] = value;
        //}
        //else if (size < capacity) {
        //    end_idx = (end_idx + 1) % capacity;
        //    arr[end_idx] = value;
        //}
        //else {
        //    int* tmp_arr = new int[capacity];
        //    if (begin_idx < end_idx) {
        //        for (unsigned int i = begin_idx; i <= end_idx; i++)
        //            tmp_arr[i] = arr[i];
        //    }
        //    else {
        //        unsigned int pos_counter = 0;
        //        for (unsigned int i = begin_idx; i < capacity; i++) {
        //            tmp_arr[i] = arr[i];
        //            pos_counter++;
        //        }
        //        for (unsigned int i = 0; i <= end_idx; i++)
        //            tmp_arr[i + pos_counter] = arr[i];
        //    }
        //    delete[] arr;
        //    arr = new int[capacity * 2];
        //    for (unsigned int i = 0; i < capacity; i++)
        //        arr[i] = tmp_arr[i];
        //    delete[] tmp_arr;
        //    begin_idx = 0;
        //    end_idx = capacity;
        //    arr[end_idx] = value;
        //    capacity *= 2;
        //}
        //size++;
    }

    int pop_front() {
        if (!size)
            return -1;
        else {
            size--;
            if (begin_idx + 1 >= capacity) {
                begin_idx = 0;
                return arr[capacity - 1];
            }
            else
                return arr[begin_idx++];
        }
    }

    ~Queue_1() { delete[] arr; }
};

bool execute(Queue_1* queue, unsigned int command, unsigned int value) {
    if (command == 2) {
        return value == queue->pop_front();
    }
    else if (command == 3) {
        queue->push_back(value);
        return true;
    }
}

// 3.2

// 3.3
class Stack {
private:
    int* arr;
    unsigned int size;
    unsigned int capacity = 8;

public:
    Stack() : size(0) { arr = new int[capacity]; }

    void push_back(unsigned int value) {
        if (size + 1 <= capacity) {
            arr[size++] = value;
        }
        else {
            int* tmp_arr = new int[capacity];
            for (unsigned int i = 0; i < capacity; i++)
                tmp_arr[i] = arr[i];
            delete[] arr;
            arr = new int[capacity * 2];
            for (unsigned int i = 0; i < capacity; i++)
                arr[i] = tmp_arr[i];
            delete[] tmp_arr;
            arr[size++] = value;
            capacity *= 2;
        }
    }

    int pop_back() {
        if (!size)
            return -1;
        return arr[--size];
    }

    unsigned int length() { return size; }

    ~Stack() { delete[] arr; }
};

class Queue_3 {
private:
    Stack* input, * output;

public:
    Queue_3() {
        input = new Stack();
        output = new Stack();
    }

    void push_back(unsigned int value) { input->push_back(value); }

    int pop_front() {
        if (input->length() == 0 && output->length() == 0) return -1;
        if (output->length() == 0) {
            while (input->length() > 0)
                output->push_back(input->pop_back());
        }
        return output->pop_back();
    }

    ~Queue_3() { delete input, output; }
};

bool execute(Queue_3* queue, unsigned int command, unsigned int value) {
    if (command == 2) {
        return value == queue->pop_front();
    }
    else if (command == 3) {
        queue->push_back(value);
        return true;
    }
}

int main() {
    // 3.1
    Queue_1* queue = new Queue_1();
    unsigned int operations, command, value;
    bool flag = true;
    
    std::cin >> operations;
    for (unsigned int i = 0; i < operations; i++) {
        std::cin >> command >> value;
        if (!execute(queue, command, value)) { flag = false; }
    }
    if (flag)
        std::cout << "YES" << std::endl;
    else
        std::cout << "NO" << std::endl;

    // 3.3
    //Queue_3* queue = new Queue_3();
    //unsigned int operations, command, value;
    //bool flag = true;
    //
    //std::cin >> operations;
    //for (unsigned int i = 0; i < operations; i++) {
    //    std::cin >> command >> value;
    //    if (!execute(queue, command, value)) { flag = false; }
    //}
    //if (flag)
    //    std::cout << "YES" << std::endl;
    //else
    //    std::cout << "NO" << std::endl;

    return 0;
}

//16
//3 1
//3 2
//3 3
//3 4
//2 1
//2 2
//3 5
//3 6
//3 7
//3 8
//2 3
//2 4
//3 9
//3 10
//2 5
//2 6
//YES

//16
//3 1
//3 2
//3 3
//3 4
//3 5
//3 6
//2 1
//2 2
//2 3
//3 7
//3 8
//3 9
//2 4
//2 5
//2 6
//2 7
//YES