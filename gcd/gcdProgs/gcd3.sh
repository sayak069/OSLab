gcd(){
    x=$1
    y=$2
    if [[ $x =~ ^-?[0-9]+$ ]] && [[ $y =~ ^-?[0-9]+$ ]]
    then
        if [ $x -eq 0 ]
        then
            echo "$y"
        else
            gcd `expr $y % $x ` $x
        fi
    else
        echo "np"
    fi  
}
x=$1
y=$2
gcd $x $y