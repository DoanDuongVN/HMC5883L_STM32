
#include "HMC5883L.h"
//#include <math.h>

float mgPerDigit;
Vector v;
int xOffset, yOffset;

extern I2C_HandleTypeDef I2C;

Vector HMC5883L_readRaw(void)
{
    v.XAxis = HMC5883L_readRegister16(HMC5883L_REG_OUT_X_M) - xOffset;
    v.YAxis = HMC5883L_readRegister16(HMC5883L_REG_OUT_Y_M) - yOffset;
    v.ZAxis = HMC5883L_readRegister16(HMC5883L_REG_OUT_Z_M);

    return v;
}

Vector HMC5883L_readNormalize(void)
{
    v.XAxis = ((float)HMC5883L_readRegister16(HMC5883L_REG_OUT_X_M) - xOffset) * mgPerDigit;
    v.YAxis = ((float)HMC5883L_readRegister16(HMC5883L_REG_OUT_Y_M) - yOffset) * mgPerDigit;
    v.ZAxis = (float)HMC5883L_readRegister16(HMC5883L_REG_OUT_Z_M) * mgPerDigit;

    return v;
}

void HMC5883L_setOffset(int xo, int yo)
{
    xOffset = xo;
    yOffset = yo;
}

void HMC5883L_setRange(hmc5883l_range_t range)
{
    switch(range)
    {
	case HMC5883L_RANGE_0_88GA:
	    mgPerDigit = 0.73f;
	    break;

	case HMC5883L_RANGE_1_3GA:
	    mgPerDigit = 0.92f;
	    break;

	case HMC5883L_RANGE_1_9GA:
	    mgPerDigit = 1.22f;
	    break;

	case HMC5883L_RANGE_2_5GA:
	    mgPerDigit = 1.52f;
	    break;

	case HMC5883L_RANGE_4GA:
	    mgPerDigit = 2.27f;
	    break;

	case HMC5883L_RANGE_4_7GA:
	    mgPerDigit = 2.56f;
	    break;

	case HMC5883L_RANGE_5_6GA:
	    mgPerDigit = 3.03f;
	    break;

	case HMC5883L_RANGE_8_1GA:
	    mgPerDigit = 4.35f;
	    break;

	default:
	    break;
    }

    HMC5883L_writeRegister8(HMC5883L_REG_CONFIG_B, range << 5);
}

hmc5883l_range_t HMC5883L_getRange(void)
{
    return (hmc5883l_range_t)((HMC5883L_readRegister8(HMC5883L_REG_CONFIG_B) >> 5));
}

void HMC5883L_setMeasurementMode(hmc5883l_mode_t mode)
{
    uint8_t value;

    value = HMC5883L_readRegister8(HMC5883L_REG_MODE);
    value &= 0xFC;
    value |= mode;

    HMC5883L_writeRegister8(HMC5883L_REG_MODE, value);
}

hmc5883l_mode_t HMC5883L_getMeasurementMode(void)
{
    uint8_t value;

    value = HMC5883L_readRegister8(HMC5883L_REG_MODE);
    value &= 0x03;

    return (hmc5883l_mode_t)value;
}

void HMC5883L_setDataRate(hmc5883l_dataRate_t dataRate)
{
    uint8_t value;

    value = HMC5883L_readRegister8(HMC5883L_REG_CONFIG_A);
    value &= 0xE3;
    value |= (dataRate << 2);

    HMC5883L_writeRegister8(HMC5883L_REG_CONFIG_A, value);
}

hmc5883l_dataRate_t HMC5883L_getDataRate(void)
{
    uint8_t value;

    value = HMC5883L_readRegister8(HMC5883L_REG_CONFIG_A);
    value &= 0x1C;
    value >>= 2;

    return (hmc5883l_dataRate_t)value;
}

void HMC5883L_setSamples(hmc5883l_samples_t samples)
{
    uint8_t value;

    value = HMC5883L_readRegister8(HMC5883L_REG_CONFIG_A);
    value &= 0x9F;
    value |= (samples << 5);

    HMC5883L_writeRegister8(HMC5883L_REG_CONFIG_A, value);
}

hmc5883l_samples_t HMC5883L_getSamples(void)
{
    uint8_t value;

    value = HMC5883L_readRegister8(HMC5883L_REG_CONFIG_A);
    value &= 0x60;
    value >>= 5;

    return (hmc5883l_samples_t)value;
}

// Write byte to register
void HMC5883L_writeRegister8(uint8_t reg, uint8_t value)
{
    HAL_I2C_Mem_Write(&I2C, HMC5883L_DEFAULT_ADDRESS, reg, 1 , &value,1,500);
}

// Read byte to register
uint8_t HMC5883L_fastRegister8(uint8_t reg)
{
    uint8_t value;
//  HAL_I2C_Mem_Write(&I2C, HMC5883L_ADDRESS, reg, 1 ,value,1,500)
    HAL_I2C_Mem_Read(&I2C, HMC5883L_DEFAULT_ADDRESS , reg, 1, &value, 1, 500);
    return value;
}

// Read byte from register
uint8_t HMC5883L_readRegister8(uint8_t reg)
{
    uint8_t value;
    HAL_I2C_Mem_Read(&I2C, HMC5883L_DEFAULT_ADDRESS , reg, 1, &value, 1, 500);
    return value;
}

// Read word from register
int16_t HMC5883L_readRegister16(uint8_t reg)
{
    int16_t value;
	  
	  uint8_t vha[2];
	
    HAL_I2C_Mem_Read(&I2C,  HMC5883L_DEFAULT_ADDRESS, reg, 1, vha, 2, 500);
	  
	  value = vha[0] <<8 | vha[1];
    return value;
}