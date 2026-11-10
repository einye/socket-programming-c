# C Socket Programming - Calculator & Bank

A small collection of C networking projects demonstrating **connection-oriented (TCP)**, **connectionless (UDP)**, and **standalone** program design across **Windows (Winsock2)** and **Linux (BSD sockets)**.

All programs share a simple text-based request/response model: the client sends an expression or command, the server parses it, computes a response, and sends it back.
## Projects

| File | Platform | Protocol | Role | Description |
|------|----------|----------|------|-------------|
| `standaloneCalculator.c` | Any | — | — | Local stdin calculator (no networking) |
| `windows_tcp_server_calculator.c` | Windows | TCP | Server | Accepts `int op int`, returns result |
| `windows_tcp_client_calculator.c` | Windows | TCP | Client | Sends expression, prints result |
| `windows_udp_server_calculator.c` | Windows | UDP | Server | Datagram-based calculator |
| `windows_udp_client_calculator.c` | Windows | UDP | Client | Sends expression via UDP |
| `linux_bank_server.c` | Linux | UDP | Server | Handles `open/close/deposit/withdraw/balance/statement/exit` |
| `linux_bank_client.c` | Linux | UDP | Client | Interactive menu-driven client |

---

## Requirements

- **Windows:** MSVC or MinGW (`gcc`), link `Ws2_32.lib`
- **Linux:** GCC or Clang

## Installation & Build

### Windows (MinGW)
```bash
gcc windows_tcp_server_calculator.c -o tcp_server -lws2_32
gcc windows_tcp_client_calculator.c -o tcp_client -lws2_32
gcc windows_udp_server_calculator.c -o udp_server -lws2_32
gcc windows_udp_client_calculator.c -o udp_client -lws2_32
gcc standaloneCalculator.c -o standaloneCalculator -lws2_32
```

### Linux
```bash
gcc linux_bank_server.c -o bank_server
gcc linux_bank_client.c -o bank_client
```
## Known Limitations / Issues

Bank server is a stub, no real persistence, balances, PINs, or account state. Every request returns a canned response.

No authentication - PINs are sent in plaintext over UDP; no transport security.

UDP bank app has no delivery guarantee - packets can be dropped, duplicated, or reordered.

Calculator is integer-only - no floating point, no precedence, no parentheses.

Division is integer division (/ truncates; no float).

Single-threaded servers - TCP server handles one client at a time.

No timeout or error handling on recv / recvfrom (blocking calls assumed to succeed).

Winsock errors are not checked - WSAStartup, socket, connect, bind, listen, accept return values are ignored for brevity.

SERVER_IP is hardcoded (127.0.0.1) - must be edited manually for remote testing.

Buffer handling is minimal - snprintf/strncpy used in most paths, but some scanf/strcpy-style reads assume well-formed input.

No build system - compilation is manual; no Makefile or CMake.

## Notes

Windows programs require Winsock initialization (WSAStartup / WSACleanup), Linux does not.

The Linux and Windows calculator logic is identical; only the socket API differs (closesocket vs close, SOCKET vs int, -lws2_32 vs default libc).

The bank server uses strncasecmp for case-insensitive command matching.