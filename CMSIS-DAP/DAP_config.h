/*
* Copyright (c) 2013-2017 ARM Limited. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the License); you may
* not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an AS IS BASIS, WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* ----------------------------------------------------------------------
*
* $Date:        1. December 2017
* $Revision:    V2.0.4
*
* Project:      CMSIS-DAP Configuration
* Title:        DAP_config.h CMSIS-DAP Configuration File (Template)
*
*---------------------------------------------------------------------------*/

#ifndef __DAP_CONFIG_H__
#define __DAP_CONFIG_H__

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

extern void vResetTarget(uint8_t bit);

typedef const struct
{
  void  (* LedConnected)  (uint16_t);
  void  (* LedRunning)    (uint16_t);
} CoreDescriptor_t;

extern const CoreDescriptor_t * pCoreDescriptor;

typedef const struct
{
  void    (* UserInit)  (CoreDescriptor_t * core);
  uint32_t  (* UserProcess) (const uint8_t *, uint8_t *);
  void    (* UserAbort) (void);
} UserAppDescriptor_t;

#if  !defined ( BLUEPILL      )  \
  && !defined ( BOARD_V1      ) \
  && !defined ( BOARD_V2      ) \
  && !defined ( STLINK_V20    ) \
  && !defined ( STLINK_V21    ) \
  && !defined ( BOARD_STM32RF ) \
  && !defined ( STLINK_V2A    ) \
  && !defined ( STLINK_V2B    ) \
  && !defined ( JLINK_OB      )
#error "Board undefined"
#endif

//**************************************************************************************************
#include <stm32f10x.h>

#define CPU_CLOCK               72000000 
#define IO_PORT_WRITE_CYCLES    2       
#define DAP_SWD                 1       

#if  defined ( BOARD_STM32RF ) \
  || defined ( STLINK_V20 )    \
  || defined ( STLINK_V21 )    \
  || defined ( STLINK_V2A )    \
  || defined ( JLINK_OB )
#define DAP_JTAG                0
#else
#define DAP_JTAG                1
#endif

#define DAP_JTAG_DEV_CNT        8       
#define DAP_DEFAULT_PORT        1       
#define DAP_DEFAULT_SWJ_CLOCK   10000000 
#define DAP_PACKET_SIZE         64      
#define DAP_PACKET_COUNT        64      
#define SWO_UART                0      
#define SWO_UART_MAX_BAUDRATE   1000000U  
#define SWO_MANCHESTER          0       
#define SWO_BUFFER_SIZE         4096U   
#define SWO_STREAM              0       
#define TIMESTAMP_CLOCK         SystemCoreClock 
#define TARGET_DEVICE_FIXED     0       

#if TARGET_DEVICE_FIXED
#define TARGET_DEVICE_VENDOR    ""    
#define TARGET_DEVICE_NAME      ""    
#endif

#define GPIO_INIT(port, data) GPIO_Init(port, (GPIO_InitTypeDef *)&data)
#define PIN_MODE_MASK(pin)    (((uint32_t)0x0F) << ((pin) << 2))
#define PIN_MODE(mode,pin)    (((uint32_t)mode) << ((pin) << 2))
#define PIN_MASK(pin)         (((uint16_t)0x01) << (pin))

typedef enum Pin_e {
  PA = 0x00, PA0 = 0x00, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PA13, PA14, PA15,
  PB = 0x10, PB0 = 0x10, PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB11, PB12, PB13, PB14, PB15,
  PC = 0x20, PC0 = 0x20, PC1, PC2, PC3, PC4, PC5, PC6, PC7, PC8, PC9, PC10, PC11, PC12, PC13, PC14, PC15,
  PD = 0x30, PD0 = 0x30, PD1, PD2,
} Pin_t;

#define USART_CDC_CLOCK(state)      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, state)
#define USART_CDC_GPIO_CLOCK(state) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, state)
#define USART_CDC_REMAP()           

