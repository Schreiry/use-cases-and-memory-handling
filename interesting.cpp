// INTEGRATION SPACE : 

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include <fstream>
#include <chrono>
#include <random>


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- //
using namespace std;
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- //

// Пример функции для записи сообщения в лог
//void logMessage(const string& message) {
//    ofstream logFile("log.txt", ios::app);
//    if (logFile.is_open()) {
//        // Получаем текущее время
//        time_t currentTime = std::time(nullptr);
//        char timeStr[26];
//        // Используем ctime_s вместо устаревшей ctime
//        ctime_s(timeStr, sizeof(timeStr), &currentTime);
//        logFile << timeStr << " " << message << endl;
//
//        logMessage("massege");
//    }
//}




// Example 1: Pointers and memory handling

//int main() {
//
//    int a = 10; // Обычная переменная
//    int* ptr = &a; // Указатель на переменную a
//
//    cout << "Value of variable a : " << a << endl;
//    cout << "Value address a : " << &a << endl;
//    cout << "Pointer value ptr : " << ptr << endl;
//    cout << "Index  ptr : " << *ptr << endl;
//
//    *ptr = 20; // Изменение значения через указатель
//    cout << "New value of the variable a : " << a << endl;
//
//
//
//    return 0;
//}

// 2 

//int main() {
//	int* ptr = new int; // Выделение памяти для переменной типа int
//	*ptr = 10; // Присвоение значения
//	cout << "Value of the variable : " << *ptr << endl;
//	delete ptr; // Освобождение памяти
//	return 0;
//}


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- //

// Example 2: Dynamic memory allocation



//int main() {
//    int* arr = new int[5]; // Динамическое выделение памяти для массива из 5 элементов
//
//    // Заполнение массива
//    for (int i = 0; i < 5; i++) {
//        arr[i] = i * 10;
//    }
//
//    // Вывод массива
//    cout << "Array : ";
//    for ( int i = 0; i < 5; i++ ) {
//        cout << arr[i] << " ";
//    }
//    cout << endl;
//
//    delete[] arr; // Освобождение памяти
//    return 0;
//}


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- //

