//[----------------------------------------------------------------------------]
//[
//[ Copyright 2022 DaleSoft (email: office@dalesoft.ru)
//[ 
//[ Licensed under the Apache License, Version 2.0 (the "License");
//[ you may not use this file except in compliance with the License.
//[ You may obtain a copy of the License at
//[ 
//[     http://www.apache.org/licenses/LICENSE-2.0
//[ 
//[ Unless required by applicable law or agreed to in writing, software
//[ distributed under the License is distributed on an "AS IS" BASIS,
//[ WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//[ See the License for the specific language governing permissions and
//[ limitations under the License.
//[ 
//[ Project:                    Mescalero
//[ File:                       mscl_defines.h
//[ Author:                     Igor Belyakov (igor@dalesoft.ru)
//[ Description:                Mescalero default defines
//[ History:
//[
//[ 15.10.22 /IB/ Created...
//[
//[----------------------------------------------------------------------------]

#ifndef MSCL_DEFINES_H
#define MSCL_DEFINES_H

#include <limits.h>

//[----------------------------------------------------------------------------]
//[ Common part
//[----------------------------------------------------------------------------]

// Platform dependent shortenings

using msclULongLong = unsigned long long;
using msclSLongLong = long long;
using msclUInt      = unsigned int;
using msclUShort    = unsigned short;
using msclUChar     = unsigned char;
using msclSChar     = signed char;

// 32-bit base types, "Number" suffix means platform independent size
#if (UINT_MAX == 4294967295U)
 using msclInt32Number  = int;
 using msclUInt32Number = unsigned int;
#elif (ULONG_MAX == 4294967295U)
 using msclInt32Number  = long;
 using msclUInt32Number = unsigned long;
#else
#error "Unable to find 32 bit types, unsupported compiler"
#endif

// 64-bit base types, "Number" suffix means platform independent size
#if defined(_WIN32) || defined(WIN32)
  using msclInt64Number = __int64;
  using msclUInt64Number = unsigned __int64;
#else
  using msclInt64Number  = msclSLongLong;
  using msclUInt64Number = msclULongLong;
#endif

//[----------------------------------------------------------------------------]
//[ ICC part
//[----------------------------------------------------------------------------]

using miccBool = int;

using miccHPROFILE = void*;
using miccHTRANSFORM = void*;
using miccHANDLE = void*;

typedef enum {
 miccSigXYZData      = 0x58595A20,  // 'XYZ '
 miccSigLabData      = 0x4C616220,  // 'Lab '
 miccSigLuvData      = 0x4C757620,  // 'Luv '
 miccSigYCbCrData    = 0x59436272,  // 'YCbr'
 miccSigYxyData      = 0x59787920,  // 'Yxy '
 miccSigRgbData      = 0x52474220,  // 'RGB '
 miccSigGrayData     = 0x47524159,  // 'GRAY'
 miccSigHsvData      = 0x48535620,  // 'HSV '
 miccSigHlsData      = 0x484C5320,  // 'HLS '
 miccSigCmykData     = 0x434D594B,  // 'CMYK'
 miccSigCmyData      = 0x434D5920,  // 'CMY '
 miccSigMCH1Data     = 0x4D434831,  // 'MCH1'
 miccSigMCH2Data     = 0x4D434832,  // 'MCH2'
 miccSigMCH3Data     = 0x4D434833,  // 'MCH3'
 miccSigMCH4Data     = 0x4D434834,  // 'MCH4'
 miccSigMCH5Data     = 0x4D434835,  // 'MCH5'
 miccSigMCH6Data     = 0x4D434836,  // 'MCH6'
 miccSigMCH7Data     = 0x4D434837,  // 'MCH7'
 miccSigMCH8Data     = 0x4D434838,  // 'MCH8'
 miccSigMCH9Data     = 0x4D434839,  // 'MCH9'
 miccSigMCHAData     = 0x4D434841,  // 'MCHA'
 miccSigMCHBData     = 0x4D434842,  // 'MCHB'
 miccSigMCHCData     = 0x4D434843,  // 'MCHC'
 miccSigMCHDData     = 0x4D434844,  // 'MCHD'
 miccSigMCHEData     = 0x4D434845,  // 'MCHE'
 miccSigMCHFData     = 0x4D434846,  // 'MCHF'
 miccSigNamedData    = 0x6e6d636c,  // 'nmcl'
 miccSig1colorData   = 0x31434C52,  // '1CLR'
 miccSig2colorData   = 0x32434C52,  // '2CLR'
 miccSig3colorData   = 0x33434C52,  // '3CLR'
 miccSig4colorData   = 0x34434C52,  // '4CLR'
 miccSig5colorData   = 0x35434C52,  // '5CLR'
 miccSig6colorData   = 0x36434C52,  // '6CLR'
 miccSig7colorData   = 0x37434C52,  // '7CLR'
 miccSig8colorData   = 0x38434C52,  // '8CLR'
 miccSig9colorData   = 0x39434C52,  // '9CLR'
 miccSig10colorData  = 0x41434C52,  // 'ACLR'
 miccSig11colorData  = 0x42434C52,  // 'BCLR'
 miccSig12colorData  = 0x43434C52,  // 'CCLR'
 miccSig13colorData  = 0x44434C52,  // 'DCLR'
 miccSig14colorData  = 0x45434C52,  // 'ECLR'
 miccSig15colorData  = 0x46434C52,  // 'FCLR'
 miccSigLuvKData     = 0x4C75764B   // 'LuvK'

} miccColorSpaceSignature;