#define USART_CDC_PORT        2     
#define USART_CDC_GPIO        GPIOA
#define USART_CDC_TX_PIN_MASK GPIO_Pin_2
#define USART_CDC_RX_PIN_MASK GPIO_Pin_3
#define USART_CDC_IRQn        USART2_IRQn
#define USART_CDC_IRQHandler  USART2_IRQHandler
#define USART_CDC_BUFFER_SIZE (1024)  

#if !defined(SWO_PB7) && !defined(SWO_PA10)
#define SWO_PB7 1
#endif

// USB Connect Pull-Up & Board Specific Pin Mappings
#if   defined ( BLUEPILL ) \
  ||  defined ( BOARD_V1 ) \
  ||  defined ( BOARD_V2 )

#define PIN_USB_CONNECT_RCC   RCC_APB2ENR_IOPAEN
#define PIN_USB_CONNECT_PORT  GPIOA
#define PIN_USB_CONNECT_PIN   8
#define PIN_USB_CONNECT_MASK  PIN_MASK(PIN_USB_CONNECT_PIN)
#define PIN_USB_MODE          GPIO_Mode_Out_PP
#define PIN_USB_CONNECT_ON()  PIN_USB_CONNECT_PORT->BSRR = PIN_USB_CONNECT_MASK
#define PIN_USB_CONNECT_OFF() PIN_USB_CONNECT_PORT->BRR  = PIN_USB_CONNECT_MASK

#elif  defined ( STLINK_V20 ) \
  ||   defined ( STLINK_V2A ) \
  ||   defined ( STLINK_V2B )

#define PIN_USB_CONNECT_ON()
#define PIN_USB_CONNECT_OFF()

#elif defined ( JLINK_OB )
#define PIN_SWDIO_TMS_PORT  GPIOA
#define PIN_SWDIO_TMS_PIN   7
#define PIN_SWCLK_TCK_PORT  GPIOA
#define PIN_SWCLK_TCK_PIN   5
#define PIN_TDI_PIN         0
#define PIN_TDO_PIN         0
#define PIN_nRESET_PIN      0

#define LED_CONNECTED_RCC   RCC_APB2ENR_IOPBEN
#define LED_RUNNING_RCC     RCC_APB2ENR_IOPBEN
#define LED_CONNECTED_PORT  GPIOB
#define LED_CONNECTED_PIN   12
#define LED_RUNNING_PORT    GPIOB
#define LED_RUNNING_PIN     12

#define PIN_USB_CONNECT_RCC   RCC_APB2ENR_IOPAEN
#define PIN_USB_CONNECT_PORT  GPIOA
#define PIN_USB_CONNECT_PIN   9
#define PIN_USB_CONNECT_MASK  PIN_MASK(PIN_USB_CONNECT_PIN)
#define PIN_USB_MODE          GPIO_Mode_Out_PP
#define PIN_USB_CONNECT_ON()  PIN_USB_CONNECT_PORT->BSRR = PIN_USB_CONNECT_MASK
#define PIN_USB_CONNECT_OFF() PIN_USB_CONNECT_PORT->BRR  = PIN_USB_CONNECT_MASK

#elif defined ( STLINK_V21 )

#define PIN_USB_CONNECT_RCC   RCC_APB2ENR_IOPAEN
#define PIN_USB_CONNECT_PORT  GPIOA
#define PIN_USB_CONNECT_PIN   15
#define PIN_USB_CONNECT_MASK  PIN_MASK(PIN_USB_CONNECT_PIN)
#define PIN_USB_MODE          GPIO_Mode_Out_OD
#define PIN_USB_CONNECT_ON()  PIN_USB_CONNECT_PORT->BSRR = PIN_USB_CONNECT_MASK
#define PIN_USB_CONNECT_OFF() PIN_USB_CONNECT_PORT->BRR  = PIN_USB_CONNECT_MASK

#elif defined ( BOARD_STM32RF )
#define PIN_USB_CONNECT_ON()
#define PIN_USB_CONNECT_OFF()
#endif

