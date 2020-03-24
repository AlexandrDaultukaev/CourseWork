#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

typedef struct setting_lang {
    char* hello;
    char* getready;
    char* correct;
    char* uncorrect;
    char* write;
} setting_lang;

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

void print(int correct, int uncorrect, double time)
{ //Функция вывода статистики
    printf("Correct words: %d\nUncorrect words: %d\nTime: %f\n",
           correct,
           uncorrect,
           time);
    exit(0);
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
    } else if (strcmp(lang, "eng") == 0) {
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
    }
}

void set_lang(char lang[], FILE** f)
{
    	if (strcmp(lang, "rus") == 0) {
        	*f = fopen("rus.txt", "r");
    	} else if (strcmp(lang, "eng") == 0) {
        	*f = fopen("eng.txt", "r");
    	} else {
    		printf("Don't understand what that means \"%s\"\n", lang);
    	}
}

void check_word(int maxlen, int amount, FILE* f, setting_lang* l)
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
                print(correct, uncorrect, time_end); // Выводим статистику
            } else { // Если это не end, то это просто неправильно введённое
                     // слово
                system("clear");
                printf("%s", l->uncorrect);
                uncorrect++; // Счётчик неправильно введённых слов
            }
        }
        time_end = time_end + wtime() - time_start;
    }
}

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
    return 0;
}
