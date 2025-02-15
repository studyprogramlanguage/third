#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int num = 42;

static int __init var_init(void) {
    printk(KERN_INFO "Variable value: %d\n", num);
    return 0;
}

static void __exit var_exit(void) {
    printk(KERN_INFO "Exiting variable module\n");
}

module_init(var_init);
module_exit(var_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION("Kernel module that prints a variable");
