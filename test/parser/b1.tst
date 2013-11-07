<cmd>
../build/42sh</cmd>

<ref>
bash</ref>

<stdin>
if true;
then
	if ! false;
	then
		echo a complex grammar | cat -e > essai 2> essai_err;
		touch essai | cat -e;
		touch essai_err | cat -e;
		rm essai; rm essai_err;
	fi;
fi;
</stdin>
