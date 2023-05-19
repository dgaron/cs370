PROJECT_NAME=HW1

FILES=Initiator.c Worker.c

OUT_EXE=Initiator

build: $(OUT_EXE)

$(OUT_EXE): $(FILES)
	gcc -Wall -Wextra -Wpedantic -o $(OUT_EXE) $(FILES)

package:
	tar -cvzf Daniel-Garon-$(PROJECT_NAME).tar *.c *.h *.txt makefile

clean:
	rm -f $(OUT_EXE)
