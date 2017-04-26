//4. Информационная запись о книге, выданной на руки абоненту представляет собой 
//структуру : номер читательского билета, фамилия абонента, дата выдачи, дата возврата, автор, название, 
//год издания, издательство, цена. Поиск по полям номер читательского билета, автор, издательство и дата возврата.


#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <functional>
#include <ctime>

class  Book {

public:
	int libraryCard;
	std::string subSurname;
	std::string issueDate;
	std::string returnDate;
	std::string author;
	std::string title;
	int publicationYear;
	std::string publishingHouse;
	unsigned short price;

	Book(int lC, std::string sS, std::string iD, std::string rD, std::string atr, std::string ttl, int pY, std::string pH, int prc) {
		libraryCard = lC;
		subSurname = sS;
		issueDate = iD;
		returnDate = rD;
		author = atr;
		title = ttl;
		publicationYear = pY;
		publishingHouse = pH;
		price = prc;
	}

	Book() {
		libraryCard = 0;
		subSurname = "";
		issueDate = "";
		returnDate = "";
		author = "";
		title = "";
		publicationYear = 2000;
		publishingHouse = "";
		price = 0;
	}



	~Book()	{}

	bool operator==(const Book& other) const {
		return	this->title == other.title;
	}
};

std::ostream& operator<<(std::ostream &os, const Book &book) {
	os << std::to_string(book.libraryCard) + "\t" +
		book.subSurname + "\t" +
		book.issueDate + "\t" +
		book.returnDate + "\t" +
		book.author + "\t" +
		book.title + "\t" +
		std::to_string(book.publicationYear) + "\t" +
		book.publishingHouse + "\t" +
		std::to_string(book.price) + "\n";
		
	return os;
}

std::istream& operator>>(std::istream &is, Book &book) {
	is >> book.libraryCard;
	is >> book.subSurname;
	is >> book.issueDate;
	is >> book.returnDate;
	is >> book.author;
	is >> book.title;
	is >> book.publicationYear;
	is >> book.publishingHouse;
	is >> book.price;

	return is;
}

Book inputBook();

//Predicats and Comparators

class LibraryCardPred {
protected:
	int card;

public:
	LibraryCardPred(int n) :card(n) {}

	bool operator() (Book book) {
		return card == book.libraryCard;
	}

	bool operator() (Book book1, Book book2) {
		return book1.libraryCard == book2.libraryCard;
	}
};

class AuthorPred {
protected:
	std::string author;

public:
	AuthorPred(std::string s) :author(s) {}

	bool operator() (Book book) {
		return author == book.author;
	}

	bool operator() (Book book1, Book book2) {
		return book1.author == book2.author;
	}
};

class PublishingHousePred {
protected:
	std::string house;

public:
	PublishingHousePred(std::string s) :house(s) {}

	bool operator() (Book book) {
		return house == book.publishingHouse;
	}

	bool operator() (Book book1, Book book2) {
		return book1.publishingHouse == book2.publishingHouse;
	}
};

class ReturnDatePred {
protected:
	std::string date;

public:
	ReturnDatePred(std::string s) :date(s) {}

	bool operator() (Book book) {
		return date == book.returnDate;
	}

	bool operator() (Book book1, Book book2) {
		return book1.returnDate == book2.returnDate;
	}
};

class LibraryCardComp {
public:
	bool operator()(Book book1, Book book2) {
		return book1.libraryCard < book2.libraryCard;
	}
};

class AuthorComp {
public:
	bool operator()(Book book1, Book book2) {
		return book1.author < book2.author;
	}
};

class PublishingHouseComp {
public:
	bool operator()(Book book1, Book book2) {
		return book1.publishingHouse < book2.publishingHouse;
	}
};

class ReturnDateComp {
public:
	bool operator()(Book book1, Book book2) {
		return book1.returnDate < book2.returnDate;
	}
};

class LibraryCardAcc {
protected:
	int card;
	std::vector<Book> *v;

public:
	LibraryCardAcc(int n) {
		card = n;
		v = new std::vector<Book>();
	}

