# Proxy Makefile — moved to repository root (../Makefile)
# Delegates targets to the top-level Makefile so `make -C tests <target>` still works

.PHONY: all perf unit run-perf run-unit deps clean

all:
	$(MAKE) -C ..

perf:
	$(MAKE) -C .. perf

unit:
	$(MAKE) -C .. unit

run-perf:
	$(MAKE) -C .. run-perf

run-unit:
	$(MAKE) -C .. run-unit

deps:
	$(MAKE) -C .. deps

clean:
	$(MAKE) -C .. clean
