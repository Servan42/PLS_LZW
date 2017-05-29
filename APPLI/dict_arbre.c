#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define max(a,b) ((a)>(b)?(a):(b))

/* structure noeud presentee en cours */

typedef struct n {
  int cle;
  struct n *fgauche, *fdroite;
} noeud ;

/* type Arbre, pointeur vers un noeud */

typedef noeud *Arbre; 

/* n nouveau n a ajouter dans l'arbre a */

typedef struct
{
  int tete,queue,taille;
  Arbre *tab;
} file;


void init(file *f, int nbelem)
{
  f->tete = 0;
  f->queue = 0;
  f->taille = nbelem;
  f->tab = malloc(nbelem * sizeof(Arbre));
}

int empty(file *f)
{
  return f->tete == f->queue;
}

Arbre get(file *f)
{
  Arbre e;
  if(empty(f)) return NULL;
  else
  {
    e = f->tab[f->tete];
    f->tete = (f->tete + 1)%f->taille;
  }
  return e;
}

void put(file *f, Arbre a)
{
  f->tab[f->queue] = a;
  f->queue =(1 + f->queue)%f->taille;
}

int feuille (Arbre a)
{
  if (a == NULL)
    return 0 ;
  else
    {
      if ((a->fgauche == NULL) && (a->fdroite == NULL))
	return 1 ;
      else
	return 0 ;
    }
}

Arbre ajouter_noeud (Arbre a, Arbre n)
{
  /* ajouter le noeud n dans l'arbre a */
  
  if (a == NULL)
    return n ;
  else if (n->cle < a->cle)
	a->fgauche = ajouter_noeud (a->fgauche, n) ;
  else
	a->fdroite = ajouter_noeud (a->fdroite, n) ;
  return a ;
  
}  

Arbre rechercher_cle_arbre (Arbre a, int valeur)
{
  if (a == NULL)
    return NULL ;
  else
    {
      if (a->cle == valeur)
	return a ;
      else
	{
	  if (a->cle < valeur)
	    return rechercher_cle_arbre (a->fdroite, valeur) ;
	  else
	    return rechercher_cle_arbre (a->fgauche, valeur) ;
	}
    }
}

Arbre ajouter_cle (Arbre a, int cle)
{
  Arbre n ;
  Arbre ptrouve ;
  
  /* 
     ajout de la clé. Creation du noeud n qu'on insere 
    dans l'arbre a
  */

  ptrouve = rechercher_cle_arbre (a, cle) ;

  if (ptrouve == NULL)
    {
      n = (Arbre ) malloc (sizeof(noeud)) ;
      n->cle = cle;
      n->fgauche = NULL ;
      n->fdroite = NULL ;

      a = ajouter_noeud (a, n) ;
      return a ;
    }
  else
    return a ;
}

void afficher_arbre (Arbre a, int niveau)
{
  /*
    affichage de l'arbre a
    on l'affiche en le penchant sur sa gauche
    la partie droite (haute) se retrouve en l'air
  */
  
  int i ;
  
  if (a != NULL)
    {
    	afficher_arbre (a->fdroite,niveau+1) ;
    	
    	for (i = 0; i < niveau; i++) printf ("\t") ;
    	printf (" %d (%d)\n\n", a->cle, niveau) ;

    	afficher_arbre (a->fgauche, niveau+1) ;
    }
  return ;
}

int hauteur_arbre (Arbre a)
{
  /*
    calculer la hauteur de l'arbre a
  */
  
  if (a == NULL)
    return 0 ;
  else
    {
      return 1 +
	     max (hauteur_arbre (a->fgauche), hauteur_arbre (a->fdroite)) ;
    }
}

void parcourir_arbre (Arbre a, int *t, int niveau)
{
  if (a == NULL)
    return ;
  
  t [niveau] = t [niveau] + 1 ;
  parcourir_arbre (a->fgauche, t, niveau+1) ;
  parcourir_arbre (a->fdroite, t, niveau+1) ;  

  return ;
}

