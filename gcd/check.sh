ls ./gcdProgs >temp.txt
len=`wc -l <temp.txt`
for(( i=1;i<=len;i++ ))
do
    file=`head -n $i temp.txt| tail -n 1`
    l=`wc -l <test.txt`
    flag=0
    for(( j=1;j<=l;j++ ))
    do
        x=`head -n $j test.txt|tail -n 1| cut -d " " -f 1`
        y=`head -n $j test.txt|tail -n 1| cut -d " " -f 2`
        z=`head -n $j test.txt|tail -n 1| cut -d " " -f 3`
        res=`sh gcdProgs/$file $x $y`
        if [ $res != $z ]
        then
            flag=1
            break
        fi
    done
    if [ $flag -eq 0 ]
    then
        echo "$file passed"
    else
        echo "$file failed"
    fi
done