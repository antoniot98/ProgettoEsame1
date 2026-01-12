#ifndef LIBRERIA_H
#define LIBRERIA_H


void controllo_lettere(char * testo);
void posizione_lettera(char chiave, char *mat, int n_righe, int n_col, int *riga, int*col);
void elimina_spazi(char*, char*);
void Crittografia(char *testo, char *mat_sostituzione, int n_righe, int n_col, char *testo_crittografato);

#endif 