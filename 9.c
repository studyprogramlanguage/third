#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>

static struct task_struct *thread;

int thread_fn(void *data) {
    while (!kthread_should_stop()) {
        printk(KERN_INFO "Thread running...\n");
        ssleep(1);
    }
    return 0;
}

static int __init thread_init(void) {
    thread = kthread_run(thread_fn, NULL, "my_thread");
    if (IS_ERR(thread)) {
        printk(KERN_ERR "Thread creation failed\n");
        return PTR_ERR(thread);
    }
    return 0;
}

static void __exit thread_exit(void) {
    kthread_stop(thread);
    printk(KERN_INFO "Thread stopped\n");
}

module_init(thread_init);
module_exit(thread_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION("Kernel module using threads");
