#!/bin/bash

NAME="$1"

clear

while true; do
    PID=$(pgrep -x "$NAME" | head -n 1)

    printf '\033[H'

    if [ -z "$PID" ]; then
		clear
        echo "Process '$NAME' not found."
        sleep 1
        continue
    fi

    echo "========================================"
    echo " Process: $NAME"
    echo " PID:     $PID"
    echo "========================================"

    echo
	echo "--- CPU / Memory ------------------------"
	ps -p "$PID" -o pid=,%cpu=,%mem=,etime= |
	awk '{
		printf "PID:        %s\n", $1
		printf "CPU:        %s %%\n", $2
		printf "Memory:     %s %%\n", $3
		printf "Runtime:    %s\n", $4
	}'

    echo
    echo "--- Threads -----------------------------"
    ps -p "$PID" -o nlwp= |
    awk '{ printf "Thread count: %s\n", $1 }'

    echo
    printf "%-10s %-10s %-10s %-12s\n" "TID" "CPU" "Memory" "Runtime"
	ps -L -p "$PID" -o tid=,%cpu=,%mem=,etime=,comm= --no-headers |
	awk '{
		printf "%-10s %-10s %-10s %-12s %s\n", $1, $2 "%", $3 "%", $4, $5
	}'

    echo
    echo "========================================"

    sleep 1
done