// Board-specific Pin Definitions for SWD / JTAG / nRESET
#if defined ( BLUEPILL )              
#if defined ( SWD_REMAP )             
#define PIN_TDI_PORT        GPIOB
#define PIN_TDI_PIN         5
#define PIN_SWDIO_TMS_PORT  GPIOA   
#define PIN_SWDIO_TMS_PIN   13
#define PIN_SWCLK_TCK_PORT  GPIOA   
#define PIN_SWCLK_TCK_PIN   14
#define PIN_TDO_PORT        GPIOB
#define PIN_TDO_PIN         7
#define PIN_nRESET_PORT     GPIOB
#define PIN_nRESET_PIN      6
#else 
#define PIN_TDI_PORT        GPIOB
#define PIN_TDI_PIN         5
#define PIN_SWDIO_TMS_PORT  GPIOB
#define PIN_SWDIO_TMS_PIN   9
#define PIN_SWCLK_TCK_PORT  GPIOB
#define PIN_SWCLK_TCK_PIN   8
#define PIN_TDO_PORT        GPIOB
#define PIN_TDO_PIN         7
#define PIN_nRESET_PORT     GPIOB
#define PIN_nRESET_PIN      6
#endif

#elif defined ( BOARD_V1 )
#define PIN_SWDIO_TMS_PORT  GPIOA
#define PIN_SWDIO_TMS_PIN   2         
#error "PA2 conflict with USART2, Please remove USART-CDC function or change PIN_SWDIO_TMS_PIN!!!!"
#define PIN_SWCLK_TCK_PORT  GPIOA
#define PIN_SWCLK_TCK_PIN   4
#define PIN_TDO_PORT        GPIOA
#define PIN_TDO_PIN         5
#define PIN_TDI_PORT        GPIOA
#define PIN_TDI_PIN         7
#define PIN_nRESET_PORT     GPIOA
#define PIN_nRESET_PIN      6

#elif defined ( BOARD_V2 )
#define PIN_SWDIO_TMS_PORT  GPIOA
#define PIN_SWDIO_TMS_PIN   4
#define PIN_SWCLK_TCK_PORT  GPIOA
#define PIN_SWCLK_TCK_PIN   5
#define PIN_TDO_PORT        GPIOA
#define PIN_TDO_PIN         6
#define PIN_TDI_PORT        GPIOA
#define PIN_TDI_PIN         7
#define PIN_nRESET_PORT     GPIOB
#define PIN_nRESET_PIN      9

#elif defined ( STLINK_V20 ) \
   || defined ( STLINK_V21 )
#define PIN_SWDIO_TMS_PORT  GPIOB
#define PIN_SWDIO_TMS_PIN   14
#define PIN_SWCLK_TCK_PORT  GPIOB
#define PIN_SWCLK_TCK_PIN   13
#define PIN_TDO_PORT        GPIOB
#define PIN_TDO_PIN         7
#define PIN_nRESET_PORT     GPIOB
#define PIN_nRESET_PIN      0

#elif defined ( BOARD_STM32RF )
#define PIN_SWDIO_TMS_PORT  GPIOA
#define PIN_SWDIO_TMS_PIN   6
#define PIN_SWCLK_TCK_PORT  GPIOA
#define PIN_SWCLK_TCK_PIN   7
#define PIN_TDO_PORT        GPIOB
#define PIN_TDO_PIN         7
#define PIN_nRESET_PORT     GPIOB
#define PIN_nRESET_PIN      9

#elif defined ( STLINK_V2A ) \
  ||  defined ( STLINK_V2B )
#define PIN_SWDIO_TMS_PORT  GPIOB
#define PIN_SWDIO_TMS_PIN   14
#define PIN_SWCLK_TCK_PORT  GPIOB
#define PIN_SWCLK_TCK_PIN   13

#if defined ( SWO_PB7 )
#define PIN_TDO_PORT        GPIOB
#define PIN_TDO_PIN         7
#elif defined ( SWO_PA10 )
#define PIN_TDO_PORT        GPIOA
#define PIN_TDO_PIN         10
#else
#define PIN_TDO_PORT        GPIOB
#define PIN_TDO_PIN         7
#endif

