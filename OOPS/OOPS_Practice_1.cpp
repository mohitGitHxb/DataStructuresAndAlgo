#include <bits/stdc++.h>
using namespace std;

/**
 * @class Utils
 * @brief Utility class providing helper functions for the banking system.
 *
 * This class contains static methods for generating unique IDs, calculating age,
 * validating mobile numbers and email addresses, and printing dividers.
 */
class Utils
{
public:
    /**
     * @brief Generates a unique 64-bit unsigned integer ID.
     * @return uint64_t A unique ID.
     */
    static uint64_t generateUniqueId()
    {
        static uint64_t id = 0;
        return id++;
    }

    /**
     * @brief Calculates the age of a person given their date of birth.
     * @param year The year of birth.
     * @param month The month of birth.
     * @param day The day of birth.
     * @return uint_fast8_t The age of the person as of the current date.
     */
    static uint_fast8_t getAgeFromDob(uint_fast16_t year, uint_fast8_t month, uint_fast16_t day)
    {
        time_t now = time(nullptr);
        tm *currentTm = localtime(&now);
        uint_fast16_t currentYear = 1900 + currentTm->tm_year;

        uint_fast16_t ageYears = currentYear - year;

        if (currentTm->tm_mon < month || (currentTm->tm_mon == month && currentTm->tm_mday < day))
        {
            ageYears--;
        }
        return ageYears > 255 ? 255 : static_cast<uint_fast8_t>(ageYears);
    }

    /**
     * @brief Checks if a given mobile number is valid.
     * @param mobileNumber The mobile number to be checked.
     * @return bool True if the mobile number is valid, false otherwise.
     */
    static bool checkMobileNumberValidity(string mobileNumber)
    {
        return regex_match(mobileNumber, regex("[6-9][0-9]{9}"));
    }

    /**
     * @brief Checks if a given email address is valid.
     * @param email The email address to be checked.
     * @return bool True if the email address is valid, false otherwise.
     */
    static bool checkEmailValidity(string email)
    {
        return regex_match(email, regex("[a-z0-9._%+-]+@[a-z0-9.-]+\\.[a-z]{2,}$"));
    }

    /**
     * @brief Prints a divider line to the console.
     */
    static void divider()
    {
        cout << "\n------------------------------------------------------\n\n";
    }
};

/**
 * @class Person
 * @brief Base class representing a person in the banking system.
 *
 * This class contains basic personal information such as name, date of birth,
 * contact details, and a unique person ID.
 */
class Person
{
protected:
    uint64_t personId;
    uint_fast16_t year;
    uint_fast8_t month;
    uint_fast16_t day;
    string firstName;
    string lastName;
    string mobileNumber;
    string email;

public:
    /**
     * @brief Construct a new Person object with first and last name.
     * @param firstName The person's first name.
     * @param lastName The person's last name.
     */
    Person(string firstName, string lastName) : personId(Utils::generateUniqueId()), firstName(firstName), lastName(lastName) {}

    /**
     * @brief Construct a new Person object with name and date of birth.
     * @param firstName The person's first name.
     * @param lastName The person's last name.
     * @param year The year of birth.
     * @param month The month of birth.
     * @param day The day of birth.
     */
    Person(string firstName, string lastName, uint_fast16_t year, uint_fast8_t month, uint_fast16_t day)
        : personId(Utils::generateUniqueId()), firstName(firstName), lastName(lastName), year(year), month(month), day(day) {}

    // Getters
    uint64_t getPersonId() const { return personId; }
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getName() const { return firstName + " " + lastName; }
    uint_fast8_t getAge() const { return Utils::getAgeFromDob(year, month, day); }

    // Setters
    void setYear(uint_fast16_t year) { this->year = year; }
    void setMonth(uint_fast8_t month) { this->month = month; }
    void setDay(uint_fast16_t day) { this->day = day; }

    /**
     * @brief Set the mobile number for the person.
     * @param mobileNumber The mobile number to set.
     */
    void setMobileNumber(string mobileNumber)
    {
        if (Utils::checkMobileNumberValidity(mobileNumber))
        {
            this->mobileNumber = mobileNumber;
        }
        else
        {
            cout << "Invalid mobile number" << endl;
        }
    }

