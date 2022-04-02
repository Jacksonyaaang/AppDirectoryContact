#include <stdlib.h>
#include <stdio.h>

#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <directory.h>
#include <contact.h>
#include <hash.h>

struct dir
{
  uint32_t NB_CONTACT; 
  uint32_t TAILLE_TABLE;
  struct contact **annu;
};

/*
  Crée un nouvel annuaire contenant _len_ listes vides (_len_ => TAILLE_TABLE).
*/
struct dir *dir_create(uint32_t len)
{
    (void)len;
    //créer un dir:
    struct dir *dir;
    dir = malloc(sizeof(*dir));
    if (dir == NULL)   //faillure de l'allocation
    {
      printf("allocation échoué \n");
      return NULL;
    }
    struct contact **annu = calloc(len, sizeof(*annu));
    if (annu == NULL)
    {
      printf("allocation échoué \n");
      return NULL;
    }
    green();
    printf("la génération du directory de taille %u --> OK!", len);
    reset();
    printf("\n");
    dir->TAILLE_TABLE = len;
    dir ->NB_CONTACT = 0;
    dir ->annu = annu;
    
    return dir;
}



/*pour redimmensionner la taillle de la table de hash, si nb occupé > 0.75*taille totale , donc on double sa taille totale
si nb occupé < 0.25*taille totale, dc la taile / 2 */

/*pour redimensionner quand l'insertion*/
void redimension_insertion(struct dir *dir)
{
  struct contact *contact_courant;
  struct contact *ancien_list;
  
  if (dir->NB_CONTACT > 0.75*(dir->TAILLE_TABLE)){  //le case de dépassement
    printf("le nombre de contact est dépasse la limite de redimention\n");
    uint32_t nouv_taille_hash = 2*(dir->TAILLE_TABLE);
    printf("donc la nouvelle taille de la directory est :%u\n", nouv_taille_hash);
    /*pour le nouvel annuaire*/
    struct contact **nouv_annu;
    nouv_annu = calloc(nouv_taille_hash, sizeof(*nouv_annu));
    uint32_t i= 0;
    while(i<(dir->TAILLE_TABLE))
    {
      ancien_list = (dir->annu)[i];
      contact_courant = supprime_contact(&ancien_list);
      // parcourir la liste:
      while (contact_courant != NULL)
      {
        char *nom_contact = recupere_nom(contact_courant);
        uint32_t key = hash(nom_contact, nouv_taille_hash);
        struct contact **list_contact = &(nouv_annu[key]);
        insertion_contact(list_contact, contact_courant);
        contact_courant = supprime_contact(&ancien_list);
      }
      i=i+1;
    }
    free(dir->annu);
    dir->annu = nouv_annu;
    dir->TAILLE_TABLE = nouv_taille_hash;
  }
  else return;
}
/*pour redimensionner quand la suppression*/
void redimension_suppression(struct dir *dir)
{
  struct contact *contact_courant;
  struct contact *ancien_list;
  if ((dir->NB_CONTACT<0.15*(dir->TAILLE_TABLE)) && (dir->TAILLE_TABLE > 15))    //taille minimal de cette table est 15
  {

    uint32_t nouv_taille_hash = (dir->TAILLE_TABLE)/2;
    if (dir->TAILLE_TABLE <=15){
      dir->TAILLE_TABLE = 15;
    }  //pour garder la nb de place minimale
    printf("le nombre de contact est moins que 0.15 fois la place totale\n");
    printf("donc la nouvelle taille de la directory est :%u", nouv_taille_hash);
/*pour le nouvel annuaire*/
    struct contact **nouv_annu;
    nouv_annu = calloc(nouv_taille_hash, sizeof(*nouv_annu));
    uint32_t i= 0;
    while(i<(dir->TAILLE_TABLE))
    {
      ancien_list = (dir->annu)[i];
      contact_courant = supprime_contact(&ancien_list);
      // parcourir la liste:
      while (contact_courant != NULL)
      {
        char *nom_contact = recupere_nom(contact_courant);
        uint32_t key = hash(nom_contact, nouv_taille_hash);
        struct contact **list_contact = &(nouv_annu[key]);
        insertion_contact(list_contact, contact_courant);
        contact_courant = supprime_contact(&ancien_list);
      }
      i=i+1;
    }
    free(dir->annu);
    dir->annu = nouv_annu;
    dir->TAILLE_TABLE = nouv_taille_hash;

  }
  else return;

}


