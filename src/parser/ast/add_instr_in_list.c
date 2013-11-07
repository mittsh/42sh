/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/

#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"

s_list_instr            *add_instr_in_list(s_list_instr         *list,
                                           s_instr              *instr,
                                           bool                 bg)
{
  s_list_instr_item     *aux = NULL;

  if (NULL == instr)
    return (NULL);

  if (NULL == list)
    list = build_list_instr();

  aux = list->last;
  list->last = build_list_instr_item(instr, NULL, bg);

  if (aux)
    aux->next = list->last;

  if (NULL == list->first)
    list->first = list->last;

  return (list);
}

