#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int getrand(int min, int max)
{
	srand(time(NULL));
	return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int begin(char run[4]) {
    while (strcmp(run, "run") != 0) {
    printf("Keyboard Ninja. Напишите \"run\" для начала игры.\nЧтобы закончить напишите \"end\"\n");
    scanf("%s", run);
    }
    return 0;
} 

void print(int correct, int uncorrect) {
    printf("Correct words: %d\nUncorrect words: %d\n", correct, uncorrect);
    exit(0);
}

int main() {
    /*typedef struct {
	char name[20];
    }type;
    char run[4];
    type worrd[10];
    char i=0;
    char word[20];
    char end[10] = "end";
    int uncorrect = 0;
    int correct = 0;
  FILE *f = fopen("words.txt", "r");
    if (begin(run)==0) {
    while (fscanf(f, "%s", worrd[i].name) != EOF) {
      printf("\"%s\"\n", worrd[i].name);
	printf("Write this word " );
	scanf("%s", word);
	if (strcmp(worrd[i].name, word) == 0) {
	    printf("Слово верно\n");
	    correct++;
	} else {
	    if (strcmp(word, end) == 0) { 
		print(correct, uncorrect);
	    } else {
	    printf("Слово неверно\n");
	    uncorrect++;
	    }
	}
	i++;
	     }
	print(correct, uncorrect);
	}*/
	FILE *fp;
    char source[30], input[10];
	char sep[5] = " \n";
	char *istr;
	int i = 0,r,yes = 0,j = 0,n;
    fp = fopen("input.txt","r");
	printf("Amount words\n");
	scanf("%d",&n);
	//fgets(source, 20, fp);
   // scanf("%s", &input);
	while (j != n)
	{
		r = getrand(1,60);
		//printf("%d\n",r);
		fseek(fp,0,SEEK_SET);
		i = 0;
		while (i != r)
		{
			if (fgets(source,30,fp) != NULL)
			{
				//printf("%s\n",source);
				i++;
			}
		}
			istr = strtok(source,sep);
			printf("%s\n",istr);
			scanf("%s",input);
			if (strcmp(istr,input) == 0)
				yes++;
			if (strcmp(istr,input) != 0)
				printf("%s\n",istr);
			j++;
	}
		//istr = strtok(NULL,sep);
		//printf("s: %s\n",istr);
	printf("%d\n",yes);
	fclose(fp);
  return 0;
}
