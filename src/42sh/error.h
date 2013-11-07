#ifndef ERROR_H_
# define ERROR_H_

/**
** @brief               42sh error : none.
*/
# define ERROR_NONE 0

/**
** @brief               42sh error : execution error.
*/
# define ERROR_EXEC -1

/**
** @brief               42sh error : parsing error.
*/
# define ERROR_PARSER -2

/**
** @brief               42sh error : lexer error.
*/
# define ERROR_LEXER -3

/**
** @brief               42sh error : arithmetic evaluation error.
*/
# define ERROR_EVALEXPR -4

/**
** @brief               42sh error : permission denied.
*/
# define ERROR_PERMISSION_DENIED -5

#endif /* !ERROR_H_ */
