gcd(){
    a=$1
    b=$2
    if [[ $a =~ ^-?[0-9]+$ ]] && [[ $b =~ ^-?[0-9]+$ ]]
    then
        if [ $b -eq 0 ]
        then    
            echo "Not_possible"
        else
            res=0
            if [ "$a" -ge "$b" ]
            then
                min=$b
            else
                min=$a
            fi
            for((i=1 ; i<=min ; i++))
            do
                if [ $(( a%i )) -eq 0 ] && [ $(( b%i )) -eq 0 ]
                then    
                    res=$i;
                fi
            done
            echo $res
        fi
    else
        echo "Not_possible"
    fi
}
res=`gcd $1 $2`
echo "$res"