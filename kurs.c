#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

double wtime() { // Таймер
  struct timeval t;
  gettimeofday(&t, NULL);
  return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max) // Рандом
{
  srand(time(NULL));
  return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int begin(char run[4]) { //Функция проверки начала программы
  while (strcmp(run, "run") != 0) {
    printf("Keyboard Ninja. Напишите \"run\" для начала игры.\nЧтобы закончить "
           "напишите \"end\"\n");
    scanf("%s", run);
  }
  return 0;
}

void print(int correct, int uncorrect,
           double time) { //Функция вывода статистики
  printf("Correct words: %d\nUncorrect words: %d\nTime: %f\n", correct,
         uncorrect, time);
  exit(0);
}

int main() {
  typedef struct {
    char name[20];
  } type;
  char run[4]; // Переменная для проверки начала работы программы
  type worrd[10];
  char i = 0, source[30];
  char word[20];
  char end[10] = "end"; // Для проверки конца программы
  int uncorrect = 0, r;
  int correct = 0;
  double time_1, time_2;
  FILE *f = fopen("input.txt", "r");
  if (begin(run) ==
      0) { // Если пользователь написал run, перейдёт к циклу while(ниже)
    time_1 = wtime();
    while (fscanf(f, "%s", worrd[i].name) != EOF) { // Пока не конец файла
      r = getrand(1, 60);                           //<-
      fseek(f, 0, SEEK_SET);                        //<-
      int ii = 0;                                   // <-
      while (ii != r)                               // <-
      { // <-   Функция выбора рандомного слова из списка
        if (fgets(source, 30, f) != NULL) // <-
        {                                 // <-
          ii++;                           //  <-
        }                                 //   <-
      }
      printf("\"%s\"\n",
             worrd[i]
                 .name); //Выводит слово, которое пользователь должен напечатать
      printf("Write this word ");
      scanf("%s", word); //Слово, напечатанное пользователем
      if (strcmp(worrd[i].name, word) ==
          0) { //Проверка напечатанного пользователем слова(написано верно или с
               //ошибкой(ми)
        printf("Слово верно\n");
        correct++; // Счётчик правильно введённых слов
      } else {
        if (strcmp(word, end) == 0) { // Если пользователь написал end
          time_2 = wtime();
          time_2 = time_2 - time_1;
          print(correct, uncorrect, time_2); // Выводим статистику
        } else { // Если это не end, то это просто неправильно введённое слово
          printf("Слово неверно\n");
          uncorrect++; // Счётчик неправильно введённых слов
        }
      }
      i++; // Возможно рудимент.
    }
    // print(correct, uncorrect); // Возможно рудимент
  }
  return 0;
}
