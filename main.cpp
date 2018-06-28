/*
 *  mbed-os-example-blinky - LED blinking example with heap statistics
 *
 *  Copyright (C) 2006-2016, Arm Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */
#include <inttypes.h>
#include "mbed.h"
#include "mbed_stats.h"

DigitalOut led1(LED1);

/**
 * Print current heap statistics
 * NOTE! If -DMBED_HEAP_STATS_ENABLED was not given as compilation parameter, this function is void.
 * IN: event - char ptr to a describing event.
 */
void heap_stats(char *event)
{
#ifdef MBED_HEAP_STATS_ENABLED
    printf("**** heap_stats at %s\n", event);
    mbed_stats_heap_t stats;
    mbed_stats_heap_get(&stats);
    printf("**** current_size: %" PRIu32 "\n", stats.current_size);
    printf("**** max_size    : %" PRIu32 "\n", stats.max_size);
#endif // MBED_HEAP_STATS_ENABLED
}


// main() runs in its own thread in the OS
int main() {

    printf("\nStarting mbed-os-example-blinky\n");
#if defined(MBED_MAJOR_VERSION)
    printf("Using Mbed OS %d.%d.%d\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
#else
    printf("Using Mbed OS from master.\n");
#endif

    heap_stats("Heap at start: \n");
    while (true) {
        int print_once = 0;
        led1 = !led1;
        wait(0.5);
        if (print_once == 0) {
            print_once++;
            heap_stats("Heap in while: \n");
        }
    }
}

