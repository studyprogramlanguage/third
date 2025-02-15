#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

static int __init file_init(void) {
    struct file *file;
    mm_segment_t old_fs;
    
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    
    file = filp_open("/tmp/hello_kernel.txt", O_CREAT | O_WRONLY, 0644);
    if (IS_ERR(file)) {
        printk(KERN_ERR "Error creating file\n");
        return PTR_ERR(file);
    }
    
    vfs_write(file, "Hello Kernel!\n", 14, &file->f_pos);
    filp_close(file, NULL);
    
    set_fs(old_fs);
    return 0;
}

static void __exit file_exit(void) {
    printk(KERN_INFO "File write complete\n");
}

module_init(file_init);
module_exit(file_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION("Kernel module to create and write to a file");
