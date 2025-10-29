#include <iostream>
class Applicant {
private:
    int applicationId;
    std::string name;
    int score;
    static int nextId;

public:
    Applicant() : applicationId(++nextId) {}

    void receiveData() {
        std::cout << "Enter Applicant Name: ";
        std::cin >> name;
        std::cout << "Enter Applicant Score: ";
        std::cin >> score;
    }

    void showDetails() const {
        std::cout << "Applicant ID: " << applicationId << ", Name: " << name << ", Score: " << score << std::endl;
    }

    static int getNumberApplicants() {
        return nextId;
    }
};
int Applicant::nextId = 0;