#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

// Structure for Book
class Book {
public:
    int id;
    string title;
    string author;
    string isbn;
    bool isAvailable = true;

    Book(int i, string t, string a, string isbn_) : id(i), title(t), author(a), isbn(isbn_) {}
};

// Structure for Borrower
class Borrower {
public:
    int id;
    string name;

    Borrower(int i, string n) : id(i), name(n) {}
};

// Structure for Transaction
class Transaction {
public:
    int bookId;
    int borrowerId;
    time_t checkoutDate;
    time_t dueDate;
    time_t returnDate;
    bool returned = false;

    Transaction(int bId, int borId) {
        bookId = bId;
        borrowerId = borId;
        time(&checkoutDate);
        dueDate = checkoutDate + (14 * 24 * 60 * 60); // 14 days
        returnDate = 0;
    }

    double calculateFine() {
        if (!returned) return 0;
        double daysLate = difftime(returnDate, dueDate) / (60 * 60 * 24);
        return daysLate > 0 ? daysLate * 2 : 0;
    }
};

// Database Vectors
vector<Book> books;
vector<Borrower> borrowers;
vector<Transaction> transactions;

// Utility to find book by ID
Book* findBook(int id) {
    for (auto& book : books)
        if (book.id == id)
            return &book;
    return nullptr;
}

// Utility to find borrower by ID
Borrower* findBorrower(int id) {
    for (auto& borrower : borrowers)
        if (borrower.id == id)
            return &borrower;
    return nullptr;
}

// Add Book
void addBook() {
    int id;
    string title, author, isbn;
    cout << "Enter Book ID, Title, Author, ISBN: ";
    cin >> id;
    cin.ignore();
    getline(cin, title);
    getline(cin, author);
    getline(cin, isbn);
    books.push_back(Book(id, title, author, isbn));
    cout << "Book added successfully!\n";
}

// Add Borrower
void addBorrower() {
    int id;
    string name;
    cout << "Enter Borrower ID and Name: ";
    cin >> id;
    cin.ignore();
    getline(cin, name);
    borrowers.push_back(Borrower(id, name));
    cout << "Borrower added!\n";
}

// Search Books
void searchBook() {
    string query;
    cout << "Enter title, author or ISBN to search: ";
    cin.ignore();
    getline(cin, query);

    for (const auto& book : books) {
        if (book.title.find(query) != string::npos || book.author.find(query) != string::npos || book.isbn == query) {
            cout << "Book ID: " << book.id
                 << ", Title: " << book.title
                 << ", Author: " << book.author
                 << ", ISBN: " << book.isbn
                 << ", Available: " << (book.isAvailable ? "Yes" : "No") << endl;
        }
    }
}

// Checkout Book
void checkoutBook() {
    int bookId, borrowerId;
    cout << "Enter Book ID and Borrower ID: ";
    cin >> bookId >> borrowerId;

    Book* book = findBook(bookId);
    if (!book || !book->isAvailable) {
        cout << "Book not available.\n";
        return;
    }

    if (!findBorrower(borrowerId)) {
        cout << "Borrower not found.\n";
        return;
    }

    transactions.push_back(Transaction(bookId, borrowerId));
    book->isAvailable = false;
    cout << "Book checked out!\n";
}

// Return Book
void returnBook() {
    int bookId, borrowerId;
    cout << "Enter Book ID and Borrower ID to return: ";
    cin >> bookId >> borrowerId;

    for (auto& t : transactions) {
        if (t.bookId == bookId && t.borrowerId == borrowerId && !t.returned) {
            time(&t.returnDate);
            t.returned = true;
            Book* book = findBook(bookId);
            if (book) book->isAvailable = true;

            double fine = t.calculateFine();
            cout << "Book returned successfully. Fine: ?" << fixed << setprecision(2) << fine << endl;
            return;
        }
    }
    cout << "No matching active transaction found.\n";
}

// Main Menu
void showMenu() {
    int choice;
    do {
        cout << "\n====== Library Menu ======\n";
        cout << "1. Add Book\n";
        cout << "2. Add Borrower\n";
        cout << "3. Search Book\n";
        cout << "4. Checkout Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: addBorrower(); break;
            case 3: searchBook(); break;
            case 4: checkoutBook(); break;
            case 5: returnBook(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 6);
}

int main() {
    showMenu();
    return 0;
}
