/*=============================================================================================
 * Includes
 * ============================================================================================*/
#include <linux/module.h>  /* Needed by all kernel modules */
#include <linux/kernel.h>  /* Needed for loglevels (KERN_WARNING, KERN_EMERG, KERN_INFO, etc.) */
#include <linux/version.h> /* Needed for the module version to be compatible with the kernel it is going to be loaded into*/ 
#include <linux/init.h>    /* Needed for __init and __exit macros. */
#include <linux/delay.h>   /* Needed for sleeps*/
#include <linux/io.h>      /* Needed for input (inb, inw, inl) & output (outb, outw, out1) instructions*/

#include <linux/serial_reg.h> /* Provides macros for serial register offsets and the register bit masks*/

/*=============================================================================================
 * Defines
 * ============================================================================================*/
#define SERIAL_PORT_BASE 0x3F8 /* Base port address -- can be found in /proc/ioports*/

/*===============================================================================================
 * entry function
 * =============================================================================================*/
static int __init onload(void) { 
    int i;
    u8 data;

    data = inb(SERIAL_PORT_BASE + UART_LCR);
    for (i = 0; i < 5; i++) {
        /* Pull the Tx line low */
        data |= UART_LCR_SBC;
        outb(data, SERIAL_PORT_BASE + UART_LCR);
        msleep(500);
        /* Defaulting the Tx line high */
        data &= ~UART_LCR_SBC;
        outb(data, SERIAL_PORT_BASE + UART_LCR);
        msleep(500);
    }
    return 0;
}

/*==============================================================================================*/
// exit function
static void __exit onunload(void) {
    printk(KERN_INFO "Deregistered LKM\n");
}

/*==============================================================================================*/
// register entry/exit point functions
module_init(onload);
module_exit(onunload);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mark Mester <mmester@parrylabs.com>");
MODULE_DESCRIPTION("A loadable Linux kernel module for a serial device");
