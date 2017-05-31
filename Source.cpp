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
#include <math.h>
#include "Date.h"
#include "Decimal.h"


class  Book {

public:
	int libraryCard;
	std::string subSurname;
	Date issueDate;
	Date returnDate;
	std::string author;
	std::string title;
	int publicationYear;
	std::string publishingHouse;
	dec::decimal<2> price;

	Book(int lC, std::string sS, Date &iD, Date &rD, std::string atr, std::string ttl, int pY, std::string pH, dec::decimal<2> prc) {
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
		issueDate = Date();
		returnDate = Date();
		author = "";
		title = "";
		publicationYear = 2000;
		publishingHouse = "";
		price = 0;
	}

	~Book()	{}

	bool operator==(const Book& other) const {
		return  this->libraryCard == other.libraryCard &&
				this->subSurname == other.subSurname &&
				this->issueDate == other.issueDate &&
				this->returnDate == other.returnDate &&
				this->author == other.author &&
				this->title == other.title &&
				this->publicationYear == other.publicationYear &&
				this->publishingHouse == other.publishingHouse &&
				this->price == other.price;
	}
};

std::ostream& operator<<(std::ostream &os, const Book &book) {
	os << std::to_string(book.libraryCard) + "\t" +
		book.subSurname + "\t" +
		book.issueDate.ToString() + "\t" +
		book.returnDate.ToString() + "\t" +
		book.author + "\t" +
		book.title + "\t" +
		std::to_string(book.publicationYear) + "\t" +
		book.publishingHouse + "\t" +
		dec::toString(book.price) + "\n";
		
	return os;
}

std::istream& operator>>(std::istream &is, Book &book) {
	std::string iDate, rDate;
	is >> book.libraryCard;
	is >> book.subSurname;
	is >> iDate;
	book.issueDate.TryStrToDate(iDate);
	is >> rDate;
	book.returnDate.TryStrToDate(rDate);
	is >> book.author;
	is >> book.title;
	is >> book.publicationYear;
	is >> book.publishingHouse;
	dec::fromStream(is, book.price);

	return is;
}

Book inputBook();
void inputBookChanged(std::vector<Book>::iterator &it);

//Predicats and Comparators

class LibraryCardPred {
protected:
	int card;

public:
	LibraryCardPred(int n) :card(n) {}

	bool operator() (Book book) {
		return card == book.libraryCard;
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
};

class PublishingHousePred {
protected:
	std::string house;

public:
	PublishingHousePred(std::string s) :house(s) {}

	bool operator() (Book book) {
		return house == book.publishingHouse;
	}
};

class ReturnDatePred {
protected:
	Date date;

public:
	ReturnDatePred(Date _date) {
		date = _date;
	}

