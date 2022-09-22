#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h> 
//*******Inclusion des bibliotheques necessaires au fonctionnement de l'appli****

//*******Structures**********
struct Produit{
	float prix;
	int code;
	int quantite;
	char nom[30];
};

struct Date{
	int jour;
	int mois;
	int annee;
};

typedef struct Produit Produit;
typedef struct Date Date;

struct Vente{
	Produit produit;
	Date date;
	 
};

typedef struct Vente Vente;

//******************
//********Prototypes**********
void menu();
void afficherMenuChoix(int choix);
void ajouterNouveauProduit();
void ajouterPlusieursProduits();
int checkProduit(Produit produit);
void lister();
void listerParNom();
void listerParPrix();
void permutation(Produit a, Produit b,int i);
void rechercher();
int rechercherParCode(int code);
void afficher();
void rechercherParQuantite(int quantite);
void AfficherProduit(Produit produit);
int min(int a, int b);
void acheterProduit();
void supprimerProduit(int code);
void supprimerProduitonCode();
void etatDeStock();
void alimenterStock();
void totalVentesJournee();
void moyenVentesJournee();
void maxVente();
void minVente();
void statistics();
void toupperFonc(char nom[]);
int maxProduitVendu();

//*********Prototype time********
Date dateDaujourdhui();
//*******************
//*******Prototypes pour le modele*******
void enregistrerData();
void recupererData();
void enregistrerVente();
void recupererVentes();
//******************

//*********creation des tableaux qui vont abriter notre stock et notre ventes**
Produit stockProduits[150];
Vente ventes[150];
int length=0;
int indiceVente=0;
float TVA=0.15;

//*******************
//*********controller********
int main(){
	recupererData();
	recupererVentes();
	menu();	
	
	return 0;
}
//******************


void menu(){
	 
	 int choix;
	 do{  
	 system("cls");
	 
	 printf("\t\t\t\t\t\tGesPHarma\t\t\t\t\t\t\n\n");
	 printf("1:Ajouter un produit.\n\n");
	 printf("2:Ajouter plusiers produits.\n\n");
	 printf("3:Lister les produits.\n\n");
	 printf("4:Acheter un produit.\n\n");
	 printf("5:Rechercher les produits.\n\n");
	 printf("6:Etat de stock.\n\n");
	 printf("7:Alimenter le stock.\n\n");
	 printf("8:Supprimer les produits.\n\n");
	 printf("9:Statistiques de vente.\n\n");
	 printf("choisissez la fonctionnalite voulue en indiquant le numero correspondant.\n\n");
	 
     scanf("%d",&choix);
	 afficherMenuChoix(choix);
	 
    }while(choix<1 || choix>9);
}


void afficherMenuChoix(int choix){
	system("cls");
	switch(choix){
		case 1:
			printf("1:Ajouter un produit.\n");
			ajouterNouveauProduit();
			menu();
			
			break;
		case 2:
			printf("2:Ajoutes plusiers produits.\n");
			ajouterPlusieursProduits();
			
			break;
		case 3:
			printf("3:Lister les produits.\n");
			lister();
			afficher();
			
			break;	
		case 4:
			printf("4:Acheter un produit.\n");
			acheterProduit();
			
			break;	
		case 5:
			printf("5:Rechercher les produits.\n");
			rechercher();
			
			break;
		case 6:
			printf("6:Etat de stock.\n");
			etatDeStock();
			
			break;
		case 7:
			printf("7:Alimenter le stock.\n");
			alimenterStock();
			
			break;
		case 8:
			printf("8:Supprimmer les produits.\n");
			supprimerProduitonCode();
			
			break;
		case 9:
			printf("9:Statistiques de vente.\n");
			statistics();
			
			break;

	}
	
}


