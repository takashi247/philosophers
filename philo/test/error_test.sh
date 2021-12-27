#!/bin/bash

GREEN="\033[32m"
RESET="\033[39m"

philo_test () {
	echo -e ${GREEN}${1}${RESET}
	eval $1
	echo ""
}

philo_test './philo 10 400 100'
philo_test './philo 10 400 100 100 3 3'
philo_test './philo 10 400 "" 100'
philo_test './philo 10 400 -100 100'
philo_test './philo 10 400 100 100 -1'
philo_test './philo 10 400 100 100 0'
philo_test './philo 10 hundred 100 100'
philo_test './philo 10a 400 100 100'
philo_test './philo 0 400 100 100'
philo_test './philo 10 400 2147483648 100'
philo_test './philo 10 4294967300 100 100'
philo_test './philo 4294967300 400 100 100'