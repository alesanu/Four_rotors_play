/**
 * controls.h
 * Define functions for controlling and stabilizing the quadcopter
 */

#ifndef CONTROLS_H
#define CONTROLS_H

#include "stm32f30x_conf.h"


/**
 * Indicator modes
 */
#define CONTROL_COMMAND_MODE   (uint8_t)(0x00)
#define CONTROL_ECHO           (uint8_t)(0x0F)
#define CONTROL_PID_UPDATE     (uint8_t)(0x10)

/**
 * Command structure
 * roll     - float between -30° and +30° (in radians)
 * pitch    - float between -30° and +30° (in radians)
 * throttle - float between -100 and 100
 * yaw      - float between -180° and +180° (in radians)
 */
typedef struct {
  float roll;
  float pitch;
  float throttle;
  float yaw;
} command_t;

extern command_t command;


/**
 * Command structure
 * roll     - uint16_t capture from timer in ms
 * pitch    - uint16_t capture from timer in ms
 * throttle - uint16_t capture from timer in ms
 * yaw      - uint16_t capture from timer in ms
 */
typedef struct command_radio_list{
  uint32_t roll;
  uint32_t pitch;
  uint32_t throttle;
  uint32_t yaw;
  struct command_radio_list* next;
} command_radio_list_t;

extern command_radio_list_t* command_radio_list_start;
extern command_radio_list_t* command_radio_list_end;

/**
 * Unparsed commands linked list
 * raw         - pointer to raw (unparsed) command bytes
 * timestamp   - time indicator
 * TODO: determine needed scale
 * next        - pointer to next command in list
 */
typedef struct command_list {
  uint8_t* raw;
  uint8_t timestamp;
  struct command_list* next; 
  uint8_t valid;
} command_list_t;

extern command_list_t* command_list_start;
extern command_list_t* command_list_end;

/**
 * Unparsed commands linked list
 * command         - pointer to command (unparsed) command array
 * timestamp   - time indicator
 * TODO: determine needed scale
 * next        - pointer to next command in list
 */

// TODO: doc
uint8_t command_parse(command_t* command);

// TODO: doc
void command_reset(command_t* command);

// TODO: doc
void command_control(command_t* command);


void command_control_radio(command_t* command);

// TODO: doc
void command_pid_update(command_list_t* command);

// TODO: doc
void command_echo(command_list_t* command);

// TODO: doc
uint8_t command_timeout(void);

#endif
