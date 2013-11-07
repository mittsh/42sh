/**
** @author maarek_j
** @date Thu Nov 11 15:46:55 2010
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "../ast.h"

s_list_c_items          *add_item_in_list_items(s_list_c_items  *list_c_items,
                                                s_list_words    *list_words,
                                                s_list_instr    *list_instr)
{
  s_list_c_items        *aux = list_c_items;
  s_list_c_items        *par = aux;

  aux = mcalloc(1, sizeof (s_list_c_items));
  aux->next = NULL;
  aux->list_instr = list_instr;
  aux->list_words = list_words;

  if (list_c_items == NULL)
    return (aux);

  par = list_c_items;
  while (par->next != NULL)
    par = par->next;

  par->next = aux;

  return (list_c_items);
}

void                    free_list_c_items(s_list_c_items        *elmt)
{
  if (elmt)
  {
      free_list_words(elmt->list_words);
      free_list_instr(elmt->list_instr);
      free_list_c_items(elmt->next);
  }
}

