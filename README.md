# FastLog

## Project Goal
**FastLog** is a high-performance C++ log processing engine designed to handle massive datasets efficiently. The primary objective is to build a baseline implementation and then iteratively optimize it to achieve a **4x speedup** through advanced techniques in memory management, concurrency, and I/O.

This project serves as a real-world playground for systems programming concepts:
- Zero-copy parsing
- SIMD optimization
- Lock-free data structures
- Custom memory allocators

## Log Format
The engine processes newline-delimited log files with the following structure:
```text
<TIMESTAMP> <LEVEL> <SERVICE_NAME> <MESSAGE>
```

**Example:**
```text
1638210000 INFO  auth_service  User login successful id=42
1638210005 ERROR db_shard_1    Connection timeout retrying...
1638210012 WARN  cache_layer   High memory usage detected
```

## How to Run

### Prerequisites
- C++17 compliant compiler (GCC/Clang/MSVC)
- CMake 3.15+

### Build
```bash
cmake -B build
cmake --build build
```

### Run
```bash
./build/fastlog datasets/sample.log
```

## Milestones

### Month 1: Foundation
- [ ] **Baseline I/O**: Efficient file reading (chunks/mmap).
- [ ] **Basic Parser**: Convert raw lines to structured `LogEntry` objects.
- [ ] **Stats Engine**: Aggregate counts by level and service.
- [ ] **Benchmarking Harness**: Establish the "Ground Truth" performance.

### Month 2: Optimization
- [ ] **Profiling**: Identify hotspots (CPU/Memory).
- [ ] **Multithreading**: Implement thread pool for parallel processing.
- [ ] **Memory Optimization**: Reduce allocations (std::string overhead).
- [ ] **Goal**: Achieve 4x throughput vs Month 1 baseline.

### Month 3: Polish
- [ ] **API Cleanup**: internal interfaces are stable and clean.
- [ ] **Final Benchmarks**: Comprehensive report generation.
- [ ] **Demo**: One-click script to show processing of a 1GB+ file.