CC = gcc
CFLAGS = -std=c11 -O2 -Wall

all:
	@$(CC) $(CFLAGS) -I"main code files" "main code files/main.c" "algorithm used in backend/dnc_sort.c" "algorithm used in backend/greedy.c" "algorithm used in backend/dp.c" "algorithm used in backend/backtracking_bnb.c" "algorithm used in backend/flow_matching.c" -o "Executable file/traffic_sim.exe"

run: all
	@"Executable file\traffic_sim.exe"

clean:
	cmd /c del /f /q "Executable file\traffic_sim.exe" 2>nul

.PHONY: all run clean
