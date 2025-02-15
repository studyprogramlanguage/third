#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

static int __init proc_info_init(void) {
    struct task_struct *task;
    for_each_process(task) {
        printk(KERN_INFO "Process: %s (PID: %d)\n", task->comm, task->pid);
    }
    return 0;
}

static void __exit proc_info_exit(void) {
    printk(KERN_INFO "Exiting process info module\n");
}

module_init(proc_info_init);
module_exit(proc_info_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION("Kernel module to print process information");