void nombre_noeuds_par_niveau (Arbre a)
{
  int i  ;
  int *t ;
  int h  ;
  
  h = hauteur_arbre (a) ;

  /* Allocation d'un tableau d'entier, une case par niveau */
  t = malloc (h * sizeof (int)) ;

  /* initialisation du tableau */
  
  for (i = 0; i < h ; i++)
    t[i] = 0 ;

  /* 
     Parcourir l'arbre a partir du niveau 0
     le tableau t est passe en parametre
  */
  
  parcourir_arbre (a, t, 0) ;

  for (i = 0; i < h ; i++)
    printf ("Niveau %d: nombre cles %d\n", i, t[i]) ;

  free (t) ;
  return ;
}

int nombre_cles_arbre (Arbre a)
{
  if (a == NULL)
    return 0 ;
  else
    {
      return 1 + nombre_cles_arbre (a->fgauche) + nombre_cles_arbre (a->fdroite) ;
    }
}



Arbre cle_superieure_arbre (Arbre a, int valeur, Arbre *sup)
{
  if (a == NULL)
    return *sup ;
  
  if (valeur < a->cle)
    {
      *sup = a ;
      return cle_superieure_arbre (a->fgauche, valeur, sup) ;
    }
  else
    {
      return cle_superieure_arbre (a->fdroite, valeur, sup) ;
    }
}

Arbre rechercher_cle_sup_arbre (Arbre a, int valeur)
{
  Arbre ptrouve ;
  Arbre psup = NULL ;
    
  ptrouve = cle_superieure_arbre (a, valeur, &psup) ;
  return ptrouve ;
  
}

Arbre cle_inferieure_arbre (Arbre a, int valeur, Arbre *inf)
{
  if (a == NULL)
    return *inf ;
  
  if (valeur > a->cle)
    {
      *inf = a ;
      return cle_inferieure_arbre (a->fdroite, valeur, inf) ;
    }
  else
    {	    
      return cle_inferieure_arbre (a->fgauche, valeur, inf) ;
    }
}

Arbre rechercher_cle_inf_arbre (Arbre a, int valeur)
{
  Arbre ptrouve ;
  Arbre pinf = NULL ;
    
  ptrouve = cle_inferieure_arbre (a, valeur, &pinf) ;
  return ptrouve ;
  
}

int EquilibreComplet1 (Arbre a)
{
  int h ;
  int nbcles;
  
  int p = 1 ;
  
  h = hauteur_arbre (a) ;
  p = (p << h) - 1  ;

  nbcles = nombre_cles_arbre (a) ;

  if (p == nbcles)
    return 1 ;
  else
    return 0 ;
}

int EquilibreComplet2 (Arbre a)
{

  if (a == NULL)
    return 1 ;

  if ((a->fgauche != NULL && a->fdroite == NULL) || (a->fgauche == NULL && a->fdroite != NULL))
    return 0 ;

  return (EquilibreComplet2 (a->fgauche) && EquilibreComplet2 (a->fdroite)) ; 
}

Arbre lire_arbre (char *nom_fichier)
{
  FILE *f ;
  int cle;
  Arbre a = NULL;
  
  f = fopen (nom_fichier, "r") ;

  while (fscanf (f, "%d", &cle) != EOF)
    {
      a = ajouter_cle (a, cle) ;
    }
    
  fclose (f) ;

  return a ;
}

Arbre detruire_cle_arbre (Arbre a, int cle)
{
    //Ajouter un cas pour la suppresion de la racine.

    Arbre AC = NULL;
    Arbre AP = NULL;
    Arbre AD = NULL;
    int G;

    if((a == NULL) || rechercher_cle_arbre(a,cle) == NULL) return a;
    else if(a->cle == cle)
    {
      if(a->fdroite==NULL) return a->fgauche;
      AC = a->fdroite;
      if(a->fgauche != NULL) ajouter_noeud(a->fdroite,a->fgauche);
      //free(a);
      return AC;

    }
    else
    {
      AC = a;


        while(AC != NULL && AC->cle != cle)
        {
          if(AC->cle < cle) 
            {
              AP = AC;
              AC = AC->fdroite;
            }
          else if(AC->cle > cle) 
            {
              AP = AC;
              AC = AC->fgauche;
            }
        }

        if(AP->fgauche != NULL && AP->fgauche->cle == cle) 
          {
            G = 1;
            AP->fgauche = AC->fdroite;
          }
        else
          {
            G = 0;
            AP->fdroite = AC->fdroite;
            if(AP->fdroite != NULL) AP = AP->fdroite;
          } 



        AC = AC->fgauche;
        while(AP->fgauche != NULL) AP = AP->fgauche;
        if(G) AP->fgauche = AC;
        else AP->fdroite = AC;

      /*
      //Zoran's bullshit
      //Trying to fix Servan's inefficiency :P
      AP=NULL;
      if(AC->fgauche!=NULL){AP=AC->fgauche;}
      if(AC->fdroite!=NULL){AD=AC->fdroite;}
      free(AC);
      ajouter_noeud(a,AP);
      ajouter_noeud(a,AD);
      */
      
    return a;
    }

}

