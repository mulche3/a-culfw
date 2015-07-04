#ifndef BOARD_H 
#define BOARD_H

#define _BV(a) (1<<(a))
#define bit_is_set(sfr, bit) ((sfr) & _BV(bit))


//#define LONG_PULSE

#define TTY_BUFSIZE          128      // RAM: TTY_BUFSIZE*4
#define ARM
#define HAS_USB
#define USB_IsConnected		(USBD_GetState() == USBD_STATE_CONFIGURED)
#define USB_DESCRIPTOR_SN	'1'

#define HAS_FHT_80b
#define HAS_FHT_8v
//#define HAS_RF_ROUTER
#define HAS_CC1101_RX_PLL_LOCK_CHECK_TASK_WAIT
#define HAS_CC1101_PLL_LOCK_CHECK_MSG
#define HAS_CC1101_PLL_LOCK_CHECK_MSG_SW

#define FHTBUF_SIZE          174
#define RCV_BUCKETS            4      //                 RAM: 25b * bucket
#define RFR_DEBUG
#define FULL_CC1100_PA
#define HAS_RAWSEND
#define HAS_FASTRF
#define HAS_ASKSIN
#define HAS_ASKSIN_FUP
#define HAS_MORITZ
#define HAS_RWE
#define HAS_ESA
#define HAS_HMS
#define HAS_TX3
#define HAS_INTERTECHNO
#define HAS_UNIROLL
#define HAS_HOERMANN
#define HAS_SOMFY_RTS
//#define HAS_MAICO

//#define HAS_MBUS
//#define HAS_MEMFN

#if defined(HM_CFG)

#elif defined(HM_CFG_BL)
#define HM_CFG
#elif defined(bootloader_HM_CFG)
#undef  TTY_BUFSIZE
#define TTY_BUFSIZE          512
#define HM_CFG
#elif defined(CUBE)

#elif defined(CUBE_BL)
#define CUBE
#elif defined(bootloader_CUBE)
#define CUBE
#undef  TTY_BUFSIZE
#define TTY_BUFSIZE          512
#else
#define CUBE
#endif

#if defined(HM_CFG)
	#define BOARD_NAME 			"CUL-HM-CFG"
	#define BOARD_ID_STR        "CUL-HM-CFG"
#elif defined(CUBE)
	#define USE_DATAFLASH
	#define BOARD_NAME 			"CUBe"
	#define BOARD_ID_STR        "CUBe"
#else
    #error no target defined.
#endif

#ifdef CUBE
#define SPI_SS				(1<<12)
#define SPI_MISO			(1<<16)
#define SPI_MOSI			(1<<17)
#define SPI_SCLK			(1<<18)

#define CC1100_CS_PIN		12
#define CC1100_CS_BASE		AT91C_BASE_PIOA
#define CC1100_OUT_PIN      30
#define CC1100_OUT_BASE     AT91C_BASE_PIOA
#define CC1100_IN_PIN       29
#define CC1100_IN_BASE		AT91C_BASE_PIOA
#define CC1100_IN_PORT     	CC1100_IN_BASE->PIO_PDSR

/*
//additional CC1101 Transceiver
#define CC1100_ASKSIN		0
#define CC1100_MORITZ		1
//#define CC1100_MAICO		0

#define CC1100_2_CS_PIN		24
#define CC1100_2_CS_BASE	AT91C_BASE_PIOB
#define CC1100_2_IN_PIN     25
#define CC1100_2_IN_BASE	AT91C_BASE_PIOB

#define CC1100_3_CS_PIN		6
#define CC1100_3_CS_BASE	AT91C_BASE_PIOA
#define CC1100_3_IN_PIN     5
#define CC1100_3_IN_BASE	AT91C_BASE_PIOA

#define CCCOUNT				2
#define CCTRANSCEIVERS		{{CC1100_2_CS_BASE,CC1100_2_CS_PIN, CC1100_2_IN_BASE,CC1100_2_IN_PIN},\
							 {CC1100_3_CS_BASE,CC1100_3_CS_PIN, CC1100_3_IN_BASE,CC1100_3_IN_PIN}}
*/
#define BOOTLOADER_PIN		(1<<14)

//#define HAS_ETHERNET            1       // undef or define...1
//#define HAS_ETHERNET_KEEPALIVE  1
//#define ETHERNET_KEEPALIVE_TIME 30
//#define HAS_NTP                 1       // undef or define...1

