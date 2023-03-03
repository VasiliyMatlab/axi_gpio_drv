/**
 * \file defs.h
 * \author VasiliyMatlab
 * \brief Global defines module
 * \version 1.0
 * \date 01.03.2023
 * \copyright Vasiliy (c) 2023
 */

#ifndef __DEFS_H__
#define __DEFS_H__


#include <inttypes.h>

#define __align(x) __attribute__((aligned(x)))	///< Выравнивание на x байт
#define alen(x) (sizeof(x) / sizeof((x)[0]))	///< Длина данных в составных частях

/**
 * \brief Запись данных по адресу
 * 
 * \param[in] addr Адрес памяти
 * \param[in] data 4 байта данных
 */
__inline__ static void mwr(uint32_t volatile *addr, uint32_t data) {
	*(volatile uint32_t* volatile)(addr) = (data);
}

/**
 * \brief Чтение данных по адресу
 * 
 * \param[in] addr Адрес памяти
 * \return 4 прочитанных байта данных
 */
__inline__ static uint32_t mrd(const uint32_t volatile *addr) {
	uint32_t ret;
	ret = (*(volatile uint32_t* volatile)(addr));
	return ret;
}


#endif /* __DEFS_H__ */
