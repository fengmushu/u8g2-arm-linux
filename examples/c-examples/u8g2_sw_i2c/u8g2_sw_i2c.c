#include <stdio.h>
#include "u8g2port.h"

#define OLED_I2C_PIN_SCL                    447
#define OLED_I2C_PIN_SDA                    446
#define OLED_I2C_PIN_RST                    376

/*  
*   echo 446 > /sys/class/gpio/unexport 
*   echo 447 > /sys/class/gpio/unexport
*   
*   modprobe i2c-gpio
*   insmod i2c-gpio-custom.ko bus0=12,446,447
*   
*/

int main(void)
{
    u8g2_t u8g2;

    srandom(time(NULL));

    // Initialization
    u8g2_Setup_uc1604_i2c_jlx19248_f( &u8g2, U8G2_R0, u8x8_byte_sw_i2c, u8x8_arm_linux_gpio_and_delay);
    u8x8_SetPin(u8g2_GetU8x8(&u8g2), U8X8_PIN_I2C_CLOCK, OLED_I2C_PIN_SCL);
    u8x8_SetPin(u8g2_GetU8x8(&u8g2), U8X8_PIN_I2C_DATA, OLED_I2C_PIN_SDA);
    u8x8_SetPin(u8g2_GetU8x8(&u8g2), U8X8_PIN_RESET, OLED_I2C_PIN_RST);

    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);

    // Draw
    /* full buffer example, setup procedure ends in _f */
    u8g2_ClearBuffer(&u8g2);

    u8g2_SetFont(&u8g2, u8g2_font_helvR12_tf);
    u8g2_DrawStr(&u8g2, 1, 18, "Smart martin ... aha");
    u8g2_SendBuffer(&u8g2);

    sleep_ms(10); 
    u8g2_SetFont(&u8g2, u8g2_font_unifont_t_symbols);
    u8g2_DrawGlyph(&u8g2, random() % 160, random() % 48 + 8, 0x2603 );
    u8g2_SendBuffer(&u8g2);

    sleep_ms(10);
    u8g2_DrawGlyph(&u8g2, random() % 160, random() % 48 + 8, 0x2603 );
    u8g2_SendBuffer(&u8g2);

    sleep_ms(10);
    u8g2_DrawGlyph(&u8g2, random() % 160, random() % 48 + 8, 0x2603 );
    u8g2_SendBuffer(&u8g2);

    printf("Initialized ...\n");

    return 0;
}
