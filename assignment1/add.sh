add(){
    a=$1
    b=$2
    echo $((a + b))
}
res=`add $1 $2`
echo "$res"