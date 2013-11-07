#ifndef AST_H_
# define AST_H_

/**
** @file                        ast.h
** @brief                       This file contains the types and
**                              function about AST.
** @author                      maarek_j and lanoe_j
*/

# include <stdbool.h>

/**
** @enum                        e_instr_type
** @brief                       Enumeration on the type of instrutions
** @param                       AST_INSTR_AND,
** @param                       AST_INSTR_OR,
** @param                       AST_INSTR_NOT,
** @param                       AST_INSTR_BRACK,
** @param                       AST_INSTR_PAREN,
** @param                       AST_INSTR_PIPE,
** @param                       AST_INSTR_REDIR,
** @param                       AST_INSTR_FUNC,
** @param                       AST_INSTR_IF,
** @param                       AST_INSTR_FOR,
** @param                       AST_INSTR_WHILE,
** @param                       AST_INSTR_UNTIL,
** @param                       AST_INSTR_CASE,
** @param                       AST_INSTR_CMD
*/
typedef enum                    e_instr_type
{
  AST_INSTR_AND,
  AST_INSTR_OR,
  AST_INSTR_NOT,
  AST_INSTR_BRACK,
  AST_INSTR_PAREN,
  AST_INSTR_PIPE,
  AST_INSTR_REDIR,
  AST_INSTR_FUNC,
  AST_INSTR_IF,
  AST_INSTR_FOR,
  AST_INSTR_WHILE,
  AST_INSTR_UNTIL,
  AST_INSTR_CASE,
  AST_INSTR_CMD
}                               e_instr_type;

/**
** @struct                      s_instr
** @brief                       An instruction is:
*/
typedef struct                  s_instr
{
  e_instr_type                  type;
  void                          *instr;
  bool                          can_free;
}                               s_instr;

/**
** @struct                      s_list_instr_item.
** @brief                       list instruction of items.
*/
typedef struct                  s_list_instr_item
{
  s_instr                       *elmt;
  struct s_list_instr_item      *next;
  bool                          bg;
}                               s_list_instr_item;

/**
** @struct                      s_list_instr
** @brief                       List of instruction
*/
typedef struct                  s_list_instr
{
  s_list_instr_item             *first;
  s_list_instr_item             *last;
}                               s_list_instr;

/**
** @typedef                     t_ast
** @brief                       Alias on type s_list_instr
*/
typedef s_list_instr            t_ast;

/**
** @struct                      s_instr_and
** @brief                       Structure for the AND instruction.
** @param instr_l               Left instruction.
** @param instr_r               Right instruction.
*/
typedef struct                  s_instr_and
{
  s_instr                       *instr_l;
  s_instr                       *instr_r;
}                               s_instr_and;

/**
** @struct                      s_instr_or
** @brief                       Structure for the OR instruction.
** @param instr_l               Left instruction.
** @param instr_r               Right instruction.
*/
typedef struct                  s_instr_or
{
  s_instr                       *instr_l;
  s_instr                       *instr_r;
}                               s_instr_or;

/**
** @struct                      s_instr_not
** @brief                       Structure for the NOT instruction.
** @param instr                 The NOT instruction.
*/
typedef struct                  s_instr_not
{
  s_instr                       *instr;
}                               s_instr_not;

/**
** @struct                      s_instr_pipe
** @brief                       Structure for the PIPE instruction
** @param list_instr            The list of PIPE instructions.
*/
typedef struct                  s_instr_pipe
{
  s_list_instr                  *list_instr;
}                               s_instr_pipe;

/**
** @struct                      s_instr_paren
** @brief                       ?
** @param instr                 ?
*/
typedef struct                  s_instr_paren
{
  s_list_instr                  *list_instr;
}                               s_instr_paren;

/**
** @struct                      s_instr_brack
** @brief                       Structure for the BRACKET instruction.
** @param list_instr            The list of BRACKET instructions.
*/
typedef struct                  s_instr_brack
{
  s_list_instr                  *list_instr;
}                               s_instr_brack;

/**
** @struct                      s_instr_redir
** @brief                       Structure for the REDIRECTION instruction.
** @param instr                 The list of BRACKET instructions.
*/
typedef struct                  s_instr_redir
{
  s_instr                       *instr;
  struct s_list_redir           *list_redir;
}                               s_instr_redir;

