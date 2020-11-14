#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

//MOUDLE_LICENSE("GPL");
MODULE_AUTHOR("SELF");

static int add(int a, int b)    {
    printk(KERN_ALERT"inside add function\n");
    return (a+b);
}

EXPORT_SYMBOL(add);

static int add_init(void)   {

    printk(KERN_ALERT"\n Inside Add module init\n");
    
    return 0;
}

static void add_exit(void)  {

    printk(KERN_ALERT"\nExiting Addition Module. \n");
}

module_init(add_init);
module_exit(add_exit);