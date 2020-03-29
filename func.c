#include "kurs.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>


void other_playlist(FILE*** f)
{
    char name_playlist[30];
    char txt[8] = ".txt";
    printf("Write the name of your playlist.\nIf the playlist already exists, write its name\n");
    scanf("%s", name_playlist);
    //if (name_playlist == NULL) 
    //    strcpy(name_playlist, "other");
    strcat(name_playlist, txt);
    char words[512];
    char y_n[2];
    printf("Enter the words for your playlist.\nWhen done, write the "
           "\"end\".\nIf you want to clear the entire playlist, write "
           "\"delall\"\n");
    **f = fopen(name_playlist, "a");
    while (1) {
        printf("Write word: ");
        scanf("%s", words);
            if (strcmp("end", words) == 0) {
            fclose(**f);
            **f = fopen(name_playlist, "r");
            break;
        }
        if (strcmp("delall", words) == 0) {
            fclose(**f);
            **f = fopen(name_playlist, "w");
            fclose(**f);
            **f = fopen(name_playlist, "a");
            continue;
        }
        while (1) {
            printf("If you want to add this word Y, write, if not, then N: "
                   "%s\n",
                   words);
            scanf("%s", y_n);
            if ((strcmp(y_n, "Y") == 0) || (strcmp(y_n, "y") == 0)) {
                fputs(words, **f);
                fputs("\n", **f);
                break;
            } else if ((strcmp(y_n, "N") == 0) || (strcmp(y_n, "n") == 0)) {
                break;
            } else {
                printf("Don't understand what that means \"%s\"\n", y_n);
            }
        }
    }
}

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

