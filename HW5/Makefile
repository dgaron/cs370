PROJECT_NAME=HW5

.PHONY: build
.PHONY: package
.PHONY: clean

build: Invoker

Invoker: Invoker.java Producer.java Consumer.java Bdbuffer.java
	javac Invoker.java

package:
	tar -cvzf Daniel-Garon-$(PROJECT_NAME).tar *.java README.txt Makefile

clean:
	rm -f Invoker.class Producer.class Consumer.class Bdbuffer.class
