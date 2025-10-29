#include <iostream>
class Time {
    int h;
    int m;
    int s;

    void printPadded(int val) const {
        if (val < 10) {
            std::cout << "0";
        }
        std::cout << val;
    }

public:
    void input24hr();
    void inputAMPM();
    void display24hr() const;
    void displayAMPM() const;
};

void Time::input24hr() {
    std::cout << "Enter time (HH MM SS 24-hr): ";
    std::cin >> h >> m >> s;
}

void Time::inputAMPM() {
    int input_h, input_m, input_s;
    std::string period_str;

    std::cout << "Enter time (HH MM SS AM/PM): ";
    std::cin >> input_h >> input_m >> input_s >> period_str;

    char period_char = std::toupper(period_str[0]);
    
    h = input_h;
    m = input_m;
    s = input_s;

    if (period_char == 'P' && h != 12) {
        h += 12; // e.g., 1 PM -> 13
    } else if (period_char == 'A' && h == 12) {
        h = 0;   // 12 AM (midnight) -> 0
    }
}

void Time::display24hr() const {
    std::cout << "24-hr Time: ";
    printPadded(h);
    std::cout << ":";
    printPadded(m);
    std::cout << ":";
    printPadded(s);
    std::cout << std::endl;
}

void Time::displayAMPM() const {
    std::string period = (h >= 12) ? "PM" : "AM";
    int display_h = (h == 0 || h == 12) ? 12 : (h % 12);
    
    std::cout << "AM/PM Time: ";
    printPadded(display_h);
    std::cout << ":";
    printPadded(m);
    std::cout << ":";
    printPadded(s);
    std::cout << " " << period << std::endl;
}
