#ifndef LIBRERIA_H
#define LIBRERIA_H


void controllo_lettere(char *testo);

void posizione_lettera(char chiave, char *mat, int n_righe, int n_col, int *riga, int *col);

void elimina_spazi(char *, char *);

void Crittografia(char *testo, char *mat_sostituzione, int n_righe, int n_col, char *testo_crittografato);

void ripristina_lettere(char *testo);

void stampa_matrice(char *mat, int n_righe, int n_col);

void Decrittografia(char *testo_crittografato, char *mat_sostituzione, int n_righe, int n_col, char *testo);
#endif