	std::vector<Book> getSet() {
		return *v;
	}

	void operator()(Book book) {
		if (card == book.libraryCard)
			(*v).push_back(book);
	}
};

class AuthorAcc {
protected:
	std::string author;
	std::vector<Book> *v;

public:
	AuthorAcc(std::string s) {
		author = s;
		v = new std::vector<Book>();
	}

	std::vector<Book> getSet() {
		return *v;
	}

	void operator()(Book book) {
		if (author == book.author)
			(*v).push_back(book);
	}
};

class PublishingHouseAcc {
protected:
	std::string house;
	std::vector<Book> *v;

public:
	PublishingHouseAcc(std::string s) {
		house = s;
		v = new std::vector<Book>();
	}

	std::vector<Book> getSet() {
		return *v;
	}

	void operator()(Book book) {
		if (house == book.publishingHouse)
			(*v).push_back(book);
	}
};

class ReturnDateAcc {
protected:
	std::string date;
	std::vector<Book> *v;

public:
	ReturnDateAcc(std::string s) {
		date = s;
		v = new std::vector<Book>();
	}

	std::vector<Book> getSet() {
		return *v;
	}

	void operator()(Book book) {
		if (date == book.returnDate)
			(*v).push_back(book);
	}
};



template<class P = Book>
class MyContainer {
private:
	std::vector<P> vect;
	std::vector<P> subv;

public:
	MyContainer(int size) {
		vect = std::vector<P>(size);
	}

	MyContainer() {
		vect = std::vector<P>();
	}

	~MyContainer() {}

	bool add(P book) {
		if (!find(book)) {
			vect.push_back(book);
			return true;
		}
		
		return false;
	}

	bool find(P book, std::random_access_iterator_tag &it) {
		it = std::find(vect.begin(), vect.end(), book);
		return it != vect.end();
	}

	bool find(P book) {
		std::vector<P>::iterator it = std::find(vect.begin(), vect.end(), book);
		return it != vect.end();
	}

	void remove(std::vector<Book>::iterator it) {
		vect.erase(it);
	}

	void change(std::vector<Book>::iterator &it) {
		*it = inputBook();
	}

	bool findByLibraryCard(int card, std::vector<Book>::iterator &it) {
		LibraryCardPred pred = LibraryCardPred(card);
		it = std::find_if(vect.begin(), vect.end(), pred);
		return it != vect.end();
	}

	bool findByAuthor(std::string author, std::vector<Book>::iterator &it) {
		AuthorPred pred = AuthorPred(author);
		it = std::find_if(vect.begin(), vect.end(), pred);
		return it != vect.end();
	}

	bool findByPublishingHouse(std::string house, std::vector<Book>::iterator &it) {
		PublishingHousePred pred = PublishingHousePred(house);
		it = std::find_if(vect.begin(), vect.end(), pred);
		return it != vect.end();
	}

	bool findByReturnDate(std::string date, std::vector<Book>::iterator &it) {
		ReturnDatePred pred = ReturnDatePred(date);
		it = std::find_if(vect.begin(), vect.end(), pred);
		return it != vect.end();
	}

	bool findByLibraryCardBinary(int card, std::vector<Book>::iterator &it) {
		LibraryCardPred pred = LibraryCardPred(card);
		LibraryCardComp comp = LibraryCardComp();
		std::sort(vect.begin(), vect.end(), comp);
		P b = Book(card, "", "", "", "", "", 1990, "", 0);
		if (std::binary_search(vect.begin(), vect.end(), b, comp)) {
			it = std::find_if(vect.begin(), vect.end(), pred);
			return true;
		}
		return false;
	}

	bool findByAuthorBinary(std::string author, std::vector<Book>::iterator &it) {
		AuthorPred pred = AuthorPred(author);
		AuthorComp comp = AuthorComp();
		std::sort(vect.begin(), vect.end(), comp);
		P b = Book(0, "", "", "", author, "", 1990, "", 0);
		if (std::binary_search(vect.begin(), vect.end(), b, comp)) {
			it = std::find_if(vect.begin(), vect.end(), pred);
			return true;
		}
		return false;
	}

