/*
 * Copyright (c) 2017 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 * Not a Contribution.
 * Apache license notifications and license are retained
 * for attribution purposes only.
 *
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define ESE_MAGIC 0xEA
#define ESE_SET_PWR                         _IOW(ESE_MAGIC, 0x01, unsigned int)
#define ESE_SET_DBG                         _IOW(ESE_MAGIC, 0x02, unsigned int)
#define ESE_SET_MODE                        _IOW(ESE_MAGIC, 0x03, unsigned int)
#define NFC_ESE_SET_PWR                     _IOW(0xE9, 0x02, unsigned int)
#define NFC_ESE_GET_PWR                     _IOR(0xE9, 0x03, unsigned int)
#define NFC_NTF_TIMEOUT                     20

/* Supported Protocols */
#define NFC_PROTOCOL_UNKNOWN    0x00 /* Unknown */
#define NFC_PROTOCOL_T1T        0x01 /* Type1Tag    - NFC-A            */
#define NFC_PROTOCOL_T2T        0x02 /* Type2Tag    - NFC-A            */
#define NFC_PROTOCOL_T3T        0x03 /* Type3Tag    - NFC-F            */
#define NFC_PROTOCOL_ISO_DEP    0x04 /* Type 4A,4B  - NFC-A or NFC-B   */
#define NFC_PROTOCOL_NFC_DEP    0x05 /* NFCDEP/LLCP - NFC-A or NFC-F       */

#define MAX_CMD_LEN             255
#define READ_SAMPLE_SIZE        258
extern int                      fdNfc;           // a handle to the kernel driver
extern uint8_t                  nciReplyMessage[ 255 ];
extern NQ_CHIP_TYPE             whatNQChip;
extern sem_t                    sRspReady;
extern int ftm_nfc_nq_vs_nxp( void );
int ese_dwp_test = 0;
int ese_spi_test = 0;
void sendcmds(uint8_t buffer[][255], int no_of_cmds);
void printTecnologyDetails(char technology, char protocol);
sem_t               sRfNtf;

struct ese_spi_platform_data
{
    unsigned int use_pwr_req;
    unsigned int pwr_req;
    unsigned int ese_intr;
};

/*
 * Enum definition contains RF technology modes supported.
 * This information is a part of RF_DISCOVER_NTF or RF_INTF_ACTIVATED_NTF.
 */
typedef enum
{
    NFC_NFCA_Poll                 = 0x00, /* Nfc A Technology in Poll Mode */
    NFC_NFCB_Poll                 = 0x01, /* Nfc B Technology in Poll Mode */
    NFC_NFCF_Poll                 = 0x02, /* Nfc F Technology in Poll Mode */
    NFC_NFCA_Active_Poll          = 0x03, /* Nfc A Technology in Active Poll Mode */
    NFC_NFCF_Active_Poll          = 0x05, /* Nfc F Technology in Active Poll Mode */
    NFC_NFCISO15693_Poll          = 0x06, /* Nfc ISO15693 Technology in Poll Mode */
    NFC_NxpProp_NFCHID_Poll       = 0x70, /* Nfc Hid Technology in Poll Mode */
    NFC_NxpProp_NFCEPFGEN2_Poll   = 0x71, /* Nfc EpcGen2 Technology in Poll Mode */
    NFC_NxpProp_NFCKOVIO_Poll     = 0x72, /* Nfc Kovio Technology in Poll Mode */
    NFC_NFCA_Listen               = 0x80, /* Nfc A Technology in Listen Mode */
    NFC_NFCB_Listen               = 0x81, /* Nfc B Technology in Listen Mode */
    NFC_NFCF_Listen               = 0x82, /* Nfc F Technology in Listen Mode */
    NFC_NFCA_Active_Listen        = 0x83, /* Nfc A Technology in Active Listen Mode */
    NFC_NFCF_Active_Listen        = 0x85, /* Nfc F Technology in Active Listen Mode */
    NFC_NFCISO15693_Active_Listen = 0x86  /* Nfc ISO15693 Technology in Listen Mode */
} NFC_RfTechMode_t;

