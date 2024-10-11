#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"
#define SECINHOUR 3600
#define MININHOUR 60
#define HOURINDAY 24
#define STARTYEAR 1970
#define JANUARY 1
#define FEBRUARY 2
#define MONTHINYEAR 12
#define DAYSINNORMALYEAR 365
#define DAYSINBISECTYEAR 366
#define BISECTNONDIV 100
#define BISECTDIV 400
#define BISECTFEB 29
#define ENDDAY 31
#define PSTDIF 8
#define LUNICU30 30
#define NONBISECTFEB 28
// TODO(ilinca.tololoi): Task 1
TTime convertUnixTimestampToTime(unsigned int timestamp) {
    TTime result;
    result.hour = (timestamp / SECINHOUR) % HOURINDAY;
    result.min = (timestamp / MININHOUR) % MININHOUR;
    result.sec = timestamp % MININHOUR;
    return result;
}
int zilele_lunii(unsigned int month, unsigned int year) {
    const int vectluni[] = {0, ENDDAY, NONBISECTFEB, ENDDAY, LUNICU30, ENDDAY, LUNICU30, ENDDAY, ENDDAY,
LUNICU30, ENDDAY, LUNICU30, ENDDAY};

    if (month == FEBRUARY && ((year % 4 == 0 && year % BISECTNONDIV != 0) || (year % BISECTDIV == 0))) {
        return BISECTFEB;
    } else {
        return vectluni[month];
    }
}
// TODO(ilinca.tololoi): Task 2
TDate convertUnixTimestampToDateWithoutLeapYears(unsigned int timestamp) {
    TDate result;
    const unsigned int secondsinaday = SECINHOUR * HOURINDAY;
    const unsigned int secondsinnebisectyear = DAYSINNORMALYEAR * secondsinaday;
    result.year = STARTYEAR;
    while (timestamp >= secondsinnebisectyear) {
        timestamp -= secondsinnebisectyear;
        result.year++;
    }
    result.month = JANUARY;
    while (timestamp >= zilele_lunii(result.month, 3) * secondsinaday) {
        timestamp -= zilele_lunii(result.month, 3) * secondsinaday;
        result.month++;
        if (result.month > MONTHINYEAR) {
            result.month = JANUARY;
            result.year++;
        }
    }
    result.day = timestamp / secondsinaday + 1;
    return result;
}
// TODO(ilinca.tololoi): Task 3
TDate convertUnixTimestampToDate(unsigned int timestamp) {
    TDate result;
    const unsigned int secondsinaday = SECINHOUR * HOURINDAY;
    const unsigned int secondsinayear = secondsinaday * DAYSINNORMALYEAR;

    result.year = STARTYEAR;
    while (timestamp >= secondsinayear) {
        if ((result.year % 4 == 0 && result.year % BISECTNONDIV != 0) || (result.year % BISECTDIV == 0)) {
            if (timestamp >= secondsinaday * DAYSINBISECTYEAR) {
                timestamp -= secondsinaday * DAYSINBISECTYEAR;
                result.year++;
            } else {
                break;
            }
        } else {
            timestamp -= secondsinaday * DAYSINNORMALYEAR;
            result.year++;
        }
    }
    result.month = 1;
    while (timestamp >= secondsinaday * zilele_lunii(result.month, result.year)) {
        if (result.month == 2 && ((result.year % 4 == 0 && result.year % BISECTNONDIV != 0)
|| (result.year % BISECTDIV == 0))) {
            timestamp -= secondsinaday * BISECTFEB;
        } else {
            timestamp -= (int)(secondsinaday * zilele_lunii(result.month, result.year));
        }
        result.month++;
    }
    result.day = (int)(timestamp / secondsinaday) + 1;
    return result;
}
TDate convertDateBefore(TDate date) {
    if (date.day > 1) {
        date.day--;
    } else {
        if (date.month > 1) {
            date.month--;
            date.day = zilele_lunii(date.month, date.year);
        } else {
            date.year--;
            date.month = MONTHINYEAR;
            date.day = ENDDAY;
        }
    }
    return date;
}
TDate convertDateAfter(TDate date) {
    int daysInCurrentMonth = zilele_lunii(date.month, date.year);

    if (date.day < daysInCurrentMonth) {
        date.day++;
    } else {
        if (date.month < MONTHINYEAR) {
            date.month++;
            date.day = 1;
        } else {
            date.year++;
            date.month = 1;
            date.day = 1;
        }
    }
    return date;
}
// TODO(ilinca.tololoi): Task 4
TDateTimeTZ convertUnixTimestampToDateTimeTZ(unsigned int timestamp, TTimezone *timezones, int timezone_index) {
    TDateTimeTZ result;
    timestamp += timezones[timezone_index].utc_hour_difference * SECINHOUR;
    TDate utcDate = convertUnixTimestampToDate(timestamp);
    TTime utcTime = convertUnixTimestampToTime(timestamp);
    result.date = utcDate;
    result.time = utcTime;
    result.tz = &timezones[timezone_index];

    return result;
}
// Vectorul de timezone-uri
TTimezone timezones[] = {
    {"UTC", 0},
    {"EET", 2},
    {"PST", -PSTDIF}
};
// TODO(ilinca.tololoi): Task 5
unsigned int convertDateTimeTZToUnixTimestamp(TDateTimeTZ time) {
    unsigned int timestamp = 0;
    const unsigned int secondsinaday = SECINHOUR * HOURINDAY;
    const int zilele_lunii[] = {0, ENDDAY, NONBISECTFEB, ENDDAY, LUNICU30, ENDDAY, LUNICU30, ENDDAY,
ENDDAY, LUNICU30, ENDDAY, LUNICU30, ENDDAY};
    for (int year = STARTYEAR; year < time.date.year; year++) {
        timestamp += (((year % 4 == 0 && year % BISECTNONDIV != 0) || (year % BISECTDIV == 0))
? DAYSINBISECTYEAR : DAYSINNORMALYEAR) * secondsinaday;
    }
    for (int month = 1; month < time.date.month; month++) {
        timestamp += zilele_lunii[month] * secondsinaday;
        if (month == 2 && ((time.date.year % 4 == 0 && time.date.year % BISECTNONDIV != 0)
|| (time.date.year % BISECTDIV == 0))) {
            timestamp+=secondsinaday;
        }
    }
    timestamp += (time.date.day - 1)*secondsinaday;
    timestamp = timestamp + time.time.hour * SECINHOUR;
    timestamp = timestamp + time.time.min * MININHOUR;
    timestamp = timestamp + time.time.sec;
    timestamp -= time.tz->utc_hour_difference * SECINHOUR;
    return timestamp;
}
// TODO(ilinca.tololoi): Task 6
void printDateTimeTZ(TDateTimeTZ time) {
    const char *nume_luni[] = {"ianuarie", "februarie", "martie", "aprilie", "mai", "iunie",
                                "iulie", "august", "septembrie", "octombrie", "noiembrie", "decembrie"};
    printf("%02d %s %d, ", time.date.day, nume_luni[time.date.month - 1], time.date.year);
    printf("%02d:%02d:%02d ", time.time.hour, time.time.min, time.time.sec);
    printf("%s (UTC", time.tz->name);
    if (time.tz->utc_hour_difference >= 0) {
        printf("+%d)\n", time.tz->utc_hour_difference);
    } else {
        printf("%d)\n", time.tz->utc_hour_difference);
    }
}
