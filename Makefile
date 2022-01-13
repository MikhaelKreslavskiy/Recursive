CFLAGS=-Wall -Wextra -Werror -O2
TARGETS=main2 plug_v_1.so

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -rf *.o $(TARGETS)

main2: main2.c
	gcc $(CFLAGS) main2.c -o lab1mkN3248 -ldl

plug_v_1.so: plug_v_1.c 
	gcc $(CFLAGS) -shared -fPIC -o lib1mkN3248.so plug_v_1.c -ldl -lm