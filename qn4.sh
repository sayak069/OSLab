while [ 1 ]
do
    echo "1. files"
    echo "2. process"
    echo "3. date"
    echo "4. calender"
    echo "5. exit"
    read -p "enter choice: " choice
    case $choice in
        1) ls;;
        2) ps;;
        3) echo "$(date)";;
        4) read -p "enter year: " year
            cal "$year";;
        5) exit 0;;
        *) echo "inv choice";;
    esac
done