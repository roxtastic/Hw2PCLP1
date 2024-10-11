#include <stdio.h>
#include <stdlib.h>
#include "timelib.h"
#define TASKNUM7 7
#define TASKNUM8 8
#define STARTYEAR 1970
#define DAYBITZI 5
#define MONTHBITZI 4
#define UNSIGNEDINT 32
#define DATEINBIT 15
unsigned int extrage_zi(unsigned int data) {
    return data & ((1 << DAYBITZI) - 1);
}
unsigned int extrage_luna(unsigned int data) {
    return (data >> DAYBITZI) & ((1 << MONTHBITZI) - 1);
}
unsigned int extrage_an(unsigned int data) {
    return (data >> (DAYBITZI + MONTHBITZI)) + STARTYEAR;
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

int verificarebitzi(unsigned int data) {
    int count = 0;
    while (data) {
        count += (int)(data & 1);
        data >>= 1;
    }
    return (count % 2);
}

int main() {
    // TODO(ilinca.tololoi): Task 7 & 8
    int task = 0;
    scanf("%d", &task);
    if (task == TASKNUM7) {
        int N = 0;
        scanf("%d", &N);
        TDate date[N];
        for (int i = 0; i < N; i++) {
            unsigned int bitzi = 0;
            scanf("%u", &bitzi);
            date[i].day = (int)extrage_zi(bitzi);
            date[i].month = (int)extrage_luna(bitzi);
            date[i].year = (int)extrage_an(bitzi);
        }
        qsort(date, N, sizeof(TDate), compara_date);
        const char *nume_luni[] = {"ianuarie", "februarie", "martie", "aprilie", "mai", "iunie",
                                "iulie", "august", "septembrie", "octombrie", "noiembrie", "decembrie"};
        for (int i = 0; i < N; i++) {
            printf("%d %s %d\n", date[i].day, nume_luni[date[i].month - 1], date[i].year);
        }
    } else if (task == TASKNUM8) {
    int N = 0;
    scanf("%d", &N);
    int nr_int = (int)((N * DATEINBIT)/UNSIGNEDINT);
    if (N * DATEINBIT % UNSIGNEDINT > 0) nr_int++;
    unsigned int dates[nr_int];
    for (int i = 0; i < nr_int; ++i) {
        scanf("%u", &dates[i]);
    }
    int nr_int_ctrl = (nr_int / UNSIGNEDINT);
    if (nr_int % UNSIGNEDINT > 0)
        nr_int_ctrl++;
    unsigned int bitzicontrol[nr_int_ctrl];
    for (int i = 0; i < nr_int_ctrl; ++i) {
        scanf("%u", &bitzicontrol[i]);
    }
    unsigned int ok[nr_int];
    for (int i = 0; i < nr_int; i++) {
        if (verificarebitzi(dates[i]) == ((bitzicontrol[i/UNSIGNEDINT] >> (i % UNSIGNEDINT)) & 1)) {
            ok[i] = 1;
        } else {
            ok[i] = 0;
        }
        // printf("%d %d %d\n", ok[i], verificarebitzi(dates[i]), ((bitzicontrol[i/32] >> (i % 32)) & 1));
    }
    int line = 0, pozitie = 0;
    unsigned int extract = 0;
    // pentru fiecare data procesata
    TDate date[N];
    int k = 0;
    for (int i = 0; i < N; ++i) {
        int r = 0;
        unsigned int eok = 0;
        extract = 0;
        // printf(">>> %d\n", pozitie);
        if (pozitie + DATEINBIT <= UNSIGNEDINT) {
            // complet pe o singura linie
            for (int j = pozitie; j < pozitie + DATEINBIT; j++) {
                extract = extract | ( ((dates[line] >> j) & 1) << r);
                r++;
            }
            eok = ok[line];
            pozitie = pozitie + DATEINBIT;
            if (pozitie == UNSIGNEDINT) {
                line++;
                pozitie = 0;
            }
        } else {
            r = 0;
            for (int j = pozitie; j < UNSIGNEDINT; j++) {
                extract = extract | ( ((dates[line] >> j) & 1) << r);
                r++;
            }
            line++;
            // printf(">> r: %d\n", r);
            pozitie = 0;
            eok = (ok[line-1] && ok[line]);
            for (; r < DATEINBIT; r++) {  // completez noua data
                extract = extract | ( ((dates[line] >> pozitie) & 1) << r);
                pozitie++;
            }
        }
        // printf(">>>>>>> %d\n", pozitie);
    if (eok) {
            date[k].day = extrage_zi(extract);
            date[k].month = extrage_luna(extract);
            date[k].year = extrage_an(extract);
            k++;
    // printf("%d %d %d  ", line, pozitie, );
// const char *nume_luni[] = {"ianuarie", "februarie", "martie", "aprilie", "mai", "iunie",

                                // "iulie", "august", "septembrie", "octombrie", "noiembrie", "decembrie"};
// printf("%d %s %d\n", extrage_zi(extract), nume_luni[extrage_luna(extract)-1], extrage_an(extract));
}
    }
    const char *nume_luni[] = {"ianuarie", "februarie", "martie", "aprilie", "mai", "iunie",
                                "iulie", "august", "septembrie", "octombrie", "noiembrie", "decembrie"};
        qsort(date, k, sizeof(TDate), compara_date);
        for (int i = 0; i < k; i++) {
            printf("%d %s %d\n", date[i].day, nume_luni[date[i].month-1], date[i].year);
        }
    }
    return 0;
}
