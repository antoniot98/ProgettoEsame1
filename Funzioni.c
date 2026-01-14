#include <stdio.h>
#include <math.h>
#include <string.h>

void stampa_matrice(char *mat, int n_righe, int n_col) {
    for (int i = 0; i < n_righe; i++) {
        for (int j = 0; j < n_col; j++) {
            printf("%5c", *(mat + i * n_col + j));
        }
        printf("\n");
    }
}

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
}

/* Funzione che controlla le coppie di lettere uguali ed aggiunge una X tra le due*/
void controllo_lettere(char *testo) {
    char temp[100];
    int i = 0;
    elimina_spazi(testo);
    strupr(testo);
    //printf("\n%s\n", testo);

    /*Ciclo while finche c'è il testo controlla le coppie di lettere se sono uguali copia la parte dopo in
    una variabile temporanea, aggiugne una x e copia il contenuto della variabile temporanea nell'array principale*/
    while (i < (strlen(testo) - 1)) {
        if (*(testo + i) == *(testo + i + 1)) {
            strcpy(temp, testo + i + 1);
            *(testo + i + 1) = 'X';
            strcpy(testo + i + 2, temp);
        }
        i = i + 2;
    }
    if (strlen(testo) % 2 != 0) {
        *(testo + strlen(testo)) = 'X';
    }
}

void ripristina_lettere(char *testo) {
    char temp[100];
    int i = 0;


    while (i < (strlen(testo) - 1)) {
        if (*(testo + i) == 'X' && *(testo + i + 1) == *(testo + i - 1)) {
            strcpy(temp, testo + i + 1);
            strcpy(testo + i, temp);
        }
        i++;
    }
    if (*(testo + strlen(testo) - 1) == 'X') {
        *(testo + strlen(testo) - 1) = '\0';
    }
}

void Crittografia(char *testo, char *mat_sostituzione, int n_righe, int n_col, char *testo_crittografato) {
    int i = 0;
    int riga1, colonna1, riga2, colonna2;
    controllo_lettere(testo);

    while (i < strlen(testo) - 1) {
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
}

void Decrittografia(char *testo_crittografato, char *mat_sostituzione, int n_righe, int n_col, char *testo) {
    int i = 0;
    int riga1, colonna1, riga2, colonna2;

    while (i <= strlen(testo_crittografato) - 1) {
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
                *(testo + i) = *(mat_sostituzione + (n_righe - 1) * n_col + colonna1);
                *(testo + i + 1) = *(mat_sostituzione + (riga2 - 1) * n_col + colonna2);
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
