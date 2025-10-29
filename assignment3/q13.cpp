#include <iostream>

class Balance {
private:
    int accountNumber;
    double balance;
    std::string lastUpdateDate;

public:
    Balance(int accNum, double initialBalance, const std::string& date) 
        : accountNumber(accNum), balance(initialBalance), lastUpdateDate(date) {}

    void updateBalance(double amount, const std::string& date) {
        balance += amount;
        lastUpdateDate = date;
    }
    
    double getBalance() {
        return balance;
    }
    
    int getAccountNumber() {
        return accountNumber;
    }

    void showDetails() {
        std::cout << "\nAccount Status (" << accountNumber << ") ---" << std::endl;
        std::cout << "Current Balance: " << balance << std::endl;
        std::cout << "Last Update: " << lastUpdateDate << std::endl;
    }
};

class Transaction {
private:
    int accountNumber;
    std::string dateOfTransaction;
    double amount;
    char transactionType;

public:
    Transaction(int accNum, const std::string& date, double amt, char type) 
        : accountNumber(accNum), dateOfTransaction(date), amount(amt), transactionType(std::toupper(type)) {}

    void processTransaction(Balance& account) {
        if (accountNumber != account.getAccountNumber()) {
            std::cout << "Transaction failed: Account number mismatch." << std::endl;
            return;
        }

        if (transactionType == 'D') {
            account.updateBalance(amount, dateOfTransaction);
            std::cout << "Deposit successful. Amount: " << amount << std::endl;

        } else if (transactionType == 'W') {
            if (account.getBalance() >= amount) {
                account.updateBalance(-amount, dateOfTransaction);
                std::cout << "Withdrawal successful. Amount: " << amount << std::endl;
            } else {
                std::cout << "Transaction failed: Insufficient funds for withdrawal of " << amount 
                          << ". Current balance: " << account.getBalance() << std::endl;
            }
        } else {
            std::cout << "Transaction failed: Invalid transaction type (" << transactionType << ")." << std::endl;
        }
    }
};