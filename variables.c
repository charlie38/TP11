/*
Interpréteur de commandes à but pédagogique
Copyright (C) 2011-2018 Guillaume Huard
Ce programme est libre, vous pouvez le redistribuer et/ou le modifier selon les
termes de la Licence Publique Générale GNU publiée par la Free Software
Foundation (version 2 ou bien toute autre version ultérieure choisie par vous).

Ce programme est distribué car potentiellement utile, mais SANS AUCUNE
GARANTIE, ni explicite ni implicite, y compris les garanties de
commercialisation ou d'adaptation dans un but spécifique. Reportez-vous à la
Licence Publique Générale GNU pour plus de détails.

Vous devez avoir reçu une copie de la Licence Publique Générale GNU en même
temps que ce programme ; si ce n'est pas le cas, écrivez à la Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307,
États-Unis.

Contact: Guillaume.Huard@imag.fr
	 Bâtiment IMAG
	 700 avenue centrale, domaine universitaire
	 38401 Saint Martin d'Hères
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "debug.h"
#include "variables.h"

void init_variables(variables * ens) {
/*************** A COMPLETER ******************/
    /* 
       Initialiser a un ensemble vide.
     */
/**********************************************/
	ens->nb=0;

}

int ajouter_variable(variables * ens, char *nom, char *valeur) {
/*************** A COMPLETER ******************/
    /*
       Fonction qui affecte la valeur donnee au nom de variable donne.
       Si la variable existe deja dans les variables definies, il suffit juste
       de changer sa valeur. Dans le cas contraire, il faut l'ajouter aux
       variables definies : ajouter un couple (nom, valeur) a l'ensemble
       de variables.
     */
/**********************************************/
	int i=trouver_variable(ens,nom);
	if (i==-1 && ens->nb==NOMBRE_MAX_VARIABLES) {
		return -1;
	}else{
		if (i==-1){
			strcpy(ens->T[ens->nb].nom,nom);
			strcpy(ens->T[ens->nb].valeur,valeur);
			ens->nb++;
			return ens->nb;

		}else{
			strcpy(ens->T[i].valeur,valeur);
			return i;
		}
	}
}

int nombre_variables(variables * ens) {
/*************** A COMPLETER ******************/
    /*
       Fonction qui renvoie le nombre de variables dans l'ensemble.
     */
/**********************************************/
	return ens->nb;
}

int trouver_variable(variables * ens, char *nom) {

/*************** A COMPLETER ******************/
    /*
       Fonction qui recherche le nom de variable dans l'ensemble
       des variables definies. Si le nom est trouve, la fonction retourne
       l'indice correspondant dans le tableau, dans le cas
       contraire elle retourne -1.
     */
/**********************************************/
	int i = 0;
	while (i<ens->nb && strcmp(ens->T[i].nom,nom) != 0){
		i++;
	}
	if (i<ens->nb){
		return i;
	}else{
		return -1;
	}
}

char *nom_variable(variables * ens, int i) {
/*************** A COMPLETER ******************/
    /*
       Fonction qui renvoie le nom de la variable a l'indice i ou
       NULL si elle n'existe pas.
     */
/**********************************************/
	if (i>NOMBRE_MAX_VARIABLES){
		return NULL;
	}else{
		return ens->T[i].nom;
	}
}

char *valeur_variable(variables * ens, int i) {
/*************** A COMPLETER ******************/
    /*
       Fonction qui renvoie la valeur de la variable a l'indice i ou
       "" si elle n'existe pas.
     */
/**********************************************/

	if (i>NOMBRE_MAX_VARIABLES){
    		return "";
	}else{
		return ens->T[i].valeur;
	}
}

void modifier_valeur_variable(variables * ens, int i, char *valeur) {
/*************** A COMPLETER ******************/
    /*
       Fonction qui modifie la valeur de la variable a l'indice i.
       Comportement indeterminee si l'indice i n'est pas valide.
     */
/**********************************************/

	strcpy(ens->T[i].valeur,valeur);

}

void afficher_ensemble_variables(variables * ens) {
    for (int i = 0; i < nombre_variables(ens); i++) {
        printf("%s=%s\n", nom_variable(ens, i), valeur_variable(ens, i));
    }
}

int trouver_et_appliquer_affectation_variable(variables * ens, char *ligne) {
/*************** A COMPLETER ******************/
    /*
       Fonction qui cherche a reconnaitre une affectation de variable dans le 
       morceau de ligne de commande transmise et, le cas echeant, l'applique. 
       Pour cela il faut determiner si ce morceau de
       ligne est de la forme :
       nom=valeur
       Cette fonction est destructive : elle modifie ligne lorsqu'elle
       trouve une affectation. Retourne 1 en cas d'affectation trouvee, 0 dans le
       cas contraire.
     */
/**********************************************/

	int i=0;
	while (ligne[i]!='\0' && ligne[i]!='='){
		i++;
	}
	if (ligne[i]=='\0'){
		printf("pas d'affectation trouvee\n");
		return 0;
	}else{
		ligne[i]='\0';
		printf("affectation reussie!\n");
		return 1;
	}

}

void appliquer_expansion_variables(variables * ens, char *ligne_originale, char *ligne_expansee) {
/*************** A COMPLETER ******************/
/*
  Fonction qui prend une ligne lue en parametre et la recopie dans le tableau
  resultat en remplacant toutes les utilisations de variable (de la forme
  '$nom' ou nom est une chaine de caracteres alphanumeriques ou * ou #) par la
  valeur de la variable correspondante.
*/
/**********************************************/
    // A remplacer : le code ci-dessous n'expanse rien
    strcpy(ligne_expansee, ligne_originale);
	
	/* on parcourt la ligne originale */
	int i=0;
	while (ligne_originale[i]!='\0') {
		if (ligne_originale[i]=='$'){
			/* on copie le nom de la variable */
			char nom[TAILLE_MAX_NOM];
			i++; /* on ne copie pas le $! */
			int j=0;
			while ( (int(ligne_originale[i])<=90 && int(ligne_originale[i])>=65) || (int(ligne_originale[i])<=57 && int(ligne_originale[i])>=48) || int(ligne_originale[i])==42 || int(ligne_originale[i])==23 ){
				/* condition du while : "tant que je lis un caractère alphanumérique (minuscule), * ou #" */
				nom[j]=ligne_originale[i];
				j++;
				i++;
			}
			nom[j]='\0';
			
			/* on cherche la valeur de la variable pour la remplacer dans ligne_expansee */
			
			
		}
		i++;
	}
}

void affecter_variables_automatiques(variables *ens, int argc, char *argv[]) {
/*************** A COMPLETER ******************/
    /*
       Il faut definir les variables automatiques a partir des arguments
       donnes au programme :
       - placer la valeur de chacun des arguments transmis au programme dans la
       variable correspondante ($0, $1, $2, ...)
       - construire au fur et a mesure une chaine de caractere contenant toutes
       les valeurs et l'affecter a $*
       - affecter le nombre d'arguments a $#
     */
/**********************************************/
}
