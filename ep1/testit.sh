for type in small medium large; do
    for i in `seq 1 30`; do
        msg=$type$i
        echo $msg
        curl http://notify.moosa.it:88/9f28e1e2-934e-4136-9628-e61795e26bf1/$msg
        ./ep1 1 test_data/$type/$type$i.in test_data/$type/fcfs/$type$i.out &
        ./ep1 2 test_data/$type/$type$i.in test_data/$type/srtn/$type$i.out &
        ./ep1 3 test_data/$type/$type$i.in test_data/$type/multi/$type$i.out
    done
done
