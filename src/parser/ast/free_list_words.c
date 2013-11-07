/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/

#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"

void                    free_list_words(s_list_words            *elmt)
{
  if (NULL != elmt)
  {
      free_list_words(elmt->next);
      mfree(elmt->word);
      mfree(elmt);
  }
}
