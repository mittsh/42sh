<cmd>
../build/42sh</cmd>

<ref>
bash</ref>

<stdin>
ls && ls -a && ls -la | cat -e;
! ls || ls || ls | cat -e || ls -la || ls -a;
ls && ls -a || ls -l && ls -la || ls -a;
</stdin>
