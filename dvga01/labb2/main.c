#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>

#define MAX_INPUT 80
#define NUM_SEQUENCE_LENGTH 100
#define HIGHEST_NUM_VAL 900
#define ELEMENTS_PER_ROW 10

int sum(int list[]){
    int i;
    int sum;
    for (i = 0; i < NUM_SEQUENCE_LENGTH; i++) sum += list[i];
    return sum;
}

double mean(int list[]){
    return sum(list)/NUM_SEQUENCE_LENGTH;
}

double median(int list[]){
    return list[NUM_SEQUENCE_LENGTH/2];
}

void printArr(int list[NUM_SEQUENCE_LENGTH]){
    int i;
    for (i = 0; i<NUM_SEQUENCE_LENGTH; i++){
        if(i % ELEMENTS_PER_ROW == 0) printf("\n");
        printf("%d\t", list[i]);
    }
    puts("\n");
}

int * genNumSeq(int length){
    static int numseq[] = {};
    int i;

    for (i = 0; i<length; i++)
        numseq[i] = rand()%(HIGHEST_NUM_VAL+1);
    return numseq;
}

void swap(int* ap, int* bp){
    int temp = *ap;
    *ap = *bp;
    *bp = temp;
}

int * bubSort(int list[NUM_SEQUENCE_LENGTH]){
    int i, j;
    int swapped;
    int n = NUM_SEQUENCE_LENGTH;

    for (i = 0; i<n-1; i++){
        swapped = 0;
        for (j = 0; j < n - i - 1; j++){
            if (list[j] > list[j+1]){
                swap(&list[j], &list[j+1]);
                swapped = 1;
            }
        }
        if (swapped == 0) break;
    }
    return list;
}

int binSearch(int number, int list[], int lowest, int highest){
    if (highest >= lowest) {
        int mid = (lowest+highest)/2;

        if (list[mid] == number) return mid;
        if (list[mid] > number) return binSearch(number, list, lowest, mid-1);
        if (list[mid] < number) return binSearch(number, list, mid+1, highest);
    }
    return -1;
}

int main(){
    char input[MAX_INPUT];
    int choice;
    int i;
    int numseq[NUM_SEQUENCE_LENGTH] = {};
    bool generated = false;
    bool sorted = false;
    srand(time(NULL));

    while(1){
        puts("");
        puts("1. Generate number sequence");
        puts("2. Sort number sequence");
        puts("3. Calculate mean, median, max och minvalue");
        puts("4. Search in number sequence");
        puts("0. Exit");
        fgets(input, MAX_INPUT, stdin);
        choice = atoi(input);

        switch (choice)
        {
        case 1:
            memcpy(numseq, genNumSeq(NUM_SEQUENCE_LENGTH), sizeof(numseq));
            printArr(numseq);
            generated = true;

            break;
        case 2:
            if (generated != true){
                puts("You have not generated a numbersequence yet.\nTry option 1 instead\n");
                break;
            }
            memcpy(numseq, bubSort(numseq), sizeof(numseq));
            printArr(numseq);
            sorted = true;
            break;
        case 3:
            if (generated != true){
                puts("You have not generated a numbersequence yet.\nTry option 1 instead\n");
                break;
            }
            if (sorted != true){
                puts("You have not sorted the numbersequence yet.\nTry option 2 instead\n");
                break;
            }
            /* Ber ̈akna medelv ̈arde, median, maxv ̈arde och minv ̈arde, och skriv ut detta p ̊a sk ̈armen */
            printf("Min: %d\nMax: %d\nMean: %.1f\nMedian: %.1f\n", numseq[0], numseq[NUM_SEQUENCE_LENGTH-1], mean(numseq), median(numseq));
            break;

        case 4:
            if (generated != true){
                puts("You have not generated a numbersequence yet.\nTry option 1 instead\n");
                break;
            }
            if (sorted != true){
                puts("You have not sorted the numbersequence yet.\nTry option 2 instead\n");
                break;
            }
            /* L ̈as in ett tal n fr ̊an anv ̈andaren. Programmet ska anv ̈anda bin ̈ars ̈okning f ̈or att s ̈oka genom
            talf ̈oljden efter talet n. Om talet finns ska talets plats skrivas ut (rad och kolumn), annars ska
            det meddelas att talet inte finns i talf ̈oljden */
            puts("Number to sreach for:");
            fgets(input, MAX_INPUT, stdin);
            choice = atoi(input);

            int index = binSearch(choice, numseq, 0, NUM_SEQUENCE_LENGTH-1);

            if (index == -1) puts("The number was not in the number sequence");
            else printf("The number is present with position: \nRow: %d\nColumn: %d\n", (int)index/10+1, (int)index%10+1);

            break;
        
        case 0:
            puts("Exitted program");
            return 0;
        }

    }
}
