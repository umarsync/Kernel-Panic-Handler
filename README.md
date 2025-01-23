# Kernel Panic Handler

This kernel module customizes the behavior of the Linux kernel panic handler. It logs additional information, such as the state of CPU registers and the current process, before rebooting the system.

## Features

- **Custom Panic Handler:** Replaces the default kernel panic handler with a custom implementation.
- **Logs CPU Registers:** Logs the state of CPU registers during a panic.
- **Logs Process Information:** Logs the current process name and PID.
- **Automatic Reboot:** Reboots the system after logging the information.

## Prerequisites

- **Linux Kernel Development Environment:**
  - GCC compiler
  - Linux kernel headers
  - `make` utility
- **Root Access:** Required to load and unload kernel modules.

## Installation

### 1. Clone the Repository
Clone the repository to your local machine:
```bash
git clone https://github.com/your-username/kernel-panic-handler.git
cd kernel-panic-handler
```

### 2. Compile the Kernel Module
Use the provided `Makefile` to compile the module:
```bash
make
```
This will generate a kernel object file named `panic_handler.ko`.

### 3. Load the Module
Load the module into the kernel using `insmod`:
```bash
sudo insmod panic_handler.ko
```

### 4. Test the Module
To test the module, you can trigger a kernel panic (use with caution):
```bash
echo c > /proc/sysrq-trigger
```

### 5. View Logs
Use `dmesg` to view the panic logs:
```bash
dmesg
```

### 6. Unload the Module
Unload the module when done:
```bash
sudo rmmod panic_handler
```

## Usage

### Example Output
When a kernel panic occurs, the module logs the following information:
```bash
[  123.456789] KERNEL PANIC: <panic message>
[  123.567890] CPU Registers:
[  123.567890] RIP: <value>
[  123.567890] RAX: <value>
[  123.567890] RBX: <value>
[  123.567890] RCX: <value>
[  123.567890] RDX: <value>
[  123.567890] RSI: <value>
[  123.567890] RDI: <value>
[  123.567890] RBP: <value>
[  123.567890] RSP: <value>
[  123.567890] R8:  <value>
[  123.567890] R9:  <value>
[  123.567890] R10: <value>
[  123.567890] R11: <value>
[  123.567890] R12: <value>
[  123.567890] R13: <value>
[  123.567890] R14: <value>
[  123.567890] R15: <value>
[  123.567890] Current process: <process name> (PID: <pid>)
```

## Advanced Configuration

### Logging to a File
Instead of logging to the kernel log buffer, you can write logs to a file in `/var/log`. Use `filp_open`, `vfs_write`, and `filp_close` to implement file-based logging.

### Additional Debug Information
You can extend the module to log additional information, such as:
- Stack trace
- Memory usage
- Hardware state

## Warning

- **System Stability:** Modifying the kernel panic handler can lead to unpredictable behavior. Use this module in a controlled environment.
- **Security Risks:** This module can be used for malicious purposes. Ensure you have proper authorization before using it on any system.
- **Kernel Version Compatibility:** This module is tested on Linux kernels 5.x. It may require adjustments for other versions.

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

### Steps to Contribute:
1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Commit your changes.
4. Submit a pull request.
