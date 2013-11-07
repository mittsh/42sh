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
		! ls || ls || ls | cat -e || ls;
	fi;
fi;
</stdin>