#define PIN_TDI_PORT        GPIOB
#define PIN_TDI_PIN         8
#define PIN_nRESET_PORT     GPIOB
#define PIN_nRESET_PIN      6
#endif

// Debug Unit LEDs
#if defined ( BLUEPILL )
#define LED_CONNECTED_RCC   RCC_APB2ENR_IOPCEN
#define LED_CONNECTED_PORT  GPIOC
#define LED_CONNECTED_PIN   13
#define LED_RUNNING_RCC     RCC_APB2ENR_IOPCEN
#define LED_RUNNING_PORT    GPIOC
#define LED_RUNNING_PIN     13

#elif defined ( BOARD_V1 ) || defined ( BOARD_V2 )
#define LED_CONNECTED_RCC   RCC_APB2ENR_IOPBEN
#define LED_RUNNING_RCC     RCC_APB2ENR_IOPBEN
#define LED_CONNECTED_PORT  GPIOB
#define LED_CONNECTED_PIN   13
#define LED_RUNNING_PORT    GPIOB
#define LED_RUNNING_PIN     12

#elif defined ( STLINK_V20 ) \
  ||  defined ( STLINK_V2A ) \
  ||  defined ( STLINK_V2B )
#define LED_CONNECTED_RCC   RCC_APB2ENR_IOPAEN
#define LED_RUNNING_RCC     RCC_APB2ENR_IOPAEN
#define LED_CONNECTED_PORT  GPIOA
#define LED_CONNECTED_PIN   9
#define LED_RUNNING_PORT    GPIOA
#define LED_RUNNING_PIN     9

#elif defined ( STLINK_V21 )
#define LED_CONNECTED_RCC   RCC_APB2ENR_IOPAEN
#define LED_RUNNING_RCC     RCC_APB2ENR_IOPAEN
#define LED_CONNECTED_PORT  GPIOA
#define LED_CONNECTED_PIN   9
#define LED_RUNNING_PORT    GPIOA
#define LED_RUNNING_PIN     8

#elif defined ( BOARD_STM32RF )
#define LED_CONNECTED_RCC   RCC_APB2ENR_IOPBEN
#define LED_RUNNING_RCC     RCC_APB2ENR_IOPBEN
#define LED_CONNECTED_PORT  GPIOB
#define LED_CONNECTED_PIN   11
#define LED_RUNNING_PORT    GPIOB
#define LED_RUNNING_PIN     12
#endif

#define LED_CONNECTED_MASK      PIN_MASK(LED_CONNECTED_PIN)
#define LED_RUNNING_MASK        PIN_MASK(LED_RUNNING_PIN)

#define PIN_nRESET_MASK         PIN_MASK(PIN_nRESET_PIN)
#define PIN_SWDIO_TMS_MASK      PIN_MASK(PIN_SWDIO_TMS_PIN)
#define PIN_SWCLK_TCK_MASK      PIN_MASK(PIN_SWCLK_TCK_PIN)
#define PIN_TDI_MASK            PIN_MASK(PIN_TDI_PIN)
#define PIN_TDO_MASK            PIN_MASK(PIN_TDO_PIN)

#if defined ( JLINK_OB )
#define PIN_nRESET_LOW()       do { } while (0)
#define PIN_nRESET_HIGH()      do { } while (0)
#else

#if (PIN_nRESET_PIN >= 8)
#define PIN_nRESET_LOW()              \
  do {                               \
    PIN_nRESET_PORT->CRH =           \
      (PIN_nRESET_PORT->CRH &        \
      ~PIN_MODE_MASK(PIN_nRESET_PIN - 8)) \
      | PIN_MODE(((GPIO_Mode_Out_OD | GPIO_Speed_50MHz) & 0x0F), \
                 PIN_nRESET_PIN - 8); \
    PIN_nRESET_PORT->BRR = PIN_nRESET_MASK; \
  } while (0)

