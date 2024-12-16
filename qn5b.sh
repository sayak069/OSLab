# echo -n: -n suppreses "\n"
#read -p: -p used for giving prompt msg
width=20
height=20
center_x=10
center_y=10

read -p "Enter radius of circle: " radius
# ^[0-9]+$: format of positive integer
if ! [[ "$radius" =~ ^[0-9]+$ ]]; then
    echo "Invalid Input. Please Enter a Positive Integer for radius."
    exit 1
fi

for y in $(seq 1 $height); do # y runs from 1 to height
    for x in $(seq 1 $width); do # x runs from 1 to width

    #calculate distance of each point
    distance=$(( (x - center_x) ** 2 + (y - center_y) ** 2 ))

    #if distance is nearly equal to radius then print "." else " "
    if [ $distance -le $((radius * radius + radius)) ] && [ $distance -ge $((radius * radius - radius)) ]; then
        echo -n "."
    else
        echo -n " "
    fi
    done
    echo
done