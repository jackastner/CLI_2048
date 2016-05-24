GCC_OPTIONS=-W -Ofast
OBJECT_FILES=main.o gamelogic.o printlogic.o
EXECUTABLE=2048

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECT_FILES)
	gcc $(GCC_OPTIONS) -o $(EXECUTABLE) $(OBJECT_FILES)

main.o: main.c printlogic.h gamelogic.h
	gcc -c $(GCC_OPTIONS) -o main.o main.c

gamelogic.o: gamelogic.c gamelogic.h
	gcc -c $(GCC_OPTIONS) -o gamelogic.o gamelogic.c

printlogic.o: printlogic.c gamelogic.h printlogic.h
	gcc -c $(GCC_OPTIONS) -o printlogic.o printlogic.c

clean:
	rm $(OBJECT_FILES) $(EXECUTABLE)