/**
** @struct                      s_instr_func
** @brief                       Structure for the FUNCTION instruction.
** @param name                  The function's name.
** @param instr                 The list of the FUNCTION instructions.
*/
typedef struct                  s_instr_func
{
  char                          *name;
  s_list_instr                  *list_instr;
}                               s_instr_func;

/**
** @struct                      s_instr_if
** @brief                       Structure for the IF instruction.
** @param list_cond             The IF condition.
** @param list_instr_t          The instructions of the IF instruction.
*/
typedef struct                  s_instr_if
{
  s_list_instr                  *list_cond;
  s_list_instr                  *list_instr_t;
  s_instr                       *instr_f;
}                               s_instr_if;

/**
** @struct                      s_list_words
** @brief                       List list of words
** @param word                  The current word.
** @param next                  The next word.
*/
typedef struct                  s_list_words
{
  char                          *word;
  struct s_list_words           *next;
}                               s_list_words;

/**
** @struct                      s_list_for
** @brief                       Structure of the FOR instruction.
** @param list_words            A linked list of words of the FOR conditions.
** @param list_instr            The instructions of the FOR instructions.
*/
typedef struct                  s_instr_for
{
  char                          *var_name;
  s_list_words                  *list_words;
  s_list_instr                  *list_instr;
}                               s_instr_for;

/**
** @struct                      s_list_while
** @brief                       Structure of the WHILE instructon.
** @param list_cond             The WHILE condition.
** @param list_instr            The instructons of the WHILE instructon.
*/
typedef struct                  s_instr_while
{
  s_list_instr                  *list_cond;
  s_list_instr                  *list_instr;
}                               s_instr_while;

/**
** @struct                      s_instr_until
** @brief                       Structure of the UNTIL condition.
** @param list_cond             The UNTIL condition.
** @param list_instr            The instructons of the UNTIL instructon.
*/
typedef struct                  s_instr_until
{
  s_list_instr                  *list_cond;
  s_list_instr                  *list_instr;
}                               s_instr_until;

/**
** @struct                      s_list_c_items
** @brief                       Structure of the CASE ITEM instructon.
** @param list_words            A list of words matching the case.
** @param list_instr            The instructons executed if a word is matched.
** @param next                  The next group of words mathcing a case.
*/
typedef struct                  s_list_c_items
{
  s_list_words                  *list_words;
  s_list_instr                  *list_instr;
  struct s_list_c_items         *next;
}                               s_list_c_items;

/**
** @struct                      s_list_case
** @brief                       Structure of the CASE instruction.
** @param word                  The word for which we check the values.
** @param list_c_items          The CASE ITEMS to execute for that word.
*/
typedef struct                  s_instr_case
{
  char                          *word;
  s_list_c_items                *list_c_items;
}                               s_instr_case;

/**
** @struct                      s_instr_cmd
** @brief                       Structure of the COMMAND instruction.
** @param list_words            A linked list of words.
*/
typedef struct                  s_instr_cmd
{
  s_list_words                  *list_words;
}                               s_instr_cmd;

/**
** @enum                        e_redir_type
** @brief                       Enumeration of the possible redirections.
** @param AST_REDIR_OUT_TRUNC   [n] > WORD
** @param AST_REDIR_OUT_APPEND  [n] >> WORD
** @param AST_REDIR_OUTPUT_DUP  [n] >& WORD
** @param AST_REDIR_INPUT       [n] < WORD
** @param AST_REDIR_INPUT_DUP   [n] <& WORD
** @param AST_REDIR_HERE_DOC    [n] << W
** @param AST_REDIR_RDWR        [n] <> WORD
*/
typedef enum                    e_redir_type
{
  AST_REDIR_OUT_TRUNC,
  AST_REDIR_OUT_APPEND,
  AST_REDIR_OUTPUT_DUP,
  AST_REDIR_INPUT,
  AST_REDIR_INPUT_DUP,
  AST_REDIR_HERE_DOC,
  AST_REDIR_RDWR,
}                               e_redir_type;