#define PIN_nRESET_HIGH()             \
  do {                               \
    PIN_nRESET_PORT->BSRR = PIN_nRESET_MASK; \
    PIN_nRESET_PORT->CRH =           \
      (PIN_nRESET_PORT->CRH &        \
      ~PIN_MODE_MASK(PIN_nRESET_PIN - 8)) \
      | PIN_MODE(GPIO_Mode_IPU, PIN_nRESET_PIN - 8); \
  } while (0)
#else
#define PIN_nRESET_LOW()              \
  do {                               \
    PIN_nRESET_PORT->CRL =           \
      (PIN_nRESET_PORT->CRL &        \
      ~PIN_MODE_MASK(PIN_nRESET_PIN)) \
      | PIN_MODE(((GPIO_Mode_Out_OD | GPIO_Speed_50MHz) & 0x0F), \
                 PIN_nRESET_PIN); \
    PIN_nRESET_PORT->BRR = PIN_nRESET_MASK; \
  } while (0)

#define PIN_nRESET_HIGH()             \
  do {                               \
    PIN_nRESET_PORT->BSRR = PIN_nRESET_MASK; \
    PIN_nRESET_PORT->CRL =           \
      (PIN_nRESET_PORT->CRL &        \
      ~PIN_MODE_MASK(PIN_nRESET_PIN)) \
      | PIN_MODE(GPIO_Mode_IPU, PIN_nRESET_PIN); \
  } while (0)
#endif
#endif

// ???????? SWDIO ?????,?????????
#if (PIN_SWDIO_TMS_PIN >= 8)
#define PIN_SWDIO_TMS_OUT_DISABLE()         \
  do {                      \
    PIN_SWDIO_TMS_PORT->CRH = (PIN_SWDIO_TMS_PORT->CRH & ~PIN_MODE_MASK(PIN_SWDIO_TMS_PIN - 8)) | PIN_MODE(0x8, PIN_SWDIO_TMS_PIN - 8); \
    PIN_SWDIO_TMS_PORT->BSRR = PIN_SWDIO_TMS_MASK;  \
  } while (0)

#define PIN_SWDIO_TMS_OUT_ENABLE()          \
  do {                      \
    PIN_SWDIO_TMS_PORT->CRH = (PIN_SWDIO_TMS_PORT->CRH & ~PIN_MODE_MASK(PIN_SWDIO_TMS_PIN - 8)) | PIN_MODE(0x3, PIN_SWDIO_TMS_PIN - 8); \
    PIN_SWDIO_TMS_PORT->BRR  = PIN_SWDIO_TMS_MASK;  \
  } while (0)
#else
#define PIN_SWDIO_TMS_OUT_DISABLE()         \
  do {                      \
    PIN_SWDIO_TMS_PORT->CRL = (PIN_SWDIO_TMS_PORT->CRL & ~PIN_MODE_MASK(PIN_SWDIO_TMS_PIN)) | PIN_MODE(0x8, PIN_SWDIO_TMS_PIN); \
    PIN_SWDIO_TMS_PORT->BSRR = PIN_SWDIO_TMS_MASK;  \
  } while (0)

#define PIN_SWDIO_TMS_OUT_ENABLE()          \
  do {                      \
    PIN_SWDIO_TMS_PORT->CRL = (PIN_SWDIO_TMS_PORT->CRL & ~PIN_MODE_MASK(PIN_SWDIO_TMS_PIN)) | PIN_MODE(0x3, PIN_SWDIO_TMS_PIN); \
    PIN_SWDIO_TMS_PORT->BRR  = PIN_SWDIO_TMS_MASK;  \
  } while (0)
#endif

void PORT_USB_CONNECT_SETUP(void);
void LEDS_SETUP (void);

void PORT_JTAG_SETUP(void);
void PORT_SWD_SETUP(void);
void PORT_OFF(void);

#define DAP_SETUP() PORT_OFF()

