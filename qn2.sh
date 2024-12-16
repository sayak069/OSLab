factorial(){
    n=$1
    fact=1
    for(( i=1;i<=n;i++ ))
    do
        fact=$((fact * i))
    done
    echo $fact
}
expression(){
    x=$1
    n=$2
    res=0
    for(( i=0;i<n;i++ ))
    do
        expo=$((x ** (2 * i)))
        fact=$(factorial $((2 * i)))
        # awk used for floating point calculation
        val=$(awk "BEGIN {print $expo / $fact}")
        res=$(awk "BEGIN {print $res + $val}")
    done
    echo "$res"
}
read -p "enter x and n: " x n
expression $x $n