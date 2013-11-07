#ifndef LIST_DUP_H_
# define LIST_DUP_H_

/**
** @brief               File descriptor duplication list.
**                      Usefull for pipes and redirections.
** @param fd_in         Input file descriptor.
** @param fd_out        Output file descriptor.
** @param next          Next list item. NULL for last element of list.
*/
typedef struct          list_dup
{
  int                   fd_in;
  int                   fd_out;
  struct list_dup       *next;
}                       s_list_dup;

/**
** @brief               Insert a new file descriptor duplicator in a list.
** @param list_dup      Input list.
** @param fd_in         Input file descriptor.
** @param fd_out        Output file descriptor.
** @return              Returns the new file descriptor list.
*/
s_list_dup              *list_dup_insert(s_list_dup             *list_dup,
                                         int                    fd_in,
                                         int                    fd_out);

/**
** @brief               Frees a file descriptor duplication list.
** @param list_dup      Target file descriptor duplication list.
** @return              void
*/
void                    list_dup_free(s_list_dup                *list_dup);

#endif /* !LIST_DUP_H_ */
