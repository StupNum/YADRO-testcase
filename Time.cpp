#include "Time.h"
#include "common.h"
#include <iostream>

Time::Time() : hours(0), minutes(0) {}

Time::Time(int minutes) : hours(minutes / 60), minutes(minutes % 60) {}
Time::Time(int h, int m) : hours(h), minutes(m) {}

Time::Time(const std::string& string) {
    if (string.size() == 5 && isNumber(string.substr(0, 2))
        && isNumber(string.substr(3, 2))) {
        hours = std::stoi(string.substr(0, 2));
        minutes = std::stoi(string.substr(3, 2));
    }
    else {
        hours = minutes = -1; // невалидное время
    }
}
int Time::Time2Minutes() const {
    return minutes + hours * 60;
}
int Time::GetRoundedHours() const{
    return hours + (int)(minutes > 0);
}
bool Time::isValid() const {
    return (hours >= 0 && hours < 24) && (minutes >= 0 && minutes < 60);
}

bool Time::operator> (const Time& other) const {
    return (hours > other.hours) || (hours == other.hours && minutes > other.minutes);
}
bool Time::operator== (const Time& other) const {
    return (hours == other.hours && minutes == other.minutes);
}
bool Time::operator>= (const Time& other) const {
    return *this > other || *this == other;
}

Time Time::operator+(const Time& other) const {
    return Time(this->Time2Minutes() + other.Time2Minutes());
}

Time Time::operator-(const Time& other) const {
    return Time(this->Time2Minutes() - other.Time2Minutes());
}

std::ostream& operator<<(std::ostream& os, const Time& time) {
    if (time.isValid()) {
        os << (time.hours < 10 ? "0" : "") << time.hours << ":"
            << (time.minutes < 10 ? "0" : "") << time.minutes;
    }
    else {
        os << "Invalid Time";
    }
    return os;
}

