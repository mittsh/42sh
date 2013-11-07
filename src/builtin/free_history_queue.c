#include <unistd.h>
#include <stdlib.h>
#include "history.h"

#include "../mmalloc/mmalloc.h"

void            free_history_queue(s_queue_history      *hist_q)
{
  s_hqueue      *tmp = NULL;
  s_hqueue      *aux = NULL;

  if (hist_q)
  {
    tmp = hist_q->first;
    while (tmp)
    {
      mfree(tmp->element);
      aux = tmp;
      tmp = tmp->next;
      mfree(aux);
    }
    mfree(hist_q);
  }
}
