/**
 * \file axi_gpio.h
 * \author VasiliyMatlab
 * \brief GPIO Registers module
 * \version 1.1
 * \date 03.03.2023
 * \copyright Vasiliy (c) 2023
 */

#ifndef __AXI_GPIO_H__
#define __AXI_GPIO_H__


#include <stdint.h>

/// AXI GPIO FLAGS
#define AXI_GPIO_GLOBAL_INTERRUPT_ENABLE        0x80000000  ///< Enable interrupt
#define AXI_GPIO_CHANNEL_1_INTERRUPT_ENABLE     0x00000001  ///< Enable channel 1 interrupt
#define AXI_GPIO_CHANNEL_2_INTERRUPT_ENABLE     0x00000002  ///< Enable channel 2 interrupt
#define AXI_GPIO_CHANNEL_1_INTERRUPT_STATUS     0x00000001  ///< Channel 1 interrupt status
#define AXI_GPIO_CHANNEL_2_INTERRUPT_STATUS     0x00000002  ///< Channel 2 interrupt status
#define AXI_GPIO_CHANNEL_OUTPUT_CONFIGURE       0x00000000  ///< I/O pins configured as output
#define AXI_GPIO_CHANNEL_INPUT_CONFIGURE        0xFFFFFFFF  ///< I/O pins configured as input

#define AXI_GPIO_INTERRUPT_REGISTER_OFFSET  0x11C    ///< AXI GPIO Interrupt Registers Offset
// #define AXI_GPIO_GIER_ADDR               0x11C    ///< Global Interrupt Enable Register Address Offset
// #define AXI_GPIO_IP_ISR_ADDR             0x120    ///< IP Interrupt Status Register Address Offset
// #define AXI_GPIO_IP_IER_ADDR             0x128    ///< IP Interrupt Enable Register Address Offset

#define AXI_GPIO_REGISTER_OFFSET       0x00     ///< AXI GPIO Registers Offset
// #define AXI_GPIO_GPIO_DATA_ADDR     0x00     ///< Channel 1 AXI GPIO Data Register Address Offset
// #define AXI_GPIO_GPIO_TRI_ADDR      0x04     ///< Channel 1 AXI GPIO 3-state Register Address Offset
// #define AXI_GPIO_GPIO2_DATA_ADDR    0x08     ///< Channel 2 AXI GPIO Data Register Address Offset
// #define AXI_GPIO_GPIO2_TRI_ADDR     0x0C     ///< Channel 2 AXI GPIO 3-state Register Address Offset

/// AXI GPIO Interrupt Registers
typedef struct axi_gpio_intrpt_regs {
    volatile uint32_t GIER;     ///< Global Interrupt Enable Register
    volatile uint32_t IP_ISR;   ///< IP Interrupt Status Register
    uint32_t align;             ///< Align
    volatile uint32_t IP_IER;   ///< IP Interrupt Enable Register
} axi_gpio_intrpt_regs_t;

/// AXI GPIO Registers
typedef struct axi_gpio_regs {
    volatile uint32_t gpio_data;    ///< Channel 1 AXI GPIO Data Register
    volatile uint32_t gpio_tri;     ///< Channel 1 AXI GPIO 3-state Register
    volatile uint32_t gpio2_data;   ///< Channel 2 AXI GPIO Data Register
    volatile uint32_t gpio2_tri;    ///< Channel 2 AXI GPIO 3-state Register
} axi_gpio_regs_t;

/// AXI GPIO Descriptor
typedef struct axi_gpio {
    axi_gpio_intrpt_regs_t *intrpt_regs;    ///< AXI GPIO Interrupt Registers
    axi_gpio_regs_t *regs;                  ///< AXI GPIO Registers
    uint32_t axi_gpio_current_data;         ///< Data in register 1
    uint32_t axi_gpio2_current_data;        ///< Data in register 2
} axi_gpio_t;


/**
 * \brief Функция инициализации GPIO
 * 
 * \param[in,out] dev Указатель на дескриптор GPIO
 * \param[in] baseaddr Базовый адрес
 * \return RETURN_SUCCESS; или RETURN_FAIL в случае ошибки
 */
int32_t axi_gpio_init(axi_gpio_t *dev, uint32_t baseaddr);

/**
 * \brief Запись в GPIO
 * 
 * \param[in,out] dev Указатель на дескриптор GPIO
 * \param[in] data Данные для записи в GPIO
 */
void axi_gpio_write(axi_gpio_t *dev, const uint32_t data);

/**
 * \brief Чтение из GPIO
 * 
 * \param[in] dev Указатель на дескриптор GPIO
 * \return Прочитанное значение
 */
uint32_t axi_gpio_read(axi_gpio_t *dev);

/**
 * \brief Обработчик прерываний GPIO
 * 
 * \param[in,out] dev Указатель на дескриптор GPIO
 */
void axi_gpio_intrpt_handler(void *dev);


#endif  /* __AXI_GPIO_H__ */