int trouver_cle_min (Arbre a)
{
  Arbre AC = NULL;

  if(a == NULL)
  {
    return 0;
  }
  else
  {
    AC = a;
    while(AC->fgauche != NULL)
    {
      AC = AC->fgauche;
    }
    return AC->cle;
  }
}

void imprimer_liste_cle_triee (Arbre a)
{
  Arbre AC = a;
  int min;
  if(a == NULL){
    return;
  } else {

    imprimer_liste_cle_triee(a->fgauche);
    printf("%d ", a->cle);
    imprimer_liste_cle_triee(a->fdroite);
  }

  

}

//Afiche les clefs de l'arbre par niveau
void parcourir_arbre_largeur (Arbre a)
{
  /*
    a completer
    Utiliser une file, voir cours
  */
  file liste, stock;
  init(&liste, nombre_cles_arbre(a));
  init(&stock, nombre_cles_arbre(a));

  put(&liste, a);
  for(int i=0;i<hauteur_arbre(a);i++){
    printf("hauteur %i : ", i);
    while(!empty(&liste)){
      Arbre AC = get(&liste);
      if(AC->fdroite!=NULL) put(&stock, AC->fdroite);
      if(AC->fgauche!=NULL) put(&stock, AC->fgauche);
      printf("%i ", AC->cle);
    }
    printf("\n");
    while(!empty(&stock)){
      put(&liste, get(&stock));
    }
  }
  printf("\n");
}



Arbre union_deux_arbres (Arbre a1, Arbre a2)
{
  int N1 = nombre_cles_arbre(a1);
  int min;
  int arbre1[N1];

  for (int i = 0; i < N1; i++)
  {
    min = trouver_cle_min(a1);
    arbre1[i] = min;
    a1 = detruire_cle_arbre(a1,min);
  }

  for (int i = 0; i < N1; i++)
  {
    ajouter_cle(a2,arbre1[i]);
  }

  return a2;

  }

Arbre intersection_deux_arbres (Arbre a1, Arbre a2)
{
  // Servan's iterativeshit
  // int N1 = nombre_cles_arbre(a1);
  // int N2 = nombre_cles_arbre(a2);
  // int min;
  // int arbre1[N1];
  // int arbre2[N2];
  // Arbre a3 = NULL;

  // for (int i = 0; i < N1; i++)
  // {
  //   min = trouver_cle_min(a1);
  //   arbre1[i] = min;
  //   a1 = detruire_cle_arbre(a1,min);
  // }


  // for (int i = 0; i < N2; i++)
  // {
  //   min = trouver_cle_min(a2);
  //   arbre2[i] = min;
  //   a2 =detruire_cle_arbre(a2,min);
  // }



  // for (int i = 0; i < N1; i++)
  // {
  //   for (int j = 0; j < N2; j++)
  //   {
  //     if(arbre1[i] == arbre2[j])
  //     {
  //       ajouter_cle(a3,arbre2[j]);
  //     }
  //   }
  // }

  // return a3;

    if(a1!=NULL){
      if(rechercher_cle_arbre(a2, a1->cle)==NULL){
        a1=detruire_cle_arbre(a1, a1->cle);
        a1=intersection_deux_arbres(a1, a2);
      }
      else if(a1->fgauche!=NULL && a1->fdroite!=NULL) {a1=ajouter_cle(union_deux_arbres(intersection_deux_arbres(a1->fgauche, a2), intersection_deux_arbres(a1->fdroite, a2)), a1->cle);}
      else if(a1->fgauche!=NULL) {a1=ajouter_cle(intersection_deux_arbres(a1->fgauche, a2), a1->cle);}
      else if(a1->fdroite!=NULL) {a1=ajouter_cle(intersection_deux_arbres(a1->fdroite, a2), a1->cle);}
      else {return a1;}
    }
  }


