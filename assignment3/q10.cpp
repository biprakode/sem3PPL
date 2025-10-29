#include <iostream>
class Student_Class {
private:
    int roll;
    std::string name;
    std::string course;
    std::string admissionDate;
    int marks[5];
    static int studentCount;

public:
    Student_Class() {
        for (int i = 0; i < 5; ++i) {
            marks[i] = 0;
        }
        studentCount++;
    }

    void receiveAdmissionData() {
        std::cout << "Enter Roll Number: ";
        std::cin >> roll;
        std::cin.ignore(); 
        std::cout << "Enter Student Name: ";
        std::getline(std::cin, name);
        std::cout << "Enter Course: ";
        std::getline(std::cin, course);
        std::cout << "Enter Admission Date (DD/MM/YYYY): ";
        std::getline(std::cin, admissionDate);
        std::cout << "Admission data received for: " << name << std::endl;
    }

    void receiveMarks() {
        std::cout << "\n--- Receiving Marks for " << name << " (Roll " << roll << ") ---" << std::endl;
        for (int i = 0; i < 5; ++i) {
            std::cout << "Enter Mark for Subject " << (i + 1) << ": ";
            std::cin >> marks[i];
        }
        std::cin.ignore(10000, '\n'); 
        std::cout << "Marks successfully recorded." << std::endl;
    }

    void prepareMarkSheet() const {
        int totalMarks = 0;
        for (int i = 0; i < 5; ++i) {
            totalMarks += marks[i];
        }
        double percentage = (double)totalMarks / 5.0;

        std::cout << "Roll No: " << roll << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Course: " << course << std::endl;
        std::cout << "Admission Date: " << admissionDate << std::endl;
        for (int i = 0; i < 5; ++i) {
            std::cout << "Subject " << (i + 1) << " Mark: " << marks[i] << std::endl;
        }
        std::cout << "total marks:"  << totalMarks << " / 500" << std::endl;
        std::cout << "percentage: " << percentage << "%" << std::endl;
    }

    static int getNumberStudents() {
        return studentCount;
    }
};

int Student_Class::studentCount = 0;
