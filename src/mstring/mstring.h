#ifndef MSTRING_H_
# define MSTRING_H_

# include <stdlib.h>
# include <unistd.h>
# include "../mmalloc/mmalloc.h"

/**
** @brief               Calculates the length of a string.
** @param str           Target string.
** @return              Returns the string length.
*/
int                     mstring_len(char                *str);

/**
** @brief               Compares two strings.
** @param str1          First string to compare.
** @param str2          Second string to compare.
** @return              Returns 1 if two string are equals (all chars are
**                      the same and have the same length), 0 if not.
*/
int                     mstring_compare(char            *str1,
                                        char            *str2);

/**
** @brief               Copies a string in a newly allocated one.
** @param str           Input string.
** @return              Pointer over the copy of str, which have been
**                      allocated.
*/
char                    *mstring_copy(char              *str);

/**
** @brief               Creates a new string from two char* pointers. It
**                      means, a new allocation will be done which containes
**                      the substring begining on begin and ending on end.
** @param begin         Marks the begin of the string.
** @param end           Marks the end of the string. The copy will stop just
**                      before end (i.e. *end will be not copied).
** @return              Newly allocated string wich size is (end - begin).
*/
char                    *mstring_fromflags(char         *begin,
                                           char         *end);

/**
** @brief               Prints a string on standard output.
** @param str           Input string.
** @return              void
*/
void                    mstring_print(char              *str);

/**
** @brief               Prints a string on standard error output.
** @param str           Input string.
** @return              void
*/
void                    mstring_print_error(char        *str);

/**
** @brief               Prints an integer on standard output.
** @param i             Input integer.
** @return              void
*/
void                    mstring_print_int(int           i);

/**
** @brief               Checks if string str contains char c.
** @param str           Input string.
** @param c             Input char to check if is in string.
** @return              Returns 1 in case of success, 0 if not.
*/
int                     mstring_haschar(char            *str,
                                        char            c);

/**
** @brief               An atoi function : converts a string into an integer.
**                      Warning ! This function only supports POSITIVE
**                      INTEGERS.
** @param str           Input string which represents a positive integer.
** @return              Integer represented by input string.
*/
int                     mstring_atoi(char               *str);

/**
** @brief               An itoa function which supports any base to 36.
**                      It supports also null and negative integers.
** @param n             Input integer.
** @param base          Base to output.
** @return              Returns a newly allocated string which represents
**                      integer n in base base.
*/
char                    *mstring_itoa_base(int          n,
                                           int          base);

/**
** @brief               An itoa function which supports null and negative
**                      integer.
** @param n             Input integer.
** @return              Returns a newly allocated string which represents
**                      integer n in base 10.
*/
char                    *mstring_itoa(int               n);

#endif /* !MSTRING_H_ */
