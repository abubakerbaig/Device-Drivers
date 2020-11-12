#include <linux/init.h> //req headers for init and cleanup func.
#include <linux/module.h>   //necessary stuff for headers
//#include <linux/moduleparam.h>   //allows passing of parameters to the module during insertion.


static int hello_init ( void ) {

    printk("\n Hello, world \n");
    return 0;
}
//macro
module_init(hello_init);

static void hello_exit(void)    {
    
    printk("Good Bye, world\n");

}

module_exit(hello_exit);
