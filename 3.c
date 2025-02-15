#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int input_val = 0;

module_param(input_val, int, S_IRUGO);

static int __init param_init(void) {
    printk(KERN_INFO "Input parameter value: %d\n", input_val);
    return 0;
}

static void __exit param_exit(void) {
    printk(KERN_INFO "Exiting parameter module\n");
}

module_init(param_init);
module_exit(param_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION("Kernel module that takes input parameter");
