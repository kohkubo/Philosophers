rm -rf act exp tmp

echo "Testing 2 ================"
./philo_bonus 200 403 200 200 > tmp; cat tmp; cat tmp | awk '{print substr($1, length($1) - 12, 13)}' | tee act | sort -n > exp;
diff -y act exp
if [ $? -eq 0 ]; then
	echo "Test 2 passed"
	rm -rf act exp tmp
else
	echo "Test 2 failed"
fi
