#include "mstring.h"

/**
** @brief               A positive itoa from base.
** @param n             Number.
** @param base          Base number.
** @param decal         Output offset.
** @return              Returns the newly allocated string.
*/
static char             *positive_itoa(int              n,
                                       int              base,
                                       unsigned int     decal)
{
  int                   puiss = 1;
  int                   nb = n;
  int                   len = 0;
  char                  *res = NULL;
  char                  *alphabet;
  unsigned int          i = decal;

  alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";

  while (nb != 0)
  {
    puiss *= base;
    nb /= base;
    len++;
  }
  puiss /= base;

  res = mmalloc(len + decal + 1);

  for (i = decal; i < len + decal; i++)
  {
    res[i] = alphabet[n / puiss];
    n %= puiss;
    puiss /= base;
  }
  res[i] = '\0';

  return (res);
}

char                    *mstring_itoa_base(int          n,
                                           int          base)
{
  char                  *res = NULL;
  unsigned int          decal = 0;
  int                   nb = n;

  if (n <= 0)
  {
    n *= -1;
    decal = 1;
  }

  res = positive_itoa(n, base, decal);

  if (nb == 0)
    res[0] = '0';
  else if (nb < 0)
    res[0] = '-';

  return (res);
}
