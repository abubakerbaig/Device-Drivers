
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/jiffies.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mirza");


static int jiffie_init(void )   {

    unsigned long future_jiffie;
    future_jiffie = jiffies + HZ * 5;
    printk("current jiffie value is : %ld\n future jiffie value is :%ld\n",jiffies, future_jiffie);

    while(time_before(jiffies, future_jiffie))    {
        schedule();
    }

    
    printk("current jiffie value is : %ld\n future jiffie value is :%ld\n",jiffies, future_jiffie);

    return 0;
}

static void jiffie_exit(void )  {
    printk("Exiting Module\n");
}

module_init(jiffie_init);
module_exit(jiffie_exit);