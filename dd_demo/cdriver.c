#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("SELFTEST");

static int sample_open(struct inode *inode, struct file *filp)  {
    printk("Open file is done\n");
    return 0;
}

ssize_t sample_read (struct file *fops, char __user *Ubuff, size_t count, loff_t *filp)    {
    printk("\nReading file\n");

    return 0;
}

ssize_t sample_write (struct file *fops, const char __user *Kbuff, size_t count, loff_t *filp) {
    printk("\nWriting file\n");
    return 0;
}

static int sample_close(struct inode *inode, struct file *filp) {
    printk("close file is done\n");
    return 0;
}


static dev_t devnum;
static struct cdev _cdev;

static struct file_operations fops={
    .open = sample_open,
    .release = sample_close,
    .read = sample_read,
    .write = sample_write,
};

static int chrdev_init(void) {
    int ret;
    int MAJOR, MINOR;
    devnum=MKDEV(30, 0);
    
    MAJOR = MAJOR(devnum);
    MINOR = MINOR(devnum);

    printk("\nThe MINOR number is = %d \n  The MAJOR number is = %d \n",MINOR, MAJOR);

    ret = register_chrdev_region(devnum, 1, "sample_dev");

    if(ret < 0) {
        printk(KERN_ALERT "\n Failed to register device region\n");
        return -1;
    }

    cdev_init(&_cdev, &fops);    //binding char dev with file operstions
    ret=cdev_add(&_cdev, devnum, 1);

    if(ret < 0) {
        printk(KERN_ALERT "\n Failed to add char device driver\n");
        unregister_chrdev_region(devnum,1);
        return -1;
    }

    printk("\nDone Initialization\n");

    return 0;

}

static void chrdev_exit(void) {
    unregister_chrdev_region(devnum, 1);
    printk(KERN_ALERT "\nremoving module driver..... \n");
}

module_init(chrdev_init);
module_exit(chrdev_exit);