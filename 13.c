#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>

static struct task_struct *thread1;
static struct task_struct *thread2;

static int shared_data = 0;
static DEFINE_MUTEX(shared_mutex);

int thread_fn1(void *data) {
    while (!kthread_should_stop()) {
        mutex_lock(&shared_mutex);
        shared_data++;
        printk(KERN_INFO "Thread 1 incremented shared_data: %d\n", shared_data);
        mutex_unlock(&shared_mutex);
        ssleep(1);
    }
    return 0;
}

int thread_fn2(void *data) {
    while (!kthread_should_stop()) {
        mutex_lock(&shared_mutex);
        shared_data--;
        printk(KERN_INFO "Thread 2 decremented shared_data: %d\n", shared_data);
        mutex_unlock(&shared_mutex);
        ssleep(1);
    }
    return 0;
}

static int __init thread_shared_data_init(void) {
    thread1 = kthread_run(thread_fn1, NULL, "thread1");
    thread2 = kthread_run(thread_fn2, NULL, "thread2");
    return 0;
}

static void __exit thread_shared_data_exit(void) {
    kthread_stop(thread1);
    kthread_stop(thread2);
    printk(KERN_INFO "Threads stopped\n");
}

module_init(thread_shared_data_init);
module_exit(thread_shared_data_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION("Kernel module with threads sharing data");
