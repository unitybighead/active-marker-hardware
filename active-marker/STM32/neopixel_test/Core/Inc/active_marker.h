/*
 * active_marker.h
 *
 *  Created on: 2024/06/05
 *      Author: harub
 */

#ifndef INC_ACTIVE_MARKER_H_
#define INC_ACTIVE_MARKER_H_

#include "main.h"
#include "neopixel_spi.h"

#define BLUE 0
#define YELLOW 1
typedef struct {
  RGB dot0;
  RGB dot1;
  RGB dot2;
  RGB dot3;
} DotPattern;

/*color define {R,G,B}
 * 0     1
 *    4
 *  2   3
 */
extern const RGB COLOR_BLUE;
extern const RGB COLOR_YELLOW ;
extern const RGB COLOR_PINK;
extern const RGB COLOR_GREEN;

extern const DotPattern PATTERN_0;
extern const DotPattern PATTERN_1;
extern const DotPattern PATTERN_2;
extern const DotPattern PATTERN_3;
extern const DotPattern PATTERN_4;
extern const DotPattern PATTERN_5;
extern const DotPattern PATTERN_6;
extern const DotPattern PATTERN_7;
extern const DotPattern PATTERN_8;
extern const DotPattern PATTERN_9;
extern const DotPattern PATTERN_10;
extern const DotPattern PATTERN_11;
extern const DotPattern PATTERN_12;
extern const DotPattern PATTERN_13;
extern const DotPattern PATTERN_14;
extern const DotPattern PATTERN_15;
extern const DotPattern* PATTERN_ADDR[];

//uint8_t getID_Rotary(void);
//uint8_t getColor(void);
void setPattern(uint8_t ID,uint8_t color);
#endif /* INC_ACTIVE_MARKER_H_ */
