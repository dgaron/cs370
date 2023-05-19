PROJECT_NAME=HW2

.PHONY: build
.PHONY: package
.PHONY: clean

build: Initiator Pell Composite Total

Initiator: Initiator.c
	gcc -Wall -Wextra -Wpedantic -o Initiator Initiator.c

Pell: Pell.c Pell.h
	gcc -Wall -Wextra -Wpedantic -o Pell Pell.c -lm

Composite: Composite.c Composite.h
	gcc -Wall -Wextra -Wpedantic -o Composite Composite.c

Total: Total.c Total.h
	gcc -Wall -Wextra -Wpedantic -o Total Total.c

package:
	tar -cvzf Daniel-Garon-$(PROJECT_NAME).tar *.c *.h *.txt makefile

clean:
	rm -f Initiator Pell Composite Total
