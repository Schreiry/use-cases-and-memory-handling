# C++ Memory Management & Multithreading Example
### This project demonstrates various aspects of C++ programming, including :

- Pointers and memory handling ; 

- Dynamic memory allocation ; 

- Multithreading and synchronization ; 

- Memory leak prevention ; 

- Logging and file handling ;
#
> [!NOTE]
> The code is divided into several sections, each focusing on a specific concept. Below, you'll find explanations and examples for each part.

## Pointers and Memory Handling
#### Explanation
Pointers are variables that store memory addresses. They allow direct manipulation of memory, which is useful for dynamic memory allocation, passing large data structures to functions, and more.

```C++
int main() {
    int a = 10; // Regular variable
    int* ptr = &a; // Pointer to variable 'a'

    cout << "Value of variable a: " << a << endl;
    cout << "Address of variable a: " << &a << endl;
    cout << "Value of pointer ptr: " << ptr << endl;
    cout << "Dereferenced value of ptr: " << *ptr << endl;

    *ptr = 20; // Modify value through pointer
    cout << "New value of variable a: " << a << endl;

    return 0;
}
```
* `int* ptr = &a;` creates a pointer ptr that stores the address of a.

* `*ptr` dereferences the pointer, allowing access to the value of a.

* Changing `*ptr` also changes the value of a.


## Dynamic Memory Allocation
Dynamic memory allocation allows programs to request memory at runtime. This is done using `new` and `delete` in C++.
```c++
int main() {
    int* arr = new int[5]; // Dynamically allocate memory for an array of 5 integers

    // Fill the array
    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
    }

    // Print the array
    cout << "Array: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr; // Free the allocated memory
    return 0;
}
```
- `new int[5]` allocates memory for an array of 5 integers.

- `delete[]` arr frees the memory to prevent memory leaks.

## Memory Leak Prevention
Memory leaks occur when dynamically allocated memory is not freed. Using `delete` or smart pointers prevents leaks.
```C++
int main() {
    // Memory leak (no delete)
    int* leak = new int;
    *leak = 100;
    cout << "Value: " << *leak << endl;

    // Proper usage (with delete)
    int* noLeak = new int;
    *noLeak = 200;
    cout << "Value: " << *noLeak << endl;
    delete noLeak; // Free memory

    return 0;
}
```
- `delete` frees memory allocated with new.

- Intelligent pointers ( e.g., `unique_ptr`, `shared_ptr` ) allow us to clearly see how neat and thoughtful, optimized memory works compared to regular memory, which we do not clean up afterwards.


## Full Example : Bank Simulation
### 📌 Overview
#### This project is a **multi-threaded banking simulation** implemented in C++. It demonstrates key concepts such as:

* **Object-Oriented Programming (OOP)** (Classes, Encapsulation, and Inheritance)

* **Memory Management** (Smart Pointers - shared_ptr)

* **Multi-threading** (Using std::thread for concurrent transactions)

* **File Handling** (Logging transactions into transactions.log)

* **Synchronization** (Using std::mutex to prevent race conditions)

The program simulates multiple clients having accounts in a bank, allowing deposits, withdrawals, and transfers. Transactions are performed in parallel using threads, ensuring concurrency and real-world simulation behavior.
The bank simulation demonstrates multithreading, synchronization, and dynamic memory allocation in a real-world scenario.

### 🏗 Implementation Breakdown
- #### 🏦 Class Account - Representing a Bank Account ; 
- #### Each account has :
- #### Account Number (string) ; 
- #### Balance (double) ; 
- #### Methods for Deposit, Withdrawal, and Transfer ;


```C++
class Account {
private:
    string accountNumber;
    double balance;

public:
    Account(const string& accNumber, double initialBalance)
        : accountNumber(accNumber), balance(initialBalance) {}

    string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        balance += amount;
        logTransaction("Deposit to account " + accountNumber + " for amount " + to_string(amount));
    }
};
```

--- 

### 👤 Class Client - Representing a Bank Customer

 - #### Each client has:

 - #### Name

 - #### Unique ID

 - #### A List of Bank Accounts


```C++
class Account {
private:
    string accountNumber;
    double balance;

public:
    Account(const string& accNumber, double initialBalance)
        : accountNumber(accNumber), balance(initialBalance) {}

    string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        balance += amount;
        logTransaction("Deposit to account " + accountNumber + " for amount " + to_string(amount));
    }
};
```
---
### 🔒 Thread-Safe Transaction Logging

- Uses `mutex` to prevent race conditions in file operations.
- ransactions are recorded in transactions.log.

```C++
mutex mtx;
void logTransaction(const string& message) {
    lock_guard<mutex> lock(mtx);
    ofstream logFile("transactions.log", ios::app);
    if (logFile.is_open()) {
        auto now = chrono::system_clock::now();
        time_t time = chrono::system_clock::to_time_t(now);
        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &time);
        logFile << buffer << " " << message << endl;
    }
}

```

--- 

### 🔄 Multi-threaded Transaction Simulation

- Random transactions are generated.
- `thread` is used for parallel execution.


```C++
void simulateTransactions() {
    vector<thread> threads;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> clientDist(0, clients.size() - 1);
    uniform_real_distribution<> amountDist(10, 5000);

    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([this, &clientDist, &gen, &amountDist]() {
            int fromClientIndex = clientDist(gen);
            int toClientIndex = clientDist(gen);
            double amount = amountDist(gen);

            if (fromClientIndex != toClientIndex) {
                auto fromClient = clients[fromClientIndex];
                auto toClient = clients[toClientIndex];
                auto fromAccount = fromClient->getAccount("ACC001");
                auto toAccount = toClient->getAccount("ACC002");
                if (fromAccount && toAccount) {
                    fromAccount->transfer(*toAccount, amount);
                }
            }
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
}
```







