    /**
     * @brief Set the email address for the person.
     * @param email The email address to set.
     */
    void setEmail(string email)
    {
        if (Utils::checkEmailValidity(email))
        {
            this->email = email;
        }
        else
        {
            cout << "Invalid email" << endl;
        }
    }

    /**
     * @brief Display the details of the person.
     */
    virtual void displayDetails() const = 0;
};

/**
 * @class BankAccount
 * @brief Represents a bank account in the banking system.
 *
 * This class inherits from Person and adds banking-specific information
 * such as account number and balance.
 */
class BankAccount : public Person
{
protected:
    uint_fast64_t accountNumber;
    double balance;

public:
    string bankName;
    string bankBranch;

    /**
     * @brief Construct a new Bank Account object.
     * @param firstName The account holder's first name.
     * @param lastName The account holder's last name.
     * @param year The year of birth of the account holder.
     * @param month The month of birth of the account holder.
     * @param day The day of birth of the account holder.
     * @param balance The initial balance of the account.
     */
    BankAccount(string firstName, string lastName, uint_fast16_t year, uint_fast8_t month, uint_fast16_t day, double balance)
        : Person(firstName, lastName, year, month, day), accountNumber(Utils::generateUniqueId()), balance(balance) {}

    /**
     * @brief Display the details of the bank account.
     */
    void displayDetails() const override
    {
        cout << "Name: " << getName() << endl;
        cout << "Age: " << getAge() << endl;
        cout << "Balance: " << balance << endl;
        cout << "Person ID: " << getPersonId() << endl;
        cout << "Email: " << email << endl;
        cout << "Mobile Number: " << mobileNumber << endl;
        cout << "Date of Birth: " << day << "/" << month << "/" << year << endl;
        cout << "Bank Name: " << bankName << endl;
        cout << "Bank Branch: " << bankBranch << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << balance << endl;

        Utils::divider();
    }

    /**
     * @brief Withdraw money from the account.
     * @param amount The amount to withdraw.
     */
    void withdraw(double amount)
    {
        if (balance < amount)
        {
            cout << "Insufficient balance" << endl;
            return;
        }
        balance -= amount;
    }

    double getBalance() const { return balance; }
    string getBankName() const { return bankName; }
    string getBankAccountNumber() const { return to_string(accountNumber); }

    /**
     * @brief Deposit money into the account.
     * @param amount The amount to deposit.
     */
    void deposit(double amount)
    {
        balance += amount;
    }
};

/**
 * @class AutoCreditSystem
 * @brief Represents an automatic credit system.
 *
 * This class manages credit scores and provides functionality to credit
 * money to bank accounts.
 */
class AutoCreditSystem
{
private:
    uint16_t creditScore;

public:
    /**
     * @brief Construct a new Auto Credit System object.
     * @param creditScore The initial credit score.
     */
    AutoCreditSystem(uint16_t creditScore = 1000) : creditScore(creditScore) {}

    /**
     * @brief Credit money to a bank account.
     * @param bankAccount The bank account to credit.
     * @param amount The amount to credit.
     */
    void creditToBankAccount(BankAccount &bankAccount, double amount)
    {
        bankAccount.deposit(amount);
    }

    uint16_t getCreditScore() const { return creditScore; }
};

/**
 * @class Employee
 * @brief Represents an employee in the banking system.
 *
 * This class inherits from Person and AutoCreditSystem, adding employee-specific
 * information such as salary and a linked bank account.
 */
class Employee : public Person, public AutoCreditSystem
{
public:
    uint_fast64_t salary;
    BankAccount *bankAccount;

    /**
     * @brief Construct a new Employee object.
     * @param firstName The employee's first name.
     * @param lastName The employee's last name.
     * @param year The year of birth of the employee.
     * @param month The month of birth of the employee.
     * @param day The day of birth of the employee.
     * @param salary The employee's salary.
     */
    Employee(string firstName, string lastName, uint_fast16_t year, uint_fast8_t month, uint_fast16_t day, uint_fast16_t salary)
        : Person(firstName, lastName, year, month, day), AutoCreditSystem(), bankAccount(nullptr)
    {
        this->salary = salary;
    }

