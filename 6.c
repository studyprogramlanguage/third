#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>

static struct timer_list my_timer;

void my_timer_callback(struct timer_list *t) {
    printk(KERN_INFO "Timer expired\n");
}

static int __init timer_init(void) {
    printk(KERN_INFO "Timer module initialized\n");
    timer_setup(&my_timer, my_timer_callback, 0);
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000));
    return 0;
}

static void __exit timer_exit(void) {
    del_timer(&my_timer);
    printk(KERN_INFO "Timer module removed\n");
}

module_init(timer_init);
module_exit(timer_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION("Kernel module with timer functionality");
