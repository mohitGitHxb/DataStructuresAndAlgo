/*
 * Library Management System (LMS) - C++ Implementation
 *
 * Overview:
 * This codebase implements a Library Management System (LMS) using Object-Oriented Programming (OOP) principles in C++.
 * The system is designed to manage library resources, members, and transactions efficiently. It provides functionalities
 * for managing members, books, and loans, along with an interactive menu for user interaction.
 *
 * System Design Thought Process:
 *
 * 1. Object-Oriented Design:
 *    - The system is designed using OOP principles to encapsulate data and behavior within classes.
 *    - Key classes include Member, Book, Loan, Librarian, and Menu, each responsible for specific functionalities.
 *
 * 2. Class Descriptions:
 *    - Member: Represents a library member with attributes like memberId, name, contactInfo, and membership status.
 *      Provides methods to update contact info, deactivate membership, and display member information.
 *
 *    - Book: Represents a book in the library with attributes like bookId, title, author, and availability status.
 *      Provides methods to mark a book as borrowed or returned, check availability, and display book information.
 *
 *    - Loan: Represents a loan transaction with attributes like loanId, memberId, bookId, loanDate, and dueDate.
 *      Provides methods to display loan information.
 *
 *    - Librarian: Manages collections of members, books, and loans using unordered maps for efficient data retrieval.
 *      Provides methods to add members and books, loan and return books, and display all members, books, and loans.
 *
 *    - Menu: Provides an interactive terminal-based interface for users to interact with the system.
 *      Offers options to add members, add books, loan books, return books, and display all entities.
 *
 * 3. Data Structures:
 *    - Unordered maps are used to store members, books, and loans, allowing for fast lookup and management.
 *
 * 4. User Interaction:
 *    - The Menu class facilitates user interaction through a simple command-line interface, allowing users to perform
 *      various operations by selecting options from a menu.
 *
 * 5. Design Goals:
 *    - The system aims to automate library processes, reduce manual labor, and improve member satisfaction by providing
 *      easy access to library resources.
 *    - The code is structured to be modular and maintainable, allowing for easy updates and expansions.
 *
 * 6. Future Enhancements:
 *    - Implementing a database for persistent data storage.
 *    - Adding features like fine calculation, book categorization, and advanced search functionalities.
 *
 * This implementation serves as a foundational framework for a Library Management System, demonstrating the use of
 * OOP principles in C++ to create a functional and user-friendly application.
 */

#include <bits/stdc++.h>
using namespace std;

// Class representing a Member
class Member
{
private:
    string memberId;
    string name;
    string contactInfo;
    bool membershipActive;

public:
    Member() : memberId(""), name(""), contactInfo(""), membershipActive(false) {}
    Member(const string &id, const string &name, const string &contact)
        : memberId(id), name(name), contactInfo(contact), membershipActive(true) {}

    void updateContactInfo(const string &newContact)
    {
        contactInfo = newContact;
    }

    void deactivateMembership()
    {
        membershipActive = false;
    }

    string getId() const
    {
        return memberId;
    }

    bool isMembershipActive() const
    {
        return membershipActive;
    }

    void displayInfo() const
    {
        cout << "Member ID: " << memberId << ", Name: " << name
             << ", Contact: " << contactInfo << ", Active: " << membershipActive << endl;
    }
};

// Class representing a Book
// Class representing a Book
class Book
{
private:
    string bookId;
    string title;
    string author;
    bool isAvailable;

public:
    // Default constructor
    Book() : bookId(""), title(""), author(""), isAvailable(true) {}

    Book(const string &id, const string &title, const string &author)
        : bookId(id), title(title), author(author), isAvailable(true) {}

    void markAsBorrowed()
    {
        isAvailable = false;
    }

    void markAsReturned()
    {
        isAvailable = true;
    }

    bool checkAvailability() const
    {
        return isAvailable;
    }

    string getId() const
    {
        return bookId;
    }

    void displayInfo() const
    {
        cout << "Book ID: " << bookId << ", Title: " << title
             << ", Author: " << author << ", Available: " << isAvailable << endl;
    }
};

// Class representing a Loan
class Loan
{
private:
    string loanId;
    string memberId;
    string bookId;
    time_t loanDate;
    time_t dueDate;

public:
    // Default constructor
    Loan() : loanId(""), memberId(""), bookId(""), loanDate(0), dueDate(0) {}

