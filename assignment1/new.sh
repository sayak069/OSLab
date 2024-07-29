file="case.txt"
while IFS= read -r line
do
    a=`echo "$line"|cut -d " " -f 1`
    b=`echo "$line"|cut -d " " -f 2`
    res=`sh gcd.sh $a $b`
    c=`echo "$line"|cut -d " " -f 3`
    if [ "$res" == "$c" ]
    then
        echo "Test passed"
    else
        echo "Test failed"
fi
done < "$file"