uint8_t NQ330_cmds[][255] =
{
{ 0x20,0x00,0x01,0x00 },
{ 0x20,0x01,0x00},
{ 0x2F,0x02,0x00 },
{ 0x20,0x03,0x03,0x01,0xA0,0x0F },
{ 0x20,0x03,0x03,0x01,0xA0,0xFC },
{ 0x20,0x03,0x03,0x01,0xA0,0xF2 },
{ 0x20,0x03,0x03,0x01,0xA0,0xD7 },
{ 0x20,0x03,0x07,0x03,0xA0,0x02,0xA0,0x03,0xA0,0x04 },
{ 0x20,0x02,0x09,0x02,0xA0,0x03,0x01,0x01,0xA0,0x04,0x01,0x06 },
{ 0x20,0x02,0x0F,0x01,0xA0,0x0E,0x0B,0x11,0x01,0xC2,0xB2,0x00,0xB2,0x1E,0x1F,0x00,0xD0,0x0C },
{ 0x20,0x02,0x05,0x01,0xA0,0xF2,0x01,0x01 },
{ 0x20,0x03,0x03,0x01,0xA0,0xEC },
{ 0x20,0x03,0x03,0x01,0xA0,0xD4 },
{ 0x20,0x03,0x03,0x01,0xA0,0x14 },
{ 0x20,0x02,0x2E,0x0E,0x28,0x01,0x00,0x21,0x01,0x00,0x30,0x01,0x08,0x31,0x01,0x03,0x32,0x01,0x60,0x38,0x01,0x01,0x33,0x04,0x01,0x02,0x03,0x04,0x54,0x01,0x06,0x50,0x01,0x02,0x5B,0x01,0x00,0x80,0x01,0x01,0x81,0x01,0x01,0x82,0x01,0x0E,0x18,0x01,0x01 },
{ 0x20,0x02,0x05,0x01,0xA0,0x62,0x01,0x01 },
{ 0x20,0x02,0x06,0x01,0xA0,0xF3,0x02,0x10,0x27 },
{ 0x20,0x03,0x03,0x01,0xA0,0x85 },
{ 0x21,0x01,0x07,0x00,0x01,0x01,0x03,0x00,0x01,0x05 },
{ 0x20,0x02,0x05,0x01,0xA0,0xF1,0x01,0x00 },
{ 0x20,0x03,0x03,0x01,0xA0,0x0F },
{ 0x20,0x03,0x03,0x01,0xA0,0xEB },
{ 0x20,0x00,0x01,0x00 },
{ 0x20,0x01,0x00},
{ 0x20,0x03,0x02,0x01,0x00 },
{ 0x20,0x03,0x02,0x01,0x29 },
{ 0x20,0x03,0x02,0x01,0x61 },
{ 0x20,0x03,0x02,0x01,0x60 },
{ 0x20,0x02,0x0F,0x01,0xA0,0x0E,0x0B,0x11,0x01,0xC2,0xB2,0x00,0xB2,0x1E,0x1F,0x00,0xD0,0x0C },
{ 0x21,0x00,0x0D,0x04,0x04,0x03,0x02,0x05,0x03,0x03,0x03,0x02,0x01,0x80,0x01,0x80 },
{ 0x20,0x03,0x07,0x03,0xA0,0xEC,0xA0,0xED,0xA0,0xD4 },
{ 0x20,0x03,0x03,0x01,0xA0,0xEB },
{ 0x20,0x03,0x03,0x01,0xA0,0xF0 },
{ 0x22,0x01,0x02,0xC0,0x01 },
{ 0x22,0x03,0x02,0xC0,0x00 },
{ 0x20,0x03,0x03,0x01,0xA0,0x14 },
{ 0x20,0x03,0x03,0x01,0xA0,0xEB },
{ 0x20,0x03,0x03,0x01,0xA0,0x07 },
{ 0x20,0x03,0x02,0x01,0x52 },
{ 0x2F,0x15,0x01,0x02 },
{ 0x21,0x03,0x07,0x03,0x80,0x01,0x81,0x01,0x82,0x01 },
{ 0x21,0x06,0x01,0x00 },
{ 0x2F,0x15,0x01,0x00 },
{ 0x20,0x02,0x07,0x02,0x32,0x01,0x60,0x38,0x01,0x01 },
{ 0x21,0x01,0x1B,0x00,0x05,0x01,0x03,0x00,0x01,0x03,0x01,0x03,0x00,0x41,0x04,0x01,0x03,0x00,0x41,0xA0,0x01,0x03,0x00,0x01,0x05,0x00,0x03,0xC0,0xC3,0x02 },
{ 0x20,0x02,0x07,0x02,0x32,0x01,0x60,0x38,0x01,0x01},
{ 0x21,0x03,0x19,0x0C,0x00,0x01,0x01,0x01,0x02,0x01,0x03,0x01,0x05,0x01,0x80,0x01,0x81,0x01,0x82,0x01,0x83,0x01,0x85,0x01,0x06,0x01,0x70,0x01}
};

