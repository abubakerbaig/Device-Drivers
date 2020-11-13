#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

//MODULE_LICENSE("GPL"); //FREE LICENSE
//MODULE_AUTHOR("I am");  //NAME OF THE AUTHOR

//var's are declared as static to keep their 
//scope local to this module and avoid namespace 
//polution

static int array[6]= {1,2,3,4,5,6};
static int intval= 1;

//macros used to initialize var's from cmd line

module_param_array(array, int, NULL, S_IRUGO); //char pointer
module_param(intval, int, S_IRUGO);     //int

static int param_init(void) {

    int i;
    printk(KERN_ALERT "\n We are in init function\n");
  //  printk(KERN_ALERT "\n The value of charval is: \n The value of intval is : %d \n" ,intval);
    for(i=0 ; i < 6 ; i++)  {

        printk(KERN_ALERT "\n array[%d]-%d \n",i,array[i]);
    
    }
    
    return 0;
}

static void param_exit(void)    {
    printk(KERN_ALERT "\n Good Bye\n");

}

module_init(param_init);
module_exit(param_exit);