void ajouterNouveauProduit(){
	Produit produit1;
	
	printf("nom: ");
	scanf("%s",produit1.nom);

	toupperFonc(produit1.nom);

	printf("code: ");
	scanf("%d",&produit1.code);
		
	printf("quantite: ");
	scanf("%d",&produit1.quantite);
	
	printf("prix: ");
	scanf("%f",&produit1.prix);
	
	
	if(checkProduit(produit1))
		
		printf("Done\n");		
	else{
		stockProduits[length] = produit1;
		length++;
		printf("Done\n");
	}
	enregistrerData();
}

void toupperFonc(char nom[]){
	int i=0;
	while(nom[i]) {
      nom[i]=toupper(nom[i]);
      i++;
   }
	
}

void ajouterPlusieursProduits(){
	int t=1;
	while(t!=0){
	ajouterNouveauProduit();
	
	printf("CLIQUEZ 0 POUR QUITTER SINON 1 \n");
	 	scanf("%d",&t);
	}
	menu();
}

int checkProduit(Produit produit){
	int i;
	int isExisted=0;
	for(i=0;i<length;i++){
		if(produit.code==stockProduits[i].code){
			 isExisted=1;
		     stockProduits[i].quantite+=produit.quantite;	
			 break;
		}
	}
	
	return isExisted;
	
}


void lister(){
	int choix;
	printf("Pour classer selon les noms croissants cliquez 1 selon les prix decroissant cliquez 2:\n");
	scanf("%d",&choix);
	switch(choix){
		case 1:
			listerParNom();
			break;
		case 2:	
			listerParPrix();
			break;
		default:
			menu();
	}
}



void listerParPrix(){
	int i,j;
		for (j=0;j<length;j++){
	     for(i=0;i<length-1;i++){
	       if(stockProduits[i].prix<stockProduits[i+1].prix){ 
	        permutation(stockProduits[i],stockProduits[i+1],i);
	      }
	    }
      }
}

void permutation(Produit a, Produit b,int i){
	stockProduits[i]=b;
	stockProduits[i+1]=a;
}

void afficher(){
	int i,t=1;
	
	  printf("Code\tProduit\t\tQuantite\tPrix\n");
	  for(i=0;i<length;i++){
	   AfficherProduit(stockProduits[i]);
		}
	while(t!=0){
		printf("Cliquer 0 pour retourner au menu ");
	    scanf("%d",&t);	
	}	
	menu(); 	
}


void rechercher(){
	int quantite;
	int choix;
	int code;
	int t=1;
	
	printf("rechercher 1 code et 2 quantite");
	scanf("%d",&choix);
	switch(choix){
		case 1:
			system("cls");
			printf(" enter code");
			scanf("%d",&code);
			printf("Code\tProduit\t\tQuantite\tPrix\n");
			if(rechercherParCode(code)!=-1){
				AfficherProduit(stockProduits[rechercherParCode(code)]);	
			}else{
				printf("Rien a Afficher\n");
			}
			break;
		case 2:	
			system("cls");
			printf(" enter quantite");
			scanf("%d",&quantite);
			rechercherParQuantite(quantite);
			while(t!=0){
		        printf("Cliquer 0 pour retourner au menu");
	            scanf("%d",&t);	
	        }	
	        menu();
			break;
		default:
			break;
	}


}

int rechercherParCode(int code){
	
	int i;
	int isExisted=-1;
	for(i=0;i<length;i++){
		if(code==stockProduits[i].code){
			 isExisted=i;	
			 break;
		}
	}
	
	return isExisted;
}

void rechercherParQuantite(int quantite){
	int i,t=1;
	printf("Code\tProduit\t\tQuantite\tPrix\n");
	for(i=0;i<length;i++){
		if(quantite==stockProduits[i].quantite){
			 AfficherProduit(stockProduits[i]);	
		}
	}
	printf("Fin");
	
	while(t!=0){
		printf("Cliquer 0 pour retourner au menu");
	    scanf("%d",&t);	
	}	
	menu();
}


