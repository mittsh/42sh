#include <stdlib.h>
#include "history.h"

int                     history_prev(s_queue_history            *hist_q)
{
  if (NULL == hist_q)
    return (0);

  if (hist_q->cur != NULL && hist_q->cur->prev != NULL)
  {
    hist_q->cur = hist_q->cur->prev;
    return (1);
  }
  else
    return (0);
}
