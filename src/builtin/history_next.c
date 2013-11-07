#include <stdlib.h>
#include "history.h"

int                     history_next(s_queue_history            *hist_q)
{
  if (NULL == hist_q)
    return (0);

  if (hist_q->cur != NULL && hist_q->cur->next != NULL)
  {
    hist_q->cur = hist_q->cur->next;
    return (1);
  }
  else
    return (0);
}
