/*
 * user_func.c
 *
 *  Created on: 2024/05/23
 *      Author: NIIMI Haru
 */

#include "user_func.h"

/*
 * @brief CycleController
 * @param[ms] ms Cycle[ms]
 */
void CycleController(float ms) {
  static bool init = false;
  static uint32_t old_time = 0;
  if (!init) {
    old_time = HAL_GetTick();
    init = true;
  }
  while (HAL_GetTick() - old_time < ms)
    ;
  old_time = HAL_GetTick();
}
