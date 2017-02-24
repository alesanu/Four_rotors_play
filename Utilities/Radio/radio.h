/**
 * radio.h
 * Functions to initalize and control radio receiver
 */

#include "stm32f30x_conf.h"
#include "stm32f30x_it.h"


/**
 * System clock runs at 72MHz
 * Set TIMER frequency at 2MHz
 * Prescaler = SYS_CLK / TIM_FREQ = 36
 * PWM frequency at 200 Hz
 * PWM period = TIM_FREQ / PWM_FREQ = 10000
 * PWM pulse length = 2000 ms
 */
#define SYS_CLK       (uint32_t)(72e6)
#define TIM_FREQ      (uint32_t)(2e6)
#define PWM_PRESCALER (uint32_t)((SYS_CLK / TIM_FREQ) - 1)
#define PWM_FREQ      (uint32_t)(400)
#define PWM_PERIOD    (uint32_t)((TIM_FREQ / PWM_FREQ) - 1)
#define PWM_PULSE     (uint32_t)(PWM_PERIOD / (1000.0/PWM_FREQ))
#define PI					3.14159265358979f


/**
 * Command range values
 * PWM pulse widths
 */

 #define ROLL_RADIO_MIN	995
 #define ROLL_RADIO_MAX	1988
 #define PITCH_RADIO_MIN	994
 #define PITCH_RADIO_MAX	1985
 #define THROTTLE_RADIO_MIN	994
 #define THROTTLE_RADIO_MAX	1988
 #define YAW_RADIO_MIN	999
 #define YAW_RADIO_MAX	1984

 #define ROLL_RANGE	ROLL_RADIO_MAX - ROLL_RADIO_MIN
 #define PITCH_RANGE	PITCH_RADIO_MAX - PITCH_RADIO_MIN
 #define THROTTLE_RANGE	THROTTLE_RADIO_MAX - THROTTLE_RADIO_MIN
 #define YAW_RANGE	YAW_RADIO_MAX - YAW_RADIO_MIN

/**
 * Command range values
 * Radians input values
 */

 #define ROLL_MIN_RADIAN	-PI/6.
 #define ROLL_MAX_RADIAN	PI/6.
 #define PITCH_MIN_RADIAN	-PI/6.
 #define PITCH_MAX_RADIAN	PI/6.
 #define THROTTLE_MIN_RADIAN	-100.f
 #define THROTTLE_MAX_RADIAN	100.f
 #define YAW_MIN_RADIAN	-PI
 #define YAW_MAX_RADIAN	PI

 #define ROLL_RANGE_RADIAN	ROLL_MAX_RADIAN - ROLL_MIN_RADIAN
 #define PITCH_RANGE_RADIAN	PITCH_MAX_RADIAN - PITCH_MIN_RADIAN
 #define THROTTLE_RANGE_RADIAN	THROTTLE_MAX_RADIAN - THROTTLE_MIN_RADIAN
 #define YAW_RANGE_RADIAN	YAW_MAX_RADIAN - YAW_MIN_RADIAN

/**
 * Identifiers for radio receiver TIM1
 * ROLL   - PB12 - CH2
 * PITCH  - PB13 - CH3
 * THROTTLE  - PB11 - CH1
 * YAW - PB14 - CH4
 * AUX1 - -
 * AUX2 - -
 */
 #define RADIO_ROLL	0x01
 #define RADIO_PITCH	0x02
 #define RADIO_THROTTLE	0x00
 #define RADIO_YAW	0x03
 #define AUX1
 #define AUX2


/**
 * Test if command PWM is within valid range
 */
 #define IS_VALID_ROLL(COMMAND) ((COMMAND >= ROLL_MIN_RADIAN) && (COMMAND <= ROLL_MAX_RADIAN))
 #define IS_VALID_PITCH(COMMAND) ((COMMAND >= PITCH_MIN_RADIAN) && (COMMAND <= PITCH_MAX_RADIAN))
 #define IS_VALID_THOTTLE(COMMAND) ((COMMAND >= THROTTLE_MIN_RADIAN) && (COMMAND <= THROTTLE_MAX_RADIAN))
 #define IS_VALID_YAW(COMMAND) ((COMMAND >= YAW_MIN_RADIAN) && (COMMAND <= YAW_MAX_RADIAN))

/**
 * Convert percentage of full speed to PWM pulse width
 */
#define MOTOR_SPEED_PERCENTAGE(PERCENTAGE) (uint32_t)((PERCENTAGE * ((MOTOR_SPEED_MAX - MOTOR_SPEED_MIN) / 100)) + MOTOR_SPEED_MIN)

/**
 * Initialize timers for PWM control
 */
void radio_init(void);

/**
 * Configure the TIM1 IRQ Handler
 */
void radio_TIM_config(void);
