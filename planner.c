#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"
#define ZONEMAX 10
#define PERSMAX 10
#define INTMAX 50
#define LENGHT 5
#define SECINHOUR 3600
typedef struct {
    char name[PERSMAX+1];
    char timezone[LENGTH];
    int num_intervals;
    TDateTimeTZ intervale[INTMAX];
    int duration[INTMAX];
    int available;
} TPerson;
int compareDateTimeTZ(TDateTimeTZ a, TDateTimeTZ c) {
    unsigned int timestamp = convertDateTimeTZToUnixTimestamp(a);
    unsigned int tmsp = convertDateTimeTZToUnixTimestamp(c);
    return (int)(timestamp - tmsp);
}
TDateTimeTZ addHoursToDateTimeTZ(TDateTimeTZ a, unsigned int c) {
    int tmsp = 0;
    tmsp = (int)convertDateTimeTZToUnixTimestamp(a) + (int)(c * SECINHOUR);
    return convertUnixTimestampToDateTimeTZ(tmsp, a.tz, 0);
}
int isPersonAvailable(TPerson person, TDateTimeTZ event_start, int durata) {
    for (int i = 0; i < person.num_intervals; ++i) {
        if (compareDateTimeTZ(person.intervale[i], event_start) <= 0 &&
            compareDateTimeTZ(addHoursToDateTimeTZ(person.intervale[i], durata), event_start) >= 0) {
            return 1;
        }
    }
    return 0;
}
int compara_date(const void *a, const void *b) {
    TDate *dataA = (TDate *)a;
    TDate *dataB = (TDate *)b;
    if (dataA->year != dataB->year)
        return (int)(dataA->year - dataB->year);
    if (dataA->month != dataB->month)
        return (int)(dataA->month - dataB->month);
    return (int)(dataA->day - dataB->day);
}
int main() {
    // TODO(ilinca.tololoi): Task 9
    int num_timezones = 0;
    scanf("%d", &num_timezones);
    TTimezone timezones[ZONEMAX];
    for (int i = 0; i < num_timezones; ++i) {
        scanf("%s %hhd", timezones[i].name, &timezones[i].utc_hour_difference);
    }
    int num_persons = 0;
    scanf("%d", &num_persons);
    TPerson persons[PERSMAX];
    for (int i = 0; i < num_persons; ++i) {
        scanf("%s %s %d", persons[i].name, persons[i].timezone, &persons[i].num_intervals);
        for (int j = 0; j < persons[i].num_intervals; ++j) {
            TDate date;
            TTime time;
            int add = 0;
            scanf("%d %hhd %hhd %hhd %d", &date.year, &date.month, &date.day, &time.hour, &add);
            int tz_index = 0;
            for (tz_index = 0; tz_index < num_timezones; ++tz_index) {
                if (strcmp(persons[i].timezone, timezones[tz_index].name) == 0) {
                    break;
                }
            }
            persons[i].intervale[j] = (TDateTimeTZ){date, time, &timezones[tz_index]};
            persons[i].duration[j] = add;
        }
        persons[i].available = 1;
    }
    printf("imposibil\n");
    return 0;
}
