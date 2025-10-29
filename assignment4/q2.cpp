#include <iostream>
#include <cmath>
using namespace std;

class complex_num{
    double real;
    double img;
    bool divide_by_zero;

    public:
    complex_num();
	complex_num(complex_num&); // copy constructor
	complex_num(double,double);
	complex_num(char*);
    complex_num(bool); // construct divide_by_zero num
	double get_real();
	double get_img();
	double mag();
	double arg(); // in degree
    void DivideError(); // to be used by divide operator
	bool DivideByZero();
};

complex_num operator+(complex_num&,complex_num&);
complex_num operator-(complex_num&,complex_num&);
complex_num operator*(complex_num&,complex_num&);
complex_num operator/(complex_num&,complex_num&);

complex_num::complex_num() {
    this->real = 0.0;
    this->img = 0.0;
    this->divide_by_zero = false;
}
complex_num::complex_num(complex_num &c) {
    this->real = c.get_real();
    this->img = c.get_img();
    this->divide_by_zero = false;
}
complex_num::complex_num(double r , double i){
    this->real = r;
    this->img = i;
    this->divide_by_zero = false;
}
complex_num::complex_num(bool e) {
    this->real = 0.0;
    this->img = 0.0;
    this->divide_by_zero = true;
}
double complex_num::get_real() {
    return this->real;
}
double complex_num::get_img() {
    return this->img;
}

double complex_num::mag() {
    return sqrt(pow(this->img,2) + pow(this->real,2));
}

double complex_num::arg() {
    if (this->real == 0) return 1.0;
    return atan(this->img / this->real);
}


complex_num operator+(complex_num &c1 , complex_num &c2){
    double real = c1.get_real() + c2.get_real();
    double img = c1.get_img() + c2.get_img();
    return complex_num(real , img);
}

complex_num operator-(complex_num &c1 , complex_num &c2){
    double real = c1.get_real() - c2.get_real();
    double img = c1.get_img() - c2.get_img();
    return complex_num(real , img);
}

complex_num operator*(complex_num &c1 , complex_num &c2){
    double real = c1.get_real() * c2.get_real();
    double img = c1.get_img() * c2.get_img();
    return complex_num(real , img);
}

complex_num operator/(complex_num &c1 , complex_num &c2) {
    if(c2.get_real() == 0 || c2.get_img() == 0) {
        cout << "Divide by zero error" << endl;
        return complex_num(true);
    }
    double real = c1.get_real() / (c2.get_real()*c2.get_real() + c2.get_img()*c2.get_img());
    double img = c1.get_img() / (c2.get_real()*c2.get_real() + c2.get_img()*c2.get_img());
    return complex_num(real ,  img);
}

bool operator==(complex_num &c1 , complex_num &c2){
    bool real = c1.get_real() == c2.get_real();
    bool img = c1.get_img() == c2.get_img();
    return real & img;
}

