#include <linux/module.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/delay.h>

static struct timer_list ktimer;

static void timer_callback (struct timer_list *fp)  {
    int ret;
    printk("Timer Callback function.\n");
    ret= mod_timer(&ktimer, jiffies+msecs_to_jiffies(3000));

}

static int timerk_init(void)    {
    int ret;

    printk("Current process is %s \n",current->comm);
    timer_setup (&ktimer, timer_callback, 0);

    ret = mod_timer(&ktimer, jiffies+msecs_to_jiffies(5000));
    if(ret)
        printk("Timer firing failed.\n");

    return 0;
}

static void timerk_exit(void)   {
    int ret;
    ret=del_timer_sync(&ktimer);
    if(ret)
        printk("The Timer is in use... \n");
    return ;

}

module_init(timerk_init);
module_exit(timerk_exit);