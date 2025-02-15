#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>

static int major;
static struct class *my_class;
static struct device *my_device;

static int __init device_driver_init(void) {
    major = register_chrdev(0, "my_device", NULL);
    if (major < 0) {
        printk(KERN_ERR "Failed to register device\n");
        return major;
    }

    my_class = class_create(THIS_MODULE, "my_class");
    if (IS_ERR(my_class)) {
        unregister_chrdev(major, "my_device");
        return PTR_ERR(my_class);
    }

    my_device = device_create(my_class, NULL, MKDEV(major, 0), NULL, "my_device");
    if (IS_ERR(my_device)) {
        class_destroy(my_class);
        unregister_chrdev(major, "my_device");
        return PTR_ERR(my_device);
    }

    printk(KERN_INFO "Device driver registered with major number %d\n", major);
    return 0;
}

static void __exit device_driver_exit(void) {
    device_destroy(my_class, MKDEV(major, 0));
    class_destroy(my_class);
    unregister_chrdev(major, "my_device");
    printk(KERN_INFO "Device driver unregistered\n");
}

module_init(device_driver_init);
module_exit(device_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION("Kernel module that registers a simple device driver");
