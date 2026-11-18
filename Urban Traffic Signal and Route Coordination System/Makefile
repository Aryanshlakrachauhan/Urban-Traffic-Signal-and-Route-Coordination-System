CC = gcc
CFLAGS = -std=c17 -O2 -Wall

all: traffic_sim

traffic_sim: main.c dnc_sort.c greedy.c dp.c backtracking_bnb.c flow_matching.c math_string.c traffic.h
	$(CC) $(CFLAGS) main.c dnc_sort.c greedy.c dp.c backtracking_bnb.c flow_matching.c math_string.c -o traffic_sim

run: traffic_sim
	./traffic_sim

clean:
	rm -f traffic_sim

.PHONY: all run clean
