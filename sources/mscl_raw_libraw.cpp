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
//[ File:                       mscl_raw_libraw.cpp
//[ Author:                     Igor Belyakov (igor@dalesoft.ru)
//[ Description:                Mescalero implementation (LibRaw+RawSpeed as RAW)
//[ History:
//[
//[ 06.11.22 /IB/ Created...
//[
//[----------------------------------------------------------------------------]


#include "interface/mscl_defines.h"
#include "interface/mscl.h"

#include "libraries/libraw/libraw.h"

//[----------------------------------------------------------------------------]
//[ RAW methods
//[----------------------------------------------------------------------------]

//[----------------------------------------------------------------------------]
//[
//[  Method:     mrawClass::mrawGetFormats
//[
//[  Purpose:    Returns Mescalero supported RAW formats
//[  Parameters: None
//[  Returns:    const char** := Constant pointer to array of strings. Last element is always "".
//[
//[----------------------------------------------------------------------------]

static const char* mrawFormats[] = {
 "3fr", "ari", "arw", "bay", "crw", "cr2", "cap", "dcs", "dcr", "dng", // 10
 "drf", "eip", "erf", "fff", "iiq", "k25", "kdc", "mdc", "mef", "mos", // 20
 "mrw", "nef", "nrw", "obm", "orf", "pef", "ptx", "pxn", "r3d", "raf", // 30
 "raw", "rwl", "rw2", "rwz", "sr2", "srf", "srw", "x3f", ""            // 38
};

const char** mrawClass::getFormats()
{
 return mrawFormats;
}

//[----------------------------------------------------------------------------]
//[
//[  Method:     mrawClass::mrawClass
//[
//[  Purpose:    Constructor
//[  Parameters: None
//[  Returns:    Nothing
//[
//[----------------------------------------------------------------------------]

mrawClass::mrawClass()
{
 // Checking arrays formats

 // resetImageData, setupImageData

 static_assert(sizeof(mrawOParams::greybox) == sizeof(libraw_output_params_t::greybox));
 static_assert(sizeof(mrawOParams::aber) == sizeof(libraw_output_params_t::aber));
 static_assert(sizeof(mrawOParams::gamm) == sizeof(libraw_output_params_t::gamm));
 static_assert(sizeof(mrawOParams::user_mul) == sizeof(libraw_output_params_t::user_mul));

 // getProcessorData

 static_assert(sizeof(mrawImageData::idata.make) == sizeof(libraw_data_t::idata.make));
 static_assert(sizeof(mrawImageData::idata.model) == sizeof(libraw_data_t::idata.model));

 static_assert(sizeof(mrawImageData::color.cam_mul) == sizeof(libraw_data_t::color.cam_mul));
 static_assert(sizeof(mrawImageData::color.pre_mul) == sizeof(libraw_data_t::color.pre_mul));
 static_assert(sizeof(mrawImageData::color.WB_Coeffs) == sizeof(libraw_data_t::color.WB_Coeffs));
 static_assert(sizeof(mrawImageData::color.WBCT_Coeffs) == sizeof(libraw_data_t::color.WBCT_Coeffs));

 // Create processor

 m_processor = new LibRaw;
 getProcessorData();
}

//[----------------------------------------------------------------------------]
//[
//[  Method:     mrawClass::~mrawClass
//[
//[  Purpose:    Destructor
//[  Parameters: None
//[  Returns:    Nothing
//[
//[----------------------------------------------------------------------------]

mrawClass::~mrawClass()
{
 delete (LibRaw*) m_processor;
}

//[----------------------------------------------------------------------------]
//[
//[  Method:     mrawClass::resetImageData
//[
//[  Purpose:    Resets configuration data for decoder to default
//[  Parameters: mrawOParams& params := data to reset
//[  Returns:    Nothing
//[
//[----------------------------------------------------------------------------]

void mrawClass::resetImageData(mrawOParams& params)
{
 libraw_output_params_t& rparams = ((LibRaw*) m_processor)->imgdata.params;

 memcpy(params.greybox, rparams.greybox, sizeof(params.greybox));
 memcpy(params.aber, rparams.aber, sizeof(params.aber));
 memcpy(params.gamm, rparams.gamm, sizeof(params.gamm));
 memcpy(params.user_mul, rparams.user_mul, sizeof(params.user_mul));

 params.bright        = rparams.bright;
 params.threshold     = rparams.threshold;
 params.half_size     = rparams.half_size;
 params.use_auto_wb   = rparams.use_auto_wb;
 params.use_camera_wb = rparams.use_camera_wb;
 params.output_color  = rparams.output_color;
}

//[----------------------------------------------------------------------------]
//[
//[  Method:     mrawClass::setupImageData
//[
//[  Purpose:    Sets configuration data for decoder
//[  Parameters: mrawOParams& params := data to set
//[  Returns:    Nothing
//[
//[----------------------------------------------------------------------------]

void mrawClass::setupImageData(mrawOParams& params)
{
 libraw_output_params_t& lparams = ((LibRaw*) m_processor)->imgdata.params;

 memcpy(lparams.greybox, params.greybox, sizeof(lparams.greybox));
 memcpy(lparams.aber, params.aber, sizeof(lparams.aber));
 memcpy(lparams.gamm, params.gamm, sizeof(lparams.gamm));
 memcpy(lparams.user_mul, params.user_mul, sizeof(lparams.user_mul));

 lparams.bright        = params.bright;
 lparams.threshold     = params.threshold;
 lparams.half_size     = params.half_size;
 lparams.use_auto_wb   = params.use_auto_wb;
 lparams.use_camera_wb = params.use_camera_wb;
 lparams.output_color  = params.output_color;
}

