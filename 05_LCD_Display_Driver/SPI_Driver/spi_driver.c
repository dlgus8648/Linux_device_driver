#include <linux/init.h>
#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/delay.h>

#include "ssd1306.h"


MODULE_LICENSE("GPL");
MODULE_AUTHOR("KIMRIHYEON");
MODULE_DESCRIPTION("SPI test device driver (OLED SSD1306)");
MODULE_VERSION("1.0");



static struct spi_device *spi_device;


struct spi_board_info spi_device_info = 
{
	.modalias     = "spi-ssd1306-driver",
	.max_speed_hz = 4000000,              // SPI 디바이스 제어 속도
	.bus_num      = SPI_BUS_NUM,          // SPI 버스 번호 (1)
	.chip_select  = 0,                    // SPI 디바이스 선택 SPI1_CE0 (GPIO 18)
	                                      // OLED 디스플레이 단독장비활용으로 SPI1_CE0 활용X
	.mode         = SPI_MODE_0            // SPI mode 0
};
/*
  SPI 4가지 동작모드:
  CPOL : 초기 클럭상태 (0: Low / 1: High)
  CPHA : 샘플링 클럭   (0: 첫번째 클럭, 1: 두번째 클럭)
  CPOL＝0，CPHA＝0		SPI_MODE_0
  CPOL＝0，CPHA＝1		SPI_MODE_1
  CPOL＝1，CPHA＝0		SPI_MODE_2
  CPOL＝1，CPHA＝1		SPI_MODE_3
*/
int spi_driver_write (uint8_t data)
{
	int ret = -1;
	uint8_t rx = 0x00;
  
	if (spi_device) {
		struct spi_transfer tr = { .tx_buf = &data,
					   .rx_buf = &rx,
					   .len = 1,};

		
		spi_sync_transfer(spi_device, &tr, 1);
	}

	
  
	return ret;
}

static int __init spi_init(void)
{
	int     ret;
	struct  spi_master *master;

	
	master = spi_busnum_to_master(spi_device_info.bus_num);
	if( master == NULL ) {
		pr_err("SPI Master not found.\n");
		return -ENODEV;
	}

	
	spi_device = spi_new_device( master, &spi_device_info );
	if (spi_device == NULL) {
		pr_err("FAILED to create slave.\n");
		return -ENODEV;
	}

	spi_device->bits_per_word = 8; 

	ret = spi_setup(spi_device); 
	if( ret ) {
		pr_err("FAILED to setup slave.\n");
		spi_unregister_device( spi_device );
		return -ENODEV;
	}

	
	SPI_SSD1306_DisplayInit();
  
	SPI_SSD1306_SetBrightness(255); 
	SPI_SSD1306_InvertDisplay(false); 
  
   
	SPI_SSD1306_StartScrollHorizontal(true, 0, 2);
  
	SPI_SSD1306_SetCursor(0,0); 

	SPI_SSD1306_String("Hyndai\n\nKIMRIHYEON\n");
  
	SPI_SSD1306_SetCursor(4,25); 

	SPI_SSD1306_String("SPI Device Driver\n");
  
	msleep(9000);
  
	pr_info("SPI driver Registered\n");
	return 0;
}
 
static void __exit spi_exit(void)
{ 
	if (spi_device) {
		SPI_SSD1306_ClearDisplay(); 
		SPI_SSD1306_DisplayDeInit(); 
		spi_unregister_device(spi_device);
		pr_info("SPI driver unnregistered\n");
	}
}
 
module_init(spi_init);
module_exit(spi_exit);