uint8_t NQ330_ESE_DWP[][255] =
{
{ 0x20,0x00,0x01,0x00 },
{ 0x20,0x01,0x00},
{ 0x20,0x02,0x05,0x01,0xA0,0xF2,0x01,0x01 },
{ 0x22,0x00,0x01,0x01 },
{ 0x22,0x01,0x2,0x01,0x01 },
{ 0x20,0x04,0x06,0x03,0x01,0x01,0x02,0x01,0x01 },
{ 0x03,0x00,0x03,0x81,0x02,0x01 },
{ 0x03,0x00,0x03,0x81,0x02,0x04 },
{ 0x03,0x00,0x03,0x81,0x02,0x07 },
{ 0x21,0x01,0x1B,0x00,0x05,0x01,0x03,0x00,0x01,0x03,0x01,0x03,0x00,0x41,0x04,0x01,0x03,0x00,0x41,0xA0,0x01,0x03,0x00,0x01,0x05,0x00,0x03,0xC0,0xC3,0x02 },
{ 0x21,0x03,0x19,0x0C,0x00,0x01,0x01,0x01,0x02,0x01,0x03,0x01,0x05,0x01,0x80,0x01,0x81,0x01,0x82,0x01,0x83,0x01,0x85,0x01,0x06,0x01,0x70,0x01},
{ 0x03,0x00,0x07,0x99,0x50,0x00,0x70,0x00,0x00,0x01},
{ 0x03,0x00,0x09,0x99,0x50,0x80,0xCA,0x00,0xFE,0x02,0xDF,0x21  }
};