	bool operator() (Book book) {
		return date == book.returnDate;
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
	Date date;
	std::vector<Book> *v;

public:
	ReturnDateAcc(Date _date) {
		date = _date;
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

template<class P>
class Container {
protected:
	std::vector<P> vect;
public:
	typedef std::_Vector_iterator<std::_Vector_val<std::_Simple_types<P>>> my_iterator;
	typedef std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<P>>> my_const_iterator;

	Container(int size) {
		vect = std::vector<P>(size);
	}

	Container() {
		vect = std::vector<P>();
	}

	void clear() {
		vect.clear();
	}

	~Container() {}

	my_const_iterator begin() {
		return vect.cbegin();
	}

	my_const_iterator end() {
		return vect.cend();
	}

	int size() {
		return vect.size();
	}

	bool add(P p) {
		if (!find(p)) {
			vect.push_back(p);
			return true;
		}

		return false;
	}

	void remove(my_iterator &it) {
		vect.erase(it);
	}

	bool find(P p) {
		return std::find(vect.begin(), vect.end(), p) != vect.end();
	}

	template<class Pred>
	bool find(Pred &pred, my_iterator &it) {
		my_iterator itTmp;
		itTmp = std::find_if(vect.begin(), vect.end(), pred);
		if (itTmp == vect.end()) return false;
		it = itTmp;
		return true;
	}

	template<class Comp>
	bool find(Comp &comp, P p, my_iterator &it) {
		my_iterator itTmp;
		std::sort(vect.begin(), vect.end(), comp);
		itTmp = std::lower_bound(vect.begin(), vect.end(), p, comp);
		if (itTmp == vect.end() || comp(p, *itTmp)) return false;
		it = itTmp;
		return true;
	}

	template<class Acc>
	std::vector<P> findSubset(Acc acc) {
		std::for_each(vect.begin(), vect.end(), acc);
		return acc.getSet();
	}
};

class MyContainer : public Container<Book> {
public:
	MyContainer() {}

	MyContainer(std::vector<Book> _vect) {
		vect = _vect;
	}

	bool findByLibraryCard(int card, my_iterator &it) {
		return find(LibraryCardPred(card), it);
	}

	bool findByAuthor(std::string author, my_iterator &it) {
		return find(AuthorPred(author), it);
	}

	bool findByPublishingHouse(std::string house, my_iterator &it) {
		return find(PublishingHousePred(house), it);
	}

	bool findByReturnDate(Date date, my_iterator &it) {
		return find(ReturnDatePred(date), it);
	}

	bool findByLibraryCardBinary(int card, my_iterator &it) {
		Book book = Book(card, "", Date(), Date(), "", "", 1990, "", dec::decimal_cast<2>(0));
		return find(LibraryCardComp(), book, it);
	}

	bool findByAuthorBinary(std::string author, my_iterator &it) {
		Book book = Book(0, "", Date(), Date(), author, "", 1990, "", dec::decimal_cast<2>(0));
		return find(AuthorComp(), book, it);
	}

	bool findByPublishingHouseBinary(std::string house, my_iterator &it) {
		Book book = Book(0, "", Date(), Date(), "", "", 1990, house, dec::decimal_cast<2>(0));
		return find(PublishingHouseComp(), book, it);
	}

	bool findByReturnDateBinary(Date date, my_iterator &it) {
		Book book = Book(0, "", Date(), date, "", "", 1990, "", dec::decimal_cast<2>(0));
		return find(ReturnDateComp(), book, it);
	}

	MyContainer findSubSetByLibraryCard(int card) {
		return MyContainer(findSubset(LibraryCardAcc(card)));
	}

	MyContainer findSubSetByAuthor(std::string author) {
		return MyContainer(findSubset(AuthorAcc(author)));
	}

	MyContainer findSubSetByPublishingHouse(std::string house) {
		return MyContainer(findSubset(PublishingHouseAcc(house)));
	}

	MyContainer findSubSetByReturnDate(Date date) {
		return MyContainer(findSubset(ReturnDateAcc(date)));
	}

	void fileInput(std::fstream fin) {
		if (fin.is_open()) {
			std::istream_iterator<Book> is(fin);
			vect.clear();
			if (fin.eof()) return;
			Book book = *is++;
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

	void fileOutput(std::fstream fout) {
		if (fout.is_open()) {
			copy(vect.begin(), vect.end(), std::ostream_iterator<Book>(fout, "\n"));
			fout.close();
		}
		else
			std::cout << "Error while opening file!" << std::endl;
	}

	void output(std::ostream_iterator<Book> os) {
		copy(vect.begin(), vect.end(), os);
	}
};


bool checkInt(std::string str) {
	if (str.length() == 0) {
		return false;
	}
	size_t i = 0;
	while ((i < str.length()) && ((str[i] == ' ') || (str[i] == '	'))) {
		++i;
	}
	if (i >= str.length()) {
		return false;
	}
	int sign = 1;
	switch (str[i]) {
	case '-': {
		sign = -1;
		++i;
		break;
	}
	case '+': {
		++i;
		break;
	}
	default: {
		break;
	}
	}

	size_t j = i;
	bool result = j < str.length();
	while ((j < str.length()) && (result)) {
		result = (str[j] >= '0') && (str[j] <= '9');
		++j;
	}

	while ((j < str.length()) && ((str[j] == ' ') || (str[j] == '	'))) {
		++j;
	}

	return (j == str.length()) && (result);
}

int inputInt(std::string message, int min = 0, int max = 10000, bool isAdd = true) {
	std::string str;
	int res;
	bool ok = false;

	while (!ok) {
		std::cout << message;
		try {
			std::cin >> str;
			if (str == "exit") throw "exit";
			if (!isAdd && str == "skip") return -1;

			if (checkInt(str)) {
				res = std::stoi(str);
				if (res < min || res > max)
					std::cout << "Wrong value. Repeat: ";
				else
					ok = true;
			}
			else
				std::cout << "Wrong value! ";
		}
		catch (std::exception&) {
			std::cout << "Wrong number!" << std::endl;
		}
	}

	return res;
}

Date inputDate(std::string message = "Input date in format dd/mm/yyyy : ", bool isAdd = true) {
	std::string res;
	Date date = Date();

	std::cout << message;
	bool ok = false;

	while (!ok) {
		std::cin >> res;
		if (res == "exit") throw "exit";
		if (!isAdd && res == "skip") return date;
		ok = date.TryStrToDate(res);
		if (!ok) std::cout << "Wrong date. Repeat: ";
	}

	return date;
}

bool checkPrice(std::string price) {
	if (price.length() == 0) {
		return false;
	}

	size_t i = 0;
	while ((i < price.length()) && ((price[i] == ' ') || (price[i] == '	'))) {
		++i;
	}

	if (i >= price.length()) {
		return false;
	}

	int sign = 1;

	switch (price[i]) {
		case '-': {
			return false;
		}

		case '+': {
			++i;
			break;
		}

		default: {
			break;
		}
	}

	size_t j = i;
	bool result = j < price.length();
	int dot_number = 0;
	while ((j < price.length()) && (result)) {
		if (price[j] == '.') {
			++dot_number;
		}
		result = ((price[j] >= '0') && (price[j] <= '9')) || ((price[j] == '.') && (dot_number <= 1));
		++j;
	}

	while ((j < price.length()) && ((price[j] == ' ') || (price[j] == '	'))) {
		++j;
	}

	return (j == price.length()) && (result);
}

dec::decimal<2> inputPrice(std::string message = "Input price : ", bool isAdd = true) {
	std::string tmp;
	dec::decimal<2> res;

	std::cout << message;
	bool ok = false;

	while (!ok) {
		std::cin >> tmp;
		if (tmp == "exit") throw "exit";
		if (!isAdd && tmp == "skip") return dec::decimal_cast<2>(-1);
		ok = checkPrice(tmp);
		if (!ok) std::cout << "Wrong price. Repeat: ";
	}
	dec::fromString(tmp, res);
	return res;
}

Book inputBook() {
	int libraryCard;
	std::string subSurname;
	Date issueDate;
	Date returnDate;
	std::string author;
	std::string title;
	int publicationYear;
	std::string publishingHouse;
	dec::decimal<2> price;

	std::cout << "-------------BOOK-------------" << std::endl;
	std::cout << "Type \"exit\" to exit" << std::endl;

	libraryCard = inputInt("Enter library card: ");

	std::cout << "Enter subscriber surname: ";
	std::cin >> subSurname;
	if (subSurname == "exit") throw "exit";

	issueDate = inputDate("Enter issue date(dd/mm/yyyy): ");

	returnDate = inputDate("Enter return date(dd/mm/yyyy): ");;

	std::cout << "Enter author: ";
	std::cin >> author;
	if (author == "exit") throw "exit";

	std::cout << "Enter title: ";
	std::cin >> title;
	if (title == "exit") throw "exit";

	publicationYear = inputInt("Enter publication year: ", 1900, 2017);

	std::cout << "Enter publishing house: ";
	std::cin >> publishingHouse;
	if (publishingHouse == "exit") throw "exit";

	price = inputPrice("Enter price: ");

	return Book(libraryCard, subSurname, issueDate, returnDate, author, title, publicationYear, publishingHouse, price);
}

void inputBookChanged(std::vector<Book>::iterator &it) {
	std::cout << "-------------BOOK-------------" << std::endl;
	std::cout << "Type \"skip\" to skip" << std::endl;
	int intTmp;
	dec::decimal<2> decTmp;
	std::string strTmp;
	Date dateTmp;
	Date defDt = Date();

	intTmp = inputInt("Enter library card(default: " + std::to_string(it->libraryCard) + "): ", 0, 1000, false);
	if (intTmp != -1) it->libraryCard = intTmp;

	std::cout << "Enter subscriber surname(dafault: " + it->subSurname + "): ";
	std::cin >> strTmp;
	if (strTmp == "exit") throw "exit";
	if (strTmp != "skip") it->subSurname = strTmp;

	strTmp = it->issueDate.ToString();
	dateTmp = inputDate("Enter issue date(dd/mm/yyyy)(default: " + strTmp + "):", false);
	if (dateTmp == defDt);
	else it->issueDate = dateTmp;

	strTmp = it->returnDate.ToString();
	dateTmp = inputDate("Enter return date(dd/mm/yyyy)(default: " + strTmp + "):", false);
	if (dateTmp == defDt);
	else it->returnDate= dateTmp;

	std::cout << "Enter author(dafault: " + it->author + "): ";
	std::cin >> strTmp;
	if (strTmp == "exit") throw "exit";
	if (strTmp != "skip") it->author = strTmp;

	std::cout << "Enter title(dafault: " + it->title + "): ";
	std::cin >> strTmp;
	if (strTmp == "exit") throw "exit";
	if (strTmp != "skip") it->title = strTmp;
	

	intTmp = inputInt("Enter publication year(default: " + std::to_string(it->publicationYear) + "): ", 1900, 2017, false);
	if (intTmp != -1) it->publicationYear = intTmp;

	std::cout << "Enter publishing house(dafault: " + it->publishingHouse + "): ";
	std::cin >> strTmp;
	if (strTmp == "exit") throw "exit";
	if (strTmp != "skip") it->publishingHouse = strTmp;
	

	decTmp = inputPrice("Enter price(default: " + dec::toString(it->price) + "): ", false);
	if (decTmp != dec::decimal_cast<2>(-1))
		it->price = decTmp;
}

void consoleInput(MyContainer &cont) {
	cont.clear();
	Book book;
	while (true) {
		try {
			book = inputBook();
		}
		catch (const char*) {
			return;
		}

		cont.add(book);
	}
}

//void consoleOutput(MyContainer cont) {
//	if (cont.size() == 0) {
//		std::cout << "Container is empty!" << std::endl;
//	}
//	else {
//		std::cout << "LC\tSub Surname\tIssue Date\tReturn Date\tAuthor\t\tTitle\tPYear\tPHouse\tPrice" << std::endl;
//		copy(cont.begin(), cont.end(), std::ostream_iterator<Book>(std::cout, "\n"));
//	}
//}

void consoleOutput(MyContainer cont) {
	if (cont.size() == 0) {
		std::cout << "Container is empty!" << std::endl;
	}
	else {
		std::cout << "LC\tSub Surname\tIssue Date\tReturn Date\tAuthor\t\tTitle\tPYear\tPHouse\tPrice" << std::endl;
		cont.output(std::ostream_iterator<Book>(std::cout, "\n"));
	}
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

void printCaption() {
	std::cout << "LC\tSub Surname\tIssue Date\tReturn Date\tAuthor\t\tTitle\tPYear\tPHouse\tPrice" << std::endl;
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
	MyContainer cont = MyContainer();
	MyContainer subcont = MyContainer();
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
				consoleInput(cont);
				break;
			case 2:
				FName = input_file_name();
				cont.fileInput(std::fstream(FName, std::ios::in));
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
				consoleOutput(cont);
				break;
			case 2:
				FName = output_file_name();
				cont.fileOutput(std::fstream(FName, std::ios::out));
				break;
			case 0:
				break;
			}
			break;
		case 3://FIND
			printMenuSearch();
			n = inputInt("Enter the command: ", 0, 2);
			switch (n) {
			case 1://SIMPLE
				binarSearch = false;
				break;
			case 2://BINARY
				binarSearch = true;
				break;
			}
			if (n != 0) {
				printMenuFindParam();
				n = inputInt("Enter the command: ", 0, 4);
				switch (n) {
				case 0:
					break;
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
					if (binarSearch)
						found = cont.findByReturnDateBinary(inputDate("Enter return date: "), it);
					else
						found = cont.findByReturnDate(inputDate("Enter return date: "), it);
					break;
				}
				if (n != 0) {
					if (found) {
						std::cout << "Record found \n";
						printAction();
						n = inputInt("Enter the command: ", 0, 3);
						while (n != 0) {
							switch (n) {
							case 1:
								printCaption();
								std::cout << *it;
								break;
							case 2:
								try {
									inputBookChanged(it);
								}
								catch (const char*) {
									break;
								}
								break;
							case 3:
								cont.remove(it);
								std::cout << "Record was deleted" << std::endl;
								break;
							case 0:
								break;
							}
							if (n == 3) break;
							printAction();
							n = inputInt("Enter the command: ", 0, 3);
						}
					}
					else
						std::cout << "Record not found \n";
				}
			}
			break;
		case 4://ADD
			try {
				cont.add(inputBook());
			}
			catch (const char*) {
				break;
			}
			break;
		case 5://SUBSET
			printMenuFindParam();
			n = inputInt("Enter the command: ", 0, 4);
			switch (n) {
			case 0:
				break;
			case 1://Library card
				subcont = cont.findSubSetByLibraryCard(inputInt("Enter library card: "));
				break;
			case 2://Author
				std::cout << "Enter author: ";
				std::cin >> str;
				subcont = cont.findSubSetByAuthor(str);
				break;
			case 3://Publishing house
				std::cout << "Enter publishing house: ";
				std::cin >> str;
				subcont = cont.findSubSetByPublishingHouse(str);
				break;
			case 4://Return date
				subcont = cont.findSubSetByReturnDate(inputDate("Enter return date: "));
				break;
			}
			if (n != 0) {
				if (subcont.size() == 0) {
					std::cout << "Subset is emty!" << std::endl;
					break;
				}
				else {
					std::cout << std::endl << subcont.size() << " record(s) found!" << std::endl;
				}
				printMenuConsoleFile();
				n = inputInt("Enter the command: ", 0, 2);
				switch (n) {
				case 1:
					consoleOutput(subcont);
					break;
				case 2:
					FName = output_file_name();
					subcont.fileOutput(std::fstream(FName, std::ios::out));
					break;
				case 0:
					break;
				}
			}
			break;
		case 0://EXIT
			return 0;
		}
	}
}