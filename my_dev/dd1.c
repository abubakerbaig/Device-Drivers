#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define NAME MyCharDevice

//Funcion prototypes

int NAME_open(struct inode *indoe, struct file *filp);
int NAME_release(struct inode *inode, struct file *filp);
ssize_t NAME_write(struct file *file, char __user *Ubuff, size_t count, loff_t *offp);
ssize_t NAME_read(struct file *file, char __user *Ubuff, size_t count, loff_t *offp);
int NAME_flush(struct file *filp);

//structure that defines the operaions that the driver provides

struct file_operations fops =
    {
        .owner = THIS_MODULE,
        .open = NAME_open,
        .read = NAME_read,
        ,write = NAME_write,
        .release = NAME_release,
        .flush = NAME_flush,
    };

//structure for a character driver

struct cdev *my_cdev;

//init module

static int __init CharDevice_init(void) {

    int result;
    int MAJOR, MINOR;
    dev_t Mydev;
    Mydev = MKDEV(255,0);//create a device number
    MAJOR = MAJOR(Mydev);
    MINOR = MINOR(Mydev);

    printk("\nThe Major Number is %d... The Minor Number is %d\n",MAJOR, MINOR);

    result = register_chardev-region(Mydev,1,"MyCharDevice");//Register device region......

    if(result < 0)  {
        printk(KERN_ALERT "\n The Region requestd is not obtained\n");
        return -1;
    }

    my_cdev = cdev_alloc();     //allocae memory to char device structure
    my_cdev->ops = &fops;       //link our file operations to the char device

    result = cdev_add(mydev, Mydev, 1); //Notify the kernel about the new device

    if(result < 0)  {
        printk(KERN_ALERT "\n The Character Device has not been created......\n");
        unregister_chrdev_region(Mydev, 1); //unreg the dev numbers and the device created
    }

    return 0;
}

//Cleanup Module
void __exit CharDevice_exit(void)   {
    dev_t Mydev;
    int MAJOR, MINOR;
    Mydev = MKDEV(255,0);
    MAJOR = MAJOR(Mydev);
    MINOR = MINOR(MYdev);

    printk("\nThe Major Number is %d... The Minor Number is %d\n",MAJOR, MINOR);

    unregister_chrdev_region(Mydev, 1); //unreg the dev numbers and the device created
    cdev_del(my_cdev);
    printk(KERN_ALERT "\nI have Unregistessressdss thess tuff that was allocated... Good Bye forever.....\n");
//    return;
}

int NAME_open(struct inode *inode, struct file *filp)   {
    printk(KERN_ALERT "\n This is the KERNEL... Open Call executing......I have nothing to do here..... \n");
    return 0;
}

int NAME_flush(structs indoe *indoe, struct file *filp) {
    printk(KERN_ALERT"\n This is the release method of my character device driver.... BaBye... \n");
    return 0;
}

ssize_t NAME_write(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp)   {
    char Kbuff[80];
    unsigned long result;
    ssize_t retval;
    //strcpy(Kbuff,Ubuff)
    result = copy_from_user((char *)Kbuff,(char *)Ubuff, count);    //get user data
    
    if(result == 0) {
        printk(KERN_ALERT"\n Messages from the user ..... \n >>> %s <<<\n",Kbuff);
        printk(KERN_ALERT "\n part DAta copied.... \n");
        retval=count;
        return retval;
    }
    else if(result > 0) {
        printk(KERN_ALERT "\n Message from the user .... \n >>> %s <<<\n",Kbuff);
        printk(KERN_ALERT "\n Part Data copied.... \n");
        retval=conut;
        return retval;
    }
    else{
        printk(KERN_ALERT "\n Error Writing Data\n");
        retval=-EFAULT;
        return retval;
    }
}

ssize_t NAME_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp)   {
    char Kbuff[] = "This is some data form the kernel to the user..... USER IF you find this.. have fun";
    unsigned long result;
    ssize_t retval;
    //strcpy(Kbuff,Ubuff)
    result = copy_to_user((char *)Ubuff,(char *)Kbuff, count);    //get user data
    
    if(result == 0) {
       // printk(KERN_ALERT"\n Messages from the user ..... \n >>> %s <<<\n",Kbuff);
        printk(KERN_ALERT "\n  DAta read successfully.... \n");
        retval=count;
        return retval;
    }
    else if(result > 0) {
       // printk(KERN_ALERT "\n Message from the user .... \n >>> %s <<<\n",Kbuff);
        printk(KERN_ALERT "\n DAta read successfully.... \n");
        retval=conut;
        return retval;
    }
    else{
        printk(KERN_ALERT "\n Error Reading Data\n");
        retval=-EFAULT;
        return retval;
    }
}

int NAME_flush (struct file *filp)      {
    printk(KERN_ALERT "\n This the close function of the file....\n");
    return 0;
}

module_init(CharDevice_init);
module_exit(CharDevice_exit);