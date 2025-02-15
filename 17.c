#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>

static struct task_struct *my_thread;

int thread_function(void *data) {
    while (!kthread_should_stop()) {
        printk(KERN_INFO "Kernel thread is running...\n");
        ssleep(1);
    }
    return 0;
}

static int __init thread_exit_init(void) {
    my_thread = kthread_run(thread_function, NULL, "my_kernel_thread");
    if (IS_ERR(my_thread)) {
        printk(KERN_ERR "Failed to create thread\n");
        return PTR_ERR(my_thread);
    }
    return 0;
}

static void __exit thread_exit_cleanup(void) {
    kthread_stop(my_thread);
    printk(KERN_INFO "Kernel thread stopped\n");
}

module_init(thread_exit_init);
module_exit(thread_exit_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION("Kernel module that demonstrates stopping a kernel thread");
