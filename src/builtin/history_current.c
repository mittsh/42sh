#include <stdlib.h>
#include "history.h"

char                    *history_current(s_queue_history        *hist_q)
{
  s_hqueue              *aux = NULL;

  if (NULL == hist_q)
    return (NULL);

  aux = hist_q->cur;
  if (NULL == aux)
    aux = hist_q->last;

  return (aux->element);
}
