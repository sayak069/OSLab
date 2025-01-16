gcd(){
    x=$1
    y=$2
    if [ $x -eq 0 ]
    then
        echo "$y"
    else
        gcd `expr $y % $x` $x
    fi
}
lcm(){
    x=$1
    y=$2
    mul=$(( x * y  ))
    echo $((mul / $(gcd $x $y)))
}
x=$1
y=$2
lcm $x $y