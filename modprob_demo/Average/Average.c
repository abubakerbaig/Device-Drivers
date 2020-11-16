#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

int add(int ,int );

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SELF");

static int total=5;
static int arr[]={1,2,3,4,5};

module_param(total, int, S_IRUGO);
module_param_array(arr, int, NULL, S_IRUGO);

static int average_init(void)   {
    
    int i;
    int avg=0;
    printk(KERN_ALERT"\n Inside Average Module init\n");

    for( i=0; i < total; i++)  {
        avg=add(avg,arr[i]);
    }

    avg/=total;

    printk(KERN_ALERT"\n Average of the given numbers is: %d \n", avg);

    return 0;
}

static void average_exit(void)  {

    printk(KERN_ALERT "\nExiting Average Module. \n");
}

module_init(average_init);
module_exit(average_exit);