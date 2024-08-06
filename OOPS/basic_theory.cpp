#include <bits/stdc++.h>
using namespace std;

/*
* Basics of C++ OOP

1. **Enum (Enumeration)**:
   - An `enum` is a user-defined type that consists of a set of named integral constants.
   - It is primarily used to assign names to integral constants, making the code more readable and maintainable.

   **Example**:
   enum Color {
       RED,
       GREEN,
       BLUE
   };
   Color myColor = RED;

2. **Union**:
   - A `union` is a user-defined type similar to a `struct`, but with a key difference: all members of a `union` share the same memory location. This means that at any given time, a union can store only one of its members.
   - It is used when you need a variable to hold different data types at different times.

   **Example**:
   union Data {
       int intValue;
       float floatValue;
       char charValue;
   };

   Data myData;
   myData.intValue = 5;     // myData now holds an int
   myData.floatValue = 3.14; // myData now holds a float (overwrites the int)

3. **Struct (Structure)**:
   - A `struct` is a user-defined type that groups together different types of variables under a single name.
   - Each member of a `struct` has its own storage location, unlike a `union`.
   - It is used to create a single data type that can hold related data of different types.

   **Example**:
   struct Person {
       std::string name;
       int age;
       float height;
   };

   Person person1;
   person1.name = "Alice";
   person1.age = 30;
   person1.height = 5.7;

### Summary:
- **Enum**: Defines named integral constants.
- **Union**: Allows storing different data types in the same memory location, but only one at a time.
- **Struct**: Groups different data types together, each with its own storage.

These types help organize and manage data efficiently in different scenarios in C++ programming.

 */

/*

@ OOPS
access modifiers: private, public, protected
* private : Only accessible within the class
* public : Accessible from outside the class
* protected : Accessible from outside the class and from subclasses

^ Inheritance: It is a mechanism in which one class acquires the properties of another class.

^ Polymorphism: It is the ability of an object to take on many forms.

^ Encapsulation: It is the process of wrapping data and the methods that work on the data within one unit.
 */

// Enum for gender specification
enum Gender
{
    MALE,
    FEMALE
};

// Class representing a basic bank account
class BankAccount
{
private:
    string accountNumber;        // Account number of the bank account
    string accountHolder;        // Name of the account holder
    unsigned long long uniqueId; // Unique identifier for the account

protected:
    double bankBalance; // Balance in the bank account

public:
    // Constructor with parameters
    BankAccount(string accountNumber, string accountHolder, unsigned long long uniqueId, double bankBalance = 0.0)
    {
        this->accountNumber = accountNumber;
        this->accountHolder = accountHolder;
        this->uniqueId = uniqueId;
        this->bankBalance = bankBalance;
    }

    // Default constructor
    BankAccount() : accountNumber(""), accountHolder(""), uniqueId(0), bankBalance(0.0) {}

    // Method to deposit an amount into the bank account
    void deposit(double amount)
    {
        bankBalance += amount;
    }

    // Method to withdraw an amount from the bank account
    void withdraw(double amount)
    {
        if (bankBalance < amount)
        {
            cout << "Insufficient balance" << endl;
            return;
        }
        bankBalance -= amount;
    }

    // Getters and Setters
    string getAccountNumber() const
    {
        return accountNumber;
    }

    void setAccountNumber(const string &accountNumber)
    {
        this->accountNumber = accountNumber;
    }

    string getAccountHolder() const
    {
        return accountHolder;
    }

    void setAccountHolder(const string &accountHolder)
    {
        this->accountHolder = accountHolder;
    }

    unsigned long long getUniqueId() const
    {
        return uniqueId;
    }

    void setUniqueId(unsigned long long uniqueId)
    {
        this->uniqueId = uniqueId;
    }

    double getBankBalance() const
    {
        return bankBalance;
    }

    void setBankBalance(double bankBalance)
    {
        this->bankBalance = bankBalance;
    }
};

