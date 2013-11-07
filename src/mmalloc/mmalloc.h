#ifndef MMALLOC_H_
# define MMALLOC_H_

# include <unistd.h>

/**
** @brief               Represents a memory allocation.
** @param ptr           Data pointer.
** @param prev          Previous allocation.
** @param next          Next allocation.
*/
typedef struct          mmalloc
{
  void                  *ptr;
  struct mmalloc        *prev;
  struct mmalloc        *next;
}                       s_mmalloc;

/**
** @brief               Represents a memory heap.
** @param first         First allocated block.
** @param last          Last allocated block.
*/
typedef struct          mmalloc_mem
{
  s_mmalloc             *first;
  s_mmalloc             *last;
}                       s_mmalloc_mem;

/**
** @brief               Initialises memory heap manager.
** @return              Returns 1 in case of success.
*/
int                     mmalloc_init(void);

/**
** @brief               Creates a new allocation.
** @param size          Allocation size.
** @return              Returns allocation pointer.
*/
void                    *mmalloc(size_t                         size);

/**
** @brief               Reallocate a new allocation.
** @param ptr           Old allocated pointer.
** @param size          Allocation size.
** @return              Returns allocation pointer.
*/
void                    *mrealloc(void                          *ptr,
                                  size_t                        size);

/**
** @brief               Creates a new allocation, sets all values to 0.
** @param count         Number of data of size 'size'
** @param size          Allocation size.
** @return              Returns allocation pointer.
*/
void                    *mcalloc(size_t                         count,
                                 size_t                         size);

/**
** @brief               Frees an allocation
** @param ptr           Input pointer.
** @return              Returns 1 in case of success.
*/
int                     mfree(void                              *ptr);

/**
** @brief               Frees all the managed heap.
** @return              Returns 1 in case of success.
*/
int                     mmalloc_free(void);

/**
** @brief               Show debug informations
** @return              Returns 1 in case of success.
*/
int                     mmalloc_debug(void);

# include "../42sh/shell.h"

#endif /* !MMALLOC_H_ */