#else //HM_CFG
#define SPI_SS				(1<<11)
#define SPI_MISO			(1<<12)
#define SPI_MOSI			(1<<13)
#define SPI_SCLK			(1<<14)

#define CC1100_CS_PIN		11
#define CC1100_CS_BASE		AT91C_BASE_PIOA
#define CC1100_OUT_PIN      20
#define CC1100_OUT_BASE     AT91C_BASE_PIOA
#define CC1100_IN_PIN       19
#define CC1100_IN_BASE		AT91C_BASE_PIOA
#define CC1100_IN_PORT      AT91C_BASE_PIOA->PIO_PDSR

#define BOOTLOADER_PIN		(1<<9)

#endif

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------
#if defined(HM_CFG)
    #include "AT91SAM7S128.h"
#elif defined(CUBE)
    #include "AT91SAM7X256.h"
#else
    #error Board does not support the specified chip.
#endif

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
/// \page "SAM7X-EK - Operating frequencies"
/// This page lists several definition related to the board operating frequency
/// (when using the initialization done by board_lowlevel.c).
/// 
/// !Definitions
/// - BOARD_MAINOSC
/// - BOARD_MCK

/// Frequency of the board main oscillator.
#define BOARD_MAINOSC           18432000

/// Master clock frequency (when using board_lowlevel.c).
#define BOARD_MCK               48000000
//------------------------------------------------------------------------------

#ifdef CUBE
//------------------------------------------------------------------------------
/// \page "SAM7X-EK - USB device"
/// This page lists constants describing several characteristics (controller
/// type, D+ pull-up type, etc.) of the USB device controller of the chip/board.
/// 
/// !Constants
/// - BOARD_USB_UDP
/// - BOARD_USB_PULLUP_ALWAYSON
/// - BOARD_USB_NUMENDPOINTS
/// - BOARD_USB_ENDPOINTS_MAXPACKETSIZE
/// - BOARD_USB_ENDPOINTS_BANKS
/// - BOARD_USB_BMATTRIBUTES

/// Chip has a UDP controller.
#define BOARD_USB_UDP

/// Indicates the D+ pull-up is always connected.
//#define BOARD_USB_PULLUP_ALWAYSON
#define BOARD_USB_PULLUP_EXTERNAL
#define PIN_USB_PULLUP {1 << 13, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_OPENDRAIN}

/// Number of endpoints in the USB controller.
#define BOARD_USB_NUMENDPOINTS                  6

/// Returns the maximum packet size of the given endpoint.
#define BOARD_USB_ENDPOINTS_MAXPACKETSIZE(i)    ((((i) == 4) || ((i) == 5)) ? 256 : (((i) == 0) ? 8 : 64))

/// Returns the number of FIFO banks for the given endpoint.
#define BOARD_USB_ENDPOINTS_BANKS(i)            ((((i) == 0) || ((i) == 3)) ? 1 : 2)

/// USB attributes configuration descriptor (bus or self powered, remote wakeup)
#define BOARD_USB_BMATTRIBUTES                  USBConfigurationDescriptor_BUSPOWERED_NORWAKEUP

/// Board EMAC Power Down control pin
#define BOARD_EMAC_PIN_PWRDN {(1<<18), AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT}
/// Board EMAC mode - RMII/MII ( 1/0 )
#define BOARD_EMAC_MODE_RMII 0 // MII is the default mode
/// The PIN list of PIO for EMAC
#define BOARD_EMAC_PINS     {0x3FFFF, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
/// The power up reset latch PIO for PHY
#define BOARD_EMAC_PIN_TEST   {(1<<15), AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT}
#define BOARD_EMAC_PIN_RMII   {(1<<16), AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT}
// We force the address
//(1<<5) PHY address 0, (1<<6) PHY address 1, (1<<13) PHY address 2,
//(1<<14) PHY address 3, (1<<4) PHY address 4
#define BOARD_EMAC_PINS_PHYAD {(1<<6)|(1<<13)|(1<<14)|(1<<4),\
                               AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT},\
                              {(1<<5), AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT}
#define BOARD_EMAC_PIN_10BT   {(1<<17), AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT}
#define BOARD_EMAC_PIN_RPTR   {(1<< 7), AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT}
/// The PIN Configure list for EMAC on power up reset (MII)
#define BOARD_EMAC_RST_PINS BOARD_EMAC_PINS_PHYAD, \
                            BOARD_EMAC_PIN_TEST, BOARD_EMAC_PIN_RMII, \
                            BOARD_EMAC_PIN_10BT, BOARD_EMAC_PIN_RPTR