void AfficherProduit(Produit produit){
	
	printf("%d\t%s\t\t%d\t\t%.2f TTC\n",produit.code,produit.nom,produit.quantite,produit.prix*(1+TVA));
	
}




void listerParNom(){
	int i,j,m,k,flag=1;
	for (j=0;j<length;j++){
	
	  for(i=0;i<length-1;i++){
	  	
	  	m=min(strlen(stockProduits[i].nom),strlen(stockProduits[i+1].nom));
	  	
	    	for(k=0;k<m;k++){ 
	    	   if(stockProduits[i].nom[k]>stockProduits[i+1].nom[k]){
	    		permutation(stockProduits[i],stockProduits[i+1],i);
	    		flag=0;
	    		break;
			    }
	        }
	        
	        if(flag){
	        	if(strlen(stockProduits[i+1].nom)<strlen(stockProduits[i].nom)){
	        		permutation(stockProduits[i],stockProduits[i+1],i);
				}
			}
	        	
		}
	 }
  }


int min(int a, int b){
	
	if(a<=b){
		return a;
	}else{
		return b;
	}
}



void acheterProduit(){
	Produit produit;
	int t;
	
	printf("code:");
		scanf("%d",&produit.code);
		
	printf("quantite:");
		scanf("%d",&produit.quantite);
	
	if(rechercherParCode(produit.code)!=-1){
		
		if(stockProduits[rechercherParCode(produit.code)].quantite>=produit.quantite){
			stockProduits[rechercherParCode(produit.code)].quantite-=produit.quantite;
			//Ajout au tableau ventes
			ventes[indiceVente].produit=stockProduits[rechercherParCode(produit.code)];
			ventes[indiceVente].produit.quantite=produit.quantite;
			ventes[indiceVente].date.jour=dateDaujourdhui().jour;
			ventes[indiceVente].date.mois=dateDaujourdhui().mois;
			ventes[indiceVente].date.annee=dateDaujourdhui().annee;
			indiceVente++;
	        enregistrerVente();
	        
			if(stockProduits[rechercherParCode(produit.code)].quantite==0){
				supprimerProduit(produit.code);
			}
			printf("Done\n");
			enregistrerData();
		}
		else{
			printf("la quantite demandee n'est pas actuellement disponible  :\n");
		}
				
    }else{
		printf("Produit indisponible pour le moment\n");
	}
	
	while(t!=0){
		printf("Cliquer 0 pour retourner au menu");
	    scanf("%d",&t);	
	}	
	menu(); 
}


void supprimerProduit(int code){
	int i;
	if(rechercherParCode(code)==-1){
		printf("Ce produit n'existe pas au stock :\n");
	}else{
		for(i=rechercherParCode(code);i<length-1;i++){
			stockProduits[i]=stockProduits[i+1];
		}
	}
	length--;
	enregistrerData();
}

void supprimerProduitonCode(){
	int i,code,t=1;
	
	printf("code:");
	scanf("%d",&code);
		
	if(rechercherParCode(code)==-1){
		printf("Ce produit n'existe pas dans le stock :\n");
	}else{
		if(rechercherParCode(code)==length-1){
			length--;
		}else{
			for(i=rechercherParCode(code);i<length-1;i++){
			stockProduits[i]=stockProduits[i+1];
		   }
		   length--;
		}
		
	}
	enregistrerData();
	while(t!=0){
		printf("Cliquer 0 pour retourner au menu");
	    scanf("%d",&t);	
	}	
	menu();
	
}


void etatDeStock(){
	int i,t,maxQuantite;
	
	printf("quantite maximale :");
		scanf("%d",&maxQuantite);
	for(i=0;i<length;i++){
	    
	   if(stockProduits[i].quantite<=maxQuantite){ 
	       AfficherProduit(stockProduits[i]);
	   }
  }
  
  while(t!=0){
		printf("Cliquer 0 pour retourner au menu");
	    scanf("%d",&t);	
	}	
	menu();
}



