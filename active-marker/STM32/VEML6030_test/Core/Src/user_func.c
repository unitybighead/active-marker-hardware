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
bool CycleController(int data, float *basis, uint32_t *old) {
  if (old[data] == 0) {
    old[data] = HAL_GetTick();
  }
  uint32_t current = HAL_GetTick();
  if (current - old[data] > 0) {
    old[data] = current;
    return 1;
  } else {
    return 0;
  }
}
