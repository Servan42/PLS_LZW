#include "dictionnaire.h"

//TODO : Revoir CodeVersChaine. Moyennement sûr de l'utilité du paramètre *longueur


/**
* @fn void initialiser()
* @brief Cette fonction sert à intialiser le dictionnaire avec pour les 256 premiers codes l'ASCII de base
*/

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

/**
* @fn Code Inserer(Code prefixe,Code mono)
* @brief Sert à insérer dans le dictionnaire une nouvelle entrées formée de deux précédentes entrées
* @param[in] prefixe Code codant le préfixe (la première partie) de code à ajouter dans le dictionnaire
* @param[in] mono Code codant le suffixe (la dernière partie) de code à ajouter dans le dictionnaire
* @return Il s'agit du code codant la séquence
*/

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

/**
* @fn uint8_t *CodeVersChaine (Code code, int *longueur)
* @brief Prends un code et renvoi la chaine correspondante
* @param[in] code Le code pour lequel il faut chercher la séquence correspondante
* @param[in] longueur ??????????????????
* @return Il s'agit de la séquence correspondante
*/

uint8_t *CodeVersChaine (Code code, int *longueur){
  uint8_t *val;
  val = dico[code].mot;
  *longueur = dico[code].longueur;
  return val;
}

/**
* @fn Code SequenceVersCode (uint8_t *sequence, int longueur)
* @brief Prends une séquence et renvoi le code correspondant. Si la séquence n'est pas présente dans le dictionnaire, renvoie -1.
* @param[in] séquence Séquence à chercher
* @param[in] longueur Longueur de la séquence à chercher
* @return Il s'agit du code correspondant, ou de -1 si la séquence n'est pas dans le dictionnaire
*/

Code SequenceVersCode (uint8_t *sequence, int longueur){
  Code result = -1;
  for(int i=0;i<MAX;i++){
    if(dico[i].longueur==longueur){
      int j;
      for(j=0;j<longueur;j++){
        if(dico[i].mot[j] != sequence[j]){
          break;
        }
      }
      if(j==(longueur-1)){
        result = i;
      }
    }
  }
  return result;
}