//[----------------------------------------------------------------------------]
//[
//[  Method:     mrawClass::getProcessorData
//[
//[  Purpose:    Retrieves image data from processor to m_Data
//[  Parameters: None
//[  Returns:    Nothing
//[
//[----------------------------------------------------------------------------]

void mrawClass::getProcessorData()
{
  libraw_data_t& rdata = ((LibRaw*) m_processor)->imgdata;

  // Set flags

  m_data.progress_flags = rdata.progress_flags;

  // Set sizes

  m_data.sizes.raw_height = rdata.sizes.raw_height;
  m_data.sizes.raw_width  = rdata.sizes.raw_width;
  m_data.sizes.height     = rdata.sizes.height;
  m_data.sizes.width      = rdata.sizes.width;
  m_data.sizes.iheight    = rdata.sizes.iheight;
  m_data.sizes.iwidth     = rdata.sizes.iwidth;
  m_data.sizes.flip       = rdata.sizes.flip;

  // Set image parameters

  memcpy(m_data.idata.make, rdata.idata.make, sizeof(m_data.idata.make));
  memcpy(m_data.idata.model, rdata.idata.model, sizeof(m_data.idata.model));

  // Set color parameters

  m_data.color.black = rdata.color.black;

  memcpy(m_data.color.cam_mul, rdata.color.cam_mul, sizeof(m_data.color.cam_mul));
  memcpy(m_data.color.pre_mul, rdata.color.pre_mul, sizeof(m_data.color.pre_mul));
  memcpy(m_data.color.WB_Coeffs, rdata.color.WB_Coeffs, sizeof(m_data.color.WB_Coeffs));
  memcpy(m_data.color.WBCT_Coeffs, rdata.color.WBCT_Coeffs, sizeof(m_data.color.WBCT_Coeffs));

  // Set other parameters

  m_data.other.iso_speed = rdata.other.iso_speed;
  m_data.other.shutter   = rdata.other.shutter;
  m_data.other.aperture  = rdata.other.aperture;
  m_data.other.focal_len = rdata.other.focal_len;

  // Set thumbnail parameters

  m_data.thumbnail.tformat  = (mrawThumbnailFormats) rdata.thumbnail.tformat;
  m_data.thumbnail.twidth   = rdata.thumbnail.twidth;
  m_data.thumbnail.theight  = rdata.thumbnail.theight;
  m_data.thumbnail.tlength  = rdata.thumbnail.tlength;
  m_data.thumbnail.tcolors  = rdata.thumbnail.tcolors;
  m_data.thumbnail.thumb    = rdata.thumbnail.thumb;
}

//[----------------------------------------------------------------------------]

#if defined(Q_OS_WIN) || defined(_WIN32) || defined(WIN32)
mrawErrors  mrawClass::open_file(const wchar_t *fname, msclInt64Number max_buff_size)
#else
mrawErrors  mrawClass::open_file(const char *fname, msclInt64Number max_buff_size)
#endif
{
 mrawErrors result = (mrawErrors)((LibRaw*) m_processor)->open_file(fname, max_buff_size);
 getProcessorData();
 return result;
}

//[----------------------------------------------------------------------------]

mrawErrors mrawClass::dcrawProcess()
{
 mrawErrors result = (mrawErrors)((LibRaw*) m_processor)->dcraw_process();
 getProcessorData();
 return result;
}

//[----------------------------------------------------------------------------]
//[
//[  Method:     mrawClass::dcrawMakeMemImage
//[
//[  Purpose:    Makes memory image
//[  Parameters: mrawProcessedImage& processedImage := Image info if success, false otherwise
//[  Returns:    mrawErrors := errorCode
//[
//[----------------------------------------------------------------------------]

mrawErrors mrawClass::dcrawMakeMemImage(mrawProcessedImage& processedImage)
{
 int result = mrawErrorUnsufficientMemory; // the only reason that dcraw_make_mem_image fails

 processedImage.mem_ptr = nullptr;

 libraw_processed_image_t* piData = ((LibRaw*) m_processor)->dcraw_make_mem_image(&result);
 if(piData)
   {
    processedImage.type      = (mrawImageFormats) piData->type;
    processedImage.height    = piData->height;
    processedImage.width     = piData->width;
    processedImage.colors    = piData->colors;
    processedImage.bits      = piData->bits;
    processedImage.data_size = piData->data_size;
    processedImage.data      = piData->data;
    processedImage.mem_ptr   = piData; // holds the pointer for the future freeing

    getProcessorData();

    result = mrawSuccess;
   }

 return (mrawErrors) result;
}

//[----------------------------------------------------------------------------]

void mrawClass::dcrawClearMem(mrawProcessedImage& processedImage)
{
 LibRaw::dcraw_clear_mem((libraw_processed_image_t*) processedImage.mem_ptr);
 processedImage.mem_ptr = nullptr;
}

//[----------------------------------------------------------------------------]

mrawErrors mrawClass::unpack()
{
 mrawErrors result = (mrawErrors)((LibRaw*) m_processor)->unpack();
 getProcessorData();
 return result;
}

//[----------------------------------------------------------------------------]

mrawErrors mrawClass::unpackThumb()
{
 mrawErrors result = (mrawErrors)((LibRaw*) m_processor)->unpack_thumb();
 getProcessorData();
 return result;
}

//[----------------------------------------------------------------------------]

void mrawClass::recycle()
{
 ((LibRaw*) m_processor)->recycle();
 getProcessorData();
}

//[----------------------------------------------------------------------------]

void mrawClass::setProgressHandler(mrawProgressCallback pcb, void* data)
{
 ((LibRaw*) m_processor)->set_progress_handler((progress_callback)pcb, data);
}

//[----------------------------------------------------------------------------]
