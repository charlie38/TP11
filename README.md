# TP11
INF203 again

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
int trouver_et_appliquer_affectation_variable(variables * ens, char *ligne) {
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
```

f. cf variables.c
**Attention : ~~à tester!~~ manque un '\0' quelque part... **

```c
void appliquer_expansion_variables(variables * ens, char *ligne_originale, char *ligne_expansee) {

	int i=0; /* compteur ligne_originale */
	int j=0; /* compteur ligne_expansee */
	
	while (ligne_originale[i]!='\0') {
		
		if (ligne_originale[i]=='$'){
			/* on copie le nom de la variable */
			char nom[TAILLE_MAX_NOM];
			i++; /* on ne copie pas le $! */
			int k=0; /* compteur nom */
			while ( ((int)ligne_originale[i]<=90 && (int)ligne_originale[i]>=65) || ((int)ligne_originale[i]<=57 && (int)ligne_originale[i]>=48) || (int)ligne_originale[i]==42 || (int)ligne_originale[i]==23 ){
				/* condition du while : "tant que je lis un caractère alphanumérique, * ou #" */
				nom[k]=ligne_originale[i];
				k++;
				i++;
			}
			nom[k]='\0';
			
			/* on cherche la valeur de la variable pour la 'remplacer' dans ligne_expansee */
			int indice=trouver_variable(ens,nom);
			char * valeur=valeur_variable(ens,indice);
			int m=0;
			while (valeur[m]!='\0') {
				ligne_expansee[j]=valeur[m];
				m++;
			}
		}else{ 
			ligne_expansee[j]=ligne_originale[i]; 
		}
		i++;
		j++;
	}
}
```
