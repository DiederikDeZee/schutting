#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>

#define DEVICE_NAME "schutting"
#define CLASS_NAME  "schut"

static int device_open_count = 0;
static int majorNumber;
static struct class* schuttingClass = NULL;
static struct device* schuttingDevice = NULL;

static int device_open(struct inode *inode, struct file *file) {
    if (device_open_count)
        return -EBUSY;
    
    device_open_count++;
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    device_open_count--;
    return 0;
}

static ssize_t device_read(struct file *file, char __user *buf, size_t len, loff_t *ppos) {
    return 0;
}

static ssize_t device_write(struct file *file, const char __user *buf, size_t len, loff_t *ppos) {
    return len;
}

static struct file_operations fops = {
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .write = device_write
};

int init_module(void) {
    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    if (majorNumber<0){
        printk(KERN_ALERT "schutting failed to register a major number\n");
        return majorNumber;
    }
    printk(KERN_INFO "schutting: registered correctly with major number %d\n", majorNumber);

    schuttingClass = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(schuttingClass)){
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(schuttingClass);
    }
    printk(KERN_INFO "schutting: device class registered correctly\n");

    schuttingDevice = device_create(schuttingClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    if (IS_ERR(schuttingDevice)){
        class_destroy(schuttingClass);
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device\n");
        return PTR_ERR(schuttingDevice);
    }
    printk(KERN_INFO "schutting: device class created correctly\n");
    return 0;
}

void cleanup_module(void) {
    device_destroy(schuttingClass, MKDEV(majorNumber, 0));     // remove the device
    class_unregister(schuttingClass);                          // unregister the device class
    class_destroy(schuttingClass);                             // remove the device class
    unregister_chrdev(majorNumber, DEVICE_NAME);             // unregister the major number
    printk(KERN_INFO "schutting: Goodbye from the LKM!\n");
}

MODULE_LICENSE("GPL");
