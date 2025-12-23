# tickstream

[![CI](https://github.com/bodeby/tickstream/actions/workflows/ci.yml/badge.svg)](https://github.com/bodeby/tickstream/actions/workflows/ci.yml)
[![CodeQL](https://github.com/bodeby/tickstream/actions/workflows/github-code-scanning/codeql/badge.svg)](https://github.com/bodeby/tickstream/actions/workflows/github-code-scanning/codeql)

**Tickstream** is a C++20 header-only library for generating pseudo real-time financial market tick data simulations. The library provides configurable random processes, realistic market microstructure, and a high-performance producer-consumer architecture suitable for algorithmic trading strategy development, backtesting, and system load testing.

## Core Design Principles

- **Header-only**: Zero dependencies beyond C++20 standard library
- **Performance-first**: Sub-microsecond tick generation, lock-free where possible
- **Deterministic**: Seed-controlled reproducibility
- **Modular**: Pluggable processes, schedulers, and consumers
- **Real-time ready**: Suitable for both simulation and live integration

## Micro Structure

```
tickstream/include/tickstream/stream_gen.hpp    # public
tickstream/include/tickstream/detail/models.hpp # private
```

## Concepts / Data-Structures

- [Ring Buffer](https://en.wikipedia.org/wiki/Circular_buffer)


## Ideas

1. Use [IMGUI](https://github.com/ocornut/imgui) for real-time tick movement visualizations.