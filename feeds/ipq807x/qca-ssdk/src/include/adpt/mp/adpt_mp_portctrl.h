/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _ADPT_PORTCTRL_H_
#define _ADPT_PORTCTRL_H_


#define GMAC_SPEED_10M                   0x0
#define GMAC_SPEED_100M                  0x1
#define GMAC_SPEED_1000M                 0x0
#define GMAC_FULL_DUPLEX                 0x1
#define GMAC_HALF_DUPLEX                 0x0
#define GMAC_PAUSE_TIME                  0xffff
#define GMAC_PAUSE_ZERO_QUANTA_ENABLE    0x0
#define GMAC_JD_ENABLE                   0x1
#define GMAC_WD_DISABLE                  0x0
#define GMAC_FRAME_BURST_ENABLE          0x1
#define GMAC_JUMBO_FRAME_ENABLE          0x1
#define GMAC_MAX_FRAME_CTRL_ENABLE       0x1
#define GMAC_LPI_LINK_UP                 0x1
#define GMAC_LPI_AUTO_MODE               0x1
#define GMAC_TX_STORE_FORWAD_ENABLE      0x1
#define GMAC_RX_STORE_FORWAD_ENABLE      0x1
#define GMAC_FORWARD_ERROR_FRAME_DISABLE 0x0
#define GMAC_DROP_GAINT_FRAME_DISABLE    0x0
#define GMAC_HW_FLOWCTRL_ENABLE          0x1
#define GMAC_HW_FLOWCTRL_DISABLE         0x0
#define PORT_LPI_ENABLE_STATUS           0x3
#define PORT_LPI_TASK_RUNNING            0x10000
#define PORT_LPI_TASK_START              0x20000

#endif
