#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <stdexcept>

using namespace std;

class Student {
public:
    uintptr_t roll;
    string name;
    Subject* subject_list;
    int max_sub;
    int sub_count;

    public:
    Student(const string name , int max_subj) : name(name) , max_sub(max_subj) , sub_count(0) {
        subject_list = new Subject[max_subj];
        roll = reinterpret_cast<std::uintptr_t>(this);
    }

    void enroll(Subject sub) {
        if (sub_count >= max_sub) {
            throw std::runtime_error("Max subject reached, no more please!");
        }
        
    }
};


class Subject {
public:
    uintptr_t roll;
    string name;
    Student* student_list;
    
};