/**
** @brief               Redirection list.
** @param type          Redirection type.
** @param ionumber      Input/output number.
** @param word          Target filename or simple word.
** @param next          Next redirection item.
*/
typedef struct                  s_list_redir
{
  e_redir_type                  type;
  char                          *ionumber;
  char                          *word;
  struct s_list_redir           *next;
}                               s_list_redir;

/**
** @brief               Build a new instruction list.
** @return              Returns new instruction list.
*/
s_list_instr            *build_list_instr(void);

/**
** @brief               Adds a new instruction on the list.
** @param list          Input list
** @param instr         Input instruction
** @param bg            Is true when instruction is to execute on background.
** @return              Returns new instruction list.
*/
s_list_instr            *add_instr_in_list(s_list_instr         *list,
                                           s_instr              *instr,
                                           bool                 bg);

/**
** @brief               Adds a new instruction item.
** @param elmt          Instruction element.
** @param next          Next instruction on the list.
** @param bg            Is true when instruction is to execute on background.
** @return              Returns the new list item.
*/
s_list_instr_item       *build_list_instr_item(s_instr                  *elmt,
                                               s_list_instr_item        *next,
                                               bool                     bg);

/**
** @brief               Builts a new instruction.
** @param type          Instruction type.
** @param instr         Input instruction content.
** @return              Returns new instruction.
*/
s_instr                 *build_instr(e_instr_type               type,
                                     void                       *instr);

/**
** @brief               Builts an AND node.
** @param instr_l       Left side instruction.
** @param instr_r       Right side instruction.
** @return              Returns an and node.
*/
s_instr_and             *build_instr_and(s_instr                *instr_l,
                                         s_instr                *instr_r);

/**
** @brief               Builts an OR node.
** @param instr_l       Left side instruction.
** @param instr_r       Right side instruction.
** @return              Returns an or node.
*/
s_instr_or              *build_instr_or(s_instr                 *instr_l,
                                        s_instr                 *instr_r);

/**
** @brief               Builts an NOT node.
** @param instr         Down side instruction.
** @return              Returns an not node.
*/
s_instr_not             *build_instr_not(s_instr                *instr);

/**
** @brief               Builts a pipe node from instruction list.
** @param list_instr    Input instruction list.
** @return              Returns pipe node.
*/
s_instr_pipe            *build_instr_pipe(s_list_instr          *list_instr);

/**
** @brief               Builts a parenthesis node from instruction list.
** @param list_instr    Input instruction list.
** @return              Returns parenthesis node.
*/
s_instr_paren           *build_instr_paren(s_list_instr         *list_instr);

/**
** @brief               Builts a bracket node from instruction list.
** @param list_instr    Input instruction list.
** @return              Returns bracket node.
*/
s_instr_brack           *build_instr_brack(s_list_instr         *list_instr);

/**
** @brief               Build instruction redirection.
** @param instr         Input instruction.
** @param list_redir    Input redirections list.
** @return              Returns a redirection node.
*/
s_instr_redir           *build_instr_redir(s_instr              *instr,
                                           s_list_redir         *list_redir);

/**
** @brief               Builts a pipe node from instruction list.
** @param name          Function name
** @param list_instr    Input instruction list.
** @return              Returns pipe node.
*/
s_instr_func            *build_instr_func(char                  *name,
                                          s_list_instr          *list_instr);

/**
** @brief               Builts an IF node.
** @param list_cond     Condition instruction list.
** @param list_instr_t  True instruction list.
** @param instr_f       False instruction.
** @return              Returns an if node.
*/
s_instr_if              *build_instr_if(s_list_instr            *list_cond,
                                        s_list_instr            *list_instr_t,
                                        s_instr                 *instr_f);

/**
** @brief               Builts a FOR node.
** @param var_name      Variable name.
** @param list_words    List words.
** @param list_instr    Instruction list
** @return              Returns a for node.
*/
s_instr_for             *build_instr_for(char                   *var_name,
                                         s_list_words           *list_words,
                                         s_list_instr           *list_instr);

/**
** @brief               Builts a WHILE node.
** @param list_instr    Instruction list condition.
** @param list_instr    Instruction list to execute.
** @return              Returns a while node.
*/
s_instr_while           *build_instr_while(s_list_instr         *list_cond,
                                           s_list_instr         *list_instr);

