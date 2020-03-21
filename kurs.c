#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

void max_len_amount_lines(int* amount, int* maxlen, FILE* f)
{
    char ch;
    int i = 0;
    while (1) {
        ch = fgetc(f);
        if ((ch == '\n') || (ch == EOF)) {
            if (*maxlen < i)
                *maxlen = i;
            i = 0;
            if (ch == EOF)
                break;
            ++*amount;
        } else
            i++;
    }
    fseek(f, 0, SEEK_SET);
}

double wtime()
{ // Таймер
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max) // Рандом
{
    srand(time(NULL));
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void begin(char lang[])
{ //Функция проверки начала программы
    if (strcmp(lang, "rus") == 0) {
        printf("Клавиатурный ниндзя.\nНажмите 'ENTER' для начала "
               "игры.\nЧтобы закончить напишите \"конец\".\n");
    } else if (strcmp(lang, "eng") == 0) {
        printf("Keyboard Ninja.\nPress 'ENTER' for start "
               "game.\nWrite \"end\" to finish\n");
    }
    getchar();
    int tik = 0;
    if (strcmp(lang, "rus") == 0)
        printf("Приготовьтесь...\n");
    else if (strcmp(lang, "eng") == 0)
        printf("Get ready...\n");
    while (1) {
        if (tik < 3) {
            printf("%d...\n", 3 - tik);
        } else {
            printf("RUN!\n");
            break;
        }
        sleep(1);
        tik++;
    }
    sleep(1);
    system("clear");
}

void print(int correct, int uncorrect, double time)
{ //Функция вывода статистики
    printf("Correct words: %d\nUncorrect words: %d\nTime: %f\n",
           correct,
           uncorrect,
           time);
    exit(0);
}

int main()
{
    setlocale(LC_CTYPE, "Russian");
    char lang_word[4];
    char engl[] = "input.txt";
    char rusk[] = "inputrus.txt";
    printf("Choose language words eng/rus\n");
    scanf("%s", lang_word);
	FILE *fe = fopen(engl, "r");
	FILE *fr = fopen(rusk, "r");
    system("clear");
    int i = 0;
    char lang[4];
    int amount = 0, amount_1 = 0;
    int maxlen = -1, maxlen_1 = -1;
    max_len_amount_lines(&amount, &maxlen, fr);
    max_len_amount_lines(&amount_1, &maxlen_1, fe);
    char source[maxlen * 2];
    char word[maxlen * 2];
    int uncorrect = 0, r;
    int correct = 0;
    double time_start, time_end = 0;
    printf("Отладка : amount = %d, maxlen = %d\n", amount, maxlen);
    printf("Choose language\neng\nrus\n");
    scanf("%s", lang);
    system("clear");
    getchar();
    // Если пользователь написал run, перейдёт к циклу while(ниже)
    begin(lang);
    while (1) { // Пока не конец файла
        time_start = wtime();
        //r = getrand(0, amount); //<-
	if (strcmp(lang_word, "rus") == 0) {
	    r = getrand(0, amount);
    	    fseek(fr, 0, SEEK_SET);
	    int ii = 0;
	    while (ii != r) 
	    {
		if (fscanf(fr, "%s", source) != EOF)
		{
		    ii++;
		}
	    }
	} else {
	    r = getrand(0, amount_1);
	    fseek(fe, 0, SEEK_SET);
	
        int ii = 0;             // <-
        while (ii != r)         // <-
        { // <-   Функция выбора рандомного слова из списка
            if (fscanf(fe, "%s", source) != EOF) // <-
            {                                   // <-
                ii++;                           //  <-
            }                                   //   <-
        }
	}
        printf("\"%s\"\n",
               source); //Выводит слово, которое пользователь должен
                        //напечатать
        if (strcmp(lang, "rus") == 0)
            printf("Введите это слово: ");
        else if (strcmp(lang, "eng") == 0)
            printf("Write this word: ");
        scanf("%s", word); //Слово, напечатанное пользователем
                           //Проверка напечатанного пользователем
                           //слова(написано верно или с ошибкой(ми))
        if (strcmp(source, word) == 0) {
            system("clear");
            if (strcmp(lang, "rus") == 0)
                printf("Слово верно\n");
            else if (strcmp(lang, "eng") == 0)
                printf("word is correct\n");
            correct++; // Счётчик правильно введённых слов
        } else {
            if ((strcmp(word, "end") == 0)
                || (strcmp(word, "конец")
                    == 0)) { // Если пользователь написал end
                system("clear");
                print(correct, uncorrect, time_end); // Выводим статистику
            } else { // Если это не end, то это просто неправильно введённое
                     // слово
                system("clear");
                if (strcmp(lang, "rus") == 0)
                    printf("Слово неверно\n");
                else if (strcmp(lang, "eng") == 0)
                    printf("word is uncorrect\n");
                uncorrect++; // Счётчик неправильно введённых слов
            }
        }
        time_end = time_end + wtime() - time_start;
        i++; // Возможно рудимент.
    }
    // print(correct, uncorrect); // Возможно рудимент
    return 0;
    fclose(fe);
    fclose(fr);
}
