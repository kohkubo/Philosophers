make
for i in {1..5}; do
	./philo_bonus $1 $2 $3 $4 
	echo "+++++"
	sleep 3
done

echo "end end end end end end end end"

# ./philo 200 410 200 200 | awk '{print $1}' | tee act | sort -n > exp; diff -u exp act
# ./philo 4 410 200 200 | awk '{print substr($1, length($1) - 12, 13) " " $2 " " $NF}'
