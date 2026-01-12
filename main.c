#include <stdio.h>
#include <stdlib.h>
#include "Funzioni.h"
int main(int argc, char const *argv[])
{
char testo_crittografato[100];
char messaggio[]="LET US MEET AT NOON";
char mat_sostituzione[][8]={
{'8','J','E','Q','D','N','5','O'},
{'P','U','3','A','R','F','L','W'},
{'4','V','C','2','T','M','B','I'},
{'K','7','Z','S','G','X','H','Y'}};
controllo_lettere(messaggio);
// stampa_a2d_char(&mat_sostituzione[0][0],4,8);
Crittografia(messaggio,&mat_sostituzione[0][0],4,8,testo_crittografato);
printf("\n%s\n",messaggio);
printf("\n%s\n",testo_crittografato);

}