void begin(char lang[], setting_lang* l)
{ //Функция проверки начала программы
    printf("%s", l->hello);

    getchar();
    int tik = 0;
    printf("%s", l->getready);
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

void print(
        int correct, int uncorrect, double time, setting_lang* l, char lang[])
{ //Функция вывода статистики
    char sett[10];
    if (strcmp(lang, "rus") == 0) {
        printf("Верных слов: %d\nНеверных слов: %d\nВремя: %f\n",
               correct,
               uncorrect,
               time);
    } else if (strcmp(lang, "eng") == 0) {
        printf("Correct words: %d\nUncorrect words: %d\nTime: %f\n",
               correct,
               uncorrect,
               time);
    }
    while (1) {
        printf("%s", l->settings);
        scanf("%s", sett);
        if ((strcmp(sett, "settings") == 0)
            || (strcmp(sett, "настройки") == 0)) {
            main();
            break;
        } else if (
                (strcmp(sett, "close") == 0)
                || (strcmp(sett, "закрыть") == 0)) {
            exit(0);
        } else {
            if (strcmp(lang, "eng") == 0)
                printf("Don't understand what that means \"%s\"\n", sett);
            else
                printf("Не понимаю, что это значит \"%s\"\n", sett);
        }
    }

    // exit(0);
}

void language(char lang[], setting_lang* l)
{
    if (strcmp(lang, "rus") == 0) {
        l->hello = (char*)malloc(
                sizeof("Клавиатурный ниндзя.\nНажмите 'ENTER' для начала "
                       "игры.\nЧтобы закончить напишите \"конец\".\n"));
        l->hello
                = "Клавиатурный ниндзя.\nНажмите 'ENTER' для начала "
                  "игры.\nЧтобы закончить напишите \"конец\".\n";
        l->getready = (char*)malloc(sizeof("Приготовьтесь...\n"));
        l->getready = "Приготовьтесь...\n";
        l->correct = (char*)malloc(sizeof("Слово верно\n"));
        l->correct = "Слово верно\n";
        l->uncorrect = (char*)malloc(sizeof("Слово неверно\n"));
        l->uncorrect = "Слово неверно\n";
        l->write = (char*)malloc(sizeof("Введите это слово: "));
        l->write = "Введите это слово: ";
        l->settings = (char*)malloc(sizeof(
                "Напишите \"закрыть\" если вы хотите выйти из игры.\nНапишите "
                "\"настройки\" если вы хотите перейти в настроки\n"));
        l->settings
                = "Напишите \"закрыть\" если вы хотите выйти из "
                  "игры.\nНапишите \"настройки\" если вы хотите перейти в "
                  "настройки\n";
    } else if ((strcmp(lang, "eng") == 0) || (strcmp(lang, "other") == 0)) {
        l->hello = (char*)malloc(
                sizeof("Keyboard Ninja.\nPress 'ENTER' for start game.\nWrite "
                       "\"end\" to finish\n"));
        l->hello
                = "Keyboard Ninja.\nPress 'ENTER' for start game.\nWrite "
                  "\"end\" to finish\n";
        l->getready = (char*)malloc(sizeof("Get ready...\n"));
        l->getready = "Get ready...\n";
        l->correct = (char*)malloc(sizeof("word is correct\n"));
        l->correct = "word is correct\n";
        l->uncorrect = (char*)malloc(sizeof("word is uncorrect\n"));
        l->uncorrect = "word is uncorrect\n";
        l->write = (char*)malloc(sizeof("Write this word: "));
        l->write = "Write this word: ";
        l->settings = (char*)malloc(
                sizeof("Write \"close\" if you want to exit the program. Write "
                       "\"settings\" if you want to go to settings\n"));
        l->settings
                = "Write \"close\" if you want to exit the program. Write "
                  "\"settings\" if you want to go to settings\n";
    }
}

int set_lang(char lang[], FILE** f)
{
    if (strcmp(lang, "rus") == 0) {
        *f = fopen("rus.txt", "r");
    } else if (strcmp(lang, "eng") == 0) {
        *f = fopen("eng.txt", "r");
    } else if (strcmp(lang, "new") == 0) {
        strcpy(lang, "eng");
        // return 2;
        //*f = fopen("other.txt", "a");
        other_playlist(&f);
    } else {
        printf("Don't understand what that means \"%s\"\n", lang);
    }
    return 0;
}

void check_word(int maxlen, int amount, FILE* f, setting_lang* l, char lang[])
{
    char* source = (char*)malloc(maxlen * 2 * sizeof(char));
    char* word = (char*)malloc(maxlen * 2 * sizeof(char));
    int uncorrect = 0, r;
    int correct = 0;
    double time_start, time_end = 0;
    while (1) { // Пока не конец файла
        time_start = wtime();
        r = getrand(0, amount); //<-
        fseek(f, 0, SEEK_SET);  //<-
        int ii = 0;             // <-
        while (ii != r)         // <-
        { // <-   Функция выбора рандомного слова из списка
            if (fscanf(f, "%s", source) != EOF) // <-
            {                                   // <-
                ii++;                           //  <-
            }                                   //   <-
        }
        printf("\"%s\"\n",
               source); //Выводит слово, которое пользователь должен
                        //напечатать
        printf("%s", l->write);
        scanf("%s", word); //Слово, напечатанное пользователем
                           //Проверка напечатанного пользователем
                           //слова(написано верно или с ошибкой(ми))
        if (strcmp(source, word) == 0) {
            system("clear");
            printf("%s", l->correct);
            correct++; // Счётчик правильно введённых слов
        } else {
            if ((strcmp(word, "end") == 0)
                || (strcmp(word, "конец")
                    == 0)) { // Если пользователь написал end
                system("clear");
                print(correct,
                      uncorrect,
                      time_end,
                      l,
                      lang); // Выводим статистику
            } else { // Если это не end, то это просто неправильно введённое
                     // слово
                system("clear");
                printf("%s", l->uncorrect);
                uncorrect++; // Счётчик неправильно введённых слов
            }
        }
        time_end = time_end + wtime() - time_start;
    }
    free(source);
    free(word);
}

