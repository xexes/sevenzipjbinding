# Instructions for coding agents

## Project structure

- `jbinding-java/src/` contains the public Java API, implementations, and utilities.
- `jbinding-cpp/` contains the JNI bridge and native binding code.
- `7zip/` contains the bundled 7-Zip engine.
- `test/JavaTests/` and `test/CTests/` contain Java and native tests.
- `cmake/`, `scripts/`, and `.github/workflows/` contain build and platform automation.

## Build and test

Use an out-of-tree CMake build with a JDK (8 or newer) and a native C/C++ toolchain:

```bash
cmake -S . -B build -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
    -DJAVA_JDK=/path/to/jdk
cmake --build build
ctest --test-dir build --output-on-failure
cmake --build build --target package
```

Set `JAVA_JDK` to the installed JDK path, or omit it when `JAVA_HOME` points to the JDK.
CTest runs the project's Java test bundles; the full suite may take
significant time. For a focused run, list registered tests with
`ctest --test-dir build -N` and select a test with `-R`.

## Change guidance

- Keep Java API and JNI/native behavior in sync when changing a binding method or callback.
- Add or update focused tests in the existing Java or C++ test suites for behavior changes.
- Preserve Java 8 source/runtime compatibility; the build configures `javac` to target Java 8.
- Keep generated build products in the build directory; do not commit generated binaries or
  machine-specific build output.
- Native changes must be built and tested on the affected platform where possible. Platform
  workflows in `.github/workflows/` document the supported CI toolchains and platform-specific
  build commands.