    /**
     * @brief Display the details of the employee.
     */
    void displayDetails() const override
    {
        cout << "Name: " << getName() << endl;
        cout << "Age: " << getAge() << endl;
        cout << "Salary: " << salary << endl;
        cout << "Person ID: " << getPersonId() << endl;
        cout << "Email: " << email << endl;
        cout << "Mobile Number: " << mobileNumber << endl;
        cout << "Date of Birth: " << day << "/" << month << "/" << year << endl;

        if (bankAccount)
        {
            cout << "Bank Account: " << bankAccount->getBankName() << " - " << bankAccount->getBankAccountNumber() << endl;
        }
        else
        {
            cout << "Bank Account: Not linked" << endl;
        }

        Utils::divider();
    }

    void setSalary(uint_fast16_t salary) { this->salary = salary; }

    /**
     * @brief Link a bank account to the employee.
     * @param account Pointer to the bank account to link.
     */
    void linkBankAccount(BankAccount *account)
    {
        bankAccount = account;
    }

    /**
     * @brief Add the employee's salary to their linked bank account.
     */
    void addToBankAccount()
    {
        if (bankAccount)
        {
            creditToBankAccount(*bankAccount, salary);
            cout << "Salary added to bank account." << endl;
        }
        else
        {
            cout << "Bank account not linked." << endl;
        }
    }
};

/**
 * @class Menu
 * @brief Manages the user interface and operations of the banking system.
 *
 * This class provides static methods to display menus, create employees and bank accounts,
 * link accounts, and perform various banking operations.
 */

class Menu
{
public:
    /**
     * @brief Display the main menu of the banking system.
     *
     * Prints the main menu to the console, prompting the user to
     * enter a choice to perform one of the following operations:
     *   1. Create new employee
     *   2. Link bank account to employee
     *   3. Add salary to bank account
     *   4. Display employee details
     *   5. Display bank account details
     *   6. Exit
     */
    static void displayMenu()
    {
        cout << "\nMenu:\n";
        cout << "1. Create new employee\n";
        cout << "2. Create new bank account\n";
        cout << "3. Link bank account to employee\n";
        cout << "4. Add salary to bank account\n";
        cout << "5. Display employee details\n";
        cout << "6. Display bank account details\n";
        cout << "7. Exit\n";
        cout << "\nEnter your choice: ";
    }

    /**
     * @brief Create a new Employee object and add it to the list of employees.
     *
     * Prompts the user for first name, last name, year of birth, month of birth,
     * day of birth, and salary. Then, creates an Employee object with the given
     * information and adds it to the vector of employees.
     */
    static void createEmployee()
    {
        string firstName, lastName;
        uint_fast16_t year, day;
        uint_fast8_t month;
        uint_fast16_t salary;

        cout << "Enter first name: ";
        cin >> firstName;
        cout << "Enter last name: ";
        cin >> lastName;
        cout << "Enter year of birth: ";
        cin >> year;
        cout << "Enter month of birth: ";
        cin >> month;
        cout << "Enter day of birth: ";
        cin >> day;
        cout << "Enter salary: ";
        cin >> salary;

        Employee employee(firstName, lastName, year, month, day, salary);
        employees.push_back(employee);
        cout << "Employee created successfully.\n";
        cout << "Here are your details:\n";
        employee.displayDetails();
    }

    /**
     * @brief Link a bank account to an employee.
     *
     * Prompts the user for employee ID and bank account number.
     * Then, links the bank account to the employee with the given ID.
     */
    static void linkBankAccountToEmployee()
    {
        uint64_t employeeId;
        uint_fast64_t accountNumber;

        cout << "Enter employee ID: ";
        cin >> employeeId;
        cout << "Enter bank account number: ";
        cin >> accountNumber;

        Employee *employee = findEmployeeById(employeeId);
        BankAccount *bankAccount = findBankAccountByAccountNumber(accountNumber);

        if (employee && bankAccount)
        {
            employee->linkBankAccount(bankAccount);
            cout << "Bank account linked to employee successfully.\n";
        }
        else
        {
            cout << "Employee or bank account not found.\n";
        }
    }

