#ifndef KURS_H
#define KURS_H
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    char* hello;
    char* getready;
    char* correct;
    char* uncorrect;
    char* write;
    char* settings;
} setting_lang;

typedef struct {
	char pl[40];
} Playlist;

int main();
void other_playlist(FILE*** f);
void max_len_amount_lines(int* amount, int* maxlen, FILE* f);
double wtime();
int getrand(int min, int max);
void begin(char lang[], setting_lang* l);
void print(int correct, int uncorrect, double time, setting_lang* l, char lang[]);
void language(char lang[], setting_lang* l);
int set_lang(char lang[], FILE** f);
void check_word(int maxlen, int amount, FILE* f, setting_lang* l, char lang[]);

#endif