	bool findByPublishingHouseBinary(std::string house, std::vector<Book>::iterator &it) {
		PublishingHousePred pred = PublishingHousePred(house);
		PublishingHouseComp comp = PublishingHouseComp();
		std::sort(vect.begin(), vect.end(), comp);
		P b = Book(0, "", "", "", "", "", 1990, house, 0);
		if (std::binary_search(vect.begin(), vect.end(), b, comp)) {
			it = std::find_if(vect.begin(), vect.end(), pred);
			return true;
		}
		return false;
	}

	bool findByReturnDateBinary(std::string date, std::vector<Book>::iterator &it) {
		ReturnDatePred pred = ReturnDatePred(date);
		ReturnDateComp comp = ReturnDateComp();
		std::sort(vect.begin(), vect.end(), comp);
		P b = Book(0, "", "", date, "", "", 1990, "", 0);
		if (std::binary_search(vect.begin(), vect.end(), b, comp)) {
			it = std::find_if(vect.begin(), vect.end(), pred);
			return true;
		}
		return false;
	}

	void findSubSetByLibraryCard(int card) {
		LibraryCardAcc acc = LibraryCardAcc(card);
		std::for_each(vect.begin(), vect.end(), acc);
		subv = acc.getSet();
	}

	void findSubSetByAuthor(std::string author) {
		AuthorAcc acc = AuthorAcc(author);
		std::for_each(vect.begin(), vect.end(), acc);
		subv = acc.getSet();
	}

	void findSubSetByPublishingHouse(std::string house) {
		PublishingHouseAcc acc = PublishingHouseAcc(house);
		std::for_each(vect.begin(), vect.end(), acc);
		subv = acc.getSet();
	}

	void findSubSetByReturnDate(std::string date) {
		ReturnDateAcc acc = ReturnDateAcc(date);
		std::for_each(vect.begin(), vect.end(), acc);
		subv = acc.getSet();
	}

	void consoleInput() {
		vect.clear();
		P book;
		while (true) {
			try {
				book = inputBook();
			}
			catch(const char* str) {
				return;
			}

			add(book);
		}
	}

	void consoleOutput() {
		copy(vect.begin(), vect.end(), std::ostream_iterator<P>(std::cout, "\n"));
	}

	void consoleOutputSub() {
		copy(subv.begin(), subv.end(), std::ostream_iterator<P>(std::cout, "\n"));
	}

	void fileInput(std::string fn) {
		std::fstream fin(fn, std::ios::in);
		if (fin.is_open()) {
			std::istream_iterator<P> is(fin);
			vect.clear();
			P book = *is++;
			while (!fin.fail() && !fin.eof()) {
				add(book);
				book = *is++;
			}
			add(book);
			fin.close();
		}
		else
			std::cout << "File doesn't exist!" << std::endl;
	}

	void fileOutput(std::string fn) {
		std::fstream fout(fn, std::ios::out);
		if (fout.is_open()) {
			copy(vect.begin(), vect.end(), std::ostream_iterator<P>(fout, "\n"));
			fout.close();
		}
		else
			std::cout << "Error while opening file!" << std::endl;
	}

	void fileOutputSub(std::string fn) {
		std::fstream fout(fn, std::ios::out);
		if (fout.is_open()) {
			copy(subv.begin(), subv.end(), std::ostream_iterator<P>(fout, "\n"));
			fout.close();
		}
		else
			std::cout << "Error while opening file!" << std::endl;
	}
};


int inputInt(std::string message, int min = 0, int max = 10000) {
	std::string str;
	int res;

	while (true) {
		std::cout << message;
		try {
			std::cin >> str;
			if (str == "exit") throw "exit";
			res = std::stoi(str);
			while (res < min || res > max) {
				std::cout << "Error (value < " << min << " or value > " << max << "). Repeat: ";
				std::cin >> res;
			}
			return res;
		}
		catch (std::exception &e) {
			std::cout << "Wrong number!" << std::endl;
		}
	}
}

