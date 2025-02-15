#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/spinlock.h>

static spinlock_t my_lock;
static struct timer_list my_timer;

void my_timer_callback(struct timer_list *t) {
    unsigned long flags;
    spin_lock_irqsave(&my_lock, flags);
    printk(KERN_INFO "Timer expired, inside spinlock\n");
    spin_unlock_irqrestore(&my_lock, flags);
}

static int __init spinlock_timer_init(void) {
    spin_lock_init(&my_lock);
    timer_setup(&my_timer, my_timer_callback, 0);
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000));
    return 0;
}

static void __exit spinlock_timer_exit(void) {
    del_timer(&my_timer);
    printk(KERN_INFO "Spinlock and timer module removed\n");
}

module_init(spinlock_timer_init);
module_exit(spinlock_timer_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION("Kernel module with spinlock and timer");
