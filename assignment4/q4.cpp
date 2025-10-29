#include <iostream>
#include <cstdlib>

using namespace std;

class string_class;

int manual_strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

ostream& operator<<(ostream& os, const string_class& obj);
int operator>(const string_class &str1 , const string_class &str2);
int operator<(const string_class &str1 , const string_class &str2);
int operator==(const string_class &str1 , const string_class &str2);


class string_class {
private:
    char *str;
    size_t size;
    size_t capacity;

    void resize(size_t new_cap) {
        if (new_cap < size + 1) {
            new_cap = capacity << 1;
            while (new_cap < size + 1) {
                new_cap <<= 1;
            }
        }
        char *new_str = new char[new_cap];
        if (str) {
            for (size_t i = 0; i <= size; ++i) { 
                new_str[i] = str[i];
            }
            delete[] str;
        }

        str = new_str;
        capacity = new_cap;
    }

public:
    string_class(const char c='' , int str_size) : size(str_size) {
        capacity = size + 1;
        str = new char[capacity];
        
        for(size_t i = 0; i < size; ++i) {
            str[i] = c;
        }
        str[size] = '\0';
    }

    string_class(const string_class& other) : size(other.size), capacity(other.capacity) {
        str = new char[capacity];
        // Replaced std::copy
        for (size_t i = 0; i <= size; ++i) { 
            str[i] = other.str[i];
        }
    }

    string_class &operator=(const string_class &other) {
        if (this != &other) { 
            delete[] str;
            size = other.size;
            capacity = other.capacity;
            str = new char[capacity];
            for (size_t i = 0; i <= size; ++i) {
                str[i] = other.str[i];
            }
        }
        return *this;
    }


    string_class(const char *input_string = "") {
        size_t len = 0;
        if (input_string) {
            while (input_string[len] != '\0') { 
                len++;
            }
        }
        
        size = len;
        capacity = 16;
        while (capacity <= size) {
            capacity <<= 1;
        }

        str = new char[capacity];
        
        // Manual copy
        for (size_t i = 0; i < size; ++i) { 
            str[i] = input_string[i];
        }
        str[size] = '\0';
    }

    size_t getsize() const {
        return size;
    }

    // Mutable subscript operator - Fixed error handling (no std::out_of_range)
    char &operator[](const int index) {
        if(index < 0 || (size_t)index >= size) {
            cerr << "Error: Index out of bounds." << endl;
            exit(1);
        }
        return str[index];
    }
    
    // Const subscript operator
    const char &operator[](const int index) const {
        if(index < 0 || (size_t)index >= size) {
            cerr << "Error: Index out of bounds." << endl;
            exit(1);
        }
        return str[index];
    }

    string_class &operator+=(const string_class &other ) {
        size_t new_size = size + other.size;

        if (new_size >= capacity) {
            resize(new_size + 1);
        }

        for (size_t i = 0; i < other.size; ++i) {
            str[size + i] = other.str[i];
        }
        
        size = new_size;
        str[size] = '\0';
        return *this;
    }

    string_class operator+(const string_class& other) const {
        string_class temp = *this; 
        temp += other;
        return temp;
    }

    friend ostream& operator<<(ostream& os, const string_class& obj);
    friend int operator>(const string_class &str1 , const string_class &str2);
    friend int operator<(const string_class &str1 , const string_class &str2);
    friend int operator==(const string_class &str1 , const string_class &str2);

    void display() const {
        cout << *this;
    }

    ~string_class() {
        delete[] str;
        str = nullptr;
        size = 0;
        capacity = 0;
    }
};

ostream& operator<<(ostream& os, const string_class& obj) {
    if (obj.str) {
        os << obj.str;
    } else {
        os << "(null)";
    }
    return os;
}

int operator>(const string_class &str1 , const string_class &str2) {
    return manual_strcmp(str1.str, str2.str) > 0;
}

int operator<(const string_class &str1 , const string_class &str2) {
    return manual_strcmp(str1.str, str2.str) < 0;
}

int operator==(const string_class &str1 , const string_class &str2) {
    return manual_strcmp(str1.str, str2.str) == 0;
}


int main() {
    cout << "--- Custom String Class (C-Style) Demo ---" << endl;

    string_class s1("Hello");
    string_class s2(" World");
    string_class s3('!', 5);

    cout << "1. s1 (C-string): "; s1.display(); cout << endl;
    cout << "2. s3 (char, size): "; s3.display(); cout << endl;

    s1[0] = 'J';
    cout << "3. s1[0] changed: " << s1 << endl;

    string_class s4 = s1 + s2 + s3;
    cout << "4. s4 (s1 + s2 + s3): " << s4 << endl;

    s1 += " there";
    cout << "5. s1 after += \" there\": " << s1 << endl;
    
    // Testing comparison
    string_class comp1("apple");
    string_class comp2("apricot");
    string_class comp3("apple");
    cout << "\n6. Comparison Demo:" << endl;
    cout << "   \"apple\" > \"apricot\": " << (comp1 > comp2) << endl; 
    cout << "   \"apple\" < \"apricot\": " << (comp1 < comp2) << endl; 
    cout << "   \"apple\" == \"apple\": " << (comp1 == comp3) << endl; 

    // Test Copy/Assignment
    string_class s5 = s4; 
    string_class s6("Initial");
    s6 = s1; 

    cout << "\n7. s5 (Copy of s4): " << s5 << endl;
    cout << "   s6 (Assignment of s1): " << s6 << endl;

    return 0;
}
