

#ifndef USE_MAKE
//#define F031_DEV
// #define FD6288_F051
// #define IFLIGHT
// #define MP6531
// #define TMOTOR55     // like iflight but with leds
// #define TMOTOR45
// #define HGLRC
// #define SISKIN
// #define MAMBA_F50PRO
// #define WRAITH32
// #define AIKON20X20
// #define AIKONSINGLE
// #define FLYCOLOR
// #define HKMICRO
// #define AM32REF_F051
// #define BLPWR
// #define HVFLYCOLOR
// #define AM32REF_F051

// #define G072ESC
// #define G071ENABLE
// #define G071_OPEN_DRAIN
// #define G071_OPEN_DRAIN_B
// #define GEN_64K_G071
// define  DT120_G071

// #define WRAITH32_F421
// #define GD32DEV
// #define GD32DEV_B
// #define GD32SKYSTARS20
// #define GD32SKYSTARS25
// #define GD32SKYSTARS30
// #define GD32SKYSTARS40
#endif

// used to hold a port/pin in a single 16 bit integer
// used to hold a port/pin in a single 16 bit integer
#define GPIO_PORT_PIN(portnum, pinnum) ((portnum)<<8|(pinnum))

/*********************************************************************
 * AT32F421 targets using HARDWARE_GROUP_AT_B + HARDWARE_GROUP_AT_045
 *********************************************************************/







#ifdef  TEKKO32_4IN1_F421
#define FIRMWARE_NAME "Tekko32 4in1"
#define FILE_NAME "TEKKO32_4IN1_F421"
#define DEAD_TIME 80
#define HARDWARE_GROUP_AT_B
#define HARDWARE_GROUP_AT_045
#define USE_SERIAL_TELEMETRY
#endif






#ifndef FIRMWARE_NAME
/* if you get this then you have forgotten to add the section for your target above */
#error "Missing defines for target"
#endif

/********************************** defaults if not set
 * ***************************/

#ifndef TARGET_VOLTAGE_DIVIDER
#define TARGET_VOLTAGE_DIVIDER 110
#endif

#ifndef SINE_DIVIDER
#define SINE_DIVIDER 2
#endif

#ifndef MILLIVOLT_PER_AMP
#define MILLIVOLT_PER_AMP 20
#endif

#ifndef CURRENT_OFFSET
#define CURRENT_OFFSET 0
#endif

#ifndef TARGET_STALL_PROTECTION_INTERVAL
#define TARGET_STALL_PROTECTION_INTERVAL 6500
#endif

#ifndef RAMP_SPEED_STARTUP
#define RAMP_SPEED_STARTUP 2 // adjusted 2.14 to match duty cycle change between mcu targets.
#endif

#ifndef RAMP_SPEED_LOW_RPM // below commutation interval of 250us
#define RAMP_SPEED_LOW_RPM 6
#endif

#ifndef RAMP_SPEED_HIGH_RPM
#define RAMP_SPEED_HIGH_RPM 16
#endif

/************************************ AT32F421 Hardware Groups
 * ****************************/

#ifdef HARDWARE_GROUP_AT_B

#define MCU_AT421
#define USE_TIMER_3_CHANNEL_1
#define INPUT_PIN GPIO_PINS_4
#define INPUT_PIN_SOURCE GPIO_PINS_SOURCE4
#define INPUT_PIN_PORT GPIOB
#define IC_TIMER_CHANNEL TMR_SELECT_CHANNEL_1
#define IC_TIMER_REGISTER TMR3
#define INPUT_DMA_CHANNEL DMA1_CHANNEL4
#define IC_DMA_IRQ_NAME DMA1_Channel5_4_IRQn

#define PHASE_A_GPIO_LOW GPIO_PINS_1
#define PHASE_A_PIN_SOURCE_LOW GPIO_PINS_SOURCE1
#define PHASE_A_GPIO_PORT_LOW GPIOB
#define PHASE_A_GPIO_HIGH GPIO_PINS_10
#define PHASE_A_PIN_SOURCE_HIGH GPIO_PINS_SOURCE10
#define PHASE_A_GPIO_PORT_HIGH GPIOA

