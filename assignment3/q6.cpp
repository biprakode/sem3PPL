#include <iostream>

struct Student {
    int roll;
    int score;

    void inputData() {
        std::cout << "Enter Roll No: ";
        std::cin >> roll;
        std::cout << "Enter Score: ";
        std::cin >> score;
    }

    void showData() {
        std::cout << "Roll: " << roll << ", Score: " << score << std::endl;
    }
};

void modifyScore(Student& s, int newScore) {
    s.score = newScore;
}

void showStudentData(const Student& s) {
    std::cout << "Global show: Roll: " << s.roll << ", Score: " << s.score << std::endl;
}

int main() {

    Student s1;

    s1.inputData();
    s1.showData();
    modifyScore(s1, 95);
    showStudentData(s1);

    return 0;
}