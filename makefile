CC=gcc

default:
	$(CC) -o zvec zvec.c main.c -pedantic -Wall -Wextra -std=c89
