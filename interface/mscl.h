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
//[ File:                       mscl.h
//[ Author:                     Igor Belyakov (igor@dalesoft.ru)
//[ Description:                Mescalero definitions
//[ History:
//[
//[ 13.10.22 /IB/ Created...
//[
//[----------------------------------------------------------------------------]

#ifndef MESCALERO_H
#define MESCALERO_H

#include <QtCore/qglobal.h>

#ifdef __BORLANDC__
#error "Unsupported compiler (Borland)"
#endif

#if defined(Q_OS_WIN)
#  if defined(MESCALERO_LIBRARY)
#    define MSCLAPI Q_DECL_EXPORT
#  else
#    define MSCLAPI Q_DECL_IMPORT
#  endif
#elif defined(Q_OS_LINUX) || defined(Q_OS_MAC)
#  if defined(MESCALERO_LIBRARY)
#    define MSCLAPI Q_DECL_EXPORT
#  else
#    define MSCLAPI
#  endif
#endif

// Version 0.4.0
#define MESCALERO_VER_STR "0.4.0"
#define MESCALERO_VER_MAJOR 0
#define MESCALERO_VER_MINOR 4
#define MESCALERO_VER_PATCH 0

//[----------------------------------------------------------------------------]
//[ Common part
//[----------------------------------------------------------------------------]

typedef enum {

 msclPartTypeAbsent = -1,

 msclPartTypeMSCL   = 0,
 msclPartTypeICC    = 1,
 msclPartTypeRAW    = 2,

 msclPartTypeCount

} msclPartType;

struct msclPart
{
  msclPartType  type;      // msclPartTypeAbsent if no such a part
  int           isDynamic; // 0 if static linkage, dynamic otherwise
  int           majorVer;
  int           minorVer;
  int           patchVer;
  const char*   version;
  const char*   name;
  const char*   license;   // Just a name of it
  const char*   url;       // License url
};


MSCLAPI msclPart* msclGetVersion(msclPartType pType);

//[----------------------------------------------------------------------------]
//[ ICC part
//[----------------------------------------------------------------------------]

MSCLAPI miccColorSpaceSignature miccGetColorSpace(miccHPROFILE hProfile);
MSCLAPI msclUInt32Number miccGetProfileInfoASCII(miccHPROFILE hProfile, miccInfoType Info,
                                                 const char LanguageCode[3], const char CountryCode[3],
                                                 char* Buffer, msclUInt32Number BufferSize);
MSCLAPI miccHPROFILE miccOpenProfileFromMem(const void* MemPtr, msclUInt32Number dwSize);
MSCLAPI miccBool miccCloseProfile(miccHPROFILE hProfile);
MSCLAPI miccBool miccSaveProfileToMem(miccHPROFILE hProfile, void* MemPtr, msclUInt32Number* BytesNeeded);
MSCLAPI miccHTRANSFORM miccCreateTransform(miccHPROFILE Input, msclUInt32Number InputFormat,
                                           miccHPROFILE Output, msclUInt32Number OutputFormat,
                                           msclUInt32Number Intent, msclUInt32Number dwFlags);
MSCLAPI void miccDeleteTransform(miccHTRANSFORM hTransform);
MSCLAPI void miccDoTransform(miccHTRANSFORM Transform, const void* InputBuffer, void* OutputBuffer, msclUInt32Number Size);

//[----------------------------------------------------------------------------]
//[ RAW part
//[----------------------------------------------------------------------------]

using mrawProgressCallback = int (*)(void* data, mrawProgress stage, int iteration, int expected);

class MSCLAPI mrawClass
{
  private:

     void*                m_processor;
     mrawImageData        m_data;

     void                 getProcessorData();

  public:
                          mrawClass();
                         ~mrawClass();

     static const char**  getFormats();

     const mrawImageData& getImageData() {return const_cast<const mrawImageData&>(m_data);}
     void                 resetImageData(mrawOParams& params);
     void                 setupImageData(mrawOParams& params);

#if defined(Q_OS_WIN) || defined(_WIN32) || defined(WIN32)
     mrawErrors open_file(const wchar_t* fname, msclInt64Number max_buff_size = mrawDataStreamMaxSize);
#else
     mrawErrors open_file(const char* fname, msclInt64Number max_buff_size = mrawDataStreamMaxSize);
#endif

     mrawErrors           dcrawProcess();
     mrawErrors           dcrawMakeMemImage(mrawProcessedImage& processedImage);
     static void          dcrawClearMem(mrawProcessedImage& processedImage);

     mrawErrors           unpack();
     mrawErrors           unpackThumb();
     void                 recycle();

     void                 setProgressHandler(mrawProgressCallback pcb, void* data);

};

#endif // MESCALERO_H