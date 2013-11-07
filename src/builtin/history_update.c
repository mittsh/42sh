#include "history.h"

#include "../mmalloc/mmalloc.h"

void                    history_update(s_queue_history          *hist_q,
                                       char                     *str)
{
  s_hqueue              *cur = NULL;

  cur = hist_q->cur;

  mfree(cur->element);
  cur->element = mstring_copy(str);
}
