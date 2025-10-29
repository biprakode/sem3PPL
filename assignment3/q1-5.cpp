#include <iostream>

//q1
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

//q2
int& max2(int& a, int& b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

//q3
int max1(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

double calculateTax(double income, double taxRate = 0.10) {
    return income * taxRate;
}

void f(int) {
    std::cout << "inside f(int)" << std::endl;
}

void f(float) {
    std::cout << "inside f(float)" << std::endl;
}

void f(int a, int b) {
    std::cout << "inside f(int, int)" << std::endl;
}

void f(char a, int b) {
    std::cout << "inside f(char, int)" << std::endl;
}

int main() {
    int i = 10;
    char c = 'a';
    float f_val = 3.14f;
    double d = 9.99;

    std::cout << "Call f(" << i << ") (int): ";
    f(i);

    //Promotes to int
    std::cout << "Call f('" << c << "') (char): ";
    f(c);

    // float actual argument -> Converts to float
    std::cout << "Call f(" << f_val << ") (float): ";
    f(f_val);

    // double actual argument -> Converts to double
    std::cout << "Call f(" << d << ") (double): ";
    //f(d);



    // int actual argument -> Exact match f(int)
    std::cout << "Call f(" << i << ") (int): ";
    f(i);

    // char actual argument -> Promotion to int
    std::cout << "Call f('" << c << "') (char): ";
    f(c);

    // float actual argument -> Exact match f(float)
    std::cout << "Call f(" << f_val << ") (float): ";
    f(f_val);

    // double actual argument -> Conversion to float
    std::cout << "Call f(" << d << ") (double): ";
    //f(d);

    std::cout << "\nCall f(int, char):" << std::endl;
    std::cout << "f(" << i << ", '" << c << "') -> ";
    f(i, c);

    std::cout << "\nCall f(char, char):" << std::endl;
    std::cout << "f('" << c << "', '" << c << "') -> ";
    f(c, c);

    std::cout << "\nCall f(float, float):" << std::endl;
    std::cout << "f(" << f_val << ", " << f_val << ") -> " << std::endl;
}