# TP11

## Compte rendu

a. Pour l'instant, les fonctions ne font rien.
b. cf. lignes.c
```c
int lire_ligne_fichier(FILE * fichier, char *ligne) {
	int i=0;
	char c='\0';
	fscanf(fichier,"%c",&c);
	while (c!='\n' && !feof(fichier)){
		ligne[i]=c;
		fscanf(fichier, "%c", &c);		
		i++;	
	}
	ligne[i]='\0';

	if (!feof(fichier) || i!=0){
		return 1;
	}else{
		return 0;
	}
}
```
c. La  commande echo ne fonctionne pas car, son exécution requiert un argument.

d. cf variables.c
```c
void init_variables(variables * ens) {
	ens->nb=0;
}

int ajouter_variable(variables * ens, char *nom, char *valeur) {

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
	return ens->nb;
}

int trouver_variable(variables * ens, char *nom) {

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

	if (i>NOMBRE_MAX_VARIABLES){
		return NULL;
	}else{
		return ens->T[i].nom;
	}
}

char *valeur_variable(variables * ens, int i) {

	if (i>NOMBRE_MAX_VARIABLES){
    		return "";
	}else{
		return ens->T[i].valeur;
	}
}

void modifier_valeur_variable(variables * ens, int i, char *valeur) {
	strcpy(ens->T[i].valeur,valeur);
}
```
e. cf variables.c
```c
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

	/* reconnait une affectation */
	int egal=indice_egal(ligne);
	if (egal==-1){
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
			return 0;
		}

		valeur[i_val]=ligne[i];
		i_val++;
		i++;
	}

	valeur[i_val]='\0';
	
	/* affectation */
	ajouter_variable(ens,nom,valeur);
	return 1;

}
```

f. cf variables.c

```c
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

```

g. cf lignes.c

```c
void decouper_ligne(char *ligne, char *ligne_decoupee[]) {

	int i_l = 0;
	int i_d = 0;
	int premier_espace = 1;

	/* on s'occupe du premier mot */
	ligne_decoupee[i_d]=&ligne[i_l];
	i_d++;
	i_l++;

	while (ligne[i_l]!='\0'){

		if (ligne[i_l]==' '){

			if (premier_espace){

				ligne[i_l]='\0';
				i_l++;

				premier_espace = 0;

				ligne_decoupee[i_d]=&ligne[i_l];
				i_d++;
			}else{
				i_l++;
			}
		}else{
			if (!premier_espace) {
				premier_espace = 1;
			}
			i_l++;
		}
	}
	ligne_decoupee[i_d] = NULL;
	
}
```
