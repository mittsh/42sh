<cmd>
../build/42sh</cmd>

<ref>
bash</ref>

<stdin>
a=20
b=3
c=9
echo "oh $(($a * $(($b + $c)))) yeah, also in the string"
</stdin>
