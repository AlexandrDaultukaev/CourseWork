#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

void max_len_amount_lines(int* amount, int* maxlen, FILE* f)
{
	char ch;
	int counter_lines = 1;
	int max = -1;
	int i = 0;
	while (1)
	{
		ch = fgetc(f);
		if ((ch == '\n') || (ch == EOF))
		{
			if (max < i)
				max = i;
			i = 0;
			if (ch == EOF)
				break;
			counter_lines++;
		}
		else
		i++;
	}
	*amount = counter_lines;
	*maxlen = max;
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

int begin(char run[4])
{ //Функция проверки начала программы
    while (strcmp(run, "run") != 0) {
        printf("Keyboard Ninja. Напишите \"run\" для начала игры.\nЧтобы "
               "закончить "
               "напишите \"end\"\n");
        scanf("%s", run);
    }
    int tik = 0;
    printf("Приготовьтесь...\n");
    while (tik<3) {
	printf("%d...\n",3-tik);
	sleep(1);
	tik++;
    }
    printf("RUN!\n");
    return 0;
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
	FILE* f = fopen("input.txt", "r");
    char run[4]; // Переменная для проверки начала работы программы
    int i = 0;
	int amount = 0;
	int maxlen = -1;
	max_len_amount_lines(&amount, &maxlen, f);
    char source[maxlen];
    char word[maxlen];
    int uncorrect = 0, r;
    int correct = 0;
    double time_start, time_end = 0;
	printf("amount = %d, maxlen = %d\n",amount,maxlen);
    // Если пользователь написал run, перейдёт к циклу while(ниже)
    if (begin(run) == 0) {
        while (1) {                // Пока не конец файла
			time_start = wtime();
            r = getrand(0, amount);    //<-
            fseek(f, 0, SEEK_SET); //<-
            int ii = 0;            // <-
            while (ii != r)        // <-
            { // <-   Функция выбора рандомного слова из списка
                if (fscanf(f, "%s", source) != EOF) // <-
                {                                   // <-
                    ii++;                           //  <-
                }                                   //   <-
            }
            printf("\"%s\"\n",
                   source); //Выводит слово, которое пользователь должен
                            //напечатать
            printf("Write this word ");
            scanf("%s", word); //Слово, напечатанное пользователем
                               //Проверка напечатанного пользователем
                               //слова(написано верно или с ошибкой(ми))
            if (strcmp(source, word) == 0) {
                printf("Слово верно\n");
                correct++; // Счётчик правильно введённых слов
            } else {
                if (strcmp(word, "end") == 0) { // Если пользователь написал end
                    print(correct, uncorrect, time_end); // Выводим статистику
                } else { // Если это не end, то это просто неправильно введённое
                         // слово
                    printf("Слово неверно\n");
                    uncorrect++; // Счётчик неправильно введённых слов
                }
            }
			time_end = time_end + wtime() - time_start;
            i++; // Возможно рудимент.
        }
        // print(correct, uncorrect); // Возможно рудимент
    }
    return 0;
}
