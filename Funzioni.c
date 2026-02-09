#include <stdio.h>
#include <math.h>
#include <string.h>
/* La funzione riceve in input la matrice e relativo numero riga e colonne e stampa a video i suoi elementi*/
void stampa_matrice(char *mat, int n_righe, int n_col) {
    for (int i = 0; i < n_righe; i++) {
        for (int j = 0; j < n_col; j++) {
            printf("%5c", *(mat + i * n_col + j));
        }
        printf("\n");
    }
}

/*La funzione riceve in input una chiave, una matrice con il relativo numero di righe e di colonne e due puntatori di
 *variabili di numeri interi.
 * Si effettua la ricerca della chiave nella matrice e viene salvata la posizione dell'elemento trovato assegnando
 * l'inidce di riga e di colonna rispetivamente nelle variabili passate per riferimento alla funzione.
 */
void posizione_lettera(char chiave, char *mat, int n_righe, int n_col, int *riga, int *colonna) {
    int i = 0;

    for (i = 0; i < n_righe; i++) {
        for (int j = 0; j < n_col; j++) {
            if (*(mat + i * n_col + j) == chiave) {
                *riga = i;
                *colonna = j;
            }
        }
    }
}

/*La funzione riceve in input un array di caratteri ed elimina gli spazi tra le parole*/
void elimina_spazi(char *testo) {
    char testo_senza_spazi[100] = "\0";
    char *token;
    int i = 0;
    token = strtok(testo, " ");

    while (token != NULL) {
        strcat(testo_senza_spazi, token);
        token = strtok(NULL, " ");
    }

    strcpy(testo, testo_senza_spazi);
    *(testo+strlen(testo)) = '\0';
}

/* Funzione riceve in input una stringa e controlla se ci sono coppie di lettere uguali aggiungendo una X tra le due */
void controllo_lettere(char *testo) {
    char temp[100];
    int i = 0;
    int len = strlen(testo);
    elimina_spazi(testo);
    strupr(testo);


    /* finche c'è il testo controlla le coppie di lettere se sono uguali copia la parte dopo in
    una variabile temporanea, aggiugne una x e copia il contenuto della variabile temporanea nell'array principale*/
    while (i < len - 1) {
        if (*(testo + i) == *(testo + i + 1)) {
            strcpy(temp, testo + i + 1);
            *(testo + i + 1) = 'X';
            strcpy(testo + i + 2, temp);
        }
        i = i + 2;
    }
    if (strlen(testo) % 2 != 0) {
        *(testo + len) = 'X';

    }
    *(testo + strlen(testo)) = '\0';

}

/*La funziona riceve una stringa di testo ed elimina le X che sono state aggiunte tra le coppie consecutive di caratteri uguali*/
void ripristina_lettere(char *testo) {
    char temp[100];
    int i = 0;
    int len = strlen(testo);

    while (i < (len - 1)) {
        if (*(testo + i) == 'X' && *(testo + i + 1) == *(testo + i - 1)) {
            strcpy(temp, testo + i + 1);
            strcpy(testo + i, temp);
        }
        i++;
    }
    if (*(testo + len - 1) == 'X') {
        *(testo + len - 1) = '\0';
    }
    *(testo + strlen(testo)) = '\0';
}

/*
 *La funzione riceve in input una stringa contente il messaggio, la matrice di sostituzione e il relativo numero di
 *righe e colonne e una stringa vuotae.
 *Effettua la codifica del testo passato in riferimento alla posizione degli elementi della matrice:
 * Se la posizione dei due caratteri ha lo stesso indice di riga prendo il carattere della colonna successiva
 * Se la posizione dei due caratteri ha lo stesso indice di colonna allora prendo il carattere alla riga successiva
 * In questi due casi attraverso degli if annidati verifico che, nel primo caso non mi trovi nell'ultima colonna
 *  nel secondo caso che non mi trovi nell'ultima riga
 * Se il numero di riga e di colonna sono diversi allora prendo il carattere della stessa riga ma della colonna dell'altro
 */

