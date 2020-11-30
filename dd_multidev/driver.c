#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/circ_buf.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/semaphore.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MIRZA");

#define NMAJOR 3
#define NMICROS 3 
#define DEV_NAME "dev_dri"
#define SIZE 32

static dev_t devnum;

static struct mydevices {
    struct semaphore _sem;
    struct cdev _cdev;
    struct circ_buf cbuff;
    wait_queue_head_t wqR,wqW;

}devs[NMICROS];

static int sample_open (struct inode *inodep, struct file *fp )   {
    struct mydevices *devp;
    printk("Opening a file driver.\n");
    devp = container_of(inodep->i_cdev, struct mydevices, _cdev);

    fp->private_data = devp;

    return 0;
}

static int sample_close(struct inode *inode, struct file *fp)  {

    printk("closing a file driver.\n");
    return 0;
}

static ssize_t sample_read (struct file *fp, char __user *Ubuff, size_t count, loff_t *offset)    {

    int mini,i,ret;
    struct mydevices *devp = fp->private_data;

    printk("Reading a file driver.\n");

    wait_event_interruptible(devp->wqR, CIRC_CNT(devp->cbuff.head, devp->cbuff.tail, SIZE)>0);
        
    mini= min(count, (size_t)CIRC_CNT(devp->cbuff.head,devp->cbuff.tail,SIZE));

    for(i=0; i<mini; i++)   {
    
        ret = copy_to_user(Ubuff+i, devp->cbuff.buf+devp->cbuff.tail,1);
        if(ret) {
            printk("failed to read byte no. %d",i);
            return -EFAULT;
        }
        printk("data written to user is : %c\n",devp->cbuff.buf[devp->cbuff.tail]);
        devp->cbuff.tail=(devp->cbuff.tail+1) & (SIZE-1);
    }
    wake_up(&devp->wqW);
   
    return i;
}

static ssize_t sample_write(struct file *fp, const char __user *Ubuff, size_t count, loff_t *offset)    {

    int mini,i,ret;
    struct mydevices *devp = fp->private_data;

    printk("Writing a file driver.\n");

    wait_event_interruptible(devp->wqW, CIRC_SPACE(devp->cbuff.head, devp->cbuff.tail, SIZE)>0);
    down(&devp->_sem);    
    mini= min(count, (size_t)CIRC_SPACE(devp->cbuff.head,devp->cbuff.tail,SIZE));
    msleep(1000);
    for(i=0; i<mini; i++)   {
        ret= copy_from_user(devp->cbuff.buf+devp->cbuff.head, Ubuff+i,1);
        if(ret) {
            printk("failed to write  byte no. %d\n", i);
            return -EFAULT;
        }
        printk("data written to kernel device is : %c\n", devp->cbuff.buf[devp->cbuff.head]);
        devp->cbuff.head = (devp->cbuff.head+1)&(SIZE-1);
    }
    wake_up(&devp->wqR);
    up(&devp->_sem);
    return i;
}

static struct file_operations fops = {
    .open = sample_open,
    .release = sample_close,
    .read = sample_read,
    .write = sample_write,

};

static int dev_init(void)   {

    int i,ret, MAJOR, MINOR;

    printk("\n Initializing device. please wiat... \n");

    devnum = MKDEV(NMAJOR, 0);
    ret = register_chrdev_region(devnum, NMICROS, DEV_NAME);
    if(ret) {
            printk(KERN_ALERT" Error in registering device. \n");
            goto reg_err;
        }

    for(i=0; i<NMICROS; i++)    {
       
        devnum = MKDEV(NMAJOR, i);   

        MAJOR = MAJOR(devnum);
        MINOR = MINOR(devnum);

        printk("\n Creating device number %d %d. \n", MAJOR, MINOR);

        cdev_init(&devs[i]._cdev, &fops);

        devs[i].cbuff.buf = kmalloc(SIZE, GFP_KERNEL);
        
        if(devs[i].cbuff.buf == NULL)   {
            printk(KERN_ALERT" Error in memory allocation. \n");
            goto kmalloc_err;
        }

        init_waitqueue_head(&devs[i].wqR);
        init_waitqueue_head(&devs[i].wqW);
        sema_init(&devs[i]._sem,1);
        
        ret = cdev_add(&devs[i]._cdev, devnum, 1);
        if(ret) {
            printk(KERN_ALERT "\n Unable to add cdev\n");
            goto cdev_add_err;
        }
    }

    printk("\nInitialization is successful\n");
    return 0;

cdev_add_err:
        for(--i;i>=0;i++)
            cdev_del(&devs[i]._cdev); 

kmalloc_err:
        for(--i;i>=0;i++)
            kfree(devs[i].cbuff.buf);

reg_err:
        unregister_chrdev_region(devnum, NMICROS);      
        return -1;

}

static void dev_exit(void)  {
    int i;
    for(i=0;i<NMICROS;i++)   {
        cdev_del(&devs[i]._cdev);
        kfree(devs[i].cbuff.buf);
    }
    unregister_chrdev_region(devnum, NMICROS);  
    printk("\nRemoving of driver is successful\n");
}

module_init(dev_init);
module_exit(dev_exit);