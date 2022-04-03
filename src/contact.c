#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <contact.h>


/*le struct d'un contact*/
struct contact{
	char *nom;   //un pointeur qui est vers le nom, plus meilleur à utiliser le mem.
	char *numero;
	struct contact *next;
};

//pour créer un nouveau contact
struct contact *genere_contact(const char *name, const char *num)
{
    //faire la meme chose pour la section "numéro"
    /*allouer un espace mémoire pour le pointeur nouv_num, +1 ==> pr \0*/
    char *nouv_num = malloc((strlen(num)+1)*sizeof(*nouv_num));
    strcpy(nouv_num, num); //copier le contenu de name au *nouv_nom
    char *nouv_nom = malloc((strlen(name)+1)*sizeof(*nouv_nom)); 
    strcpy(nouv_nom, name);  


    //créer un contact
    struct contact *contact = malloc(sizeof(*contact));
    contact ->nom = nouv_nom;
    contact ->numero = nouv_num;
    contact->next = NULL;
    return contact;
}

/*faire une insertion par un nouveau contact "c" dans la liste*/
void insertion_contact(struct contact **list, struct contact *contact)
{
    //tester si le contact est vide
    if (contact == NULL)
    {
        printf("contact inséré est vide\n");
        return;
    }
    contact->next = *list;   // *list = @ de la tête
    *list = contact;
}

/*supprimer le tête de la liste de contactet retourner lequel supprimé*/
struct contact *supprime_contact(struct contact **list)
{
    if (*list == NULL){
        return NULL;
    }
    else{
        struct contact *contact_courant = *list; // ici, contact_courant -> &contact
        *list = contact_courant ->next;
        contact_courant->next = NULL;
        return contact_courant;
    }

}

/*cherche un contact dans la liste, si rien a trouvé, retourner NULL, precedent qui sera utilise pour relier 2 contacts*/
struct contact *cherche_contact(struct contact *list, const char *name, struct contact **precedent)
{
    *precedent = NULL;
    struct contact *contact_courant = list;
    while(contact_courant != NULL)
    {
        uint32_t compare = strcmp(contact_courant->nom, name);//si ==0, dc nom == name
        if ( compare ==0)  
        {
            return contact_courant;
        }
        *precedent = contact_courant;
        contact_courant = contact_courant->next;
    }
    *precedent = NULL;
    return NULL;
}

/*supprimer le contact qu'on veut, si il exist pas , retourne null*/
struct contact *supprime_liste(struct contact **list, const char *nom)
{
    struct contact *precedent;
    struct contact *contact_supprime = cherche_contact(*list, nom, &precedent);
    if (contact_supprime == NULL)
    {
        return NULL;
    }
    if (precedent == NULL)  //le cas le contact qu'on cherche est le premier
    {
        *list = contact_supprime->next;        
    }
    else
    {
        precedent->next = contact_supprime->next;  //supprimer le contact au millieu

    }
    contact_supprime->next = NULL;
    return contact_supprime;
}

/*libérer les mémoire d'un contact ou  la liste de contact*/
void free_contact(struct contact *contact){
    free(contact->numero);
    free(contact->nom);
    free(contact);

}
void free_list_contact(struct contact *list)
{
    struct contact *contact_courant = list;
    struct contact *copie = NULL;
    //boucle pour free
    while(contact_courant != NULL){
        copie = contact_courant->next;
        free(contact_courant);
        contact_courant = copie;
    }
}
/*retourner le nom du contact*/
char *recupere_nom(struct contact *contact)
{
    return contact->nom;
}

/*Retourne le numéro du contact.*/
char *recupere_numero(struct contact *contact){
    return contact->numero;
}

/*mettre a jour les contenus d'un contact*/
char *changer_nom(struct contact *contact, const char *name)//mettre a jour le nom d'un contact
{
    char *copie_name = contact->nom;
    char *nom = malloc((strlen(name)+1)*sizeof(*nom));
    strcpy(nom, name);
    contact->nom = nom;
    return copie_name;

}

char *changer_numero(struct contact *contact, const char *num)//mettre a jour le numéro d'un contact
{
    //meme opération pour "numéro"
    char *copie_num = contact->numero;
    char *number = malloc((strlen(num)+1)*sizeof(*number));
    strcpy(number, num);
    contact->numero = number;
    return copie_num;
}

/*pour mettre en couleur*/
void red () {
  printf("\033[1;41m");
}
void rouge() {
  printf("\033[1;31m");
}
void green() {
  printf("\033[1;42m");
}
void cyon(){
  printf("\033[0;33m");
}
void light_blue(){
  printf("\033[0;32m");
}
void sous_ligne(){
  printf("\033[0;4m");
}
void vert(){
    printf("\033[0;32m");
}
void reset() {
  printf("\033[0m");
}

/*afficher la liste*/
void print_list(struct contact *list)
{
    struct contact *contact_courant = list;
    //une boucle pour afficher les contacts
    while (contact_courant != NULL){
        red();    //si marche pas avec votre ordinateur, l'enlever
        printf("NAME\t");
        reset();
        printf(":%21s\t", contact_courant->nom);  //ici %21s permet l'output avoir un bon forma (aligner)
        red();    //si marche pas avec votre ordinateur, l'enlever
        printf("\tNUMERO\t");
        reset();
        printf(":\t%s", contact_courant->numero);
        printf("\n");
        contact_courant = contact_courant->next;
    }
}
