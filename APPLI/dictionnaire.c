#include "dictionnaire.h"

void initialiser(){
  ind_dico = 0;
  for(;ind_dico<256;ind_dico++){
    elem e;
    char c =(char) ind_dico;
    e.longueur = 1;
    e.mot = &c;
    dico[ind_dico] = e;
  }
  ind_dico++;
}

Code Inserer(Code prefixe,Code mono){
  char * str_pref = dico[prefixe].mot;
  int longueur_pref = dico[prefixe].longueur;
  char * str_mono = dico[mono].mot;
  int longueur_mono = dico[mono].longueur;
  char nv_mot[longueur_mono+longueur_pref];
  int i;
  for(i=0;i<longueur_pref;i++){
    nv_mot[i] = str_pref[i];
  }
  for(int j=0;j<longueur_mono;j++){
    i++;
    nv_mot[i] = str_mono[j];
  }
  elem e;
  e.longueur = longueur_mono+longueur_pref;
  e.mot = nv_mot;
  dico[ind_dico] = e;
  ind_dico++;
  return ind_dico-1;
}

uint8_t *CodeVersChaine (Code code, int *longueur){
  return 0;
}

Code SequenceVersCode (uint8_t *sequence, int longueur){
  return 0;
}
