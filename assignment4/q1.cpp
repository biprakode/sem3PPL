#include <iostream>
#include <vector>
using namespace std;

class account {
    int account_number;
    static int ac_num_counter;
    int balance;
    
    public:
    account(int bal) {
        account_number = ac_num_counter;
        ac_num_counter++;
        balance = bal;
    }

    int get_ac_num() {
        return account_number;
    }

    void get_info() {
        cout << "Account Number:- " << account_number << endl;
        cout << "available balance:- " << balance << endl;
    }

    void deposit(int money) {
        balance+=money;
        cout << "new balance:- " << balance << endl;
    }

    void withdraw(int money) {
        if(balance >= money) {
            balance -= money;
            cout << "new balance:- " << balance << endl;
        }else {
            cout << "Insufficient funds" << endl;
            return;
        }
    }
};

void transaction(vector<account> &accounts , const string type , int ac_num , int money) {
    int found = 0;
    account* target = nullptr;
    for(auto &i : accounts) {
        if(i.get_ac_num() == ac_num) {
            found = 1;
            target = &i;
            break;
        }
    }
    if(!found) {
        cout << "Transaction error account number incorrect" << endl;
    } else {
        if(type == "w") {
            target->withdraw(money);
        } else if (type == "d") {
            target->deposit(money);
        } else {
            cout << "Invalid option" << endl;
        }
    }
}

int main() {
    vector<account> accounts;
    while(1) {
        cout << "Enter intial balance:- ";
        int bal;
        cin >> bal;
        accounts.push_back(account(bal));
        cout << "another?";
        char choice;
        cin >> choice;
        if(!(choice == 'y' || choice == 'Y')){
            break;
        }
    }
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Account\n";
        cout << "2. Transaction (Deposit/Withdraw)\n";
        cout << "3. View Accounts\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        int option;
        cin >> option;

        if (option == 1) {
            cout << "Enter initial balance: ";
            int bal;
            cin >> bal;
            accounts.push_back(account(bal));
        } else if (option == 2) {
            cout << "Enter account number: ";
            int ac_num;
            cin >> ac_num;
            cout << "Enter transaction type ('d' for deposit, 'w' for withdraw): ";
            string t;
            cin >> t;
            cout << "Enter amount: ";
            int amount;
            cin >> amount;
            transaction(accounts, t, ac_num, amount);
        } else if (option == 3) {
            for (auto &acc : accounts) {
                acc.get_info();
                cout << endl;
            }
        } else if (option == 4) {
            break;
        } else {
            cout << "Invalid option." << endl;
        }
    }

}