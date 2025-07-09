
CFLAGS ?= -O0
APP ?= memtrace


build:
	gcc benchmarks/$(APP)/$(APP).c $(CFLAGS) -o bin/$(APP).out


trace:
	valgrind --tool=lackey --trace-mem=yes bin/$(APP).out 2> $(APP).txt
	python3 trace.py $(APP).txt $(APP)_fmt.txt

run:
	cd Trace-Driven-Cache-Simulator && python2 ./cachesimulator.py