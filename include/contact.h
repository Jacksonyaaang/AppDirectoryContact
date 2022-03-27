#ifndef _CONTACT_H_
#define _CONTACT_H_

/*
  Un contact représente une association {nom, numéro}.
*/
struct contact; /*son contenu est dans contact.c*/

//pour créer un nouveau contact
extern struct contact *genere_contact(const char *name, const char *num);

/*faire une insertion par un nouveau contact "c" dans la liste*/
extern void insertion_contact(struct contact **list, struct contact *contact);

/*supprimer le contact qu'on veut, si il exist pas , retourne null*/
extern struct contact *supprime_liste(struct contact **list, const char *nom);

/*supprimer le tête de la liste de contactet retourner lequel supprimé*/
extern struct contact *supprime_contact(struct contact **list);

/*cherche un contact dans la liste*/
extern struct contact *cherche_contact(struct contact *list, const char *name, struct contact **precedent);


/*libérer les mémoire d'un contact ou  la liste de contact*/
extern void free_contact(struct contact *contact);
extern void free_list_contact(struct contact *list);

/*afficher la liste*/
extern void print_list(struct contact *list);


/*mettre a jour les contenud d'un contact*/

extern void *changer_nom(struct contact *contact, const char *name);//mettre a jour le nom d'un contact

extern void *changer_numero(struct contact *contact, const char *num);//mettre a jour le numéro d'un contact



#endif /* _CONTACT_H_ */