/**
** @brief               Builts an UNTIL node.
** @param list_instr    Instruction list condition.
** @param list_instr    Instruction list to execute.
** @return              Returns an until node.
*/
s_instr_until           *build_instr_until(s_list_instr         *list_cond,
                                           s_list_instr         *list_instr);

/**
** @brief               Adds an item in an item list.
** @param list_c_items  Input items.
** @param list_words    Matching words list.
** @param list_instr    Instruction to do list.
** @return              Returns an instruction list.
*/
s_list_c_items          *add_item_in_list_items(s_list_c_items  *list_c_items,
                                                s_list_words    *list_words,
                                                s_list_instr    *list_instr);

/**
** @brief               Builts a CASE node.
** @param word          Case matching word.
** @param list_c_items  Case items.
** @return              Returns a case instruction.
*/
s_instr_case            *build_instr_case(char                  *word,
                                          s_list_c_items        *list_c_items);

/**
** @brief               Builds an command from words list.
** @param list_words    Input word list.
** @return              Returns an output command instruction.
*/
s_instr_cmd             *build_instr_cmd(s_list_words           *list_words);

/**
** @brief               Frees an instruction list.
** @param elmt          Input instruction element.
** @return              void
*/
void                    free_list_instr(s_list_instr            *elmt);

/**
** @brief               Free an @a elmt.
** @param[in] elmt      To free.
*/
void                    free_list_instr_item(s_list_instr_item  *elmt);

/**
** @brief               Free an @a elmt.
** @param[in] elmt      To free.
*/
void                    free_instr(s_instr                      *elmt);

/**
** @brief               Free an @a elmt.
** @param[in] elmt      To free.
*/
void                    free_instr_or(s_instr_or                *elmt);

/**
** @brief               Free an @a elmt.
** @param[in] elmt      To free.
*/
void                   free_instr_and(s_instr_and               *elmt);

/**
** @brief               Free an @a elmt.
** @param[in] elmt      To free.
*/
void                   free_instr_not(s_instr_not               *elmt);

/**
** @brief               Free an @a elmt.
** @param[in] elmt      To free.
*/
void                   free_instr_pipe(s_instr_pipe             *elmt);

/**
** @brief               Free an @a elmt.
** @param[in] elmt      To free.
*/
void                   free_instr_paren(s_instr_paren           *elmt);

/**
** @brief               Free an @a elmt.
** @param[in] elmt      To free.
*/
void                   free_instr_brack(s_instr_brack           *elmt);

/**
** @brief               Free an @a elmt.
** @param[in] elmt      To free.
*/
void                   free_instr_redir(s_instr_redir           *elmt);

/**
** @brief               Free an @a elmt.
** @param[in] elmt      To free.
*/
void                   free_instr_func(s_instr_func             *elmt);

/**
** @brief               Free an @a elmt.
** @param[in] elmt      To free.
*/
void                   free_instr_if(s_instr_if                 *elmt);

/**
** @brief               Free an @a elmt.
** @param[in] elmt      To free.
*/
void                   free_instr_for(s_instr_for               *elmt);

/**
** @brief               Free an @a elmt.
** @param[in] elmt      To free.
*/
void                   free_instr_while(s_instr_while           *elmt);

/**
** @brief               Free an @a elmt.
** @param[in] elmt      To free.
*/
void                   free_instr_until(s_instr_until           *elmt);

/**
** @brief               Free an @a elmt.
** @param[in] elmt      To free.
*/
void                   free_instr_case(s_instr_case             *elmt);

/**
** @brief               Free an @a elmt.
** @param[in] elmt      To free.
*/
void                   free_instr_cmd(s_instr_cmd               *elmt);

/**
** @brief               Free an @a elmt.
** @param[in] elmt      To free.
*/
void                    free_list_redir(s_list_redir            *elmt);

/**
** @brief               Free an @a elmt.
** @param[in] elmt      To free.
*/
void                    free_list_words(s_list_words            *elmt);

/**
** @brief               Free an @a elmt.
** @param[in] elmt      To free.
*/
void                    free_list_c_items(s_list_c_items        *elmt);

# include "../mmalloc/mmalloc.h"

#endif /* !AST_H_ */
