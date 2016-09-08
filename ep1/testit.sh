for type in small; do
    for i in `seq 1 1`; do
        ./ep1 1 test_data/$type/$type.in test_data/$type/fcfs/$type$i.out &
        ./ep1 2 test_data/$type/$type.in test_data/$type/srtn/$type$i.out &
        ./ep1 3 test_data/$type/$type.in test_data/$type/multi/$type$i.out
    done
done