    Loan(const string &loanId, const string &memberId, const string &bookId)
        : loanId(loanId), memberId(memberId), bookId(bookId)
    {
        loanDate = time(nullptr);
        dueDate = loanDate + 14 * 24 * 60 * 60; // 2 weeks loan period
    }

    string getLoanId() const
    {
        return loanId;
    }

    string getMemberId() const
    {
        return memberId;
    }

    string getBookId() const
    {
        return bookId;
    }

    void displayInfo() const
    {
        cout << "Loan ID: " << loanId << ", Member ID: " << memberId
             << ", Book ID: " << bookId << ", Loan Date: " << ctime(&loanDate)
             << ", Due Date: " << ctime(&dueDate) << endl;
    }
};

// Class representing a Librarian
class Librarian
{
private:
    unordered_map<string, Member> members;
    unordered_map<string, Book> books;
    unordered_map<string, Loan> loans;

public:
    void addMember(const Member &member)
    {
        members.emplace(member.getId(), member);
    }

    void addBook(const Book &book)
    {
        books.emplace(book.getId(), book);
    }

    void loanBook(const string &memberId, const string &bookId)
    {
        if (members.count(bookId) && books.count(bookId))
        {
            if (books[bookId].checkAvailability() && members[memberId].isMembershipActive())
            {
                string loanId = "L" + to_string(loans.size() + 1);
                loans[loanId] = Loan(loanId, memberId, bookId);
                books[bookId].markAsBorrowed();
                cout << "Book loaned successfully. Loan ID: " << loanId << endl;
            }
            else
            {
                cout << "Book is not available or membership is inactive." << endl;
            }
        }
        else
        {
            cout << "Invalid member or book ID." << endl;
        }
    }

    void returnBook(const string &loanId)
    {
        if (loans.count(loanId))
        {
            string bookId = loans[loanId].getBookId();
            books[bookId].markAsReturned();
            loans.erase(loanId);
            cout << "Book returned successfully." << endl;
        }
        else
        {
            cout << "Invalid loan ID." << endl;
        }
    }

    void displayAllMembers() const
    {
        for (const auto &pair : members)
        {
            pair.second.displayInfo();
        }
    }

    void displayAllBooks() const
    {
        for (const auto &pair : books)
        {
            pair.second.displayInfo();
        }
    }

    void displayAllLoans() const
    {
        for (const auto &pair : loans)
        {
            pair.second.displayInfo();
        }
    }
};

// Class representing the Menu
class Menu
{
private:
    Librarian librarian;

public:
    void displayMenu()
    {
        int choice;
        do
        {
            cout << "\nLibrary Management System Menu:\n";
            cout << "1. Add Member\n";
            cout << "2. Add Book\n";
            cout << "3. Loan Book\n";
            cout << "4. Return Book\n";
            cout << "5. Display All Members\n";
            cout << "6. Display All Books\n";
            cout << "7. Display All Loans\n";
            cout << "8. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                addMember();
                break;
            case 2:
                addBook();
                break;
            case 3:
                loanBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                librarian.displayAllMembers();
                break;
            case 6:
                librarian.displayAllBooks();
                break;
            case 7:
                librarian.displayAllLoans();
                break;
            case 8:
                cout << "Exiting the system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 8);
    }

    void addMember()
    {
        string id, name, contact;
        cout << "Enter Member ID: ";
        cin >> id;
        cout << "Enter Member Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Contact Info: ";
        getline(cin, contact);
        librarian.addMember(Member(id, name, contact));
        cout << "Member added successfully." << endl;
    }

    void addBook()
    {
        string id, title, author;
        cout << "Enter Book ID: ";
        cin >> id;
        cout << "Enter Book Title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        librarian.addBook(Book(id, title, author));
        cout << "Book added successfully." << endl;
    }

    void loanBook()
    {
        string memberId, bookId;
        cout << "Enter Member ID: ";
        cin >> memberId;
        cout << "Enter Book ID: ";
        cin >> bookId;
        librarian.loanBook(memberId, bookId);
    }

    void returnBook()
    {
        string loanId;
        cout << "Enter Loan ID: ";
        cin >> loanId;
        librarian.returnBook(loanId);
    }
};

int main()
{
    Menu menu;
    menu.displayMenu();
    return 0;
}
