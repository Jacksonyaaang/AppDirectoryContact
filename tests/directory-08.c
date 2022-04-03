/*
  Test du module directory.

  Teste le rétrécissement du directory.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <contact.h>

int main(void)
{ 
    
    struct contact *contact_test = genere_contact("jackson yang", "0766236988");
    printf("\ngénérer un contact et l'afficher:\n");
    print_list(contact_test);
    printf("\nmaintenant ajouter quelques contact et l'afficher:\n");
    char *tab_name[10] = {"Liam", "Noah", "Oliver", "Elijah", "William", "James", "Benjamin", "Lucas", "Henry", "Alexander"};
    char *tab_number[10] = {"3757692234", "33757690986", "757691141", "757691199", "757693000", "33757690885", "757690930", "757690856", "757691034", "757690964"};
    for (uint32_t i = 0; i <10; i++) {
        struct contact *ok =genere_contact(tab_name[i], tab_number[i]);
        insertion_contact(&contact_test, ok);
    }
    print_list(contact_test);
    printf("\n******************************************************************************************\n");
    printf("\n\nmaintenant on teste la supression: (on supprime 8 premier contact et afficher étape par étape) \n");
    for (uint32_t j=0;j<8;j++){
      printf("\n\nla %u ière supression:\n", j+1);
      supprime_contact(&contact_test);
      print_list(contact_test);
    }
    printf("\n******************************************************************************************\n");
    printf("\n\nmaintenant on fait un cherche sur cette liste de contact: (on cherche 'jackson yang'et afficher son numéro )\n\n");
    struct contact *prece = NULL;
    struct contact *res_contact = cherche_contact(contact_test, "jackson yang", &prece);
    char *res_numero = recupere_numero(res_contact);
    printf("\ndonc le numéro de 'jackson yang' est %s\n", res_numero);
    printf("\n\nmaintenant on free le list:\n");
    free_list_contact(contact_test);
    printf("on l'affiche pour tester:\n");
    print_list(contact_test);
    green();
    printf("OK! le mémoire c'était free, \net la raison que vous voyez encore les affichage, car j'ai free le mémoire, mais le pointeur les référence encore");
    reset();
    printf("\n");
    return EXIT_SUCCESS;
}