std::vector<std::string> split(const std::string &text, char sep) {
	std::vector<std::string> tokens;
	std::size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != std::string::npos) {
		if (end != start) {
			tokens.push_back(text.substr(start, end - start));
		}
		start = end + 1;
	}
	if (end != start) {
		tokens.push_back(text.substr(start));
	}
	return tokens;
}

bool checkDate(std::string date) {
	std::vector<std::string> tokens = split(date, '/');
	if (tokens.size() != 3) return false;
	try {
		int day = std::stoi(tokens[0]);
		if (day < 1 || day > 31) return false;
		int month = std::stoi(tokens[1]);
		if (month < 1 || month > 12) return false;
		int year = std::stoi(tokens[2]);
		if (year < 1900 || year > 2017) return false;
	}
	catch (...) {
		return false;
	}
	return true;
}

std::string inputDate(std::string message = "Input date in format dd/mm/yyyy : ") {
	std::string res;

	std::cout << message;
	std::cin >> res;

	while (true) {
		if (checkDate(res)) return res;
		std::cout << "Wrong date. Repeat: ";
		std::cin >> res;
	}
}

Book inputBook() {
	int libraryCard;
	std::string subSurname;
	std::string issueDate;
	std::string returnDate;
	std::string author;
	std::string title;
	int publicationYear;
	std::string publishingHouse;
	int price;

	std::cout << "-------------BOOK-------------" << std::endl;
	std::cout << "Type \"exit\" to exit" << std::endl;

	libraryCard = inputInt("Enter library card: ");

	std::cout << "Enter subscriber surname: ";
	std::cin >> subSurname;

	issueDate = inputDate("Enter issue date(dd/mm/yyyy): ");

	returnDate = inputDate("Enter return date(dd/mm/yyyy): ");;

	std::cout << "Enter author: ";
	std::cin >> author;

	std::cout << "Enter title: ";
	std::cin >> title;

	publicationYear = inputInt("Enter publication year: ", 1700, 2017);

	std::cout << "Enter publishing house: ";
	std::cin >> publishingHouse;

	price = inputInt("Enter price: ");

	return Book(libraryCard, subSurname, issueDate, returnDate, author, title, publicationYear, publishingHouse, price);
}



void printMainMenu() {
	std::cout << "-------------------------------------" << std::endl;
	std::cout << " 1)Input" << std::endl;
	std::cout << " 2)Output" << std::endl;
	std::cout << " 3)Find" << std::endl;
	std::cout << " 4)Add" << std::endl;
	std::cout << " 5)Subset" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "-------------------------------------" << std::endl;
}

void printMenuConsoleFile() {
	std::cout << "-------------------------------------" << std::endl;
	std::cout << " 1)Console" << std::endl;
	std::cout << " 2)File" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "-------------------------------------" << std::endl;
}

void printMenuFindParam() {
	std::cout << "-------------------------------------" << std::endl;
	std::cout << " 1)By library card" << std::endl;
	std::cout << " 2)By author" << std::endl;
	std::cout << " 3)By publishing house" << std::endl;
	std::cout << " 4)By return date" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "-------------------------------------" << std::endl;
}

void printMenuSearch() {
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "Command list:" << std::endl;
	std::cout << " 1)Simple search" << std::endl;
	std::cout << " 2)Binary search" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "-------------------------------------" << std::endl;
}

void printAction() {
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "Action with record:" << std::endl;
	std::cout << " 1)Print" << std::endl;
	std::cout << " 2)Change" << std::endl;
	std::cout << " 3)Delete" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "-------------------------------------" << std::endl;
}

std::string output_file_name() {
	std::string name;
	std::cout << "Enter file name(empty string = 'defaulname'): " << std::endl;
	std::getline(std::cin, name);
	std::getline(std::cin, name);
	if (name == "") name = "defaultname";
	return name + ".txt";
}

