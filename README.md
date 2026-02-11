# Local Area Network Monitoring System

**Project Name:** Local Area Network Monitoring System  
**Author:** Kshitij Ban, Niraj Mandal  
**Date:** 2-10-2026  
**Language:** C++  
**Dependencies:** Linux environment, POSIX sockets  

---

## Description

This project is a **low-level LAN monitoring system** implemented in C++. It demonstrates the use of **raw socket programming** to:

1. Detect active hosts in the local area network (LAN).  
2. Serve a simple web interface over HTTP to display the list of active hosts.  

The system works by "poking" each IP address in the LAN on a common port (default: 443) to check if the host is up, and then it listens on port `9898` for incoming browser connections to display the results.

---

## Features

- Scan the LAN IP range for active hosts.  
- Non-blocking socket connections with configurable timeouts.  
- Simple HTTP server to show live results in a browser.  
- Modular design for easier extension and customization.  

---

## Usage

1. **Compile the project:**

```bash
g++ -o lan_monitor lan_monitor.cpp
```
2. **Run the Project**
```
./lan_monitor
```
3. **Connect Frontend**
```
Go to browser and visit
<LAN-IP>/localhot:9898/
```
