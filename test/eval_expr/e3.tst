<cmd>
../build/42sh</cmd>

<ref>
bash</ref>

<stdin>
a=1
b=2
c=3
echo " in the $(($(($a)) + $(($b / $c)))) string"
</stdin>
