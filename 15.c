#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>

#define DEVICE_NAME "my_ioctl_device"
#define IOCTL_CMD _IOW('a', 1, int)

static int major;
static char data_buffer[256];

static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    switch (cmd) {
        case IOCTL_CMD:
            if (copy_from_user(data_buffer, (int *)arg, sizeof(int))) {
                return -EFAULT;
            }
            printk(KERN_INFO "Received data from user space: %d\n", *((int *)data_buffer));
            break;
        default:
            return -EINVAL;
    }
    return 0;
}

static struct file_operations fops = {
    .unlocked_ioctl = device_ioctl,
};

static int __init ioctl_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) {
        printk(KERN_ERR "Failed to register device\n");
        return major;
    }
    printk(KERN_INFO "Device registered with major number %d\n", major);
    return 0;
}

static void __exit ioctl_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "Device unregistered\n");
}

module_init(ioctl_init);
module_exit(ioctl_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION("Kernel module for ioctl communication with user space");
