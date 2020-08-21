
/*
	HMC5883L_STM32 (run 100%)
	https://github.com/DoanDuongVN/HMC5883L_STM32 
	This library for STM32 HAL is based on ARDUINO library: https://github.com/jarzebski/Arduino-HMC5883L
*/
#ifndef HMC5883L_h
#define HMC5883L_h

#include <inttypes.h>
#include "stm32f1xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

#define I2C hi2c1
#define HMC5883L_ADDRESS              0x1E // this device only has one address
#define HMC5883L_DEFAULT_ADDRESS    (HMC5883L_ADDRESS<<1)

//#define HMC5883L_ADDRESS              (0x1E)
#define HMC5883L_REG_CONFIG_A         (0x00)
#define HMC5883L_REG_CONFIG_B         (0x01)
#define HMC5883L_REG_MODE             (0x02)
#define HMC5883L_REG_OUT_X_M          (0x03)
#define HMC5883L_REG_OUT_X_L          (0x04)
#define HMC5883L_REG_OUT_Z_M          (0x05)
#define HMC5883L_REG_OUT_Z_L          (0x06)
#define HMC5883L_REG_OUT_Y_M          (0x07)
#define HMC5883L_REG_OUT_Y_L          (0x08)
#define HMC5883L_REG_STATUS           (0x09)
#define HMC5883L_REG_IDENT_A          (0x0A)
#define HMC5883L_REG_IDENT_B          (0x0B)
#define HMC5883L_REG_IDENT_C          (0x0C)

typedef enum
{
    HMC5883L_SAMPLES_8     =  3,
    HMC5883L_SAMPLES_4     =  2,
    HMC5883L_SAMPLES_2     =  1,
    HMC5883L_SAMPLES_1     =  0
}hmc5883l_samples_t ;

typedef enum
{
    HMC5883L_DATARATE_75HZ       = 6,
    HMC5883L_DATARATE_30HZ       = 5,
    HMC5883L_DATARATE_15HZ       = 4,
    HMC5883L_DATARATE_7_5HZ      = 3,
    HMC5883L_DATARATE_3HZ        = 2,
    HMC5883L_DATARATE_1_5HZ      = 1,
    HMC5883L_DATARATE_0_75_HZ    = 0
} hmc5883l_dataRate_t;

typedef enum
{
    HMC5883L_RANGE_8_1GA     = 7,
    HMC5883L_RANGE_5_6GA     = 6,
    HMC5883L_RANGE_4_7GA     = 5,
    HMC5883L_RANGE_4GA       = 4,
    HMC5883L_RANGE_2_5GA     = 3,
    HMC5883L_RANGE_1_9GA     = 2,
    HMC5883L_RANGE_1_3GA     = 1,
    HMC5883L_RANGE_0_88GA    = 0
} hmc5883l_range_t;

typedef enum
{
    HMC5883L_IDLE          = 2,
    HMC5883L_SINGLE        = 1,
    HMC5883L_CONTINOUS     = 0
} hmc5883l_mode_t;


typedef struct
{
    float XAxis;
    float YAxis;
    float ZAxis;
} Vector;

	Vector HMC5883L_readRaw(void);
	Vector HMC5883L_readNormalize(void);

	void  HMC5883L_setOffset(int xo, int yo);

	void  HMC5883L_setRange(hmc5883l_range_t range);
	hmc5883l_range_t HMC5883L_getRange(void);

	void  HMC5883L_setMeasurementMode(hmc5883l_mode_t mode);
	hmc5883l_mode_t HMC5883L_getMeasurementMode(void);

	void  HMC5883L_setDataRate(hmc5883l_dataRate_t dataRate);
	hmc5883l_dataRate_t HMC5883L_getDataRate(void);

	void  HMC5883L_setSamples(hmc5883l_samples_t samples);
	hmc5883l_samples_t HMC5883L_getSamples(void);

	void HMC5883L_writeRegister8(uint8_t reg, uint8_t value);
	uint8_t HMC5883L_readRegister8(uint8_t reg);
	uint8_t HMC5883L_fastRegister8(uint8_t reg);
	int16_t HMC5883L_readRegister16(uint8_t reg);

#ifdef __cplusplus
}
#endif

#endif
