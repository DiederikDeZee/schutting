#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define DEVICE_NAME "schutting"

static int device_open = 0;

static int device_open(struct inode *inode, struct file *file) {
    if (device_open)
        return -EBUSY;

    device_open++;
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    device_open--;
    return 0;
}

static ssize_t device_write(struct file *file, const char __user *buf, size_t len, loff_t *ppos) {
    // Discard the written data and return successful write
    return len;
}

static struct file_operations fops = {
    .open = device_open,
    .release = device_release,
    .write = device_write
};

int init_module(void) {
    int ret;

    ret = register_chrdev(0, DEVICE_NAME, &fops);

    if (ret < 0) {
        printk(KERN_ALERT "schutting load failed with %d\n", ret);
        return ret;
    }

    printk(KERN_INFO "schutting module loaded with device major number %d\n", ret);
    return 0;
}

void cleanup_module(void) {
    unregister_chrdev(0, DEVICE_NAME);
    printk(KERN_INFO "schutting module unloaded\n");
}
