# 🔍 CScan — A TCP Port Scanner in C

> Built from scratch in C as part of a journey into cybersecurity and low-level network programming.

---

## About

CScanner is a lightweight TCP port scanner written in pure C. It resolves hostnames via DNS, connects to target ports using raw sockets, and classifies each port as Open, Closed, or Filtered — similar to how tools like `nmap` work under the hood.

This project was built to understand the fundamentals of:
- Raw socket programming
- DNS resolution with `getaddrinfo`
- Network reconnaissance techniques
- Memory management in C

---

## Features

- Scan single or multiple targets (IP or hostname)
- Resolves hostnames to all mapped IPs automatically
- Classifies ports as `OPEN`, `CLOSED`, or `FILTERED`
- Configurable port ranges (default: top 1024)
- Clean scan report output per IP

---

## Usage

```bash
# Single target
./cscan google.com

# Multiple targets
./cscan google.com 192.168.1.1 scanme.nmap.org

# Coming soon: custom ports
./cscan google.com -p 80 443
./cscan google.com -p 1-1024
```

---

## Build

```bash
git clone https://github.com/Kshitij-jj/Local-Area-Network-Monitoring-Tool
cd cscan
make
```

**Dependencies:** None — pure POSIX C, standard libraries only.

**Tested on:** Linux (Ubuntu/Kali)

---

## Project Structure

```
C/
├── main.c          # Entry point, scan loop
├── scanner.c/h     # TCP connect scan logic
├── input.c/h       # Argument parsing, DNS resolution
├── output.c/h      # Scan report printing
├── helper.c/h      # Memory cleanup
└── common.h        # Shared structs, enums, defines
```

---

## How It Works

CScanner uses **TCP Connect Scanning** — the same technique used by nmap's `-sT` flag:

1. Creates a raw TCP socket
2. Attempts `connect()` to target IP:port
3. Classifies result:
   - Connection success → `OPEN`
   - `ECONNREFUSED` → `CLOSED`
   - `ETIMEDOUT` / `EHOSTUNREACH` → `FILTERED`

```
Target → DNS Resolution → IP List → TCP Connect per Port → Report
```

---

## Roadmap

- [ ] Custom port ranges via `-p` flag
- [ ] Multithreaded scanning (thread pool)
- [ ] UDP scan support
- [ ] Output to file (JSON / CSV)
- [ ] Banner grabbing (service detection)
- [ ] OS fingerprinting

---

## Legal Disclaimer

> This tool is intended for **educational purposes** and **authorized penetration testing only**.
> Scanning systems without explicit permission is **illegal** and unethical.
> Always obtain written permission before scanning any network or system you do not own.

---

## Author

Built as a learning project while diving deep into cybersecurity, network programming, and C systems development.

> *"To understand security tools, you must build them yourself."*

---

## Learning Resources

- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- [Nmap — The Art of Port Scanning](https://nmap.org/book/toc.html)
- [TCP/IP Illustrated — W. Richard Stevens](https://www.amazon.com/TCP-Illustrated-Protocols-Addison-Wesley-Professional/dp/0321336313)
- [The Linux Programming Interface](https://man7.org/tlpi/)
