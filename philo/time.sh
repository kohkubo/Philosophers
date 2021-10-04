rm -rf at exp tmp

echo "Testing 2 ================"
./philo 200 403 200 200 > tmp; cat tmp; cat tmp | awk '{print substr($1, length($1) - 12, 13)}' | tee act | sort -n > exp;
gsed -i '$d' act;
gsed -i '1d' exp;
diff -y act exp
if [ $? -eq 0 ]; then
	echo "Test 2 passed"
	rm -rf at exp tmp
else
	echo "Test 2 failed"
fi
