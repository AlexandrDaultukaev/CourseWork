#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include "kurs.h"

int main()
{
    setting_lang* l = malloc(sizeof(setting_lang));
    setlocale(LC_CTYPE, "Russian");
    system("clear");
    FILE* f = NULL;
    char lang[4];
    int amount = 0;
    int maxlen = -1;
    while (f == NULL) {
    	printf("Choose language\neng\nrus\n");
    	scanf("%s", lang);
    	set_lang(lang, &f);
	}
    language(lang, l);
    max_len_amount_lines(&amount, &maxlen, f);
    system("clear");
    getchar();
    begin(lang, l);
    check_word(maxlen, amount, f, l);
    free(l->hello);
    free(l->correct);
    free(l->uncorrect);
    free(l->write);
    free(l->getready);
    free(l);
    return 0;
}
