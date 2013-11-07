<cmd>
../build/42sh</cmd>

<ref>
bash</ref>

<stdin>
for i in 1 2 3; do
    for j in 1 2 3; do
        for k in 1 2 3; do
           echo $i;
           echo $j;
           echo $k;
        done
    done
done
</stdin>
