/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/

#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"

void                    free_list_redir(s_list_redir            *elmt)
{
  if (NULL != elmt)
  {
      if (elmt->next)
        free_list_redir(elmt->next);
      if (elmt->word)
        mfree(elmt->word);
      if (elmt->ionumber)
        mfree(elmt->ionumber);

      mfree(elmt);
  }
}
