#include <string.h>
#include "print_ast.h"

#define CASE_REDIR_TYPE(Type, String)                   \
  case AST_REDIR_ ## Type:                              \
    return (String);					\
    break

char                    *print_instr_redir_type(e_redir_type    type)
{
  switch (type)
  {
      CASE_REDIR_TYPE(OUT_TRUNC, ">");
      CASE_REDIR_TYPE(OUT_APPEND, ">>");
      CASE_REDIR_TYPE(OUTPUT_DUP, ">&");
      CASE_REDIR_TYPE(INPUT, "<");
      CASE_REDIR_TYPE(INPUT_DUP, "<&");
      CASE_REDIR_TYPE(HERE_DOC, "<<");
      CASE_REDIR_TYPE(RDWR, "<>");
      default:
        break;
  }

  return ("");
}

void                    print_instr_redir(s_instr               *instr,
                                          FILE                  *fd)
{
  s_instr_redir         *instr_redir = NULL;
  s_list_redir          *list_redir = NULL;

  if (instr == NULL || instr->instr == NULL)
    return;

  instr_redir = instr->instr;

  fprintf(fd, "itm%p [label=\"Redirection\" "AST_STYLE_REDIRECTION"]\n",
          getptr(instr));

  fprintf(fd, "itm%p -> itm%p\n", getptr(instr),
          getptr(instr_redir->instr));
  print_instr(instr_redir->instr, fd);

  list_redir = instr_redir->list_redir;
  for (; list_redir != NULL; list_redir = list_redir->next)
  {
      if (!list_redir->ionumber)
	list_redir->ionumber = mstring_copy("0");
      fprintf(fd, "itm%p -> itm%p\n", getptr(instr),
	      getptr(list_redir));
      fprintf(fd,
	      "itm%p [label=\"%s%s%s\"]\n",
	      getptr(list_redir),
	      list_redir->ionumber,
	      print_instr_redir_type(list_redir->type),
	      list_redir->word);
  }
}
