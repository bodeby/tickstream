# Makefile for Tickstream

.PHONY: all run debug run-release run-asan run-ubsan test asan ubsan lint bench clean

APP ?= demo
PRESET ?= debug

all: run

# ------------------------
# Run / Debug (generic)
# ------------------------

run:
	cmake --preset $(PRESET)
	cmake --build --preset $(PRESET) --target tickstream_$(APP)
	./build/$(PRESET)/apps/$(APP)/tickstream_$(APP)

debug:
	cmake --preset $(PRESET)
	cmake --build --preset $(PRESET) --target tickstream_$(APP)
	lldb ./build/$(PRESET)/apps/$(APP)/tickstream_$(APP)

# ------------------------
# Convenience targets (primary app)
# ------------------------

run-release:
	$(MAKE) run PRESET=release

run-asan:
	$(MAKE) run PRESET=asan

run-ubsan:
	$(MAKE) run PRESET=ubsan

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

BENCH ?= domain/tx/tx_encoder_bench

bench:
	cmake --preset release-bench
	cmake --build --preset release-bench
	./build/release-bench/benchmarks/$(BENCH) --benchmark_min_time=1s
