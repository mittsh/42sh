#ifndef MASSO_H_
# define MASSO_H_

# include <stdlib.h>
# include <unistd.h>

/**
** @brief               Sets the init size of the array, then the array will
**                      be reallocated by a factor 2.
*/
# define MASSO_DEFAULT_SIZE 4

/**
** @brief               Represents an associative array data.
** @param key           String key.
** @param value         Value pointer.
*/
typedef struct          masso_data
{
    char                *key;
    void                *value;
}                       s_masso_data;

/**
** @brief               Represents an associative array.
** @param array         An array of all pointers to all data.
** @param size          Size of the array.
** @param max_size      The maximum size of the array (i.e. the allocated
**                      size).
*/
typedef struct          masso
{
    s_masso_data        *array;
    int                 size;
    int                 max_size;
}                       s_masso;

/**
** @brief               Inits a new associative array.
** @param               void
** @return              Returns the pointer of this array.
*/
s_masso                 *masso_init(void);

/**
** @brief               Adds a new element in an associative array.
** @param asso          Target associative array.
** @param key           Key of the data : this string will be copied.
** @param value         The data value : this pointer has to be allocated.
**                      Not any copy will be made.
** @return              Returns the position of this data in the array.
*/
int                     masso_add(s_masso       *asso,
                                  char          *key,
                                  void          *value);

/**
** @brief               Sets a new element in an associative array.
**                      If element with key dosen't exist, it's added, else
**                      value is changed.
**                      Warning ! The old value is freed, without any check.
** @param asso          Target associative array.
** @param key           Key of the data : this string will be copied.
** @param value         The data value : this pointer has to be allocated.
**                      Not any copy will be made.
** @return              Returns the position of this data in the array.
*/
int                     masso_set(s_masso       *asso,
                                  char          *key,
                                  void          *value);

/**
** @brief               Gets the value witch has key 'key' in 'asso'.
** @param asso          Target associative array.
** @param key           Key to get the value.
** @return              Returns the pointer over the value.
*/
void                    *masso_get(s_masso      *asso,
                                   char         *key);

/**
** @brief               Gets the n-th value of the associative array 'asso'.
** @param asso          Target associative array.
** @param n             Position of the data value to get.
** @return              Returns the pointer over the value or NULL if key is
**                      not found.
*/
void                    *masso_getn(s_masso     *asso,
                                    int         n);
/**
** @brief               Gets the n-th key of the associative array 'asso'.
** @param asso          Target associative array.
** @param n             Position of the data key to get.
** @return              Returns the pointer over the key.
*/
char                    *masso_getn_key(s_masso *asso,
                                        int     n);

/**
** @brief               Frees the associative array. Warning : possible memory
**                      leaks due to not free of the value. Use masso_freep.
** @param asso          Target associative array.
** @return              void
*/
void                    masso_free(s_masso      *asso);

/**
** @brief               Frees the associative array with a callback function.
** @param asso          Target associative array.
** @param cb            Function pointer to free value.
** @return              void
*/
void                    masso_freep(s_masso     *asso,
                                    void        (*cb)());

/**
** @brief               Unlinks the value witch has key 'key' in 'asso'.
** @param asso          Target associative array.
** @param key           Key to unlink to the value.
** @return              void
*/
void                    masso_unlink(s_masso    *asso,
                                     char       *key);

/**
** @brief               Lists keys.
** @param asso          Target associative array.
** @param printer       Function pointer to print value.
*/
void                    masso_list_keys(s_masso *asso,
                                        void    (*printer)());

# include "../mstring/mstring.h"
# include "../mmalloc/mmalloc.h"

#endif /* !MASSO_H_ */
