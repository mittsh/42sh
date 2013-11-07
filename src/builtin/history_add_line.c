#include "../masso/masso.h"
#include "history.h"
#include "../42sh/shell.h"
#include "../masso/masso.h"

/**
** @brief               Gets maximum history length.
** @return              Returns maximum history length.
*/
static inline size_t            get_nbmax_history(void)
{
  char                          *str = NULL;

  if (NULL == (str = getenv("HISTSIZE")))
    if (NULL == (str = masso_get(g_shell->vars, "HISTSIZE")))
      return (500);

  return (atoi(str));
}

/**
** @brief               Truncates history to its maximum length.
** @param hist_q        Input history queue.
** @return              Returns truncated history queue.
*/
static inline s_queue_history   *trunc_history(s_queue_history  *hist_q)
{
  size_t                        i;
  s_hqueue                      *tmp = NULL;
  s_hqueue                      *tmp2 = NULL;
  s_hqueue                      *aux = NULL;

  i = get_nbmax_history() - 1;
  hist_q->len = i + 1;
  tmp = hist_q->last;
  while ((tmp) && (i > 0))
  {
      tmp = tmp->prev;
      i--;
  }

  tmp2 = hist_q->first;
  while (tmp2 != tmp)
  {
      aux = tmp2;
      tmp2 = tmp2->next;
      mfree(aux);
  }

  hist_q->first = tmp2;

  return (hist_q);
}

s_queue_history         *history_add_line(s_queue_history       *hist_q,
                                          char                  *line)
{
  s_hqueue              *aux = NULL;

  hist_q = hist_q == NULL ? mcalloc(1, sizeof (s_queue_history)) : hist_q;

  aux = mcalloc(1, sizeof (s_hqueue));
  aux->element = mstring_copy(line);
  aux->next = aux->prev = NULL;

  if (hist_q->first == NULL)
    hist_q->first = hist_q->last = aux;
  else
  {
    hist_q->last->next = aux;
    aux->prev = hist_q->last;
  }

  hist_q->last = hist_q->cur = aux;
  hist_q->len++;

  if (hist_q->len > get_nbmax_history())
    hist_q = trunc_history(hist_q);

  return (hist_q);
}
