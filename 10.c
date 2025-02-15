#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/spinlock.h>

static spinlock_t my_lock;

static int __init spinlock_init(void) {
    spin_lock_init(&my_lock);
    spin_lock(&my_lock);
    printk(KERN_INFO "Spinlock acquired\n");
    spin_unlock(&my_lock);
    printk(KERN_INFO "Spinlock released\n");
    return 0;
}

static void __exit spinlock_exit(void) {
    printk(KERN_INFO "Spinlock module exited\n");
}

module_init(spinlock_init);
module_exit(spinlock_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION("Kernel module using spinlocks");
