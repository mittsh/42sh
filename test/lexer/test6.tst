<cmd>
./main_test/lexer_tst "echo just        a check          to test           with spaces and        "$'\t'"tabs"</cmd>

<ref>
cat ./lexer/test6.ref</ref>

<ret>
0</ret>