//Dit si l'ensemble des clefs de a1 sont inclues dans a2
int inclusion_arbre (Arbre a1, Arbre a2)
{
  if(a1!=NULL){
    return ((rechercher_cle_arbre(a2, a1->cle)!=NULL) && inclusion_arbre(a1->fgauche, a2) && inclusion_arbre(a1->fdroite, a2));
  }
  else{
    return 1;
  }

}

int main (int argc, char**argv)
{
  Arbre a,a1,a2 ;
  int x ;
  int bool ;
  Arbre  ptrouve = NULL ;

  if (argc != 3)
    {
      fprintf (stderr, "il manque le parametre nom de fichier\n") ;
      exit (-1) ;
    }

  a = lire_arbre (argv[1]) ;
  a1 = lire_arbre (argv[2]) ;

  printf("a1 : \n\n") ;
  afficher_arbre (a,0) ;
  printf("------------\n") ;
  printf("a2 : \n\n") ;
  afficher_arbre (a1,0) ;
  printf("------------\n") ;
  printf("a1Ua2 :\n\n") ;
  a2 = union_deux_arbres(a,a1) ;
  afficher_arbre (a2,0) ;

  printf("Tests d'inclusion : \n") ;
  printf(">> a1 contenu dans a1Ua2 : %i\n", inclusion_arbre(a, a2)) ;
  printf(">> a2 contenu dans a1Ua2 : %i\n", inclusion_arbre(a1, a2)) ;
  printf(">> a1Ua2 contenu dans a1Ua2 : %i\n", inclusion_arbre(a2, a2)) ;
  printf(">> a1Ua2 contenu dans a1 : %i\n\n", inclusion_arbre(a2, a)) ;

  a = lire_arbre (argv[1]) ;
  a1 = lire_arbre (argv[2]) ;

  printf("a1 : \n\n") ;
  afficher_arbre (a,0) ;
  printf("------------\n") ;
  printf("a2 : \n\n") ;
  afficher_arbre (a1,0) ;
  printf("------------\n") ;
  printf("a1 inter a2 :\n\n") ;
  a2 = intersection_deux_arbres(a,a1) ;
  afficher_arbre (a2,0) ;


  a = lire_arbre (argv[1]) ;
  a1 = lire_arbre (argv[2]) ;

  // printf("Detruire clé arbre :");
  // scanf("%d",&x);
  // a = detruire_cle_arbre(a,x);
  // afficher_arbre (a,0) ;



  printf("Cles triees de a1 : ") ;
  imprimer_liste_cle_triee(a) ;
  printf("\n") ;

  printf("Parcours en largeur de a2 :\n") ;
  parcourir_arbre_largeur(a1) ;

  printf("Clé min : %d\n",trouver_cle_min(a));

  printf ("Hauteur %d\n", hauteur_arbre (a)) ;

  nombre_noeuds_par_niveau (a) ;

  printf ("Nombre cles de l'arbre %d\n", nombre_cles_arbre (a)) ;

  bool = EquilibreComplet1 (a) ;

  if (bool = 1)
    printf ("Methode 1: Arbre equilibre complet\n") ;
  else
    printf ("Methode 1: Arbre n'est pas equilibre complet\n") ;

    bool = EquilibreComplet2 (a) ;

  if (bool = 1)
    printf ("Methode 2: Arbre equilibre complet\n") ;
  else
    printf ("Methode 2: Arbre n'est pas equilibre complet\n") ;


  /*
    Appels des fonctions de recherche de cles
  */

  printf ("Entrez une cle a rechercher\n") ;

  scanf ("%d", &x) ;

  ptrouve = rechercher_cle_arbre (a, x) ;

  if (ptrouve != NULL)
    printf ("la cle %d est dans l'arbre\n", x) ;
  else
    printf ("la cle %d n'est pas dans l'arbre\n", x) ;

  ptrouve = rechercher_cle_sup_arbre (a, x) ;

  if (ptrouve != NULL)
    printf ("la cle sup de %d est %d\n", x, ptrouve->cle) ;
  else
    printf ("il n'y a pas de cle sup pour %d\n", x) ;

  ptrouve = rechercher_cle_inf_arbre (a, x) ;

  if (ptrouve != NULL)
    printf ("la cle inf de %d est %d\n", x, ptrouve->cle) ;
  else
    printf ("il n'y a pas de cle inf pour %d\n", x) ;
}
