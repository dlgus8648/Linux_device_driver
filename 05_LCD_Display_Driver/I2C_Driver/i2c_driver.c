#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include "ssd1306.h"

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("KIMRIHYEON");
MODULE_DESCRIPTION("I2C test device driver (OLED SSD1306)");
MODULE_VERSION("1.0");

static struct i2c_adapter *i2c_adapter     = NULL;
static struct i2c_client  *i2c_client_oled = NULL;

static int i2c_write(unsigned char *buf, unsigned int len)
{
	
	int ret = i2c_master_send(i2c_client_oled, buf, len);
  
	return ret;
}
 
static int i2c_read(unsigned char *buf, unsigned int len)
{
	int ret = i2c_master_recv(i2c_client_oled, buf, len);
  
	return ret;
}
  
static int i2c_oled_probe(struct i2c_client *client,
                          const struct i2c_device_id *id)
{
	SSD1306_DisplayInit();
  
	SSD1306_SetCursor(0,0);   
	SSD1306_StartScrollHorizontal( true, 0, 2);

	SSD1306_String("Hyundai Motors!\n\nKIM RIHYEON!\n\n");
  
	pr_info("OLED Probed\n");
  
	return 0;
}

static int i2c_oled_remove(struct i2c_client *client)
{
	SSD1306_String("Good bye!");
  
	msleep(1000);
  
	SSD1306_SetCursor(0,0);


	SSD1306_Fill(0x00);
  
	SSD1306_Write(true, 0xAE); 
  
	pr_info("OLED removed\n");
	return 0;
}

static const struct i2c_device_id i2c_oled_id[] = {
	{ DEVICE_NAME, 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, i2c_oled_id);
 
static struct i2c_driver i2c_oled_driver = {
	.driver = {
		.name   = DEVICE_NAME,
		.owner  = THIS_MODULE,
	},
	.probe          = i2c_oled_probe,
	.remove         = i2c_oled_remove,
	.id_table       = i2c_oled_id,
};
 
static struct i2c_board_info oled_i2c_board_info = { 
	I2C_BOARD_INFO(DEVICE_NAME, SSD1306_ADDR) 
};

static int __init i2c_driver_init(void)
{
	int ret = -1;

	i2c_adapter = i2c_get_adapter(I2C_BUS_AVAILABLE);
  
	if( i2c_adapter != NULL ) {

		i2c_client_oled = i2c_new_device(i2c_adapter, &oled_i2c_board_info);
    
		if( i2c_client_oled != NULL ) {
			i2c_add_driver(&i2c_oled_driver);
			ret = 0;
		}
		i2c_put_adapter(i2c_adapter);
	}

	pr_info("i2c driver added\n");
	return ret;
}
 
static void __exit i2c_driver_exit(void)
{

	i2c_unregister_device(i2c_client_oled);
	i2c_del_driver(&i2c_oled_driver);
	pr_info("i2c driver removed\n");
}
 
module_init(i2c_driver_init);
module_exit(i2c_driver_exit);
 
