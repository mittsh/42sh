#ifndef HISTORY_H_
# define HISTORY_H_

# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct          hqueue
{
  char                  *element;
  struct hqueue         *next;
  struct hqueue         *prev;
}                       s_hqueue;

typedef struct          queue_history
{
  s_hqueue              *first;
  s_hqueue              *last;
  s_hqueue              *cur;
  size_t                len;
}                       s_queue_history;

/**
** @brief               Function load history from ~/.42sh_history
** @return              A s_queue_history containing the history
*/
s_queue_history         *history_load(void);

/**
** @brief               Save the history in the file ~/.42sh_history
** @param[in] hist_q    The history save.
** @return              void
*/
void                    history_save(s_queue_history            *hist_q);

/**
** @brief               Add a line in the structure history @a hist_q
** @param hist_q        The history where the @a line is add.
** @param[in] line      The line add in the @a hist_q
** @return              void
*/
s_queue_history         *history_add_line(s_queue_history       *hist_q,
                                          char                  *line);

/**
** @brief               This function get the current line of history
** @param               hist_q
** @return              Returns the current line of the history @a hist_q
*/
char                    *history_current(s_queue_history        *hist_q);

/**
** @brief               Shift the current line of history to next.
** @param hist_q        The history to shift current
** @return              void
*/
int                     history_next(s_queue_history            *hist_q);

/**
** @brief               Shift the current line of history to prev.
** @param hist_q        The history to shift current
** @return              void
*/
int                     history_prev(s_queue_history            *hist_q);

/**
** @brief               Updates the current history line from input string.
** @param hist_q        Target input history queue.
** @param str           Input string.
** @return              void
*/
void                    history_update(s_queue_history          *hist_q,
                                       char                     *str);

/**
** @brief               Frees the @a hist_q
** @return              void
*/
void                    free_history_queue(s_queue_history      *hist_q);

#endif /* !HISTORY_H_ */
