#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;
struct catalog
{
    int code;
    string lastname;
    int page;
    string title;
    int year;
} m;

// створення файлу
// запис інформації
// вивід інформації
// функція з інтерфейсу
void GetInfo(struct catalog *m);
void FillFile(string filename, struct catalog m);

bool CheckIsNumber(string &userInput);
string SearchBook(struct catalog m,string filename);
int interface();
bool continueOrNot();

int main()
{

	string filename = "catalog.txt";
	int userChoosing;
	bool breaker = true;


	while (breaker)
	{
		userChoosing = interface();
		switch (userChoosing)
		{
		case 0:
			breaker = false;
			break;
		case 1:
			do
			{
				GetInfo(&m);
				FillFile(filename, m);

			} while (continueOrNot());
			break;
		case 2:
			do
			{

				SearchBook(m, filename);

			} while (continueOrNot());

			break;
		default:
			cout << "Unexpected value";
			break;
		}
		}

		
}






void GetInfo(struct catalog *m)
{
	string userInput;

	cin.ignore(999999, '\n');
	do
	{
		std::cout << "Enter code of the book:" << std::endl;
		getline(cin, userInput);

		if (CheckIsNumber(userInput))
		{
			m->code = stoi(userInput);
			break;
		}
		else
		{
			std::cout << "Invalid input. Please enter a valid number.\n"
					  << std::endl;
		}
	} while (true);

	cout << "Enter last_name of the author:" << endl;
	getline(cin, m->lastname);
	

	cout << "Enter title of the author:" << endl;
	getline(cin, m->title);

	do
	{
		cout << "Enter year of publication of the book:" << endl;
		getline(cin, userInput);

		if (CheckIsNumber(userInput))
		{
			m->year = stoi(userInput);
			break;
		}
		else
		{
			std::cout << "Invalid input. Please enter a valid year.\n"
					  << std::endl;
		}
	} while (true);

	do
	{
		cout << "Enter number of page in the book:" << endl;
		getline(cin, userInput);

		if (CheckIsNumber(userInput))
		{
			m->page = stoi(userInput);
			break;
		}
		else
		{
			std::cout << "Invalid input. Please enter a valid number.\n"
					  << std::endl;
		}
	} while (true);

}

bool CheckIsNumber(string &userInput)
{
	bool containsOnlyDigits = true;

	for (char c : userInput)
	{
		if (!isdigit(c))
		{
			containsOnlyDigits = false;
			break;
		}
	}

	return containsOnlyDigits;
}

void FillFile(string filename, struct catalog m)
{

	ofstream file;
	file.open(filename,std::ios::app);

	if (!file)
	{
		cerr << "File was not found" << endl;
	}

	file << m.code
		 << "\t" << m.lastname
		 << "\t" << m.page
		 << "\t" << m.title
		 << "\t" << m.year << "\n";

	file.close();
}

string SearchBook(struct catalog m, string filename)
{
	string title_of_search_book;
	cout << "Enter a searched book" << endl;
	getline(cin, title_of_search_book);

	ifstream file(filename);

	string line;

	while(getline(file, line)){
		
	}

}

int interface()
{
	std::cout << "Welcome in catalog-lib" << std::endl
			  << "---------------------------------------------------------------" << std::endl
			  << "What are you going to do?" << std::endl
			  << "0) Close app" << std::endl
			  << "1) Add the book to the catalog" << std::endl
			  << "2) Find the book in the catalog" << std::endl
			  << "Enter 0, 1 or 2" << std::endl;

	string userChoosing;
	int choosingInInt;
	do
	{
		cin >> userChoosing;
		if (CheckIsNumber(userChoosing))
		{
			choosingInInt = stoi(userChoosing);
			break;
		}
		else
		{
			cerr << "Incorrect value";
		}
	} while (true);

	return choosingInInt;
}

bool continueOrNot()
{
	string userChoosing;
	cout << "< Exit -press 0" << endl
		 << "< Add another -press 1" << endl;
	do
	{
		cin >> userChoosing;
		if (userChoosing == "1")
		{
			return true;
		}
		else if (userChoosing == "0")
		{
			return false;
		}
		else
		{
			std::cout << "Invalid input. Please enter 0 or 1." << std::endl;
		}

	} while (true);
}
