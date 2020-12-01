#include <linux/init.h>
#include <linux/module.h>
#include <linux/workqueue.h>    /* for work queue */
#include <linux/slab.h>         /* for kmalloc() */
MODULE_LICENSE("GPL");
struct workqueue_struct *wq;
static struct work_struct  mywork;
static void work_handler(struct work_struct *work){
    printk("In workqueue handler\n");
}

static int __init workq_init(void){
    wq = create_singlethread_workqueue("my_single_thread");

    INIT_WORK(&mywork, work_handler);
    queue_work(wq, &mywork);
    
    return 0;
}

static void __exit workq_exit(void){
    flush_workqueue(wq);
    destroy_workqueue(wq);
}
module_init(workq_init);
module_exit(workq_exit);
    