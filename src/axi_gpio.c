/*
 * file:        axi_gpio.c
 * author:      VasiliyMatlab
 * version:     1.0
 * date:        01.03.2022
 * copyright:   Vasiliy (c) 2023
 */

#include <string.h>

#include "axi_gpio.h"
#include "defs.h"

// Initialize AXI GPIO
int32_t axi_gpio_init(axi_gpio_t *dev, uint32_t baseaddr) {
    if (dev == NULL) {
        return -1;
    }
    
    // Выставление адресов
    dev->regs           = (axi_gpio_regs_t *) (baseaddr + AXI_GPIO_REGISTER_OFFSET);
    dev->intrpt_regs    = (axi_gpio_intrpt_regs_t *) (baseaddr + AXI_GPIO_INTERRUPT_REGISTER_OFFSET);

    // Инициализация регистров
    dev->axi_gpio_current_data  = 0;
    dev->axi_gpio2_current_data = 0;
    dev->regs->gpio_data        = 0;
    dev->regs->gpio2_data       = 0;
    dev->regs->gpio_tri         = AXI_GPIO_CHANNEL_INPUT_CONFIGURE;
    dev->regs->gpio2_tri        = AXI_GPIO_CHANNEL_OUTPUT_CONFIGURE;
    dev->intrpt_regs->GIER      = AXI_GPIO_GLOBAL_INTERRUPT_ENABLE;
    dev->intrpt_regs->IP_IER    = AXI_GPIO_CHANNEL_1_INTERRUPT_ENABLE;
    
    // Проверка статусов прерываний (сброс при наличии)
    if (dev->intrpt_regs->IP_ISR & AXI_GPIO_CHANNEL_1_INTERRUPT_STATUS)
        dev->intrpt_regs->IP_ISR = AXI_GPIO_CHANNEL_1_INTERRUPT_STATUS;
    if (dev->intrpt_regs->IP_ISR & AXI_GPIO_CHANNEL_2_INTERRUPT_STATUS)
        dev->intrpt_regs->IP_ISR = AXI_GPIO_CHANNEL_2_INTERRUPT_STATUS;
    
    // Считываем изначальное состояние регистра
    mwr(&dev->axi_gpio_current_data, mrd(&dev->regs->gpio_data));

    return 0;
}

// Write to AXI GPIO
void axi_gpio_write(axi_gpio_t *dev, uint32_t data) {
    mwr(&dev->regs->gpio2_data, data);
}

// Interrupt handler for AXI GPIO
void axi_gpio_intrpt_handler(void *priv) {
    axi_gpio_t *dev = priv;

    // Чтение из GPIO
    if (mrd(&dev->intrpt_regs->IP_ISR) & AXI_GPIO_CHANNEL_1_INTERRUPT_STATUS) {
        mwr(&dev->axi_gpio_current_data, mrd(&dev->regs->gpio_data));
        mwr(&dev->intrpt_regs->IP_ISR, AXI_GPIO_CHANNEL_1_INTERRUPT_STATUS);
    }
}
