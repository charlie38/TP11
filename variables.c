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

int indice_egal(char *ligne){
/* vérifie si la ligne est de la forme "nom=valeur" (ie. sans espace autour de '=')
retourne l'indice de '=', sinon -1 */

	int i=0;

	while (ligne[i]!='\0' && ligne[i]!='='){
		i++;
	}

	if (ligne[i]=='\0'){
		return -1;
	}

	if (ligne[i-1]==' ' || ligne[i+1]==' '){
		return -1;
	}

	return i;
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

	//message de debug

	/* reconnait une affectation */
	int egal=indice_egal(ligne);
	if (egal==-1){
		//printf("pas d'affectation trouvee\n");
		return 0;
	}

	/* on s'occupe du nom */
	int i=0;
	char * nom = NULL;
	int debut_nom=0;

	
	while (i<egal){
		if (ligne[i]==' '){
			debut_nom=i+1;
		}
		i++;
	}
	nom=&ligne[debut_nom];

	/* on remplace le '=' */
	ligne[i]='\0';
	

	/* valeur */
	i++;
	char valeur[TAILLE_MAX_VALEUR];
	int i_val=0;

	while (ligne[i]!='\0'){

		if (ligne[i]==' '){	/* pas de ' ' après '=' */
			//printf("pas d'affectation trouvee : espace dans valeur\n");
			return 0;
		}

		valeur[i_val]=ligne[i];
		i_val++;
		i++;
	}

	valeur[i_val]='\0';
	
	/* affectation */
	ajouter_variable(ens,nom,valeur);
	//printf("affectation reussie!\n");
	return 1;

}

int dollar(char * ligne_originale){
/* determine si un dollar indique bien la presence d'une variable
renvoie son indice, sinon -1 */
	int i=0;
	while (ligne_originale[i]!='$' && ligne_originale[i]!='\0'){
		i++;
	}
	if (ligne_originale[i]=='\0' || ligne_originale[i+1]==' '){
		return -1;
	}
	return i;

}


int expansion(char * ligne_expansee, int i_exp, char * valeur) {
/* concatene la valeur de la variable reconnue dans ligne expansee 
retourne l'indice de fin de ligne_expansee pour la completer afterwards */
	int i_val=0;
	while (valeur[i_val]!='\0') {
		ligne_expansee[i_exp]=valeur[i_val];
		i_exp++;
		i_val++;
	}
	return i_exp;	
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
    //strcpy(ligne_expansee, ligne_originale);
	
	/* on parcourt la ligne originale et on copie au fur et à mesure ligne_originale dans ligne_expansee */
	/* (en remplaçant la variable par sa valeur) */

	int i_org=0; 
	int i_exp=0;
	while (ligne_originale[i_org]!='\0') {
		
		if (ligne_originale[i_org]=='$'){

			/* si dollar n'indique pas la présence d'une variable */
			if (dollar(ligne_originale)==-1){
				ligne_expansee[i_exp]=ligne_originale[i_org];
				i_exp++;
				i_org++;
			}else{
				i_org++; /* on ne copie pas $ */ 
				/* on copie le nom de la variable */
				char nom[TAILLE_MAX_NOM];
				int i_nom=0; 
				while ( isalnum(ligne_originale[i_org]) || ligne_originale[i_org]=='*' || ligne_originale[i_org]=='#' ){
					nom[i_nom]=ligne_originale[i_org];
					i_nom++;
					i_org++;
				}
				nom[i_nom]='\0';
				
				/* on cherche la valeur de la variable */
				int indice=trouver_variable(ens,nom);
				char *valeur=valeur_variable(ens,indice);

				/* on remplace la valeur de la variable dans ligne_expansee */
				/* et on met à jour i_exp */
				i_exp=expansion(ligne_expansee,dollar(ligne_originale),valeur);
			}
		}else{
			ligne_expansee[i_exp]=ligne_originale[i_org];
			i_exp++;
			i_org++;
		}
		
	}
	ligne_expansee[i_exp]='\0';
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