#define PHASE_B_GPIO_LOW GPIO_PINS_0
#define PHASE_B_PIN_SOURCE_LOW GPIO_PINS_SOURCE0
#define PHASE_B_GPIO_PORT_LOW GPIOB
#define PHASE_B_GPIO_HIGH GPIO_PINS_9
#define PHASE_B_PIN_SOURCE_HIGH GPIO_PINS_SOURCE9
#define PHASE_B_GPIO_PORT_HIGH GPIOA

#define PHASE_C_GPIO_LOW GPIO_PINS_7
#define PHASE_C_PIN_SOURCE_LOW GPIO_PINS_SOURCE7
#define PHASE_C_GPIO_PORT_LOW GPIOA
#define PHASE_C_GPIO_HIGH GPIO_PINS_8
#define PHASE_C_PIN_SOURCE_HIGH GPIO_PINS_SOURCE8
#define PHASE_C_GPIO_PORT_HIGH GPIOA

#endif

#ifdef HARDWARE_GROUP_AT_045
#define PHASE_A_COMP 0x400000E5 // pa0 Medium Comp Power
#define PHASE_B_COMP 0x400000C5 // pa4
#define PHASE_C_COMP 0x400000D5 // pa5
#endif

/************************************ MCU COMMON PERIPHERALS
 * **********************************************/

#ifdef MCU_AT421
#define ARTERY
#define CPU_FREQUENCY_MHZ 120
#define EEPROM_START_ADD (uint32_t)0x08007C00
#define INTERVAL_TIMER TMR6
#define TEN_KHZ_TIMER TMR14
#define UTILITY_TIMER TMR17
#define COM_TIMER TMR16
#define APPLICATION_ADDRESS 0x08001000
#define EXTI_LINE EXINT_LINE_21
#ifndef TARGET_MIN_BEMF_COUNTS
#define TARGET_MIN_BEMF_COUNTS 3
#endif
#define COMPARATOR_IRQ ADC1_CMP_IRQn
#define USE_ADC
#ifndef CURRENT_ADC_CHANNEL
#define CURRENT_ADC_CHANNEL ADC_CHANNEL_6
#endif
#ifndef CURRENT_ADC_PIN
#define CURRENT_ADC_PIN GPIO_PINS_6
#endif
#ifndef VOLTAGE_ADC_CHANNEL
#define VOLTAGE_ADC_CHANNEL ADC_CHANNEL_3
#endif
#ifndef VOLTAGE_ADC_PIN
#define VOLTAGE_ADC_PIN GPIO_PINS_3
#endif
#ifndef TEMP_ADC_CHANNEL
#define TEMP_ADC_CHANNEL ADC_CHANNEL_16
#endif
#define DSHOT_PRIORITY_THRESHOLD 50
#define COM_TIMER_IRQ TMR16_GLOBAL_IRQn
#endif

#ifndef LOOP_FREQUENCY_HZ
#define LOOP_FREQUENCY_HZ 20000
#endif

#define PID_LOOP_DIVIDER (LOOP_FREQUENCY_HZ / 1000)

// default to no DroneCAN support
#ifndef DRONECAN_SUPPORT
#define DRONECAN_SUPPORT 0
#elif DRONECAN_SUPPORT == 1
// all DroneCAN ESCs use 128k flash layout
#undef EEPROM_START_ADD
#define EEPROM_START_ADD (uint32_t)0x0801F800
#endif

#ifndef NOMINAL_PWM
// use a nominal PWM for commutation via TIM1 of 24kHz
#define NOMINAL_PWM 24000U
#endif

#ifndef TIM1_AUTORELOAD
// calculate commutation timer ARR based on a nominal 24kHz PWM
#define TIM1_AUTORELOAD    ((uint16_t)(CPU_FREQUENCY_MHZ * 1000U * 1000U / NOMINAL_PWM)-1)
#endif

#ifndef POLLING_MODE_THRESHOLD
#define POLLING_MODE_THRESHOLD 2000
#endif