// mutex - для синхронизации доступа к общим ресурсам
//mutex mtx;
//
//// Логирование транзакций
//void logTransaction(const string& message) {
//    lock_guard<mutex> lock(mtx);
//    ofstream logFile("transactions.log", ios::app);
//    if (logFile.is_open()) {
//        auto now = chrono::system_clock::now();
//        time_t time = chrono::system_clock::to_time_t(now);
//        char buffer[26];
//        ctime_s(buffer, sizeof(buffer), &time); // Используем ctime_s вместо ctime
//        logFile << buffer << " " << message << endl;
//    }
//}
//
//// Класс Счет
//class Account {
//private:
//    string accountNumber;
//    double balance;
//
//public:
//    Account(const string& accNumber, double initialBalance)
//        : accountNumber(accNumber), balance(initialBalance) {
//    }
//
//    string getAccountNumber() const {
//        return accountNumber;
//    }
//
//    double getBalance() const {
//        return balance;
//    }
//
//    void deposit(double amount) {
//        balance += amount;
//        logTransaction("Deposit to account " + accountNumber + " for amount " + to_string(amount));
//        cout << "Deposit to account " << accountNumber << " for amount " << amount << endl;
//    }
//
//    void withdraw(double amount) {
//        if (balance >= amount) {
//            balance -= amount;
//            logTransaction("Withdrawal from account " + accountNumber + " for amount " + to_string(amount));
//            cout << "Withdrawal from account " << accountNumber << " for amount " << amount << endl;
//        }
//        else {
//            logTransaction("Error: Insufficient funds in account " + accountNumber);
//            cout << "Error: Insufficient funds in account " << accountNumber << endl;
//        }
//    }
//
//    void transfer(Account& toAccount, double amount) {
//        if (balance >= amount) {
//            balance -= amount;
//            toAccount.deposit(amount);
//            logTransaction("Transfer from account " + accountNumber + " to account " + toAccount.getAccountNumber() + " for amount " + to_string(amount));
//            cout << "Transfer from account " << accountNumber << " to account " << toAccount.getAccountNumber() << " for amount " << amount << endl;
//        }
//        else {
//            logTransaction("Error: Insufficient funds in account " + accountNumber + " for transfer");
//            cout << "Error: Insufficient funds in account " << accountNumber << " for transfer" << endl;
//        }
//    }
//};
//
//// Класс Клиент
//class Client {
//private:
//    string name;
//    int id;
//    vector<shared_ptr<Account>> accounts;
//
//public:
//    Client(const string& clientName, int clientId)
//        : name(clientName), id(clientId) {
//    }
//
//    void addAccount(const shared_ptr<Account>& account) {
//        accounts.push_back(account);
//    }
//
//    void listAccounts() const {
//        cout << "Accounts of client " << name << ":" << endl;
//        for (const auto& account : accounts) {
//            cout << "Account: " << account->getAccountNumber() << ", Balance: " << account->getBalance() << endl;
//        }
//    }
//
//    shared_ptr<Account> getAccount(const string& accountNumber) {
//        for (const auto& account : accounts) {
//            if (account->getAccountNumber() == accountNumber) {
//                return account;
//            }
//        }
//        return nullptr;
//    }
//};
//
//// Класс Банк
//class Bank {
//private:
//    vector<shared_ptr<Client>> clients;
//
//public:
//    void addClient(const shared_ptr<Client>& client) {
//        clients.push_back(client);
//    }
//
//    void simulateTransactions() {
//        vector<thread> threads;
//        random_device rd;
//        mt19937 gen(rd());
//        uniform_int_distribution<> clientDist(0, clients.size() - 1);
//        uniform_real_distribution<> amountDist(10, 5000);
//
//        for (int i = 0; i < 10; ++i) {
//            threads.emplace_back([this, &clientDist, &gen, &amountDist]() {
//                int fromClientIndex = clientDist(gen);
//                int toClientIndex = clientDist(gen);
//                double amount = amountDist(gen);
//
//                if (fromClientIndex != toClientIndex) {
//                    auto fromClient = clients[fromClientIndex];
//                    auto toClient = clients[toClientIndex];
//
//                    auto fromAccount = fromClient->getAccount("ACC001"); // Пример счета
//                    auto toAccount = toClient->getAccount("ACC002"); // Пример счета
//         
//
//                    if (fromAccount && toAccount) {
//                        fromAccount->transfer(*toAccount, amount);
//                    }
//                }
//                });
//        }
//
//        for (auto& thread : threads) {
//            thread.join();
//        }
//    }
//
//    void listAllClients() const {
//        cout << "List of all clients:" << endl;
//        for (const auto& client : clients) {
//            client->listAccounts();
//        }
//    }
//};
//
//int main() {
//    Bank bank;
//
//    // Создаем клиентов и счета
//    auto client1 = make_shared<Client>("Mirian Putkaradze", 1);
//    auto client2 = make_shared<Client>("Alexander Tsurtsumia", 2);
//    auto client3 = make_shared<Client>("Tamar Tinikashvili", 3);
//    auto client4 = make_shared<Client>("Andrey Greve", 4);
//    auto client5 = make_shared<Client>("Alexander Greve", 5);
//    auto client6 = make_shared<Client>("David Greve", 6);
//
//    auto account1 = make_shared<Account>("ACC001", 1500);
//    auto account2 = make_shared<Account>("ACC002", 502);
//    auto account3 = make_shared<Account>("ACC003", 724);
//    auto account4 = make_shared<Account>("ACC004", 4500);
//    auto account5 = make_shared<Account>("ACC005", 2300);
//    auto account6 = make_shared<Account>("ACC006", 230);
//
//
//    client1->addAccount(account1);
//    client2->addAccount(account2);
//    client3->addAccount(account3);
//    client4->addAccount(account4);
//    client5->addAccount(account5);
//    client6->addAccount(account6);
//
//
//    bank.addClient(client1);
//    bank.addClient(client2);
//    bank.addClient(client3);
//    bank.addClient(client4);
//    bank.addClient(client5);
//    bank.addClient(client6);
//
//    // Симуляция транзакций
//    cout << "Starting transaction simulation..." << endl;
//    bank.simulateTransactions();
//    cout << "Transaction simulation completed." << endl;
//
//    // Вывод информации о клиентах
//    bank.listAllClients();
//
//    return 0;
//}



// Example 4: Memory leaks and their prevention

#include <iostream>

//int main() {
//    // Утечка памяти (не освобождаем память)
//    int* leak = new int;
//    *leak = 100;
//    cout << "value: " << *leak << std::endl;
//
//    // Правильное использование (освобождаем память)
//    int* noLeak = new int;
//    *noLeak = 200;
//    cout << "value: " << *noLeak << std::endl;
//    delete noLeak; // Освобождение памяти
//
//    return 0;
//}