#include "gpio-file-operation.h"

/* Meta Information */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ahmed Sami");
MODULE_DESCRIPTION("Hello world from gpio");


#define DRIVER_NAME "led-home"
#define DRIVER_CLASS 'mygpio_class'

struct mydata{
    dev_t my_device_nr;
    // Character Device
    struct cdev cdev_object;
    // File Operation 
    struct file_operations fops;
    // Class 
    struct class *my_class;
}mygpioData_st={
    .fops={
        .owner = THIS_MODULE,
        .open = driver_open,
        .release = driver_close,
        .read = driver_read,
        .write = driver_write
    }
};

static int __init my_init(void) {
    printk("Hello, Kernel!\n");
    /* Allocate a device nr */
    if(alloc_chrdev_region(&mygpioData_st.my_device_nr, 0, 1, DRIVER_NAME) < 0 ){
        printk("Deice nr. could not be allocated!\n");
        return -1;
    }

    cdev_init(&mygpioData_st.cdev_object, &mygpioData_st.fops);

    /* Registring device to kernel */

    if(cdev_add(&mygpioData_st.cdev_object, mygpioData_st.my_device_nr,1) == -1){
        printk("Registring of device to kernel faild!");
        goto DEV_ERROR;
    }

    /* Create device class */

    if((mygpioData_st.my_class = class_create(THIS_MODULE, DRIVER_CLASS)) = NULL){
        printk("Class can not be created!\n");
        goto ClassError;
    }
    
    /* Create device file */

    if(device_create(mygpioData_st.my_class, NULL, mygpioData_st.my_device_nr, NULL, DRIVER_NAME) == NULL){
        printk("Can not create device file!\n");
        goto FileError;
    }

    /* GPIO 21 Initializaion */

    if(gpio_request(21, "rpi-gpio-21")){
        printk("Can not allocate GPIO 21!\n");
        goto DeviceError;
    }

    /* Set GPIO Direction */
    
    if(gpio_direction_output(21, GPIOF_INIT_LOW)){
        printk("Can not set GPIO 21 to output\n");
        goto Gpio21Error;
    }
    return 0;
Gpio21Error:
    gpio_free(21);
DeviceError:
    device_destroy(mygpioData_st.my_class, mygpioData_st.my_device_nr);
FileError:
    class_destroy(mygpioData_st.my_class);
classError:
    cdev_del(&mygpioData_st.cdev_object);
DEV_ERROR:
    unregister_chrdev_region(mygpioData_st.my_device_nr,1);
    return -1;
}
/** 
* @brief This function is called when the module is removed from kernel
*/

static void __exit my_exit(void){
    gpio_set_value(21,0);
    gpio_free(21);
    device_destroy(mygpioData_st.my_class, mygpioData_st.my_device_nr);
    class_destroy(mygpioData_st.my_class);
    cdev_del(&mygpioData_st.cdev_object);
    unregister_chrdev_region(mygpioData_st.my_device_nr, 1);
}

module_init(my_init);
module_exit(my_exit);