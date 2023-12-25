#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

struct CatalogEntry {
    long long code;
    string lastname;
    int page;
    string title;
    int year;
};

vector<CatalogEntry> getInput(CatalogEntry& entry);
bool isNumber(const string& str);
void writeFile(const string& filename, const CatalogEntry& entry);
void searchBook(vector<CatalogEntry>& books);
int getUserChoice();
bool shouldContinue(const string &text);
vector<CatalogEntry> readBookFromFile(string &filename);
void displayCatalog( vector<CatalogEntry> books);

int main() {
    string filename = "catalog.txt";
    vector<CatalogEntry> books;
    int userChoice;

    cout << "======================" << endl;
    cout << "Welcome to catalog-lib\n";
    cout << "======================" << endl;

    while (true) {
        userChoice = getUserChoice();
        books = readBookFromFile(filename);

        switch (userChoice) {
            case 0:
                exit(0);
                break;
            case 1:
                do {
                    CatalogEntry newEntry;
                    displayCatalog(getInput(newEntry));
                    writeFile(filename, newEntry);
                } while (shouldContinue("Add another book"));
                break;
            case 2:
                do {
                    searchBook(books);
                } while (shouldContinue("Search another book"));
                break;
            default:
                cout << "\nUnexpected value\n" << endl;
                break;
        }
    }

    return 0;
}

vector<CatalogEntry> getInput(CatalogEntry& entry) {
	string userInput;
    vector<CatalogEntry> addedBook;

    cout << "Enter code of the book: ";
    do {
        getline(cin, userInput);
        if (isNumber(userInput)) {
            entry.code = stoll(userInput);
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
            entry.year = stoll(userInput);
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

    cout << "\nAdded book:\n"<<endl;
    addedBook.push_back(entry);
    return addedBook;
}

bool isNumber(const string& str) {
    if(str == ""){
        return false;
    }
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

void searchBook(vector<CatalogEntry> &books) {
    // string namefile = filename;
    // vector<CatalogEntry> books = readBookFromFile(namefile);

    cout << "\nTo find a book enter title" << endl;

    string elementToFind;
    getline(cin, elementToFind);
   

  	transform(elementToFind.begin(), elementToFind.end(), elementToFind.begin(), ::tolower);

    vector<CatalogEntry> result;
    string g1;

    for (const CatalogEntry &book : books){
        g1 = book.title;

        // Convert the author's name, publisher, and title in the database to lowercase
        transform(g1.begin(), g1.end(), g1.begin(), ::tolower);

        if (g1.find(elementToFind) != string::npos)
        {
            result.push_back(book);
        }
	}
     cout << "Found book:" << endl;
    displayCatalog(result);
}

int getUserChoice() {
    int choice;
    string userInput;

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

    cout << "\n\n< Exit - press 0\n";
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

vector<CatalogEntry> readBookFromFile(string &filename){
    vector<CatalogEntry> books;

    ifstream file(filename);

    if(!file.is_open()){
        cerr << "File is not found" << endl;
        exit(EXIT_FAILURE);
    }else{
        CatalogEntry book;
        string line;

        while(getline(file, line)){
            stringstream iss(line); 
            string i;
            getline(iss, i, '\t');
            book.code = stoll(i);
            getline(iss, book.lastname, '\t');
            getline(iss, i, '\t');
            book.page = stoi(i);
            getline(iss, book.title, '\t');
            getline(iss, i);
            book.year = stoi(i);

        //     iss >> book.code >> book.lastname >> book.page >> book.title >> book.year;
            books.push_back(book);
        }
    }

    file.close();
    return books;
}

void displayCatalog(vector<CatalogEntry> books){
    CatalogEntry book;

    cout << left << setw(25) << "    Code" << setw(19) << "Lastname" << setw(15) << "Page" << setw(20) << "Title" << setw(10) << right << "Year" << endl;
    for (size_t i = 0; i < books.size(); i++){
        cout << i + 1 << ")" << left << setw(20) << books[i].code << setw(20) << books[i].lastname << setw(10) << books[i].page << setw(25) << books[i].title << setw(15) << right << books[i].year << endl;
    }
	cout << "\n\n";

}