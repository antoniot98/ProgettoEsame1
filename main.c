#include <stdio.h>
#include <stdlib.h>
#include "Funzioni.h"

/*
 *Nel main vengono dichiarate le stringhe vuote e la matrice di sostituzione.
 *In un ciclo for  vengono effettuati 4*8 permutazioni delle nella matrice, generando due indici di
 *riga e di colonna  tramite la funzione rand(), e vengono scambiati reciprocamente.
 *Viene chiesto di inserire all'utente un messaggio da cifrare, il messaggio viene passato alla funzione Crittografia
 *insieme alla matrice di sostituzione per efettuarne la cifratura, e viene stampato a video il messaggio cifrato.
 *Infine il messaggio cifrato viene poi passato alla funzione Decrittografia insieme alla matrice, che lo ritrasforma
 *nel messaggio originale inserito dall'utente e lo mostra a video.
 *
 */

int main(int argc, char const *argv[]) {
    char testo_crittografato[100] = "";
    // char messaggio[100]="LET US MEET AT NOON";
    char messaggio[100] = "";
    char testo_decrittografato[100] = "";
    char mat_sostituzione[][8] = {
        {'8', 'J', 'E', 'Q', 'D', 'N', '5', 'O'},
        {'P', 'U', '3', 'A', 'R', 'F', 'L', 'W'},
        {'4', 'V', 'C', '2', 'T', 'M', 'B', 'I'},
        {'K', '7', 'Z', 'S', 'G', 'X', 'H', 'Y'}
    };
    srand(time(NULL));


    for (int i = 1; i < 4 * 8; i++) {
        char temp;
        int riga1 = rand() % 4;
        int riga2 = rand() % 4;
        int colonna1 = rand() % 8;
        int colonna2 = rand() % 8;
        temp = mat_sostituzione[riga1][colonna1];
        mat_sostituzione[riga1][colonna1] = mat_sostituzione[riga2][colonna2];
        mat_sostituzione[riga2][colonna2] = temp;
    }
    stampa_matrice(&mat_sostituzione[0][0], 4, 8);
    printf("Inserisci messaggio da crittografare:");
    gets(messaggio);

    Crittografia(messaggio, &mat_sostituzione[0][0], 4, 8, testo_crittografato);
    printf("\nIl testo crittografato e uguale a:%s\n", testo_crittografato);
    Decrittografia(testo_crittografato, &mat_sostituzione[0][0], 4, 8, testo_decrittografato);
    printf("\nIl testo decrittografato e uguale a:%s\n", testo_decrittografato);
}
