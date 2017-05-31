#pragma once
#include <string>

class Date {
private:
	int day;
	int month;
	int year;

protected:
	static int Days(int month, int year);\
		
public:
	Date(int _day, int _month, int _year);

	Date();

	Date(const Date& other);

	~Date();

	bool TryStrToDate(std::string date);

	static bool TryStrToDate(std::string str, Date &date);

	Date& operator=(const Date &date);

	bool operator==(const Date& other) const;

	bool operator<(const Date& other);

	std::string ToString() const;

	std::ostream& operator<<(std::ostream& cout);

	std::istream& operator >> (std::istream& cin);
};