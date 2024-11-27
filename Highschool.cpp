#include <iostream>
#include <vector> // For dynamic arrays (containers that can grow and shrink in size).
#include <string>
#include <stdexcept> //  For exception handling (throwing and catching errors).
#include <algorithm> // For generic algorithms (searching, sorting, etc., on containers).
using namespace std;

// Enum for Genre of books
enum class Genre { fiction, nonfiction, periodical, biography, children };

// Convert Genre enum to string for display purposes
string genreToString(Genre genre) {
    switch (genre) {
        case Genre::fiction: return "Fiction";
        case Genre::nonfiction: return "Nonfiction";
        case Genre::periodical: return "Periodical";
        case Genre::biography: return "Biography";
        case Genre::children: return "Children";
        default: return "Unknown"; // Default case if genre is not recognized
    }
}

// Book Class: Represents a book in the library
class Book {
private:
    string ISBN;          // Unique identifier for the book
    string title;         // Title of the book
    string author;        // Author of the book
    int copyrightDate;    // Year the book was published
    bool checkedOut;      // Whether the book is checked out or not
    Genre genre;          // Genre of the book (fiction, nonfiction, etc.)

public:
    // Constructor to initialize a Book object
    Book(string isbn, string t, string a, int date, Genre g)
        : ISBN(isbn), title(t), author(a), copyrightDate(date), checkedOut(false), genre(g) {}

    // Getters for the Book's properties
    string getISBN() const { return ISBN; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getCopyrightDate() const { return copyrightDate; }
    bool isCheckedOut() const { return checkedOut; }
    Genre getGenre() const { return genre; }

    // Function to check out the book (set checkedOut to true)
    void checkOut() { checkedOut = true; }

    // Function to check in the book (set checkedOut to false)
    void checkIn() { checkedOut = false; }

    // Overload == operator to compare books based on ISBN
    bool operator==(const Book& other) const {
        return ISBN == other.ISBN;
    }

    // Overload != operator to compare books based on ISBN
    bool operator!=(const Book& other) const {
        return ISBN != other.ISBN;
    }

    // Overload << operator to display book details
    friend ostream& operator<<(ostream& os, const Book& book) {
        os << "Title: " << book.title << "\n"
           << "Author: " << book.author << "\n"
           << "ISBN: " << book.ISBN << "\n"
           << "Genre: " << genreToString(book.genre) << "\n";
        return os;
    }
};

// Patron Class: Represents a library user
class Patron {
private:
    string userName;     // Name of the patron
    string cardNumber;   // Unique card number of the patron
    int owedFees;        // Fees owed by the patron

public:
    // Constructor to initialize a Patron object
    Patron(string name, string card, int fees = 0)
        : userName(name), cardNumber(card), owedFees(fees) {}

    // Getters for Patron's properties
    string getUserName() const { return userName; }
    string getCardNumber() const { return cardNumber; }
    int getOwedFees() const { return owedFees; }

    // Setter for owed fees
    void setOwedFees(int fees) { owedFees = fees; }

    // Function to check if the patron owes fees
    bool owesFees() const { return owedFees > 0; }
};

// Transaction Class: Represents a book check-out or check-in transaction
class Transaction {
private:
    Book book;           // The book involved in the transaction
    Patron patron;       // The patron involved in the transaction
    string activity;     // Activity: "Check Out" or "Check In"
    string date;         // Date of the transaction

public:
    // Constructor to initialize a Transaction object
    Transaction(const Book& b, const Patron& p, string act, string d)
        : book(b), patron(p), activity(act), date(d) {}

    // Display transaction details (overloaded ostream operator)
    friend ostream& operator<<(ostream& os, const Transaction& transaction) {
        os << "Transaction Details:\n"
           << transaction.book
           << "Patron: " << transaction.patron.getUserName() << "\n"
           << "Activity: " << transaction.activity << "\n"
           << "Date: " << transaction.date << "\n";
        return os;
    }
};

// Library Class: Represents the library that manages books and patrons
class Library {
private:
    vector<Book> books;        // List of books in the library
    vector<Patron> patrons;    // List of patrons in the library
    vector<Transaction> transactions; // List of transactions (checkouts/checkins)

public:
    // Function to add a book to the library
    void addBook(const Book& book) {
        books.push_back(book);
    }

    // Function to add a patron to the library
    void addPatron(const Patron& patron) {
        patrons.push_back(patron);
    }

    // Function to check out a book
    void checkOutBook(const string& isbn, const string& cardNumber, const string& date) {
        // Find the book by ISBN
        auto bookIt = find_if(books.begin(), books.end(), [&](const Book& book) { return book.getISBN() == isbn; });
        if (bookIt == books.end()) {
            throw runtime_error("Book not found in library.");
        }
        // Check if the book is already checked out
        if (bookIt->isCheckedOut()) {
            throw runtime_error("Book is already checked out.");
        }

        // Find the patron by card number
        auto patronIt = find_if(patrons.begin(), patrons.end(), [&](const Patron& patron) { return patron.getCardNumber() == cardNumber; });
        if (patronIt == patrons.end()) {
            throw runtime_error("Patron not found in library.");
        }
        // Check if the patron owes fees
        if (patronIt->owesFees()) {
            throw runtime_error("Patron owes fees and cannot check out books.");
        }

        // Perform the checkout: mark book as checked out and record the transaction
        bookIt->checkOut();
        transactions.emplace_back(*bookIt, *patronIt, "Check Out", date);
    }

    // Function to return a list of patrons who owe fees
    vector<string> patronsOwingFees() const {
        vector<string> owingPatrons;
        for (const auto& patron : patrons) {
            if (patron.owesFees()) {
                owingPatrons.push_back(patron.getUserName());
            }
        }
        return owingPatrons;
    }
};

// Main function where the program starts
int main() {
    try {
        // Create a library instance
        Library library;

        // Add books to the library
        library.addBook(Book("123", "C++ Primer", "Stanley Lippman", 2012, Genre::nonfiction));
        library.addBook(Book("456", "The Great Gatsby", "F. Scott Fitzgerald", 1925, Genre::fiction));

        // Add patrons to the library
        library.addPatron(Patron("Alice", "001"));
        library.addPatron(Patron("Bob", "002", 10)); // Bob owes fees

        // Attempt to check out a book (Alice checks out "C++ Primer")
        library.checkOutBook("123", "001", "2024-11-25");

        // List patrons who owe fees
        auto owingPatrons = library.patronsOwingFees();
        cout << "Patrons who owe fees:\n";
        for (const auto& name : owingPatrons) {
            cout << name << "\n";
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
