#include <iostream>

class Date {
private:
    int year{1960};
    int month{1};
    int day{1};
    int hour{0};
    int minute{0};
    int seconds{0};
    bool isOurEra{true};

    Date(int y,
         int m,
         int d,
         int h,
         int min,
         int sec,
         bool e) : year(y), month(m), day(d), hour(h), minute(min), seconds(sec), isOurEra(e) {
        if (!isOurEra) {
            year = -year + (year == 0 ? -1 : 0);
        }
    }

public:
    static bool isLeapYear(int year) {
        year = abs(year);
        if (year % 4 != 0) return false;
        if (year % 100 != 0) return true;
        if (year % 400 != 0) return false;
        return true;
    }

    static int DaysInMonth(int year, int month) {
        switch (month) {
            case 4:
            case 6:
            case 9:
            case 11:
                return 30;
            case 2:
                return (isLeapYear(year) ? 29 : 28);
            default:
                return 31;
        }
    }

    Date operator+(const Date &d_2) const {
        Date result = *this;

        // Складываем компоненты даты, обрабатываем переполнение
        result.seconds += d_2.seconds;
        if (result.seconds >= 60) {
            result.seconds -= 60;
            result.minute++;
        }

        result.minute += d_2.minute;
        if (result.minute >= 60) {
            result.minute -= 60;
            result.hour++;
        }

        result.hour += d_2.hour;
        if (result.hour >= 24) {
            result.hour -= 24;
            result.day++;
        }

        result.day += d_2.day;
        while (result.day > DaysInMonth(result.year, result.month)) {
            result.day -= DaysInMonth(result.year, result.month);
            result.month++;
            if (result.month > 12) {
                result.month = 1;
                result.year++;
                if (result.year == 0) result.year = 1; // Переход от 1 до н.э. к 1 н.э.
            }
        }

        result.month += d_2.month;
        while (result.month > 12) {
            result.month -= 12;
            result.year++;
            if (result.year == 0) result.year = 1; // Переход от 1 до н.э. к 1 н.э.
        }

        result.year += d_2.year;

        // Установка эры для итоговой даты
        result.isOurEra = result.year > 0;
        if (!result.isOurEra) {
            result.year = -result.year; // Если до н.э., то делаем год отрицательным
        }

        return result;
    }

    Date &operator+=(const Date &d_2) {
        // Складываем компоненты даты, обрабатываем переполнение
        this->seconds += d_2.seconds;
        if (this->seconds >= 60) {
            this->seconds -= 60;
            this->minute++;
        }

        this->minute += d_2.minute;
        if (this->minute >= 60) {
            this->minute -= 60;
            this->hour++;
        }

        this->hour += d_2.hour;
        if (this->hour >= 24) {
            this->hour -= 24;
            this->day++;
        }

        this->day += d_2.day;
        while (this->day > DaysInMonth(this->year, this->month)) {
            this->day -= DaysInMonth(this->year, this->month);
            this->month++;
            if (this->month > 12) {
                this->month = 1;
                this->year++;
                if (this->year == 0) this->year = 1; // Переход от 1 до н.э. к 1 н.э.
            }
        }

        this->month += d_2.month;
        while (this->month > 12) {
            this->month -= 12;
            this->year++;
            if (this->year == 0) this->year = 1; // Переход от 1 до н.э. к 1 н.э.
        }

        this->year += d_2.year;

        // Установка эры для итоговой даты
        this->isOurEra = this->year > 0;
        if (!this->isOurEra) {
            this->year = -this->year; // Если до н.э., то делаем год отрицательным
        }

        return *this;
    }

    Date operator-(const Date &d_2) const {
        Date result = *this;

        // Складываем компоненты даты, обрабатываем переполнение
        result.seconds -= d_2.seconds;
        if (result.seconds < 0) {
            result.seconds += 60;
            result.minute--;
        }

        result.minute -= d_2.minute;
        if (result.minute < 60) {
            result.minute += 60;
            result.hour--;
        }

        result.hour -= d_2.hour;
        if (result.hour < 0) {
            result.hour += 24;
            result.day--;
        }

        result.day -= d_2.day;
        while (result.day <= 0) {
            // Если количество дней отрицательное, мы должны "занять" дни из предыдущего месяца.
            if (--result.month <= 0) {
                // Если месяц становится отрицательным или равным нулю, это означает, что
                // мы перешли к предыдущему году, так как месяцы идут от 1 до 12.
                result.month += 12; // Это переводит нас в декабрь предыдущего года.
                result.year--;       // Уменьшаем год на единицу.

                // Особый случай перехода от 1 года н.э. к 1 году до н.э.
                if (result.year == 0) result.year = 1;
            }

            // Добавляем количество дней предыдущего месяца к текущему количеству дней.
            result.day += DaysInMonth(result.year, result.month);
        }


        result.month -= d_2.month;
        while (result.month > 12) {
            result.month -= 12;
            result.year--;
            if (result.year == 0) result.year = 1; // Переход от 1 до н.э. к 1 н.э.
        }

        result.year -= d_2.year;

        // Установка эры для итоговой даты
        result.isOurEra = result.year > 0;
        if (!result.isOurEra) {
            result.year = -result.year; // Если до н.э., то делаем год отрицательным
        }

        return result;
    }

