set -ux

./philo_bonus 0 800 200 200
./philo_bonus 2 0 200 200
./philo_bonus 2 500 0 200
./philo_bonus 2 500 100 0
./philo_bonus 2 500 100 200 0
./philo_bonus 2 2147483648 100 100
./philo_bonus 300 410 200 200


echo "too few --------------"
./philo_bonus 1
./philo_bonus 2 2
./philo_bonus 3 3 3

echo "too many -------------"
./philo_bonus 6 6 6 6 6 6
./philo_bonus 6 6 6 6 6 6 7

echo "not numbers ----------"
./philo_bonus 10 10 10 a
./philo_bonus 10 10 a 10
./philo_bonus 10 a 10 10
./philo_bonus a 10 10 10

echo "too large ----------"
./philo_bonus 2147483648 100 100 100 100

echo "neg"
./philo_bonus -1 100 100 100 100

echo "ok ---------------------------"
# ./philo_bonus 12 13 14 15 16
# ./philo_bonus 12 13 14 15

exit 0
