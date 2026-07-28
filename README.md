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

## Roadmap

| Process Name                    | Process Type     | Implemented |
| ------------------------------- | ---------------- | :---------: |
| Random Walk                     | Price            |     ⬜      |
| Geometric Brownian Motion (GBM) | Price            |     ✅      |
| Heston                          | Price            |     ✅      |
| Ornstein-Uhlenbeck (OU)         | Price            |     ⬜      |
| Cox-Ingersoll-Ross (CIR)        | Price / Variance |     ⬜      |
| Merton Jump Diffusion           | Price            |     ⬜      |
| Markov Switching GBM            | Price            |     ⬜      |
| Markov Switching Heston         | Price            |     ⬜      |
| Fixed Interval                  | Timestamp        |     ⬜      |
| Poisson Arrival                 | Timestamp        |     ⬜      |
| Hawkes Arrival                  | Timestamp        |     ⬜      |
| Constant Quantity               | Quantity         |     ⬜      |
| Uniform Quantity                | Quantity         |     ⬜      |
| Poisson Quantity                | Quantity         |     ⬜      |
| Log-Normal Quantity             | Quantity         |     ⬜      |
| Pareto Quantity                 | Quantity         |     ⬜      |
| Bernoulli Side                  | Side             |     ⬜      |
| Markov Side                     | Side             |     ⬜      |
| Imbalance Side                  | Side             |     ⬜      |
| Discrete Event Type             | Event Type       |     ⬜      |
| State-Dependent Event Type      | Event Type       |     ⬜      |
| Constant Spread                 | Spread           |     ⬜      |
| Ornstein-Uhlenbeck Spread       | Spread           |     ⬜      |
| Regime Spread                   | Spread           |     ⬜      |