    Date operator-=(const Date &d_2) {

        // Складываем компоненты даты, обрабатываем переполнение
        this->seconds -= d_2.seconds;
        if (this->seconds < 0) {
            this->seconds += 60;
            this->minute--;
        }

        this->minute -= d_2.minute;
        if (this->minute < 60) {
            this->minute += 60;
            this->hour--;
        }

        this->hour -= d_2.hour;
        if (this->hour < 0) {
            this->hour += 24;
            this->day--;
        }

        this->day -= d_2.day;
        while (this->day <= 0) {
            // Если количество дней отрицательное, мы должны "занять" дни из предыдущего месяца.
            if (--this->month <= 0) {
                // Если месяц становится отрицательным или равным нулю, это означает, что
                // мы перешли к предыдущему году, так как месяцы идут от 1 до 12.
                this->month += 12; // Это переводит нас в декабрь предыдущего года.
                this->year--;       // Уменьшаем год на единицу.

                // Особый случай перехода от 1 года н.э. к 1 году до н.э.
                if (this->year == 0) this->year = 1;
            }

            // Добавляем количество дней предыдущего месяца к текущему количеству дней.
            this->day += DaysInMonth(this->year, this->month);
        }


        this->month -= d_2.month;
        while (this->month > 12) {
            this->month -= 12;
            this->year--;
            if (this->year == 0) this->year = 1; // Переход от 1 до н.э. к 1 н.э.
        }

        this->year -= d_2.year;

        // Установка эры для итоговой даты
        this->isOurEra = this->year > 0;
        if (!this->isOurEra) {
            this->year = -this->year; // Если до н.э., то делаем год отрицательным
        }

        return *this;
    }

    Date &operator=(const Date &d_2) {
        this->year = d_2.year;
        this->month = d_2.month;
        this->day = d_2.day;
        hour = d_2.hour;
        this->minute = d_2.minute;
        this->seconds = d_2.seconds;
        this->isOurEra = d_2.isOurEra;

        return *this;
    }

    bool operator<(const Date &d_2) const {
        if (this->year != d_2.year) {
            return this->year < d_2.year;
        }
        if (this->month != d_2.month) {
            return this->month < d_2.month;
        }
        if (this->day != d_2.day) {
            return this->day < d_2.day;
        }
        if (this->hour != d_2.hour) {
            return this->hour < d_2.hour;
        }
        if (this->minute != d_2.minute) {
            return this->minute < d_2.minute;
        }
        return this->seconds < d_2.seconds;
    }

    bool operator>(const Date &d_2) const {
        if (this->year != d_2.year) {
            return this->year > d_2.year;
        }
        if (this->month != d_2.month) {
            return this->month > d_2.month;
        }
        if (this->day != d_2.day) {
            return this->day > d_2.day;
        }
        if (this->hour != d_2.hour) {
            return this->hour > d_2.hour;
        }
        if (this->minute != d_2.minute) {
            return this->minute > d_2.minute;
        }
        return this->seconds > d_2.seconds;
    }

    bool operator==(const Date &d_2) const {
        return this->year == d_2.year &&
               this->month == d_2.month &&
               this->day == d_2.day &&
               this->hour == d_2.hour &&
               this->minute == d_2.minute &&
               this->seconds == d_2.seconds &&
               this->isOurEra == d_2.isOurEra;
    }

    friend std::ostream &operator<<(std::ostream &out, const Date &date) {
        out << "Year: " << date.year << " Month: " << date.month << " Day: " << date.day
            << " Hour: " << date.hour << " Min: " << date.minute << " Sec: " << date.seconds << " "
            << (date.isOurEra ? " Our era" : " Before our era");
        return out;
    }

    Date add(unsigned y, unsigned short m, unsigned short d,
             unsigned short h, unsigned short min, unsigned short s, bool era) {
        Date sum = *this + Date(y, m, d, h, min, s, era);
        return sum;
    }

    Date subtract(unsigned y, unsigned short m, unsigned short d,
                  unsigned short h, unsigned short min, unsigned short s, bool era) {
        Date diff = *this - Date(y, m, d, h, min, s, era);
        return diff;
    }
};