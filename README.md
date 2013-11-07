# 42sh: Welcome to the dinosaur age

42sh is a bash-style shell we developped at school, all in C. It was a 4 months project, with 5 team members, even though all were not as fervent we, [JC](http://github.com/jclanoe) and [I](http://github.com/mittsh), were.
[EPITA](http://www.epita.fr/en/) is one of the leading Computer Science Engineering School in France, and make us learn low-level stuff (including some asm) to allow us understand deeply what's going on under the hood.

## No memory leaks. At all.

One instruction was: "If you leak, you're dead." Even one leak. And [Valgrind](http://valgrind.org/) was the  witness.
We hacked night and day to make our shell work, from old-style dirty parsing (Bison, Flex, Lex, Yacc, Regex libraries forbidden), to [AST](http://en.wikipedia.org/wiki/Abstract_syntax_tree) building and interpretation. Though, last weekend, we had 2 leaks left, in the very edge case where the user would quit badly the shell. Plus, we weren't sure whether we missed some other cases, and would loose pride with a nasty leak.

So I decided to write `mmalloc` (yes `malloc` with 2 `m`, like *mittsh-malloc*). It also had `mfree`, `calloc` and `mrealloc`, and worked exactly as the original library functions. Except something. It kept linked list of pointers to all allocations. So when I need, we just had to call `mmalloc_free`, the magic method documented as *Frees all the managed heap.*.
See [mmalloc here](https://github.com/mittsh/42sh/blob/master/src/mmalloc/mmalloc.h).

In fact, the day of presentation, the jury asked us *So, is there any leak?*, [JC](http://github.com/jclanoe) answered very convinced *No leak*. After running their Valgrind-based test suite, the jury said *Nice, you're the first team saying they don't have any leak, and actually not having any.*. It was reliving!

## The Original README

I wrote that README to tell the story behing 42sh, but you can checkout the [original 80' style one](https://github.com/mittsh/42sh/blob/master/README).

# LICENSE

All work done at EPITA, is the property of EPITA. Though, nobody asked not to open-source it.