typedef enum
{
 miccInfoDescription  = 0,
 miccInfoManufacturer = 1,
 miccInfoModel        = 2,
 miccInfoCopyright    = 3

} miccInfoType;

//[----------------------------------------------------------------------------]
//[ RAW part
//[----------------------------------------------------------------------------]

#define mrawDataStreamMaxSize (250 * 1024L * 1024L)

typedef enum
{
 mrawProgressStart   = 0,
 mrawProgressLoadRow = 1 << 3

} mrawProgress;

typedef enum
{
 mrawSuccess                  = 0,
 mrawErrorFileUnsupported     = -2,
 mrawErrorUnsufficientMemory  = -100007,
 mrawErrorIO                  = -100009,
 mrawErrorCancelledByCallback = -100010

} mrawErrors;

typedef enum
{
  mrawImageFormatJPG = 1,
  mrawImageFormatBMP = 2

} mrawImageFormats;

typedef enum
{
  mrawThumbnailFormatUnknown = 0,
  mrawThumbnailFormatJpeg    = 1,
  mrawThumbnailFormatBitmap  = 2,
  mrawThumbnailFormatBmp16   = 3,
  mrawThumbnailFormatLayer   = 4,
  mrawThumbnailFormatRollei  = 5

} mrawThumbnailFormats;

//[----------------------------------------------------------------------------]

typedef struct
{
  msclUShort  raw_height;
  msclUShort  raw_width;
  msclUShort  height;
  msclUShort  width;
  msclUShort  iheight;
  msclUShort  iwidth;
  int         flip;

} mrawImageSizes;

typedef struct
{
  char make[64];
  char model[64];

} mrawIParams;

typedef struct
{
  msclUInt greybox[4];
  double   aber[4];
  double   gamm[6];
  float    user_mul[4];
  float    bright;
  float    threshold;
  int      half_size;
  int      use_auto_wb;
  int      use_camera_wb;
  int      output_color;

} mrawOParams;

typedef struct
{
  mrawImageFormats  type;
  msclUShort        height;
  msclUShort        width;
  msclUShort        colors;
  msclUShort        bits;
  msclUInt          data_size;
  msclUChar*        data;
  void*             mem_ptr; // memory to clear after using

} mrawProcessedImage;

typedef struct
{
  msclUInt  black;
  float     cam_mul[4];
  float     pre_mul[4];
  int       WB_Coeffs[256][4];
  float     WBCT_Coeffs[64][5];

} mrawColorData;

typedef struct
{
  float  iso_speed;
  float  shutter;
  float  aperture;
  float  focal_len;

} mrawImageOther;

typedef struct
{
  mrawThumbnailFormats  tformat;
  msclUShort            twidth;
  msclUShort            theight;
  msclUInt              tlength;
  int                   tcolors;
  char*                 thumb;

} mrawThumbnail;

typedef struct
{
 msclUInt           progress_flags;
 mrawImageSizes     sizes;
 mrawIParams        idata;
 mrawColorData      color;
 mrawImageOther     other;
 mrawThumbnail      thumbnail;

} mrawImageData;

//[----------------------------------------------------------------------------]

#endif // MSCL_DEFINES_H
