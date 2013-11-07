#include "print_ast.h"

void			print_label(s_instr_if			*instr_if,
				    s_instr			*instr,
				    FILE			*fd)
{
  if (NULL == instr_if->list_cond)
    fprintf(fd,
	    "itm%p [label=\"else\" "AST_STYLE_COND"]\n",
	    getptr(instr));
  else
    fprintf(fd,
	    "itm%p [label=\"if\" "AST_STYLE_COND"]\n",
	    getptr(instr));
}

void                    print_instr_if(s_instr                  *instr,
                                       FILE                     *fd)
{
  s_instr_if            *instr_if = NULL;

  if (instr == NULL || instr->instr == NULL)
    return;

  instr_if = instr->instr;

  print_label(instr_if, instr, fd);

  if (instr_if->list_cond)
    fprintf(fd,
	    "itm%p -> itm%p [color=black style=dotted "
	    "label=\"Condition\" fontsize=10]\n",
	    getptr(instr), getptr(instr_if->list_cond));
  fprintf(fd,
          "itm%p -> itm%p [color=green label=\"Success body\" fontsize=10]\n",
          getptr(instr), getptr(instr_if->list_instr_t));

  if (instr_if->instr_f != NULL)
    fprintf(fd,
            "itm%p -> itm%p [color=red label=\"Fail body\" fontsize=10]\n",
            getptr(instr), getptr(instr_if->instr_f));

  print_list_instr(instr_if->list_cond, fd);
  print_list_instr(instr_if->list_instr_t, fd);

  if (instr_if->instr_f != NULL)
    print_instr(instr_if->instr_f, fd);
}
