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
//[ 24.11.22 /IB/ Methods were grouped into classes
//[ 10.12.22 /IB/ New methods were added, format of some old ones changed
//[
//[----------------------------------------------------------------------------]

#ifndef MESCALERO_H
#define MESCALERO_H

#include <QtCore/qglobal.h>
#include <string>

#include <mscl_defines.h>

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

// Interface version 0.11.0
#define MESCALERO_VER_STR "0.11.0"
#define MESCALERO_VER_MAJOR 0
#define MESCALERO_VER_MINOR 11
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
  int           majorVer;
  int           minorVer;
  int           patchVer;
  const char*   version;
  const char*   name;      // It's a case sensitive code of the library
  const char*   license;   // Just a name of it
  const char*   url;       // License url
};

//[----------------------------------------------------------------------------]
//[ Common part
//[----------------------------------------------------------------------------]

class MSCLAPI msclClass
{
 public:

    static msclPart* msclGetVersion(msclPartType pType);
};

//[----------------------------------------------------------------------------]
//[ ICC part
//[----------------------------------------------------------------------------]

class MSCLAPI miccClass
{
 public:

    static miccColorSpaceSignature getColorSpace(miccHPROFILE hProfile);
    static msclUInt32Number        getProfileInfo(miccHPROFILE hProfile, char* Buffer, msclUInt32Number BufferSize);
    static miccHPROFILE            openProfileFromMem(const void* MemPtr, msclUInt32Number dwSize);
    static miccBool                closeProfile(miccHPROFILE hProfile);
    static miccBool                saveProfileToMem(miccHPROFILE hProfile, void* MemPtr, msclUInt32Number* BytesNeeded);
    static miccHTRANSFORM          createTransform(miccHPROFILE Input, msclUInt32Number InputFormat,
                                                   miccHPROFILE Output, msclUInt32Number OutputFormat,
                                                   msclUInt32Number Intent, msclUInt32Number dwFlags);
    static void                    deleteTransform(miccHTRANSFORM hTransform);
    static void                    doTransform(miccHTRANSFORM Transform, const void* InputBuffer,
                                               void* OutputBuffer, msclUInt32Number Size);
};

//[----------------------------------------------------------------------------]
//[ RAW part
//[----------------------------------------------------------------------------]

using mrawProgressCallback = int (*)(void* data, mrawProgress stage, int iteration, int expected);

#if defined(Q_OS_WIN) || defined(_WIN32) || defined(WIN32)
#define MRAW_FNTYPE    wchar_t*
#define MRAW_EMPTYSTR  const_cast<MRAW_FNTYPE>(L"")
#else
#define MRAW_FNTYPE    char*
#define MRAW_EMPTYSTR  const_cast<MRAW_FNTYPE>("")
#endif

class MSCLAPI mrawClass
{
  private:

     void*                m_processor;
     mrawImageData        m_data;
     MRAW_FNTYPE          m_filename;

     void                 resetProcessorData();
     void                 getProcessorData();

  public:
                          mrawClass();
                         ~mrawClass();

     // RAW files options
     static const char**  getFormats();
     static bool          isThumbnailSupported();
     static bool          isExtendedParamsSupported();
     static bool          isProgressHandlerSupported();

     const void*          getProcessor() {return const_cast<const void*>(m_processor);}
     const mrawImageData& getImageData() {return const_cast<const mrawImageData&>(m_data);}
     const MRAW_FNTYPE    getFileName() {return const_cast<const MRAW_FNTYPE>(m_filename);}

     void                 resetImageData(mrawOParams& params);
     void                 setupImageData(mrawOParams& params);

     mrawErrors           openFile(const MRAW_FNTYPE fname);

     mrawErrors           dcrawProcess();
     mrawErrors           dcrawMakeMemImage(mrawProcessedImage& processedImage);
     static void          dcrawClearMem(mrawProcessedImage& processedImage);

     mrawErrors           unpack();
     mrawErrors           unpackThumb();
     void                 recycle();

     void                 setProgressHandler(mrawProgressCallback pcb, void* data);

};

//[----------------------------------------------------------------------------]

#endif // MESCALERO_H
