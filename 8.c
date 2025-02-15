#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>

static int __init memory_init(void) {
    char *buf;
    buf = kmalloc(1024, GFP_KERNEL);
    if (!buf) {
        printk(KERN_ERR "Memory allocation failed\n");
        return -ENOMEM;
    }
    strcpy(buf, "Memory allocated successfully!\n");
    printk(KERN_INFO "%s", buf);
    kfree(buf);
    return 0;
}

static void __exit memory_exit(void) {
    printk(KERN_INFO "Memory module exited\n");
}

module_init(memory_init);
module_exit(memory_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION("Kernel module that demonstrates memory allocation");
