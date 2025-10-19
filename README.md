# Cdefer

**A Next-Generation Memory-Safe Preprocessor for C & C++**

Bringing modern memory safety and zero-configuration builds to classic C & C++.

## Overview

`cdefer` draws inspiration from `Zig` & `Golang`, integrating their modern safety and simplicity features directly into C & C++ — while staying fully within the existing languages (no new language required).

`cdefer` is an open-source **preprocessor and tooling layer for C & C++** with one core mission, make C & C++ memory-safe by default — without changing the language.

It enhances traditional compilation pipelines with automatic memory safety checks, build orchestration, and (soon) built-in package management. Unlike other approaches, `cdefer` does not require switching languages, runtimes, or toolchains.

## Install / Update

```bash
curl -L https://raw.githubusercontent.com/krishnaTORQUE/cdefer/refs/heads/main/install.sh | sh
```

## Uninstall

```bash
curl -L https://raw.githubusercontent.com/krishnaTORQUE/cdefer/refs/heads/main/uninstall.sh | sh
```

## To start a project (Example)

```shell
git clone https://github.com/krishnaTORQUE/start
cd start
cdefer run
```

## How it works. Step by step

### Step: 1. Your main.c file

```c
#include <cdeferlib/defer.h>
#include <cdeferlib/try.h>
#include <stdio.h>
#include <stdlib.h>

char* file_content(char* name) {
    char* buf = malloc(1024);
    Defer free(buf);

    FILE* f;
    Try(f, fopen(name, "r"), return "");
    Defer fclose(f);

    fgets(buf, 1024, f);
    return buf;
}

int main() {
    char* content = file_content("start.txt");
    Defer free(content);
    printf("%s\n", content);
    return 0;
}
```

### Step: 2. Check & free memory when out of scope

```c
#include <cdeferlib/try.h>
#include <stdio.h>
#include <stdlib.h>

char* file_content(char* name) {
    char* buf = malloc(1024);

    FILE* f;
    Try(f, fopen(name, "r"), free(buf); return "");

    fgets(buf, 1024, f);
    fclose(f);
    return buf;
}

int main() {
    char* content = file_content("start.txt");
    printf("%s\n", content);
    free(content);
    return 0;
}
```

### Step: 3. Expand macro for compile

```c
#include <stdio.h>
#include <stdlib.h>

char* file_content(char* name) {
    char* buf = malloc(1024);

    FILE* f;
    do {
        f = fopen(name, "r");
        if (!(f)) {
            free(buf);
            return "";
        }
    } while (0);

    fgets(buf, 1024, f);
    fclose(f);
    return buf;
}

int main() {
    char* content = file_content("start.txt");
    printf("%s\n", content);
    free(content);
    return 0;
}
```

-   As you can see the `defer` call when the code get out of scope in `step: 2`.

-   Then it will expand macro `Try` to handle Io operation safely in `step: 3`.

-   If the Io operation fail the code will be out of scope and it will free all the allocated memory.

-   `Step: 4` the code is ready to compile.

## Key Features

#### Memory Safety (Implemented ✅)

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

-   Automatic build system generation
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

## Note

-   This project is still in **Alpha**.

## License

This project is licensed under the **MIT** | [View License](LICENSE)

## Contribution

Unless you explicitly state otherwise, any contribution intentionally submitted
for this project by you, shall be licensed as **MIT**, without any additional
terms or conditions.