/// The runtime pin configure list for EMAC
#define BOARD_EMAC_RUN_PINS BOARD_EMAC_PINS

//------------------------------------------------------------------------------
#else //HM_CFG
/// Indicates the chip has a UDP controller.
#define BOARD_USB_UDP

/// Indicates the D+ pull-up is externally controlled.
#define BOARD_USB_PULLUP_EXTERNAL
#define PIN_USB_PULLUP {1 << 16, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}

/// Number of endpoints in the USB controller.
#define BOARD_USB_NUMENDPOINTS                  4

/// Returns the maximum packet size of the given endpoint.
/// \param i  Endpoint number.
/// \return Maximum packet size in bytes of endpoint.
#define BOARD_USB_ENDPOINTS_MAXPACKETSIZE(i)    ((i == 0) ? 8 : 64)

/// Returns the number of FIFO banks for the given endpoint.
/// \param i  Endpoint number.
/// \return Number of FIFO banks for the endpoint.
#define BOARD_USB_ENDPOINTS_BANKS(i)            (((i == 0) || (i == 3)) ? 1 : 2)

/// USB attributes configuration descriptor (bus or self powered, remote wakeup)
//#define BOARD_USB_BMATTRIBUTES                  USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP
#define BOARD_USB_BMATTRIBUTES                  USBConfigurationDescriptor_BUSPOWERED_NORWAKEUP
#endif
//------------------------------------------------------------------------------


#ifdef CUBE
/// List of all DBGU pin definitions.
#define PINS_DBGU  { (1<<27)|(1<<28), AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/// LED #0 pin definition.A8
#define PIN_LED_0  {1 << 8, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
/// LED #1 pin definition.
#define PIN_LED_1  {1 << 30, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT}
/// LED #2 pin definition.
#define PIN_LED_2  {1 << 29, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT}
/// LED #3 pin definition.
#define PINS_LEDS  PIN_LED_0, PIN_LED_1, PIN_LED_2


/// USART0 RXD pin definition.
#define PIN_USART0_RXD  {1 << 0, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// USART0 TXD pin definition.
#define PIN_USART0_TXD  {1 << 1, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/// USART1 RXD pin definition.
#define PIN_USART1_RXD  {1 << 27, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// USART1 TXD pin definition.
#define PIN_USART1_TXD  {1 << 28, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}


/// SPI0 MISO pin definition.
#define PIN_SPI1_MISO   {1 << 24, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
/// SPI0 MOSI pin definition.
#define PIN_SPI1_MOSI   {1 << 23, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_PULLUP}
/// SPI0 SPCK pin definition.
#define PIN_SPI1_SPCK   {1 << 22, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_PULLUP}
/// List of SPI0 pin definitions (MISO, MOSI & SPCK).
#define PINS_SPI1       PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK
/// SPI0 chip select 0 pin definition.
#define PIN_SPI1_NPCS0  {1 << 21, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_PULLUP}

/// Base address of SPI peripheral connected to the dataflash.
#define BOARD_AT45_A_SPI_BASE         AT91C_BASE_SPI1
/// Identifier of SPI peripheral connected to the dataflash.
#define BOARD_AT45_A_SPI_ID           AT91C_ID_SPI1
/// Pins of the SPI peripheral connected to the dataflash.
#define BOARD_AT45_A_SPI_PINS         PINS_SPI1
/// Dataflahs SPI number.
#define BOARD_AT45_A_SPI              1
/// Chip select connected to the dataflash.
#define BOARD_AT45_A_NPCS             0
/// Chip select pin connected to the dataflash.
#define BOARD_AT45_A_NPCS_PIN         PIN_SPI1_NPCS0

#else //HM_CFG
#define PINS_DBGU  { (1<<9)|(1<<10), AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/// LED #0 pin definition.A8
#define PIN_LED_0  {1 << 24, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}

#define PINS_LEDS  PIN_LED_0


/// USART0 RXD pin definition.
#define PIN_USART0_RXD  {1 << 0, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// USART0 TXD pin definition.
#define PIN_USART0_TXD  {1 << 1, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// USART0 SCK pin definition.


#define AT91C_BASE_SPI0		AT91C_BASE_SPI
#define AT91C_ID_SPI0		AT91C_ID_SPI
#endif



/// Indicates chip has an EFC.
#define BOARD_FLASH_EFC
/// Address of the IAP function in ROM.
#define BOARD_FLASH_IAP_ADDRESS         0x300008
//------------------------------------------------------------------------------

#endif //#ifndef BOARD_H

