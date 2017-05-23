#include "Date.h"
#include <vector>
#include <iostream>

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

int Date::Days(int month, int year) {
	return 28 + ((month + (int)std::floor(month / 8)) % 2) + 2 % month + (int)std::floor((1 + (1 - (year % 4 + 2) % (year % 4 + 1)) *
		((year % 100 + 2) % (year % 100 + 1)) + (1 - (year % 400 + 2) % (year % 400 + 1))) / month) + (int)std::floor(1 / month) -
		(int)std::floor(((1 - (year % 4 + 2) % (year % 4 + 1)) * ((year % 100 + 2) % (year % 100 + 1)) +
		(1 - (year % 400 + 2) % (year % 400 + 1))) / month);
}

Date::Date(int _day, int _month, int _year) {
	day = _day;
	month = _month;
	year = _year;
}

Date::Date() {
	day = 1;
	month = 1;
	year = 1900;
}

Date::Date(const Date &other) {
	day = other.day;
	month = other.month;
	year = other.year;
}

Date::~Date() {}

bool Date::TryStrToDate(std::string date) {
	std::vector<std::string> tokens = split(date, '/');
	if (tokens.size() != 3) return false;
	int _day = 0, _month = 0, _year = 0;
	try {
		_month = std::stoi(tokens[1]);
		if (_month < 1 || _month > 12) return false;
		_year = std::stoi(tokens[2]);
		if (_year < 1900 || _year > 2017) return false;
		_day = std::stoi(tokens[0]);
		if (_day < 1 || _day > Days(_month, _year)) return false;
	}
	catch (...) {
		return false;
	}
	day = _day;
	month = _month;
	year = _year;

	return true;
}

bool Date::TryStrToDate(std::string str, Date &date) {
	return date.TryStrToDate(str);
}

Date& Date::operator=(const Date &date) {
	year = date.year;
	month = date.month;
	day = date.day;
	return *this;
}

bool Date::operator==(const Date& other)
{
	return day == other.day &&
		month == other.month &&
		year == other.year;
}

bool Date::operator<(const Date& other) {
	if (year < other.year) return true;
	if (year == other.year) {
		if (month < other.month) return true;
		if (month == other.month) return day < other.day;
	}
	return false;
}

std::string Date::ToString() const {
	return std::to_string(day) + '/' + std::to_string(month) + '/' + std::to_string(year);
}

std::ostream& Date::operator<<(std::ostream& cout) {
	cout << ToString();
	return cout;
}

std::istream& Date::operator >> (std::istream& cin) {
	std::string buf;
	bool ok = false;
	while (!ok)
	{
		cin >> buf;
		ok = TryStrToDate(buf, *this);
		if (!ok)
			std::cout << "Wrong date!!!!";
	}
	return cin;
}