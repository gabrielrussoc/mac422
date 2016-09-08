for type in small medium large; do
    for i in `seq 1 30`; do
        echo $type $i
        ./ep1 1 test_data/$type/$type.in test_data/$type/fcfs/$type$i.out &
        ./ep1 2 test_data/$type/$type.in test_data/$type/srtn/$type$i.out &
        ./ep1 3 test_data/$type/$type.in test_data/$type/multi/$type$i.out
    done
done