void alimenterStock(){
	int t=1,code,quantite;
	
	printf("code:");
	scanf("%d",&code);
		
	printf("quantite:");
	scanf("%d",&quantite);
	
	if(rechercherParCode(code)!=-1){
		if(quantite>0){
			stockProduits[rechercherParCode(code)].quantite+=quantite;
		}else{
			printf("quantite doit etre positive\n");
		}
	}else{
		printf("produit non trouve\n");
	}
	enregistrerData();
	 while(t!=0){
		printf("Cliquer 0 pour retourner au menu");
	    scanf("%d",&t);	
	}	
	menu();	
}


void statistics(){
	
	int choix;
	printf("1 pour total ventes 2 pour moyen 3 pour max 4 pour min:\n");
	scanf("%d",&choix);
	switch(choix){
		case 1:
			system("cls");
			totalVentesJournee();
			break;
		case 2:	
		    system("cls");
		    moyenVentesJournee();
			break;
		case 3:
			system("cls");
			maxVente();
			break;
		case 4:
			system("cls");
			minVente();
			break;
		default:
			break;
   }
}

void totalVentesJournee(){
	int t=1;
	int i;
	float totalVentesJournee=0;
	
	printf("total ventes journee\n");
	
	for(i=0;i<indiceVente;i++){
		if(ventes[i].date.jour==dateDaujourdhui().jour){
			totalVentesJournee+=(ventes[i].produit.prix)*(ventes[i].produit.quantite);
		    AfficherProduit(ventes[i].produit);
		}
	}
	printf("total ventes journee.: %.2f TTC\n",totalVentesJournee*(1+TVA));
	while(t!=0){
		printf("Cliquer 0 pour retourner au menu");
	    scanf("%d",&t);	
	}	
	menu(); 
}


void moyenVentesJournee(){
	int t=1;
	printf("moyen ventes journee\n");
	int i;
	float totalVentesJournee=0;
	int quantiteProduitsVendus=0;
	
	for(i=0;i<indiceVente;i++){
		if(ventes[i].date.jour==dateDaujourdhui().jour){
			totalVentesJournee+=(ventes[i].produit.prix)*(ventes[i].produit.quantite);
		    quantiteProduitsVendus+=ventes[i].produit.quantite;
		}
	}
	
	if(indiceVente>0){
		printf("moyen ventes journee.: %.2f TTC\n",(totalVentesJournee*(1+TVA)/quantiteProduitsVendus));
	}
	else{
		printf("aucune vente pour le moment\n");
	}
	while(t!=0){
		printf("Cliquer 0 pour retourner au menu");
	    scanf("%d",&t);	
	}	
	menu(); 
}

void maxVente(){
	int t=1;
	printf("max vente\n");
	int i,j=-1;
	float max;
	
	if(indiceVente>0){
        max=ventes[0].produit.quantite*ventes[0].produit.prix;
		j=0;
	}
	
	for(i=0;i<indiceVente;i++){
		if(ventes[i].date.jour==dateDaujourdhui().jour){
	  if(ventes[i].produit.quantite*ventes[i].produit.prix>max){
			
			max=ventes[i].produit.quantite*ventes[i].produit.prix;
			j=i;
	  }
     }
	}
	if(j!=-1){
		
		AfficherProduit(ventes[j].produit);
		printf("total ");
		printf("%.2f TTC\n",max*(1+TVA));
	}
	while(t!=0){
		printf("Cliquer 0 pour retourner au menu");
	    scanf("%d",&t);	
	}	
	menu(); 
}


