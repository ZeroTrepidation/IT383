all: thread-create thread-create2 revthread-create2 primes detached

thread-create:
	gcc -o thread-create thread-create.c -pthread -lrt

thread-create2:
	gcc -o thread-create2 thread-create2.c -pthread -lrt

revthread-create2:
	gcc -o revthread-create2 revthread-create2.c -pthread -lrt

primes:
	gcc -o primes primes.c -pthread -lrt

detached:
	gcc -o detached detached.c -pthread -lrt 
