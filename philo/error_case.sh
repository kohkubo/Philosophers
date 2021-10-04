set -ux

./philo 0 800 200 200
./philo 2 0 200 200
./philo 2 500 0 200
./philo 2 500 100 0
./philo 2 500 100 200 0
./philo 2 2147483648 100 100
./philo 300 410 200 200


echo "too few --------------"
./philo 1
./philo 2 2
./philo 3 3 3

echo "too many -------------"
./philo 6 6 6 6 6 6
./philo 6 6 6 6 6 6 7

echo "not numbers ----------"
./philo 10 10 10 a
./philo 10 10 a 10
./philo 10 a 10 10
./philo a 10 10 10

echo "too large ----------"
./philo 2147483648 100 100 100 100

echo "neg"
./philo -1 100 100 100 100

echo "ok ---------------------------"
# ./philo 12 13 14 15 16
# ./philo 12 13 14 15

exit 0
