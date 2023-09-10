all: 
	gcc main.c -lm
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o vector

gr:
	chmod +x printAll.gpi
	./printAll.gpi