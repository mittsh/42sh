<cmd>
./main_test/lexer_tst 'echo "we are the \"best ones\" yeah"; echo "Share our \\\"SHELL\\\" yeah"; echo "Share\\" our \\" shell";'</cmd>

<ref>
cat ./lexer/test3.ref</ref>

<ret>
0</ret>
