# Cdefer

**A Next-Generation Memory-Safe Preprocessor for C & C++**

Bringing modern memory safety and zero-configuration builds to classic C & C++.

## Overview

`cdefer` draws inspiration from `Zig` & `Golang`, integrating their modern safety and simplicity features directly into C & C++ — while staying fully within the existing languages (no new language required).

`cdefer` is an open-source **preprocessor and tooling layer for C & C++** with one core mission, make C & C++ memory-safe by default — without changing the language.

It enhances traditional compilation pipelines with automatic memory safety checks, build orchestration, and (soon) built-in package management. Unlike other approaches, `cdefer` does not require switching languages, runtimes, or toolchains.

## Key Features

#### Full Memory Safety (Implemented ✅)

-   Enforces safe memory access patterns.
-   No ghost allocation.
-   Detects common vulnerabilities:
    -   Buffer overflows
    -   Use-after-free
    -   Double free
    -   Null dereferences
-   Applies compile-time and runtime instrumentation.
-   100% compatible with **standard C & C++ compilers**.

#### No Makefile Required (Implemented ✅)

-   **Automatic build system generation**
-   Detects source files intelligently.
-   Configures compiler flags and output targets.
-   Works across platforms (Linux, macOS, Windows).
-   Zero external dependencies.

#### Built-In Package Manager (In Progress 🚧)

-   Install libraries with a simple command.
-   Resolves dependencies automatically.
-   Versioning and reproducible builds.
-   Future support for:
    -   Remote repositories
    -   Private registries
    -   Precompiled binary packages

## Status

| Feature              | Status           |
| -------------------- | ---------------- |
| Memory Safety Engine | ✅ Complete      |
| Build Auto-Gen       | ✅ Complete      |
| CLI Tooling          | ✅ Basic Version |
| Package Manager      | 🚧 In Progress   |
| Documentation        | 🔜 Planned       |
| Linter               | 🔜 Planned       |
| LSP for IDEs         | 🔜 Planned       |

## Support OS

| OS      | Status         |
| ------- | -------------- |
| Linux   | ✅ Complete    |
| Macos   | ✅ Complete    |
| Windows | 🚧 In Progress |

## Install / Update

```bash
curl -L https://raw.githubusercontent.com/krishnaTORQUE/cdefer/refs/heads/main/install.sh | sh
```

## Uninstall

```bash
curl -L https://raw.githubusercontent.com/krishnaTORQUE/cdefer/refs/heads/main/uninstall.sh | sh
```

## Note

-   This project is still in **Alpha**.

## License

This project is licensed under the **MIT** | [View License](LICENSE)

## Contribution

Unless you explicitly state otherwise, any contribution intentionally submitted
for this project by you, shall be licensed as **MIT**, without any additional
terms or conditions.
