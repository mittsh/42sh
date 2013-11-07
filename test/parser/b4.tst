<cmd>
../build/42sh</cmd>

<ref>
bash</ref>

<stdin>
if true;
then
	if ! false;
	then
		ls && ls -a && ls -la | cat -e;
		! ls || ls || ls | cat -e || ls -la || ls -a;
		ls && ls -a || ls -l && ls -la || ls -a;
	fi;
fi;
</stdin>
