# Demo Plugin

A C++20 plugin for **IonTrader Engine** that hooks into trade events and generates trade comments for specific tracked accounts.  
The plugin uses **RapidJSON** for configuration parsing and is designed to be dynamically loaded by the server.

For more information about the IonTrader Engine, visit the [official documentation](https://iontrader.com/).  
Learn more about plugins [IonTrader Plugins](https://iontrader.com/plugins/).

---

## Features

- Hooks trade open events.
- Generates structured trade snapshots as comments.
- Configurable tracked logins via JSON.
- Safe C-compatible factory functions for dynamic loading.

---

## Requirements

- **Platform:** Linux Ubuntu 24.04 (x86_64).
- C++20 compatible compiler (Clang/GCC/MSVC).
- CMake >= 3.16.
- RapidJSON library.
- Alfa Core Server headers and structures.