uint8_t NQ220_cmds[][255] =
{
 { 0x20,0x00,0x01,0x00 },
 { 0x20,0x01,0x00 },
 { 0x2F,0x02,0x00 },
 { 0x20,0x03,0x03,0x01,0xA0,0x0F },
 { 0x20,0x03,0x07,0x03,0xA0,0x02,0xA0,0x03,0xA0,0x04 },
 { 0x20,0x02,0x05,0x01,0xA0,0x44,0x01,0x00 },
 { 0x20,0x02,0x0B,0x02,0xA0,0x66,0x01,0x00,0xA0,0x0E,0x03,0x02,0x09,0x00 },
 { 0x20,0x02,0x26,0x09,0xA0,0xEC,0x01,0x01,0xA0,0xED,0x01,0x03,0xA0,0x5E,0x01,0x01,0xA0,0x12,0x01,0x02,0xA0,0x40,0x01,0x01,0xA0,0xDD,0x01,0x2D,0xA0,0xF2,0x01,0x01,0xA0,0x96,0x01,0x01,0xA0,0x9F,0x02,0x08,0x08 },
 { 0x20,0x03,0x03,0x01,0xA0,0xEC },
 { 0x20,0x03,0x03,0x01,0xA0,0x14 },
 { 0x20,0x02,0x2E,0x0E,0x28,0x01,0x00,0x21,0x01,0x00,0x30,0x01,0x08,0x31,0x01,0x03,0x32,0x01,0x60,0x38,0x01,0x01,0x33,0x04,0x01,0x02,0x03,0x04,0x54,0x01,0x06,0x50,0x01,0x02,0x5B,0x01,0x00,0x80,0x01,0x01,0x81,0x01,0x01,0x82,0x01,0x0E,0x18,0x01,0x01 },
 { 0x20,0x02,0x05,0x01,0xA0,0x62,0x01,0x01 },
 { 0x20,0x02,0x06,0x01,0xA0,0xF3,0x02,0x10,0x27 },
 { 0x20,0x03,0x03,0x01,0xA0,0x85 },
 { 0x21,0x01,0x07,0x00,0x01,0x01,0x03,0x00,0x01,0x05 },
 { 0x20,0x02,0x05,0x01,0xA0,0xF1,0x01,0x00 },
 { 0x20,0x02,0x05,0x01,0xA0,0x91,0x01,0x01 },
 { 0x20,0x03,0x03,0x01,0xA0,0x0F },
 { 0x20,0x03,0x03,0x01,0xA0,0xEB },
 { 0x20,0x00,0x01,0x00 },
 { 0x20,0x01,0x00 },
 { 0x20,0x03,0x02,0x01,0x00 },
 { 0x20,0x03,0x02,0x01,0x29 },
 { 0x20,0x03,0x02,0x01,0x61 },
 { 0x20,0x03,0x02,0x01,0x60 },
 { 0x21,0x00,0x0D,0x04,0x04,0x03,0x02,0x05,0x03,0x03,0x03,0x02,0x01,0x80,0x01,0x80 },
 { 0x22,0x00,0x01,0x01 },
 { 0x20,0x04,0x06,0x03,0x01,0x01,0x02,0x01,0x01 },
 { 0x03,0x00,0x05,0x81,0x01,0x03,0x02,0xC0 },
 { 0x03,0x00,0x05,0x81,0x01,0x06,0x01,0x00 },
 { 0x03,0x00,0x03,0x81,0x02,0x01 },
 { 0x03,0x00,0x03,0x81,0x02,0x04 },
 { 0x20,0x03,0x05,0x02,0xA0,0xEC,0xA0,0xED },
 { 0x20,0x03,0x03,0x01,0xA0,0xEB },
 { 0x20,0x03,0x03,0x01,0xA0,0xF0 },
 { 0x20,0x03,0x05,0x02,0xA0,0xEC,0xA0,0xED },
 { 0x20,0x03,0x03,0x01,0xA0,0x14 },
 { 0x20,0x03,0x03,0x01,0xA0,0xEB },
 { 0x20,0x03,0x03,0x01,0xA0,0x07 },
 { 0x20,0x02,0x05,0x01,0xA0,0x07,0x01,0x03 },
 { 0x20,0x03,0x02,0x01,0x52 },
 { 0x21,0x01,0x16,0x00,0x04,0x01,0x03,0x00,0x01,0x03,0x01,0x03,0x00,0x41,0x04,0x01,0x03,0x00,0x41,0xA0,0x01,0x03,0x00,0x01,0x05 },
 { 0x20,0x02,0x0A,0x03,0x32,0x01,0x20,0x38,0x01,0x01,0x50,0x01,0x00 },
 { 0x21,0x03,0x07,0x03,0x80,0x01,0x81,0x01,0x82,0x01 },
 { 0x21,0x06,0x01,0x00 },
 { 0x20,0x02,0x17,0x01,0x61,0x14,0x46,0x66,0x6D,0x01,0x01,0x12,0x02,0x02,0x07,0xFF,0x03,0x02,0x00,0x13,0x04,0x01,0x64,0x07,0x01,0x03 },
 { 0x20,0x02,0x0A,0x03,0x32,0x01,0x60,0x38,0x01,0x01,0x50,0x01,0x02 },
 { 0x21,0x03,0x19,0x0C,0x00,0x01,0x01,0x01,0x02,0x01,0x03,0x01,0x05,0x01,0x80,0x01,0x81,0x01,0x82,0x01,0x83,0x01,0x85,0x01,0x06,0x01,0x70,0x01 }
};
