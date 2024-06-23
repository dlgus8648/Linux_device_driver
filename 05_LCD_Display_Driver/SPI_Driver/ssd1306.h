#define SPI_BUS_NUM             (  1 )    // SPI 1

#define SSD1306_RST_PIN         (  24 )   // Reset pin is GPIO 24
#define SSD1306_DC_PIN          (  23 )   // Data/Command pin is GPIO 23
#define SSD1306_MAX_SEG         ( 128 )   // Maximum segment
#define SSD1306_MAX_LINE        (   7 )   // Maximum line
#define SSD1306_DEF_FONT_SIZE   (   5 )   // Default font size


extern int spi_driver_write( uint8_t data );

extern int  SPI_SSD1306_DisplayInit(void);
extern void SPI_SSD1306_DisplayDeInit(void);

void SPI_SSD1306_SetCursor( uint8_t lineNo, uint8_t cursorPos );
void SPI_SSD1306_GoToNextLine( void );
void SPI_SSD1306_PrintChar(unsigned char c);
void SPI_SSD1306_String(char *str);
void SPI_SSD1306_InvertDisplay(bool need_to_invert);
void SPI_SSD1306_SetBrightness(uint8_t brightnessValue);
void SPI_SSD1306_StartScrollHorizontal( bool is_left_scroll,
                                        uint8_t start_line_no,
                                        uint8_t end_line_no
                                      );
void SPI_SSD1306_StartScrollVerticalHorizontal( 
                                                bool is_vertical_left_scroll,
                                                uint8_t start_line_no,
                                                uint8_t end_line_no,
                                                uint8_t vertical_area,
                                                uint8_t rows
                                              );
void SPI_SSD1306_DeactivateScroll( void );
void SPI_SSD1306_fill( uint8_t data );
void SPI_SSD1306_ClearDisplay( void );
void SPI_SSD1306_PrintLogo( void );


