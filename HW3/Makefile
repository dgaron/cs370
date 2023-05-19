PROJECT_NAME=HW3

.PHONY: build
.PHONY: package
.PHONY: clean

build: Initiator Reader Pell Composite Total

Initiator: Initiator.c
	gcc -Wall -Wextra -Wpedantic -o Initiator Initiator.c -lrt

Reader: Reader.c Reader.h
	gcc -Wall -Wextra -Wpedantic -o Reader Reader.c

Pell: Pell.c Pell.h
	gcc -Wall -Wextra -Wpedantic -o Pell Pell.c -lm -lrt

Composite: Composite.c Composite.h
	gcc -Wall -Wextra -Wpedantic -o Composite Composite.c -lrt

Total: Total.c Total.h
	gcc -Wall -Wextra -Wpedantic -o Total Total.c -lrt

package:
	tar -cvzf Daniel-Garon-$(PROJECT_NAME).tar *.c *.h *.txt Makefile

clean:
	rm -f Initiator Reader Pell Composite Total
