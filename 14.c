#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

static int __init log_redirection_init(void) {
    struct file *log_file;
    mm_segment_t old_fs;
    char *message = "This is a redirected log message from the kernel.\n";

    old_fs = get_fs();
    set_fs(KERNEL_DS);
    log_file = filp_open("/tmp/kernel_log.txt", O_WRONLY | O_CREAT, 0644);
    if (IS_ERR(log_file)) {
        printk(KERN_ERR "Error opening file\n");
        set_fs(old_fs);
        return PTR_ERR(log_file);
    }
    
    vfs_write(log_file, message, strlen(message), &log_file->f_pos);
    filp_close(log_file, NULL);
    set_fs(old_fs);
    return 0;
}

static void __exit log_redirection_exit(void) {
    printk(KERN_INFO "Kernel log redirection module removed\n");
}

module_init(log_redirection_init);
module_exit(log_redirection_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION("Kernel module to redirect log messages to a file");