void Crittografia(char *testo, char *mat_sostituzione, int n_righe, int n_col, char *testo_crittografato) {
    int i = 0;
    int riga1, colonna1, riga2, colonna2;
    controllo_lettere(testo);
    int len = strlen(testo);
    //Finhè l'inidice e minore della lunghezza del testo
    while (i <= len - 1) {
        //recupero la posizione delle lettere corrispondenti nella matrice di stringhe
        posizione_lettera(*(testo + i), mat_sostituzione, n_righe, n_col, &riga1, &colonna1);
        posizione_lettera(*(testo + i + 1), mat_sostituzione, n_righe, n_col, &riga2, &colonna2);

        if (riga1 == riga2) {
            if (colonna1 < n_col - 1 && colonna2 < n_col - 1) {
                *(testo_crittografato + i) = *(mat_sostituzione + riga1 * n_col + colonna1 + 1);
                *(testo_crittografato + i + 1) = *(mat_sostituzione + riga2 * n_col + colonna2 + 1);
            } else if (colonna1 == n_col - 1) {
                *(testo_crittografato + i) = *(mat_sostituzione + riga1 * n_col + 0);
                *(testo_crittografato + i + 1) = *(mat_sostituzione + riga2 * n_col + colonna2 + 1);
            } else {
                *(testo_crittografato + i + 1) = *(mat_sostituzione + riga2 * n_col + 0);
                *(testo_crittografato + i) = *(mat_sostituzione + riga1 * n_col + colonna1 + 1);
            }
            i = i + 2;
        } else if (colonna1 == colonna2) {
            if (riga1 < n_righe - 1 && riga2 < n_righe - 1) {
                *(testo_crittografato + i) = *(mat_sostituzione + (riga1 + 1) * n_col + colonna1);
                *(testo_crittografato + i + 1) = *(mat_sostituzione + (riga2 + 1) * n_col + colonna2);
            } else if (riga1 == n_righe - 1) {
                *(testo_crittografato + i) = *(mat_sostituzione + 0 * n_col + colonna1);
                *(testo_crittografato + i + 1) = *(mat_sostituzione + (riga2 + 1) * n_col + colonna2);
            } else {
                *(testo_crittografato + i) = *(mat_sostituzione + (riga1 + 1) * n_col + colonna1);
                *(testo_crittografato + i + 1) = *(mat_sostituzione + 0 * n_col + colonna2);
            }

            i = i + 2;
        } else {
            *(testo_crittografato + i) = *(mat_sostituzione + riga1 * n_col + colonna2);
            *(testo_crittografato + i + 1) = *(mat_sostituzione + riga2 * n_col + colonna1);
            i = i + 2;
        }
    }
    *(testo_crittografato + strlen(testo_crittografato))='\0';
}

/*La funzione riceve in input una stringa di testo una matrice e il numero di rihe e di colonne più una stringa vuota
 *ed effettua la decifratura del messaggio crittografato in riferimento  alla posizione delle lettere nella matrice passata
 * Se la posizione dei due caratteri ha lo stesso indice di riga prendo il carattere della colonna precedente
 * Se la posizione dei due caratteri ha lo stesso indice di colonna allora prendo il carattere alla riga precedente
 * In questi due casi attraverso degli if annidati verifico che, nel primo caso non mi trovi nella prima colonna
 *  nel secondo caso che non mi trovi nella prima riga
 * Se il numero di riga e di colonna sono diversi prendo il carattere della stessa riga ma della colonna dell'altro
 */
void Decrittografia(char *testo_crittografato, char *mat_sostituzione, int n_righe, int n_col, char *testo) {
    int i = 0;
    int riga1, colonna1, riga2, colonna2;
    int len = strlen(testo_crittografato);
    while (i <= len - 1) {
        posizione_lettera(*(testo_crittografato + i), mat_sostituzione, n_righe, n_col, &riga1, &colonna1);
        posizione_lettera(*(testo_crittografato + i + 1), mat_sostituzione, n_righe, n_col, &riga2, &colonna2);

        if (riga1 == riga2) {
            if (colonna1 > 0 && colonna2 > 0) {
                *(testo + i) = *(mat_sostituzione + riga1 * n_col + colonna1 - 1);
                *(testo + i + 1) = *(mat_sostituzione + riga2 * n_col + colonna2 - 1);
            } else if (colonna1 == 0) {
                *(testo + i) = *(mat_sostituzione + riga1 * n_col + n_col - 1);
                *(testo + i + 1) = *(mat_sostituzione + riga2 * n_col + colonna2 - 1);
            } else {
                *(testo + i + 1) = *(mat_sostituzione + riga2 * n_col + n_col - 1);
                *(testo + i) = *(mat_sostituzione + riga1 * n_col + colonna1 - 1);
            }
            i = i + 2;
        } else if (colonna1 == colonna2) {
            if (riga1 > 0 && riga2 > 0) {
                *(testo + i) = *(mat_sostituzione + (riga1 - 1) * n_col + colonna1);
                *(testo + i + 1) = *(mat_sostituzione + (riga2 - 1) * n_col + colonna2);
            } else if (riga1 == 0) {
                *(testo + i) = *(mat_sostituzione + (n_righe - 1) * n_col + colonna1);
                *(testo + i + 1) = *(mat_sostituzione + (riga2 - 1) * n_col + colonna2);
            } else {
                *(testo + i) = *(mat_sostituzione + (riga1 - 1) * n_col + colonna1);
                *(testo + i + 1) = *(mat_sostituzione + (n_righe - 1) * n_col + colonna2);
            }

            i = i + 2;
        } else {
            *(testo + i) = *(mat_sostituzione + riga1 * n_col + colonna2);
            *(testo + i + 1) = *(mat_sostituzione + riga2 * n_col + colonna1);
            i = i + 2;
        }
    }

    ripristina_lettere(testo);
}
