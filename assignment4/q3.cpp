#include <iostream>
#include <algorithm>
using namespace std;
template <typename T>

class my_array {
    T* data;
    size_t size;
    size_t capacity;

    void resize(size_t new_cap) {
        T *newData = new T[capacity];
        copy(data , data+size , newData);
        delete[] data;
        data = newData;
        capacity = new_cap;
    } 

    public:
    my_array()  : size(0), capacity(1) {
        data = new T[capacity];
    }

    my_array(int capacity) : capacity(capacity){
        data = new T[capacity];
    }

    my_array(my_array &arr) {
        size = arr.size;
        capacity = arr.capacity;
        data = new T[capacity];
        for (size_t i = 0; i < size; i++) {
            data[i] = arr.data[i];
        }
    }

    ~my_array() {
        delete[] data;
    }

    void push_back(const T &value) {
        if(size == capacity) {
            resize(capacity * 2);
        }
        data[size++] = value;
    }

    T &operator[](const T &index) {
        if(index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    T &operator[](const T &index) const {
        if(index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return capacity;
    }
};

template <typename T>
my_array<T> operator+(const my_array<T>& arr1, const my_array<T>& arr2) {
    const my_array<T> &bigger = (arr1.getSize() > arr2.getSize()) ? arr1 : arr2;
    const my_array<T> &smaller = (arr1.getSize() < arr2.getSize()) ? arr1 : arr2;
    my_array<T> result;
    size_t i = 0;
    for(; i < smaller.getSize(); i++) {
        result.push_back(smaller[i] + bigger[i]);
    }
    for(; i < bigger.getSize(); i++) {
        result.push_back(bigger[i]);
    }
    return result;
}

template <typename T>
my_array<T> operator*(const my_array<T>& arr1, const my_array<T>& arr2) {
    const my_array<T> &bigger = (arr1.getSize() > arr2.getSize())? arr1 : arr2;
    const my_array<T> &smaller = (arr1.getSize() < arr2.getSize()) ? arr1 : arr2;
    my_array<T> result;
    size_t i = 0;
    for(; i < smaller.getSize(); i++) {
        result.push_back(smaller[i] * bigger[i]);
    }
    for(; i < bigger.getSize(); i++) {
        result.push_back(bigger[i]);
    }
    return result;
}

int main() {
    my_array<float> arr1;
    my_array<float> arr2;
    
    // Fill arr1 with 1, 2, 3, 4, 5
    for (int i = 1; i <= 20; ++i) {
        arr1.push_back(i);
    }
    
    // Fill arr2 with 10, 20, 30
    for (int i = 1; i <= 10; ++i) {
        arr2.push_back(i * 10);
    }
    
    my_array<int> sum = arr1 + arr2;
    my_array<int> prod = arr1 * arr2;
    
    cout << "Array 1: ";
    for (size_t i = 0; i < arr1.getSize(); ++i) {
        cout << arr1[i] << " ";
    }
    
    cout << "\nArray 2: ";
    for (size_t i = 0; i < arr2.getSize(); ++i) {
        cout << arr2[i] << " ";
    }
    
    cout << "\nSum: ";
    for (size_t i = 0; i < sum.getSize(); ++i) {
        cout << sum[i] << " ";
    }
    
    cout << "\nProduct: ";
    for (size_t i = 0; i < prod.getSize(); ++i) {
        cout << prod[i] << " ";
    }
    
    cout << endl;
    return 0;
}