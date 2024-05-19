#ifndef TIME_H
#define TIME_H

#include <string>

class Time {
public:
    Time();

    Time(int minutes);

    Time(int h, int m);

    Time(const std::string& string);

    int Time2Minutes() const;

    int GetRoundedHours() const;

    bool isValid() const;

    bool operator> (const Time& other) const;

    bool operator== (const Time& other) const;

    bool operator>= (const Time& other) const;

    Time operator+(const Time& other) const;

    Time operator-(const Time& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Time& time);

private:
    int hours = 0;
    int minutes = 0;
};


#endif // TIME_H
