#include <linux/module.h>
#include <linux/interrupt.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("MIRZA");

static struct tasklet_struct demo_tasklet;

static void tasklet_fun(unsigned long data )  {
    printk("Tasklet function executing. %lu\n", data);
}

static int tasklets_init(void)  {

    tasklet_init(&demo_tasklet, tasklet_fun, 1);
    //demo_tasklet.func= tasklet_fun;
    tasklet_disable(&demo_tasklet);
    tasklet_schedule(&demo_tasklet);

    return 0;
}

static void tasklets_exit(void) {
    printk("Exiting module\n");
    tasklet_enable(&demo_tasklet);
    tasklet_kill(&demo_tasklet);
}

module_init(tasklets_init);
module_exit(tasklets_exit);
