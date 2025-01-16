num=$1
reverse=0
original=$num
while [ $num -gt 0 ]
do
    rem=$(( $num % 10 ))
    reverse=$(( $reverse * 10 + $rem ))
    num=$(( $num / 10 ))
done
if [ $original -eq $reverse ]
then
    echo "palindrome"
else 
    echo "not palindrome"
fi