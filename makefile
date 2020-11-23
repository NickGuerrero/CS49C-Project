CC = gcc
CFLAGS = -Wall

game: GameBoard.c GameDisplay.c GameAI.c
		$(CC) $(CFLAGS) -o game GameBoard.c GameDisplay.c GameAI.c

clean:
		$(RM) game *.o *~