void minVente(){
	int t=1;
	printf("min vente\n");
	int i,j=-1;
	float min;
	
	if(indiceVente>0){
		min=ventes[0].produit.quantite*ventes[0].produit.prix;
	}
	
	for(i=0;i<indiceVente;i++){
		if(ventes[i].date.jour==dateDaujourdhui().jour){
	   if(ventes[i].produit.quantite*ventes[i].produit.prix<=min){
			
			min=ventes[i].produit.quantite*ventes[i].produit.prix;
			j=i;
	  }
   }
     }   
	if(j!=-1){
		AfficherProduit(ventes[j].produit);
		printf("total ");
		printf("%.2f TTC\n",min*(1+TVA));
	}
	while(t!=0){
		printf("Cliquer 0 pour retourner au menu");
	    scanf("%d",&t);	
	}	
	menu(); 
}

//******************




void enregistrerData(){

    int i;
    FILE* fichier = NULL;
    
    remove("produitsEnStock.txt");
    
    fichier = fopen("produitsEnStock.txt", "w+");

    if (fichier != NULL)
    {
    	
    	for(i=0;i<length;i++){
    		
	       fprintf(fichier, "%d %s %d %.2f\n", stockProduits[i].code, stockProduits[i].nom, stockProduits[i].quantite,stockProduits[i].prix);
	       
		}
        fclose(fichier);
    }
}





void recupererData(){

    FILE* fichier = NULL;
    //char chaine[100] = "";
    Produit produit;
    int i=0;

    fichier = fopen("produitsEnStock.txt", "r");
    

    if (fichier != NULL)
    {
    	while(!feof(fichier)){
		
    		fscanf(fichier, "%d %s %d %f\n", &produit.code, &produit.nom, &produit.quantite,&produit.prix);
            stockProduits[i]=produit;
            i++;
		}
        fclose(fichier);
    }
length=i;
}





void enregistrerVente(){

    int i;
    FILE* fichier = NULL;
    
    remove("ventes.txt");
    
    fichier = fopen("ventes.txt", "w+");
    
    

    if (fichier != NULL)
    {
    	
    	for(i=0;i<indiceVente;i++){
    		
	       fprintf(fichier, "%d %s %d %.2f %d/%d/%d\n", ventes[i].produit.code, ventes[i].produit.nom, ventes[i].produit.quantite,ventes[i].produit.prix,ventes[i].date.jour,ventes[i].date.mois,ventes[i].date.annee);
	       
		}
        fclose(fichier);
    }
}


void recupererVentes(){

    FILE* fichier = NULL;
    
    Produit produit;
    Vente vente;
    int i=0,jour,mois,annee;
    
    fichier = fopen("ventes.txt", "r");
    

    if (fichier != NULL)
    {
    	while(!feof(fichier)){
		
    		fscanf(fichier,"%d %s %d %f %d/%d/%d\n", &produit.code, &produit.nom, &produit.quantite, &produit.prix,&jour,&mois,&annee);
            vente.produit=produit;
            vente.date.jour=jour;
            vente.date.mois=mois;
            vente.date.annee=jour;
            ventes[i]=vente;
            i++;
		}
        fclose(fichier);
    }
indiceVente=i;
}





int maxProduitVendu(){
	int code[indiceVente];
	int i,m,j=0,quantite=0;
	int max,codeArticle=-1;
	if(indiceVente>0){
		code[j]=ventes[0].produit.code;
	}
	
	max=0;
	
	for(m=0;m<j+1;m++){
	for(i=0;i<indiceVente;i++){
		
	   if(ventes[i].produit.code==code[m]){
			
			quantite+=ventes[i].produit.quantite;
	  }else{
	  	j++;
	  	code[j]=ventes[i].produit.code;
	  }
	  
    }
	if(quantite>max){
		max=quantite;
		quantite=0;
		codeArticle=code[m];
	}else{
		quantite=0;
	}
  }
  return codeArticle;
}








Date dateDaujourdhui(){
	time_t now;
	
	time(&now);
	
	struct tm *local = localtime(&now);
	Date date;
	date.jour = local->tm_mday;          
    date.mois = local->tm_mon + 1;     
    date.annee = local->tm_year + 1900;
	
	return date;
	
}
