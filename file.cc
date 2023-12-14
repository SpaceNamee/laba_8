#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cctype>

using namespace std;

struct CatalogEntry {
    int code;
    string lastname;
    int page;
    string title;
    int year;
};

void getInput(CatalogEntry& entry);
bool isNumber(const string& str);
void writeFile(const string& filename, const CatalogEntry& entry);
string searchBook(const string& filename, const string& title);
int getUserChoice();
bool shouldContinue(const string& text);

int main() {
    string filename = "catalog.txt";
    int userChoice;

    while (true) {
        userChoice = getUserChoice();

        switch (userChoice) {
            case 0:
                exit(0);
                break;
            case 1:
                do {
                    CatalogEntry newEntry;
                    getInput(newEntry);
                    writeFile(filename, newEntry);
                } while (shouldContinue("Add another book"));
                break;
            case 2:
                do {
                    string title;
                    cout << "Enter the title of the book to search: ";
                    cin.ignore();
                    getline(cin, title);

                    string result = searchBook(filename, title);
                    if (result.empty()) {
                        cout << "Book not found." << endl;
                    }
                } while (shouldContinue("Search another book"));
                break;
            default:
                cout << "\nUnexpected value\n" << endl;
                break;
        }
    }

    return 0;
}

void getInput(CatalogEntry& entry) {
	string userInput;

	cout << "Enter code of the book: ";
    do {
        getline(cin, userInput);
        if (isNumber(userInput)) {
            entry.code = stoi(userInput);
            break;
        } else {
            cout << "Invalid input. Please enter a valid number.\n";
        }
    } while (true);

    cout << "Enter last name of the author: ";
    getline(cin, entry.lastname);

    cout << "Enter title of the book: ";
    getline(cin, entry.title);

    cout << "Enter year of publication of the book: ";

    do {
        getline(cin, userInput);
        if (isNumber(userInput)) {
            entry.year = stoi(userInput);
            break;
        } else {
            cout << "Invalid input. Please enter a valid year.\n";
        }
    } while (true);

    cout << "Enter number of pages in the book: ";
    do {
        getline(cin, userInput);
        if (isNumber(userInput)) {
            entry.page = stoi(userInput);
            break;
        } else {
            cout << "Invalid input. Please enter a valid number.\n";
        }
    } while (true);
}

bool isNumber(const string& str) {
    return all_of(str.begin(), str.end(), ::isdigit);
}

void writeFile(const string& filename, const CatalogEntry& entry) {
    ofstream file(filename, ios::app);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    file << entry.code << "\t" << entry.lastname << "\t" << entry.page << "\t"
         << entry.title << "\t" << entry.year << "\n";

    file.close();
}

string searchBook(const string& filename, const string& title) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        if (line.find(title) != string::npos) {
            cout << "Book found:\n" << line << endl;
            return line;
        }
    }

    return "";
}

int getUserChoice() {
    int choice;
    string userInput;

    cout << "Welcome to catalog-lib\n";
    cout << "---------------------------------------------------------------\n";
    cout << "What would you like to do?\n";
    cout << "0) Close app\n";
    cout << "1) Add a book to the catalog\n";
    cout << "2) Find a book in the catalog\n";
    cout << "Enter 0, 1, or 2: ";

    do {
        getline(cin, userInput);
        if (isNumber(userInput)) {
            choice = stoi(userInput);
            break;
        } else {
            cerr << "\nError: Incorrect value. Please enter 0, 1, or 2.\n\n";
        }
    } while (true);

    return choice;
}

bool shouldContinue(const string& text) {
    string userChoice;

    cout << "< Exit - press 0\n";
    cout << "< " << text << " - press 1\n";

    do {
        cout << "Enter your choice: ";
        cin >> userChoice;
		cin.ignore();

		if (userChoice == "1") {
            return true;
        } else if (userChoice == "0") {
            return false;
        } else {
            cout << "Invalid input. Please enter 0 or 1.\n";
        }
    } while (true);
}
