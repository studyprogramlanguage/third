#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init log_level_init(void) {
    printk(KERN_DEBUG "This is a debug message\n");
    printk(KERN_INFO "This is an info message\n");
    printk(KERN_NOTICE "This is a notice message\n");
    printk(KERN_WARNING "This is a warning message\n");
    printk(KERN_ERR "This is an error message\n");
    printk(KERN_ALERT "This is an alert message\n");
    printk(KERN_CRIT "This is a critical message\n");
    printk(KERN_EMERG "This is an emergency message\n");
    return 0;
}

static void __exit log_level_exit(void) {
    printk(KERN_INFO "Log level module removed\n");
}

module_init(log_level_init);
module_exit(log_level_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION("Kernel module that demonstrates log levels");
