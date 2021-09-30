make
rm -rf output exp act tmp
N=5; ./philo_bonus $N 800 200 200 7 | awk '{print substr($1, length($1) - 12, 13) " " $2 " " $NF}' | sed '$d' | tee ./output

for i in `seq 1 $N`; do
	echo "==========="
	echo "Philosopher $i"
	echo -n "Picking:  "; cat output | grep "$i fork" | wc -l | tr -d ' ';
	echo -n "Eating:   "; cat output | grep "$i eating" | wc -l | tr -d ' ';
	echo -n "Thinking: "; cat output | grep "$i thinking" | wc -l | tr -d ' ';
	echo -n "Sleeping: "; cat output | grep "$i sleeping" | wc -l | tr -d ' ';
	echo -n "Died:     "; cat output | grep "$i died" | wc -l | tr -d ' ';
done


echo "Testing 2 ================"
./philo_bonus 200 403 200 200 | awk '{print substr($1, length($1) - 12, 13)}' | tee act | sort -n > exp;
gsed -i '$d' act;
gsed -i '1d' exp;
diff -u exp act
if [ $? -eq 0 ]; then
	echo "Test 2 passed"
else
	echo "Test 2 failed"
fi
