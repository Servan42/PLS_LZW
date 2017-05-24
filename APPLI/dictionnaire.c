#include "dictionnaire.h"

void dico_print(){
  for(int i=0;i<MAX;i++){
    if(i==256){
      i++;
    }
    else if(dico[i].longueur == 0){
      break;
    }
    int lg = dico[i].longueur;
    printf("\n");
    printf("%d : ",i);
    printf("lg = %d\n",lg);
    for(int j=0;j<lg;j++){
      printf("%c",dico[i].mot[j]);
    }
    //printf("%s\n",dico[i].mot);
  }
  printf("\n");
}

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
    e.mot = malloc(sizeof(char));
    e.mot[0] = c;
    dico[ind_dico] = e;
  }
  for(int i=256;i<MAX;i++){
    elem e;
    e.longueur = 0;
    e.mot = NULL;
    dico[i]=e;
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
  //printf("Insérer appelé\n");
  //printf("Code pref : %d\n",prefixe);
  //printf("Code mono : %d\n",mono);
  if(ind_dico >= MAX){
    initialiser();
  }
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
    nv_mot[i] = str_mono[j];
    i++;
  }
  elem e;
  e.longueur = longueur_mono+longueur_pref;
  e.mot = malloc((longueur_mono+longueur_pref)*sizeof(char));
  //dico[ind_dico].longueur = longueur_mono+longueur_pref;
  //dico[ind_dico].mot = malloc((longueur_mono+longueur_pref)*sizeof(char));
  for(int i=0;i<longueur_mono+longueur_pref;i++){
    e.mot[i] = nv_mot[i];
  }
  //strcpy(e.mot,nv_mot);
  dico[ind_dico] = e;
  /*printf("NOUVELLE ENTREE DANS LA TABLE : \n");
  printf("Code : %d\n",ind_dico);
  printf("Longueur : %d\n",dico[ind_dico].longueur);
  printf("Mot : %c",dico[ind_dico].mot[0]);
  printf("%c\n",dico[ind_dico].mot[1]);

  dico_print();*/
  ind_dico++;
  return ind_dico-1;
}

int CodeVersLongueur(Code code){
  if(code==256){
    printf("fin de tableau\n");
    return -1;
  }
  printf("CODE : %d\n",code);
  return dico[code].longueur;
}


/**
* @fn uint8_t *CodeVersChaine (Code code, int *longueur)
* @brief Prends un code et renvoiaut chercher la séquence correspondante
* @param[in] longueur Il s'agit de la longueur de la séquence retournée
* @return Il s'agit de la séquence correspondante
*/

void CodeVersChaine (Code code, uint8_t *val){
  int longueur = dico[code].longueur;
  //printf("Je lie, longueur = %d\n",*longueur);
  //free(val);
  printf("code : %d\n", code);
  //printf("________________Adresse : %d\n",*val);
  for(int i=0;i<longueur;i++){
    val[i] = dico[code].mot[i];
    printf("val[%d] = %c\n",i,dico[code].mot[i]);
  }
  printf("\n");
}

/**
* @fn Code SequenceVersCode (uint8_t *sequence, int longueur)
* @brief Prends une séquence et renvoi le code correspondant. Si la séquence n'est pas présente dans le dictionnaire, renvoie -1.
* @param[in] séquence Séquence à chercher
* @param[in] longueur Longueur de la séquence à chercher
* @return Il s'agit du code correspondant, ou de -1 si la séquence n'est pas dans le dictionnaire
*/

Code SequenceVersCode (uint8_t *sequence, int longueur){
  #ifdef DEBUG
  printf("SeqVerCode appelé avec : ");
  for(int i=0;i<longueur;i++){
    printf("%c",sequence[i]);
  }
  printf("\n");
  #endif
  Code result = -1;
  int trouve=0;
  int j = 0;
  for(int i=0;i<MAX;i++){
    if(dico[i].longueur==longueur){
      trouve = 1;
      j=0;
      for(j=0;j<longueur;++j){
        if(dico[i].mot[j] != sequence[j]){
          trouve = 0;
          break;
        }else{
          trouve = 1;
        }
      }
      if((trouve)&&(j==(longueur))){
        result = i;
        break;
      }
    }
  }
  #ifdef DEBUG
  printf("Je renvoi le code : %d\n",result);
  //dico_print();
  #endif
  return result;
}
