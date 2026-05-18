# 🔍 CRecon — A TCP Port Scanner in C

> Built from scratch in C as part of a journey into cybersecurity and low-level network programming.

---

## About

CRecon is a lightweight TCP port scanner written in pure C. It resolves hostnames via DNS, connects to target ports using non-blocking sockets, and classifies each port as Open, Closed, or Filtered — similar to how tools like `nmap` work under the hood.

This project was built to understand the fundamentals of:

- Raw socket programming with non-blocking I/O
- Multiplexing connections via `select()`
- DNS resolution with `getaddrinfo`
- Network reconnaissance techniques
- Memory management in C

---

## Screenshots

**Open Ports Detected**
![Open Ports](C/outputs/2026-05-06_16-17.png)

**Multiple Targets**
![Multiple Targets](C/outputs/2026-05-06_16-18.png)

---

## Features

- Scan single or multiple targets (IP or hostname)
- Resolves hostnames to all mapped IPs automatically
- Non-blocking sockets with `select()` — scans all ports simultaneously
- Classifies ports as `OPEN`, `CLOSED`, or `FILTERED`
- Configurable port ranges via `-p` flag (default: top 1024)
- Clean scan report output per IP

---

## Usage

```bash
# Single target
./crecon 192.168.1.1

# Multiple targets
./crecon google.com 192.168.1.1

# Specific ports
./crecon 192.168.1.1 -p 80 443

# Port range
./crecon 192.168.1.1 -p 1-1024
```

---

## Build

```bash
git clone https://github.com/Kshitij-jj/CRecon
cd C
make
```

**Dependencies:** None — pure POSIX C, standard libraries only.

**Tested on:** Linux (Kali)

---

## Project Structure

```
C/
├── src/
│   ├── main.c        # Entry point, scan loop
│   ├── scanner.c     # Non-blocking TCP scan with select()
│   ├── input.c       # Argument parsing, DNS resolution
│   ├── output.c      # Scan report printing
│   └── helper.c      # Memory cleanup, port utilities
├── include/
│   ├── common.h      # Shared structs, enums, defines
│   ├── scanner.h
│   ├── input.h
│   ├── output.h
│   └── helper.h
└── Makefile
```

---

## How It Works

### Why Sequential Scanning Is Slow

The naive approach scans one port at a time:

```
connect(port 1) → wait 1s → result
connect(port 2) → wait 1s → result
...
connect(port 1024) → wait 1s → result
```

Scanning 1024 ports with a 1 second timeout = **~17 minutes** per target. Every port blocks the thread until the connection succeeds or times out.

### CRecon's Approach — Non-blocking + `select()`

CRecon uses non-blocking sockets and `select()` to scan all ports simultaneously:

```
Create 1024 non-blocking sockets
connect() all at once → returns immediately (EINPROGRESS)
select() waits up to 1s for ANY socket to be ready
Check each ready socket → classify result
Total time: ~1 second regardless of port count
```

**Step by step:**

1. `fcntl(sockfd, F_SETFL, O_NONBLOCK)` — makes socket non-blocking
2. `connect()` returns immediately with `EINPROGRESS` instead of blocking
3. `select()` on `writefds` — sleeps until one or more connections complete
4. `getsockopt(SO_ERROR)` — checks if connection succeeded or failed
5. Classify:
   - `SO_ERROR == 0` → `OPEN`
   - `SO_ERROR == ECONNREFUSED` → `CLOSED`
   - Not ready after timeout → `FILTERED`

```
All ports → non-blocking connect() → select() → getsockopt() → Report
```

---

## Roadmap

- [x] Single target scanning
- [x] Multiple target scanning
- [x] Custom port ranges via `-p` flag
- [x] Non-blocking sockets with `select()`
- [ ] HTML report output via `-o` flag
- [ ] Multithreaded scanning (thread pool)
- [ ] Banner grabbing (service detection)
- [ ] UDP scan support
- [ ] OS fingerprinting

---

## Legal Disclaimer

> This tool is intended for **educational purposes** and **authorized penetration testing only**.
> Scanning systems without explicit permission is **illegal** and unethical.
> Always obtain written permission before scanning any network or system you do not own.

---

## Author

**Kshitij** — Built as a learning project while diving deep into cybersecurity, network programming, and C systems development.

> _"To understand security tools, you must build them yourself."_

---

## Learning Resources

- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- [Nmap — The Art of Port Scanning](https://nmap.org/book/toc.html)
- [TCP/IP Illustrated — W. Richard Stevens](https://www.amazon.com/TCP-Illustrated-Protocols-Addison-Wesley-Professional/dp/0321336313)
- [The Linux Programming Interface](https://man7.org/tlpi/)
