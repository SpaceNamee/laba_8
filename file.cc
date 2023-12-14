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
} needInfo;

// створення файлу
// запис інформації
// вивід інформації
// функція з інтерфейсу
void GetInfo(struct catalog *needInfo);
void FillFile(string filename, struct catalog needInfo);
bool CheckIsNumber(string &userInput);
string SearchBook(struct catalog needInfo, string filename);
int interface();
bool continueOrNot(string text);

int main()
{
	string filename = "catalog.txt";
	int userChoosing;

	while (true)
	{
		userChoosing = interface();
		switch (userChoosing)
		{
		case 0:
			exit(0);
			break;
		case 1:
			do
			{
				GetInfo(&needInfo);
				FillFile(filename, needInfo);

			} while (continueOrNot("Add another book"));
			break;
		case 2:
			do
			{
				if (SearchBook(needInfo, filename) == "")
				{
					cout << "Such book is not found" << endl;
				}

			} while (continueOrNot("Search another book"));

			break;
		default:
			cout<< "\nUnexpected value"<<endl;

			break;
		}
	}
}

void GetInfo(struct catalog *needInfo)
{
	string userInput;

	cin.ignore(999999, '\n');
	do
	{
		std::cout << "Enter code of the book:" << std::endl;
		getline(cin, userInput);

		if (CheckIsNumber(userInput))
		{
			needInfo->code = stoi(userInput);
			break;
		}
		else
		{
			std::cout << "Invalid input. Please enter a valid number.\n"
					  << std::endl;
		}
	} while (true);

	cout << "Enter last_name of the author:" << endl;
	getline(cin, needInfo->lastname);

	cout << "Enter title of the author:" << endl;
	getline(cin, needInfo->title);

	do
	{
		cout << "Enter year of publication of the book:" << endl;
		getline(cin, userInput);

		if (CheckIsNumber(userInput))
		{
			needInfo->year = stoi(userInput);
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
			needInfo->page = stoi(userInput);
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

void FillFile(string filename, struct catalog needInfo)
{

	ofstream file;
	file.open(filename, std::ios::app);

	if (!file)
	{
		cerr << "File was not found" << endl;
	}

	file << needInfo.code
		 << "\t" << needInfo.lastname
		 << "\t" << needInfo.page
		 << "\t" << needInfo.title
		 << "\t" << needInfo.year << "\n";

	file.close();
}

string SearchBook(struct catalog needInfo, string filename)
{

	string title_of_search_book;
	cout << "Enter a searched book" << endl;
	cin.ignore(9999, '\n');
	getline(cin, title_of_search_book);

	ifstream file(filename);

	string line;

	while (getline(file, line))
	{
		if (line.find(title_of_search_book) != string::npos)
		{
			cout << "Such book is found" << endl
				 << line << endl;
			return line;
		}
	}
	return "";
}

int interface()
{
	string userChoosing;
	int choosingInInt;
	std::cout << "Welcome in catalog-lib" << std::endl;

	do
	{
		std::cout<< "---------------------------------------------------------------" << std::endl
			  << "What are you going to do?" << std::endl
			  << "0) Close app" << std::endl
			  << "1) Add the book to the catalog" << std::endl
			  << "2) Find the book in the catalog" << std::endl
			  << "Enter 0, 1 or 2" << std::endl;
	cin >> userChoosing;

	if (CheckIsNumber(userChoosing))
	{
		choosingInInt = stoi(userChoosing);
		break;
		}
		else
		{
			cerr <<"\n"<<"Incorrect value"<<"\n"<<endl;
		}
	} while (true);

	return choosingInInt;
}

bool continueOrNot(string text)
{
	string userChoosing;
	cout << "< Exit -press 0" << endl
		 <<"<"<<text<<" -press 1" << endl;
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
