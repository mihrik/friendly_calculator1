#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define NLEN 30
#define SEATS 12
#define MAXLEN 81

char get_first(void);
void show(void);
void get_num(int *p);
char * s_gets(char * st, int n);
typedef struct b 
{
    char fname[NLEN];
    char lname[NLEN];

} PERSON;
typedef struct a 
{
    int identity;
    bool marker;
    PERSON person;
} SEAT;
void free_seats(SEAT arr[]);
void list_of_free(SEAT arr[]);
void list_of_rented(SEAT arr[]);
void rent(SEAT (*pt)[SEATS]);
void unrent(SEAT (*pt)[SEATS]);

int main(void) 
{
    FILE *fp;
    int mark;
    if ((fp = fopen("Plane.txt", "r")) == NULL) {
        puts("The information is not available");
        exit(EXIT_FAILURE);
    }
    SEAT plane[SEATS];
    for (int i = 0; i < SEATS; i++) {
        fscanf(fp, "%d %d", &plane[i].identity, &mark);
        plane[i].marker = mark;
        if (plane[i].marker) {
            fscanf(fp, "%29s %29s", plane[i].person.fname, plane[i].person.lname);
        }
    }
    if (fclose(fp) != 0) {
        puts("File accessebiluty failure");
        exit(EXIT_FAILURE);
    }
    char option;

    show();
    while ((option = get_first()) != 'f') {
        switch(option) {
            case 'a': free_seats(plane);
                break;
            case 'b': list_of_free(plane);
                break;
            case 'c': list_of_rented(plane);
                break;
            case 'd': rent(&plane);
                break;
            case 'e': unrent(&plane);
                break;
        }
        show();
    }
    puts("Good luck!");
    if ((fp = fopen("Plane.txt", "w")) == NULL) {
        puts("The changes are not availale");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < SEATS;i++) {
        fprintf(fp, "%d %d", plane[i].identity, plane[i].marker);

        if (plane[i].marker) {
            fprintf(fp, " %s %s", plane[i].person.fname, plane[i].person.lname);
        }
        fprintf(fp, "\n");
    }
    if (fclose(fp) != 0) {
        puts("File accessebiluty failure");
        exit(EXIT_FAILURE);
    }
    return 0;
}

char get_first(void) 
{
    char arr[MAXLEN];
    while (fgets(arr, MAXLEN, stdin) == NULL || arr[0] == '\0' || (arr[0] != 'a' && arr[0] != 'b'
    && arr[0] != 'c' && arr[0] != 'd' && arr[0] != 'e' && arr[0] != 'f')) {
        puts("Invalid option. Try again");
    }
    return arr[0];
}

void show(void) 
{
    puts("To select the function enter it's alphabetic equivalent:");
    puts("a) To show the amount of the free seats");
    puts("b) To show the list of the free seats");
    puts("c) To show the list of the booked seats sorted alphabetically");
    puts("d) To book the seat for the passenger");
    puts("e) To free the seat for the passenger");
    puts("f) To quit");
}

void free_seats(SEAT arr[]) 
{
    int c = 0;
    for (int i = 0; i < SEATS; i++) {
        if (!arr[i].marker)
            c += 1;
    }
    printf("The amount of the free seats is %d.\n", c);
}

void list_of_free(SEAT arr[]) 
{
    for (int i = 0; i < SEATS; i++) {
        if (!arr[i].marker) 
            printf("Seat number %d is free!\n", arr[i].identity);
    }
}

void list_of_rented(SEAT arr[]) 
{
    int c = 0;
    int now = 0;
    SEAT *pt1, temp;
    for (int i = 0; i < SEATS; i++) {
        if (arr[i].marker)
            c += 1;
    }
    if (c == 0) {
        puts("All seats are free now");
        return;
    }
    SEAT *pt = malloc(sizeof(SEAT) * c);
    for (int i = 0; i < SEATS; i++) {
        if (arr[i].marker) {
            *(pt + now) = arr[i];
            now++;
        }
    }
    if (c > 1) {
        for (int i = 0; i < c-1; i++) {
            pt1 = pt + i;
            for (int j = i+1; j < c; j++) {
                if (strcmp(pt1->person.fname, (pt + j)->person.fname) > 0) {
                    temp = *pt1;
                    *pt1 = *(pt + j);
                    *(pt + j) = temp;
                }
                else if (strcmp(pt1->person.fname, (pt + j)->person.fname) == 0) {
                    if (strcmp(pt1->person.lname, (pt + j)->person.lname) > 0) {
                        temp = *pt1;
                    *pt1 = *(pt + j);
                    *(pt + j) = temp;
                    }
                }
            }
        }
    }
    for (int i = 0; i < c; i++) {
        printf("%s %s is booked the seat number %d\n", (pt+i)->person.fname, (pt+i)->person.lname,
            (pt + i)->identity);
    }
    free(pt);
}

void get_num(int *p)
{
    while (scanf("%d", p) != 1 || (*p < 1 || *p > SEATS)) {
        puts("Not available input");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
}

char * s_gets(char * st, int n)
{
    char * ret_val;
    char * find;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');
        if (find) 
            *find = '\0';
        else
            while (getchar() != '\n');
    }
    return ret_val;
}

void rent(SEAT (*pt)[SEATS]){
    int n;
    list_of_free(*pt);
    puts("Choose the number of the free seat");
    get_num(&n);
    int k;
    for (int i = 0; i < SEATS; i++) {
        if ((*pt)[i].identity == n){
            k = i;
            break;
        }
    }
    while ((*pt)[k].marker) {
        puts("This seat is booked");
        get_num(&n);
        for (int i = 0; i < SEATS; i++) {
        if ((*pt)[i].identity == n){
            k = i;
            break;
        }
    }
    }
    puts("Enter the first name");
    s_gets((*pt)[k].person.fname, NLEN);
    puts("Enter the last name");
    s_gets((*pt)[k].person.lname, NLEN);
    (*pt)[k].marker = true;
    puts("Succesful book");
}
void unrent(SEAT (*pt)[SEATS]){
    int n;
    char fname1[NLEN];
    char lname1[NLEN];
    puts("Choose the number of the free seat");
    get_num(&n);
    int k;
    for (int i = 0; i < SEATS; i++) {
        if ((*pt)[i].identity == n){
            k = i;
            break;
        }
    }
    puts("Enter your first name for the verification");
    s_gets(fname1, NLEN);
    puts("Enter your last name for the verification");
    s_gets(lname1, NLEN);
    if (strcmp(fname1, (*pt)[k].person.fname) == 0 && strcmp(lname1, (*pt)[k].person.lname)==0) {
        (*pt)[k]= (SEAT){n, false};
        puts("Succesful unbook");
    }
    else {
        puts("Access denied");
    }
}