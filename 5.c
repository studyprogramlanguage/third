#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/syscalls.h>

unsigned long *sys_call_table;

asmlinkage int (*original_sys_getpid)(void);

asmlinkage int my_sys_getpid(void) {
    printk(KERN_INFO "Intercepted sys_getpid\n");
    return original_sys_getpid();
}

static int __init syscall_init(void) {
    sys_call_table = (unsigned long *)kallsyms_lookup_name("sys_call_table");
    if (!sys_call_table) {
        printk(KERN_ERR "Couldn't find sys_call_table\n");
        return -1;
    }
    
    original_sys_getpid = (void *)sys_call_table[__NR_getpid];
    sys_call_table[__NR_getpid] = (unsigned long)my_sys_getpid;
    
    return 0;
}

static void __exit syscall_exit(void) {
    sys_call_table[__NR_getpid] = (unsigned long)original_sys_getpid;
    printk(KERN_INFO "Syscall hook removed\n");
}

module_init(syscall_init);
module_exit(syscall_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION("Kernel module for syscall hooking");
