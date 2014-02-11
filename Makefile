default: backtrack.bin

backtrack.bin:
	gcc -std=c11 -O3 backtrack.c -o backtrack.bin