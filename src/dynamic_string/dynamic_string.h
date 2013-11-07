#ifndef DYNAMIC_STRING_H_
# define DYNAMIC_STRING_H_

# include <unistd.h>
# include <stdlib.h>
# include "../mmalloc/mmalloc.h"

/**
** @brief               Representsa dynamic string.
** @param str           Dynamic string buffer.
** @param len           Current string length (excluding end null character)
** @param max_len       Maximum buffer size.
*/
typedef struct          dynamic_string
{
  char                  *str;
  int                   len;
  int                   max_len;
}                       s_dynamic_string;

/**
** @brief               Initialises a dynamic string.
** @return              Returns dynamic string pointer.
*/
s_dynamic_string        *dynamic_string_init(void);

/**
** @brief               Gets dynamic string buffer string.
** @param dynstr        Input dynamic string.
** @return              Returns buffer string.
*/
char                    *dynamic_string_getstr(s_dynamic_string *dynstr);

/**
** @brief               Resizes a dynamic string.
** @param dynstr        Input dynamic string.
** @return              void
*/
void                    dynamic_string_resize(s_dynamic_string  *dynstr);

/**
** @brief               Adds a character on the end of the string.
** @param dynstr        Input dynamic string.
** @param c             Input character.
** @return              void
*/
void                    dynamic_string_push(s_dynamic_string    *dynstr,
                                            char                c);

/**
** @brief               Adds a string on the end of the string.
** @param dynstr        Input dynamic string.
** @param str           Input string.
** @return              void
*/
void                    dynamic_string_pushs(s_dynamic_string   *dynstr,
                                             char               *str);

/**
** @brief               Removes the last character.
** @param dynstr        Input dynamic string.
** @return              void
*/
void                    dynamic_string_pop(s_dynamic_string     *dynstr);

/**
** @brief               Adds a character on a specific position.
** @param dynstr        Input dynamic string.
** @param c             Input character.
** @param pos           Target position.
** @return              void
*/
void                    dynamic_string_insert(s_dynamic_string  *dynstr,
                                              char              c,
                                              int               pos);

/**
** @brief               Removes a character from a specific position.
** @param dynstr        Input dynamic string.
** @param pos           Target position.
*/
void                    dynamic_string_remove(s_dynamic_string  *dynstr,
                                              int               pos);

/**
** @brief               Cleans up a dynamic string.
** @param dynstr        Input dynamic string.
** @return              void
*/
void                    dynamic_string_renew(s_dynamic_string   *dynstr);

/**
** @brief               Frees a dynamic string, including its structure.
** @param dynstr        Input dynamic string.
** @return              void
*/
void                    dynamic_string_free(s_dynamic_string    *dynstr);

#endif /* !DYNAMIC_STRING_H_ */