__STATIC_INLINE uint8_t PIN_SWCLK_TCK_IN(void)
{
  return (PIN_SWCLK_TCK_PORT->ODR & PIN_SWCLK_TCK_MASK) ? 1 : 0;
}

__STATIC_INLINE void PIN_SWCLK_TCK_SET(void)
{
  PIN_SWCLK_TCK_PORT->BSRR = PIN_SWCLK_TCK_MASK;
}

__STATIC_INLINE void PIN_SWCLK_TCK_CLR (void)
{
  PIN_SWCLK_TCK_PORT->BRR = PIN_SWCLK_TCK_MASK;
}

__STATIC_INLINE uint8_t PIN_SWDIO_TMS_IN(void)
{
  return (PIN_SWDIO_TMS_PORT->IDR & PIN_SWDIO_TMS_MASK) ? 1 : 0;
}

__STATIC_INLINE void PIN_SWDIO_TMS_SET(void)
{
  PIN_SWDIO_TMS_PORT->BSRR = PIN_SWDIO_TMS_MASK;
}

__STATIC_INLINE void PIN_SWDIO_TMS_CLR(void)
{
  PIN_SWDIO_TMS_PORT->BRR = PIN_SWDIO_TMS_MASK;
}

__STATIC_INLINE uint8_t PIN_SWDIO_IN (void)
{
  return (PIN_SWDIO_TMS_PORT->IDR & PIN_SWDIO_TMS_MASK) ? 1 : 0;
}

__STATIC_INLINE void PIN_SWDIO_OUT(uint8_t bit)
{
  if (bit & 1)
    PIN_SWDIO_TMS_PORT->BSRR = PIN_SWDIO_TMS_MASK;
  else
    PIN_SWDIO_TMS_PORT->BRR  = PIN_SWDIO_TMS_MASK;
}

__STATIC_INLINE void PIN_SWDIO_OUT_ENABLE(void)
{
  PIN_SWDIO_TMS_OUT_ENABLE();
}

__STATIC_INLINE void PIN_SWDIO_OUT_DISABLE(void)
{
  PIN_SWDIO_TMS_OUT_DISABLE();
}

__STATIC_INLINE uint8_t PIN_TDI_IN(void)
{
#if ( DAP_JTAG != 0 )
  return (PIN_TDI_PORT->ODR & PIN_TDI_MASK) ? 1 : 0;
#else
  return (0);
#endif
}

__STATIC_INLINE void PIN_TDI_OUT(uint8_t bit)
{
#if ( DAP_JTAG != 0 )
  if (bit & 1)
    PIN_TDI_PORT->BSRR = PIN_TDI_MASK;
  else
    PIN_TDI_PORT->BRR  = PIN_TDI_MASK;
#endif
}

__STATIC_INLINE uint8_t PIN_TDO_IN(void)
{
#if ( DAP_JTAG != 0 )
  return (PIN_TDO_PORT->IDR & PIN_TDO_MASK) ? 1 : 0;
#else
  return (0);
#endif
}

__STATIC_INLINE uint8_t PIN_nTRST_IN(void)
{
  return (0);
}

__STATIC_INLINE void PIN_nTRST_OUT(uint8_t bit)
{
}

__STATIC_INLINE uint8_t PIN_nRESET_IN(void)
{
#if defined ( JLINK_OB )
  return 1;
#else
  return (PIN_nRESET_PORT->IDR & PIN_nRESET_MASK) ? 1 : 0;
#endif
}

#define PIN_nRESET_OUT(b) vResetTarget(b)

#define LED_CONNECTED_OUT(b)  pCoreDescriptor->LedConnected(b)
#define LED_RUNNING_OUT(b)    pCoreDescriptor->LedRunning(b)

static __inline uint32_t TIMESTAMP_GET (void) {
  return (DWT->CYCCNT);
}

__STATIC_INLINE uint8_t RESET_TARGET(void)
{
  return (1);
}

#endif /* __DAP_CONFIG_H__ */