    /**
     * @brief Add the salary of an employee to their linked bank account.
     *
     * Prompts the user for an employee ID and then adds the salary of the
     * employee with that ID to their linked bank account.
     */
    static void addSalaryToBankAccount()
    {
        uint64_t employeeId;

        cout << "Enter employee ID: ";
        cin >> employeeId;

        Employee *employee = findEmployeeById(employeeId);

        if (employee)
        {
            employee->addToBankAccount();
            cout << "Salary added to bank account successfully.\n";
        }
        else
        {
            cout << "Employee not found.\n";
        }
    }

    /**
     * @brief Display the details of an employee.
     *
     * Prompts the user for an employee ID and then displays the details of the
     * employee with that ID.
     */
    static void displayEmployeeDetails()
    {
        uint64_t employeeId;

        cout << "Enter employee ID: ";
        cin >> employeeId;

        Employee *employee = findEmployeeById(employeeId);

        if (employee)
        {
            employee->displayDetails();
        }
        else
        {
            cout << "Employee not found.\n";
        }
    }

    /**
     * @brief Display the details of a bank account.
     *
     * Prompts the user for a bank account number and then displays the details
     * of the bank account with that number.
     */
    static void displayBankAccountDetails()
    {
        uint_fast64_t accountNumber;

        cout << "Enter bank account number: ";
        cin >> accountNumber;

        BankAccount *bankAccount = findBankAccountByAccountNumber(accountNumber);

        if (bankAccount)
        {
            bankAccount->displayDetails();
        }
        else
        {
            cout << "Bank account not found.\n";
        }
    }
    /**
     * @brief Create a new BankAccount object and add it to the list of bank accounts.
     *
     * Prompts the user for first name, last name, year of birth, month of birth,
     * day of birth, and initial balance. Then, creates a BankAccount object with
     * the given information and adds it to the vector of bank accounts.
     */
    static void createBankAccount()
    {
        string firstName, lastName;
        uint_fast16_t year, day;
        uint_fast8_t month;
        double balance = 0.0; // Default balance

        cout << "Enter first name: ";
        cin >> firstName;
        cout << "Enter last name: ";
        cin >> lastName;
        cout << "Enter year of birth: ";
        cin >> year;
        cout << "Enter month of birth: ";
        cin >> month;
        cout << "Enter day of birth: ";
        cin >> day;
        cout << "Enter initial balance (optional): ";
        cin >> balance;

        BankAccount bankAccount(firstName, lastName, year, month, day, balance);
        bankAccounts.push_back(bankAccount);
        cout << "Bank account created successfully.\n";
        cout << "Here are the details:\n";
        bankAccount.displayDetails();
    }

private:
    static vector<Employee> employees;
    static vector<BankAccount> bankAccounts;

    /**
     * @brief Find an employee by their ID.
     *
     * Iterates through the list of employees and returns a pointer to the
     * employee with the given ID, if it exists.
     * @param employeeId The ID of the employee to find.
     * @return A pointer to the employee with the given ID, or nullptr if no
     * such employee exists.
     */
    static Employee *findEmployeeById(uint64_t employeeId)
    {
        for (Employee &employee : employees)
        {
            if (employee.getPersonId() == employeeId)
            {
                return &employee;
            }
        }
        return nullptr;
    }

    /**
     * @brief Find a bank account by its account number.
     *
     * Iterates through the list of bank accounts and returns a pointer to the
     * bank account with the given account number, if it exists.
     * @param accountNumber The account number to find.
     * @return A pointer to the bank account with the given account number, or
     * nullptr if no such account exists.
     */
    static BankAccount *findBankAccountByAccountNumber(uint_fast64_t accountNumber)
    {
        for (BankAccount &bankAccount : bankAccounts)
        {
            if (bankAccount.getBankAccountNumber() == to_string(accountNumber))
            {
                return &bankAccount;
            }
        }
        return nullptr;
    }
};

vector<Employee> Menu::employees;
vector<BankAccount> Menu::bankAccounts;

int main()
{
    int choice;

    do
    {
        Menu::displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            Menu::createEmployee();
            break;
        case 2:
            Menu::createBankAccount();
            break;
        case 3:
            Menu::linkBankAccountToEmployee();
            break;
        case 4:
            Menu::addSalaryToBankAccount();
            break;
        case 5:
            Menu::displayEmployeeDetails();
            break;
        case 6:
            Menu::displayBankAccountDetails();
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
