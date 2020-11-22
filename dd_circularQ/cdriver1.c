#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/circ_buf.h>
#include <linux/slab.h>

#define NAME "CBdriver"
#define SIZE 32

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SELFTEST");

static struct cdev *_cdev;
static dev_t devnum;
static struct circ_buf cbuf;


static int sample_open (struct inode *inod, struct file *filp)  {
    
    printk("\nOpening drivers file.\n");
    return 0;

}

static int sample_close (struct inode *inod, struct file *filp) {
    
    printk("\n Closing drivers file.\n");
    return 0;

}

static ssize_t sample_read (struct file *filp, char *Ubuff, size_t count, loff_t *offset)   {
    int i,ret,mini;

    mini= min(count,(size_t)CIRC_CNT(cbuf.head,cbuf.tail,SIZE));

    printk("Starting to Read data from driver....\nrequested bytes form user is %ld\nnumber of bytes kernel is allowing to read:  %d\n",count,mini);

    for(i=0; i<mini; i++)  {
        ret=copy_to_user(Ubuff+i,cbuf.buf+cbuf.tail,1);
        if(ret) {
            printk("failed to read byte no. %d",i);
            return -EFAULT;
        }
        printk("data writtn to user is : %c\n",cbuf.buf[cbuf.tail]);
        cbuf.tail=(cbuf.tail+1) & (SIZE-1);
    }
    return i;

}

static ssize_t sample_write (struct file *filp, const char *Ubuff, size_t count, loff_t *offset)    {
    int i,ret,mini;
    mini= min(count,(size_t)CIRC_SPACE(cbuf.head,cbuf.tail,SIZE));
    printk("Starting to Write Data from driver....\nrequested bytes form user is %ld\nnumber of bytes writing is: %d",count,mini);
    for(i=0; i<mini; i++)  {
        ret=copy_from_user(cbuf.buf+cbuf.head, Ubuff+i, 1);
        if(ret) {
            printk("failed to read byte no. %d",i);
            return -1;
        }
        printk("data writtn to driver is : %c\n",cbuf.buf[cbuf.head]);
        cbuf.head=(cbuf.head+1) & (SIZE-1);


    }
    return i;

}

static struct file_operations fops  = {
    .open = sample_open,
    .release = sample_close,
    .read = sample_read,
    .write = sample_write,
};


static int crdriver_init(void )    {

    int ret, MAJOR, MINOR;
    devnum=MKDEV(2,0);
    MAJOR=MAJOR(devnum);
    MINOR=MINOR(devnum);
    
    ret=register_chrdev_region(devnum, 1, NAME);

    printk("Major Number: %d\t Minor Number : %d \n",MAJOR,MINOR);

    if(ret) {
        printk(KERN_ALERT "\n Failed to register cdev region\n");
        return ret;
    }
    _cdev=cdev_alloc();     //dyanmic allocation
    _cdev->ops = &fops;
   //init_cdev(&_cdev, &fops);

    cbuf.buf=kmalloc(SIZE, GFP_KERNEL); //memory allcoation for circular buffer //get free pages
    if(cbuf.buf == NULL)   {
        printk("Failed to allocate memory for circular buffer.\n");
        unregister_chrdev_region(devnum,1);
        return -1;
    }

    ret=cdev_add(_cdev,devnum,1);
    if(ret)  {
        printk(KERN_ALERT "\n Failed to register cdev region\n");
        unregister_chrdev_region(devnum,1);
        kfree(cbuf.buf);
        return ret;
    }
    

    return 0;
}

static void crdriver_exit(void )     {
    cdev_del(_cdev);
    kfree(cbuf.buf);
    unregister_chrdev_region(devnum, 1);
    printk(KERN_ALERT "\nI have Unregistessressdss thess tuff that was allocated... Good Bye forever.....\n");
}

module_init(crdriver_init);
module_exit(crdriver_exit);