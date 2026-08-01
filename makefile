# Makefile for Tickstream

.PHONY: all server server-debug server-release test asan ubsan bench


all: server

# ------------------------
# Run / Debug (generic)
# ------------------------

server:
	cmake --preset debug
	cmake --build --preset debug --target tickstream_server
	./build/debug/apps/server/tickstream_server

server-debug:
	cmake --preset debug
	cmake --build --preset debug --target tickstream_server
	lldb ./build/debug/apps/server/tickstream_server

server-release:
	cmake --preset release
	cmake --build --preset release --target tickstream_server
	./build/debug/apps/server/tickstream_server

# ------------------------
# Tests
# ------------------------

test:
	cmake --preset debug-tests
	cmake --build --preset debug-tests
	ctest --preset debug-tests

asan:
	cmake --preset asan-tests
	cmake --build --preset asan-tests
	ctest --preset asan-tests

ubsan:
	cmake --preset ubsan-tests
	cmake --build --preset ubsan-tests
	ctest --preset ubsan-tests

# ------------------------
# Benchmarks (future)
# ------------------------

BENCH ?= gbm_benchmark

bench:
	cmake --preset release-bench
	cmake --build --preset release-bench
	./build/release-bench/bench/tickstream/$(BENCH) \
		--benchmark_min_time=1s
