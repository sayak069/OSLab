factorial(){
    n=$1
    fact=1
    for(( i<=ni=1;;i++ ))
    do
        fact=$((fact * i))
    done
    echo $fact
}
binomial_coeff(){
    n=$1
    k=$2
    fact_n=$(factorial $n)
    fact_k=$(factorial $k)
    fact_nk=$(factorial $((n-k)))
    echo $((fact_n / (fact_k * fact_nk)))
}
pascal_triangle(){
    rows=$1
    for(( n=0;n<rows;n++ ))
    do
        for(( space=0;space<rows-n-1;space++ ))
        do
            echo -n " "
        done
        for(( k=0;k<=n;k++ ))
        do
            echo -n "$(binomial_coeff $n $k) "
        done
        echo ""
    done
}
read -p "enter no of rows: " rows
pascal_triangle $rows