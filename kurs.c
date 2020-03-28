#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include "kurs.h"

//typedef struct {
//		char pl[40];
//} Playlist;

int main()
{
    setting_lang* l = malloc(sizeof(setting_lang));
    setlocale(LC_CTYPE, "Russian");
    system("clear");
    FILE* f = NULL;
    char lang[4];
    char words[30];
    int amount = 0;
    int maxlen = -1;
    int g;
    while (f == NULL) {
		printf("SETTINGS\n");
    	printf("Choose language\neng\nrus\nother\n");
    	scanf("%s", lang);
    	g = set_lang(lang, &f);
    	if (g == 2) {
    		//other_playlist(&f);
    		f = fopen("other.txt", "a");
    		while (1) {
    			printf("Write word: ");
    			scanf("%s", words);
    			fputs(words, f);
    			fputs("\n", f);

    			if (strcmp("end", words) == 0) {
    				fclose(f);
    				f = fopen("other.txt", "r");
    				break;
    			}
    		}
    	}
	}

    language(lang, l);
    max_len_amount_lines(&amount, &maxlen, f);
    system("clear");
    getchar();
    begin(lang, l);
    check_word(maxlen, amount, f, l, lang);
    free(l->hello);
    free(l->correct);
    free(l->uncorrect);
    free(l->write);
    free(l->getready);
    free(l->settings);
    free(l);
    return 0;
}
