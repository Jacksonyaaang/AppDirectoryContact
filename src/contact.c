#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*le struct d'un contact*/
struct contact{
	char *nom;   //un pointeur qui est vers le nom
	char *numero;
	struct contact *next;
};

//pour créer un nouveau contact
struct contact *genere_contact(const char *name, const char *num)
{
    uint32_t len_nouv_nom = strlen(name);
    char *nouv_nom = malloc((len_nouv_nom+1)*sizeof(*nouv_nom)); 
    //allouer un espace mémoire pour le pointeur nouv_nom, +1 ==> pr \0
    strcpy(nouv_nom, name);  //copier le contenu de name au *nouv_nom

    //faire la meme chose pour la section "numéro"
    uint32_t len_nouv_num = strlen(num);
    char *nouv_num = malloc((len_nouv_num+1)*sizeof(*nouv_num));
    strcpy(nouv_num, num);

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
        return 0;
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
    struct contact *contact_courant = *list; // ici, contact_courant -> &contact
    *list = contact_courant ->next;
    contact_courant->next = NULL;
    return contact_courant;
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
        precedent->next = contact_supprime->next;

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

/*Retourne le numéro du contact passé.*/
char *recupere_numero(struct contact *contact){
    return contact->numero;
}

/*mettre a jour les contenus d'un contact*/
char *changer_nom(struct contact *contact, const char *name)//mettre a jour le nom d'un contact
{
    char *copie_num = contact->numero;
    uint32_t len_nom = strlen(name);
    char *nom = malloc((len_nom+1)*sizeof(*nom));
    strcpy(nom, name);
    contact->nom = nom;
    return copie_num;

}

void *changer_numero(struct contact *contact, const char *num)//mettre a jour le numéro d'un contact
{
    //meme opération pour "numéro"
    uint32_t len_num = strlen(num);
    char *number = malloc((len_num+1)*sizeof(*number));
    strcpy(number, num);
    contact->numero = number;
}

/*afficher la liste*/
void print_list(struct contact *list)
{
    struct contact *contact_courant = list;
    //une boucle pour afficher les contacts
    while (contact_courant != NULL){
        printf("name : %s | number  :  %s\n", contact_courant->nom, contact_courant->numero);
        printf("\n");
        contact_courant = contact_courant->next;
    }
}
