OBJ := $(patsubst *.c, *.o, $(wildcard *.c))

Inverted_Index.exe:$(OBJ)
	gcc -o $@ $^
$(OBJ):
clean:
	rm *.o *.exe
