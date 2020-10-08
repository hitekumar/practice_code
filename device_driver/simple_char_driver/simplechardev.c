/* A simple character driver having read and write operations */


#include <linux/init.h>    
#include <linux/module.h>  
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/fs.h>


#define MESSAGE_SIZE    256
#define DEVICE_NAME     "simplechardev"
#define CLASS_NAME      "simple"

#define IOCTL_READ      _IOR('a', 0, int32_t *) 
#define IOCTL_WRITE     _IOW('a', 1, int32_t *) 


MODULE_AUTHOR("Hitesh Kumar");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple character driver for read and write operation");
MODULE_VERSION("1.0");


static int major;
static char message_buf[MESSAGE_SIZE];
static int message_size;
static int open_counts;

static struct class *simplechardev_class = NULL;
static struct device *simplechardev_dev = NULL;

//Forward declaration 
static int simplechardev_open(struct inode * inodeptr, struct file *fileptr);
static ssize_t simplechardev_read(struct file *fileptr, char *buf, size_t len, loff_t *off);
static ssize_t simplechardev_write(struct file *fileptr, const char *buf, size_t len, loff_t *offset);
static int simplechardev_release(struct inode *inodeptr, struct file * fileptr);
static long simplechardev_ioctl(struct file *flieptr, unsigned int cmd, unsigned long arg);

static struct file_operations fops = {
    .open = simplechardev_open,
    .read = simplechardev_read,
    .write = simplechardev_write,
    .release = simplechardev_release,
    .unlocked_ioctl = simplechardev_ioctl,
};


static int __init simplechardev_init(void) {
    printk(KERN_INFO "Simple char_dev: Initilizing KLM\n");

    // Init some local data 
    memset(message_buf,0,MESSAGE_SIZE);
    message_size = 0;
    open_counts = 0;

    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0 ) {
        printk(KERN_ALERT "register_chrdev failed for %s\n", DEVICE_NAME);
        return major;
    }

    // Create a device class 
    simplechardev_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(simplechardev_class)) {
        class_destroy(simplechardev_class);
        unregister_chrdev(major,DEVICE_NAME);
        printk(KERN_ALERT "Failed to create class for dev %s\n", DEVICE_NAME);
        return PTR_ERR(simplechardev_class);    // correct way to return error on pointer;
    }
    printk(KERN_INFO "Creat class is successful for dev %s\n", DEVICE_NAME);

    // Create device 
    simplechardev_dev = device_create(simplechardev_class,NULL,MKDEV(major,0),NULL,DEVICE_NAME);
    if (IS_ERR(simplechardev_dev)) {
        class_destroy(simplechardev_class);
        unregister_chrdev(major,DEVICE_NAME);
        printk(KERN_ALERT "Failed to create device for dev %s\n", DEVICE_NAME);
        return PTR_ERR(simplechardev_dev);    // correct way to return error on pointer;
    }
    return 0;
}

static void __exit simplechardev_exit(void) {
    device_destroy(simplechardev_class, MKDEV(major,0));
    class_unregister(simplechardev_class);
    class_destroy(simplechardev_class);
    unregister_chrdev(major,DEVICE_NAME);
    printk(KERN_INFO "Bye Bye from dev %s\n", DEVICE_NAME);
}

static int simplechardev_open(struct inode * inodeptr, struct file *fileptr) {
    open_counts++;
    printk(KERN_INFO "Device %s is opend for %d times\n", DEVICE_NAME, open_counts);
    return 0;
}

static ssize_t simplechardev_read(struct file *fileptr, char *buf, size_t len, loff_t *off) {
    if (copy_to_user(buf,message_buf,message_size) != 0) {
        printk(KERN_ALERT "Failed to send message to user for device %s\n", DEVICE_NAME);
        return -EFAULT;
    }
    message_size = 0;
    return 0;
}

static ssize_t simplechardev_write(struct file *fileptr, const char *buf, size_t len, loff_t *offset) {
    if (len > MESSAGE_SIZE) {
        printk(KERN_ALERT "Message is too big, max size allowed is %d:%s\n", MESSAGE_SIZE, DEVICE_NAME);
        return -EFAULT;
    }
    copy_from_user(message_buf,buf,len);
    message_size = len;
    printk(KERN_INFO "Message received(%s):%s(%d)\n", DEVICE_NAME, message_buf,message_size);
    return 0;
}

static int simplechardev_release(struct inode *inodeptr, struct file * fileptr) {
    if (open_counts) {
        open_counts--;
    }
    printk(KERN_INFO "Device(%s) is closed, open count is %d\n", DEVICE_NAME, open_counts);
    return 0;
}

static long simplechardev_ioctl(struct file *flieptr, unsigned int cmd, unsigned long arg) {
    static int32_t value;
    switch(cmd) {
        case IOCTL_WRITE:
            copy_from_user(&value, (int32_t *) arg, sizeof(value));
            printk(KERN_INFO "Value passed from user space is %d\n", value);
        break;
        case IOCTL_READ:
            value++;
            copy_to_user((int32_t *) arg, &value, sizeof(value));
            printk(KERN_INFO "Value sent to user is %d\n", value);
        break;
        default:
            return -EFAULT;

    }
    return 0;
}

module_init(simplechardev_init);
module_exit(simplechardev_exit);
