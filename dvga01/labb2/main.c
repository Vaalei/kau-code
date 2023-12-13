#include<stdio.h>
#include<stdlib.h>

#define MAX_INPUT 80


int main(){
    char input[MAX_INPUT];
    int choice;
    while(1){
        puts("1. Generera talföljd");
        puts("2. Sortera talföljd");
        puts("3. Beräkna medel, median, max och minvärde");
        puts("4. Sök i talföljd");
        puts("0. Avsluta");
        fgets(input, MAX_INPUT, stdin);
        choice = atoi(input);

        switch (choice)
        {
        case 1:
            /* Generera en talf ̈oljd med en slumpgenerator och skriv ut talen p ̊a sk ̈armen. Talen som genereras
            ska vara i intervallet 0 ≤ n ≤ 900. */
            puts("1");
            break;
        case 2:
            /* Sortera talf ̈oljden med bubbelsortering. D ̈arefter ska talen skrivas ut. Du f ̊ar ej anv ̈anda inbyggda
            sorteringsfunktioner, som exempelvis qsort */
            puts("2");
            break;
        case 3:
            /* Ber ̈akna medelv ̈arde, median, maxv ̈arde och minv ̈arde, och skriv ut detta p ̊a sk ̈armen */
            puts("3");
            break;

        case 4:
            /* L ̈as in ett tal n fr ̊an anv ̈andaren. Programmet ska anv ̈anda bin ̈ars ̈okning f ̈or att s ̈oka genom
            talf ̈oljden efter talet n. Om talet finns ska talets plats skrivas ut (rad och kolumn), annars ska
            det meddelas att talet inte finns i talf ̈oljden */
            puts("4");
            break;
        
        case 0:
            puts("Exitted program");
            return 0;
        }

    }
}