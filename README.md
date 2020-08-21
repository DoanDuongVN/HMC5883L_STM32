# HMC5883L_STM32
--> In this program I used custom library for STM32 microcontroller series. Here I use STM32F103 You can replace your microcontroller by opening the Detector.ioc file and the same setting. The HMC5883L library is based on the ARDUINO library https://github.com/jarzebski/Arduino-HMC5883L 

--> I am using I2C1 (PB6 (SCL) and PB7 (SDA)) on STM32F103      
  Replace your I2C to use it!      
  In file HMC5883L.h edit #define I2C hi2c1 // hi2c1 to    hi2c * that you use (* = 1,2 .., etc.) on your microcontroller 
  
 --> To set up the compass you write the following statements in the main function   
    HMC5883L_setRange (HMC5883L_RANGE_1_3GA);
    HMC5883L_setMeasurementMode (HMC5883L_CONTINOUS);
    HMC5883L_setDataRate (HMC5883L_DATARATE_15HZ);
    HMC5883L_setSamples (HMC5883L_SAMPLES_1);
    HMC5883L_setOffset (0, 0);
    
  --> To print magnetic values on 3 axes, you declare the part before the int function     main is as follows:   
       #ifdef __GNUC__    
       #define PUTCHAR_PROTOTYPE int __io_putchar (int ch)     
       #else     #define PUTCHAR_PROTOTYPE int fputc (int ch, FILE * f)
       #endif / * __GNUC__ * /      
       PUTCHAR_PROTOTYPE     {      
                         HAL_UART_Transmit (&huart1, (uint8_t *) &ch, 1, 100);     
                         return ch;  
                         }     
       Then use the printf function in the stdio library to print the value from the field:
          Vector mag = HMC5883L_readNormalize ();  
         printf ("XAxis% 0.2f, YAxis% 0.2f, ZAxis% 0.2f \ r \ n", mag.XAxis, mag.YAxis, mag.ZAxis); 
     Good luck ! 
    Documentation of HMC5883L datasheet:  https://pdf1.alldatasheet.com/datasheet-pdf/view/428790/HONEYWELL/HMC5883L.html