/*
  Insère un nouveau contact dans l'annuaire _dir_, construit à partir des nom et
  numéro passés en paramètre. Si il existait déjà un contact du même nom, son
  numéro est remplacé et la fonction retourne une copie de l'ancien numéro.
  Sinon, la fonction retourne NULL.
*/
char *dir_insert(struct dir *dir, const char *name, const char *num)
{

    if (dir == NULL){
      printf("directory est vide \n");
      return 0;
    }
    char *copie_numero = NULL;
    uint32_t key_hash = hash(name, dir->TAILLE_TABLE);

    struct contact **contact_courant = &((dir->annu)[key_hash]);
    struct contact *prece = NULL;
    struct contact *cherche = cherche_contact(*contact_courant, name, &prece);

    if(cherche == NULL)  //si on ne le trouve pas 
    {
      insertion_contact(contact_courant, genere_contact(name, num));
      dir->NB_CONTACT = dir->NB_CONTACT+1;
      redimension_insertion(dir);
      return NULL;

    }
    else{
      printf("il existe, donc le mettre à jours\n");
      copie_numero = changer_numero(cherche, num);
      return copie_numero;

    }

}

/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun contact
  ne correspond, retourne NULL.
*/
const char *dir_lookup_num(struct dir *dir, const char *name)
{
    (void)dir;
    (void)name;
    struct contact *Annu = (dir->annu)[hash(name, dir->TAILLE_TABLE)];
    struct contact *prece = NULL;
    struct contact *cherche = cherche_contact(Annu, name, &prece);

  /*Si aucun contactne correspond, retourne NULL.*/ 
  if (cherche == NULL){
    return NULL;
  }   
  return recupere_numero(cherche);
}

/*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
void dir_delete(struct dir *dir, const char *name)
{
    (void)dir;
    (void)name;
    uint32_t nb_place_occupe = dir->NB_CONTACT;
    struct contact **liste_contact = &((dir->annu)[hash(name, dir->TAILLE_TABLE)]);
    struct contact *contact_courant = supprime_liste(liste_contact, name);
    if (contact_courant ==NULL){
      rouge();
      printf("Dézolé, le nom « %s » n'existe pas sur ce contact, veillez d'abord l'ajouter.\nDonc afficher l'ancien director:", name);
      reset();
      return;
    }
    else{
      free_contact(contact_courant);
      dir->NB_CONTACT = nb_place_occupe -1;
      redimension_suppression(dir);
      vert();
      printf("\n\n« %s » a été supprimé sur ce directory!\n\n", name);
      reset();
    }
}

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
void dir_free(struct dir *dir)
{
    (void)dir;
    uint32_t j = 0;
    while (j<dir->TAILLE_TABLE)
    {
      free_list_contact((dir->annu)[j]);
      j = j+1;
    }
    if (dir != NULL)
    {
      free(dir->annu);
      free(dir);
      dir = NULL;   //pour évider l'erreur de "Segment fault " (pointeur vide)
      if (dir == NULL)
      {
        vert();
        printf("free complited!!\n");
        reset();
      }
    }
    
}

/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
void dir_print(struct dir *dir)
{
    (void)dir;
  printf("\n\n\n___________________________");
  sous_ligne();
  printf("MON_Annuaire");
  reset();
  printf("_______________________________\n\n");
	uint32_t i =0;
  while (i<dir->TAILLE_TABLE)
  {
    print_list((dir->annu)[i]);
    i=i+1;
  }
  printf("_____________________________");
  sous_ligne();
  printf("FIN_Annu");
  reset();
  printf("_________________________________\n\n\n\n");
}
