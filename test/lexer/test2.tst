<cmd>
./main_test/lexer_tst 'echo toto; echo $((4 + 3 (5 + (3 + 8))));'</cmd>

<ref>
cat ./lexer/test2.ref</ref>

<ret>
0</ret>