// Class representing a Demat (Dematerialized) account, inherited from BankAccount
class DematAccount : public virtual BankAccount
{
protected:
    unsigned long long dematId; // Unique identifier for the Demat account
    double dematBalance;        // Balance in the Demat account

public:
    // Constructor with parameters
    DematAccount(string accountNumber, string accountHolder, unsigned long long uniqueId, double dematBalance = 0.0)
        : BankAccount(accountNumber, accountHolder, uniqueId)
    {
        this->dematId = uniqueId;
        this->dematBalance = dematBalance;
    }
    DematAccount() : dematId(0), dematBalance(0.0) {}
    // Getters and Setters
    unsigned long long getDematId() const
    {
        return dematId;
    }

    void setDematId(unsigned long long dematId)
    {
        this->dematId = dematId;
    }

    double getDematBalance() const
    {
        return dematBalance;
    }

    void setDematBalance(double dematBalance)
    {
        this->dematBalance = dematBalance;
    }
};

// Class representing a person, inherited from both BankAccount and DematAccount
class Person : public virtual BankAccount, public DematAccount
{
private:
    int age;                     // Age of the person
    Gender gender;               // Gender of the person
    string contactNumber;        // Contact number of the person
    unsigned long long uniqueId; // Unique identifier for the person

protected:
    string address; // Address of the person
    string email;   // Email address of the person

public:
    string name; // Name of the person

    // Constructor with parameters
    Person(string name, int age, Gender gender, string contactNumber, double bankBalance = 0.0, string address = "", string email = "")
        : BankAccount(), DematAccount("", "", 0, 0.0)
    {
        this->name = name;
        this->age = age;
        this->gender = gender;
        this->contactNumber = contactNumber;
        this->uniqueId = (ULLONG_MAX % (rand() + time(NULL)));
        this->bankBalance = bankBalance;
        this->address = address.length() ? address : "N/A";
        this->email = email.length() ? email : "N/A";
    }

    // Default constructor
    Person() : age(0), gender(Gender::MALE), contactNumber(""), uniqueId(0), address("N/A"), email("N/A") {}

    // Copy constructor
    Person(const Person &other)
        : BankAccount(other), DematAccount(other)
    {
        this->name = other.name;
        this->age = other.age;
        this->gender = other.gender;
        this->contactNumber = other.contactNumber;
        this->uniqueId = other.uniqueId;
        this->address = other.address;
        this->email = other.email;
    }

    // Destructor
    ~Person()
    {
        cout << "Destructor called for " << this->name << endl;
    }

    // Getters and Setters
    int getAge() const
    {
        return age;
    }

    void setAge(int age)
    {
        this->age = age;
    }

    Gender getGender() const
    {
        return gender;
    }

    void setGender(Gender gender)
    {
        this->gender = gender;
    }

    string getContactNumber() const
    {
        return contactNumber;
    }

    void setContactNumber(const string &contactNumber)
    {
        this->contactNumber = contactNumber;
    }

    unsigned long long getUniqueId() const
    {
        return uniqueId;
    }

    void setUniqueId(unsigned long long uniqueId)
    {
        this->uniqueId = uniqueId;
    }

    double getBankBalance() const
    {
        return bankBalance;
    }

    void setBankBalance(double bankBalance)
    {
        this->bankBalance = bankBalance;
    }

    string getAddress() const
    {
        return address;
    }

    void setAddress(const string &address)
    {
        this->address = address;
    }

    string getEmail() const
    {
        return email;
    }

    void setEmail(const string &email)
    {
        this->email = email;
    }

    // Method to display the details of the person
    void displayDetails() const
    {
        cout << "Name: " << this->name << endl;
        cout << "Age: " << this->age << endl;
        cout << "Gender: " << (this->gender == Gender::MALE ? "Male" : "Female") << endl;
        cout << "Contact Number: " << this->contactNumber << endl;
        cout << "Unique ID: " << this->uniqueId << endl;
        cout << "Bank Balance: " << this->bankBalance << endl;
        cout << "Address: " << this->address << endl;
        cout << "Email: " << this->email << endl;
        cout << "Demat Balance: " << this->getDematBalance() << endl;
        cout << "Demat Account Number: " << this->getDematId() << endl;
    }
};

int main()
{
    Person person1("John", 30, Gender::MALE, "1234567890");
    Person *person2 = new Person("Jane", 25, Gender::FEMALE, "9876543210");
    person1.displayDetails();
    person2->displayDetails();
    delete person2;

    return 0;
}