std::string input_file_name() {
	std::fstream f;
	std::string res;
	std::cout << "Enter text file name(empty string = 'defaultname'): ";
	std::getline(std::cin, res);
	std::getline(std::cin, res);
	f.open(res + ".txt");
	while (!f.is_open() && res != "") {
		std::cout << "There are no such file, repeat input(empty string = 'defaultname'): ";
		std::getline(std::cin, res);
		f.open(res + ".txt");
	};
	f.close();
	return (res == "") ? "defaultname.txt" : res + ".txt";
}

int main() {
	MyContainer<> cont = MyContainer<>();
	std::string str;
	int n;
	bool binarSearch;
	bool found;
	std::string FName;
	std::vector<Book>::iterator it;

	while (true) {
		printMainMenu();
		n = inputInt("Enter the command: ", 0, 5);
		switch (n) {
		case 1://INPUT
			printMenuConsoleFile();
			n = inputInt("Enter the command: ", 0, 2);
			switch (n) {
			case 1:
				cont.consoleInput();
				break;
			case 2:
				FName = input_file_name();
				cont.fileInput(FName);
				break;
			case 0:
				break;
			}
			break;
		case 2://OUTPUT
			printMenuConsoleFile();
			n = inputInt("Enter the command:", 0, 2);
			switch (n) {
			case 1:
				cont.consoleOutput();
				break;
			case 2:
				cont.fileOutput(output_file_name());
				break;
			case 0:
				break;
			}
			break;
		case 3://FIND
			printMenuSearch();
			n = inputInt("Enter the command: ", 1, 2);
			switch (n) {
			case 1://SIMPLE
				binarSearch = false;
				break;
			case 2://BINARY
				binarSearch = true;
				break;
			}
			printMenuFindParam();
			n = inputInt("Enter the command: ", 1, 4);
			switch (n) {
			case 1://Library card
				if (binarSearch)
					found = cont.findByLibraryCardBinary(inputInt("Enter library card: "), it);
				else
					found = cont.findByLibraryCard(inputInt("Enter library card: "), it);
				break;
			case 2://Author
				std::cout << "Enter author: ";
				std::cin >> str;

				if (binarSearch)
					found = cont.findByAuthorBinary(str, it);
				else
					found = cont.findByAuthor(str, it);
				break;
			case 3://Publishing house
				std::cout << "Enter publishing house: ";
				std::cin >> str;

				if (binarSearch)
					found = cont.findByPublishingHouseBinary(str, it);
				else
					found = cont.findByPublishingHouse(str, it);
				break;
			case 4://Return date
				std::cout << "Enter return date: ";
				std::cin >> str;

				if (binarSearch)
					found = cont.findByReturnDateBinary(str, it);
				else
					found = cont.findByReturnDate(str, it);
				break;
			}
			if (found) {
				std::cout << "Record found \n";
				printAction();
				n = inputInt("Enter the command: ", 0, 3);
				switch (n) {
				case 1:
					std::cout << *it;
					break;
				case 2:
					cont.change(it);
					break;
				case 3:
					cont.remove(it);
					break;
				case 0:
					break;
				}
			}
			else
				std::cout << "Record not found \n";
			break;
		case 4://ADD
			cont.add(inputBook());
			break;
		case 5://SUBSET
			printMenuFindParam();
			n = inputInt("Enter the command: ", 1, 4);
			switch (n) {
			case 1://Library card
				cont.findSubSetByLibraryCard(inputInt("Enter library card: "));
				break;
			case 2://Author
				std::cout << "Enter author: ";
				std::cin >> str;

				cont.findSubSetByAuthor(str);
				break;
			case 3://Publishing house
				std::cout << "Enter publishing house: ";
				std::cin >> str;

				cont.findSubSetByPublishingHouse(str);
				break;
			case 4://Return date
				std::cout << "Enter return date: ";
				std::cin >> str;

				cont.findSubSetByReturnDate(str);
				break;
			}
			printMenuConsoleFile();
			n = inputInt("Enter the command: ", 0, 2);
			switch (n) {
			case 1:
				cont.consoleOutputSub();
				break;
			case 2:
				FName = output_file_name();
				cont.fileOutputSub(FName);
				break;
			case 3:
				break;
			}
			break;
		case 0://EXIT
			return 0;
		}
	}
}