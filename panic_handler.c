#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kallsyms.h>
#include <linux/reboot.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/sched/debug.h>
#include <asm/processor.h>
#include <asm/ptrace.h>

/* Function pointer to the original panic handler */
static void (*orig_panic)(const char *fmt, ...);

/* Custom panic handler */
void custom_panic(const char *fmt, ...) {
    struct pt_regs *regs;
    char buffer[256];
    va_list args;

    /* Log the panic message */
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    printk(KERN_EMERG "KERNEL PANIC: %s\n", buffer);

    /* Log the state of CPU registers */
    regs = get_irq_regs();
    if (regs) {
        printk(KERN_EMERG "CPU Registers:\n");
        printk(KERN_EMERG "RIP: %lx\n", regs->ip);
        printk(KERN_EMERG "RAX: %lx\n", regs->ax);
        printk(KERN_EMERG "RBX: %lx\n", regs->bx);
        printk(KERN_EMERG "RCX: %lx\n", regs->cx);
        printk(KERN_EMERG "RDX: %lx\n", regs->dx);
        printk(KERN_EMERG "RSI: %lx\n", regs->si);
        printk(KERN_EMERG "RDI: %lx\n", regs->di);
        printk(KERN_EMERG "RBP: %lx\n", regs->bp);
        printk(KERN_EMERG "RSP: %lx\n", regs->sp);
        printk(KERN_EMERG "R8:  %lx\n", regs->r8);
        printk(KERN_EMERG "R9:  %lx\n", regs->r9);
        printk(KERN_EMERG "R10: %lx\n", regs->r10);
        printk(KERN_EMERG "R11: %lx\n", regs->r11);
        printk(KERN_EMERG "R12: %lx\n", regs->r12);
        printk(KERN_EMERG "R13: %lx\n", regs->r13);
        printk(KERN_EMERG "R14: %lx\n", regs->r14);
        printk(KERN_EMERG "R15: %lx\n", regs->r15);
    } else {
        printk(KERN_EMERG "No register state available.\n");
    }

    /* Log the current process information */
    printk(KERN_EMERG "Current process: %s (PID: %d)\n", current->comm, current->pid);

    /* Call the original panic handler */
    if (orig_panic)
        orig_panic(fmt, args);

    /* Reboot the system */
    emergency_restart();
}

static int __init panic_handler_init(void) {
    /* Locate the original panic function */
    orig_panic = (void *)kallsyms_lookup_name("panic");
    if (!orig_panic) {
        printk(KERN_ERR "panic_handler: Unable to find the original panic function\n");
        return -ENOENT;
    }

    /* Replace the panic function with our custom handler */
    *(unsigned long *)kallsyms_lookup_name("panic") = (unsigned long)custom_panic;

    printk(KERN_INFO "panic_handler: Module loaded\n");
    return 0;
}

static void __exit panic_handler_exit(void) {
    /* Restore the original panic function */
    if (orig_panic) {
        *(unsigned long *)kallsyms_lookup_name("panic") = (unsigned long)orig_panic;
    }

    printk(KERN_INFO "panic_handler: Module unloaded\n");
}

module_init(panic_handler_init);
module_exit(panic_handler_exit);

MODULE_LICENSE("GPL_V3");
MODULE_AUTHOR("Umar");
MODULE_DESCRIPTION("A kernel module to customize the kernel panic handler");
MODULE_VERSION("1.0");
