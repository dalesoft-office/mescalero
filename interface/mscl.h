//[----------------------------------------------------------------------------]
//[
//[ Copyright 2022-2024 DaleSoft (email: office@dalesoft.ru)
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
//[ 18.01.24 /IB/ Trace methods were added
//[ 16.03.25 /IB/ v0.21.0 getCameras method was added
//[ 03.07.25 /IB/ v0.22.0 from lcms2 2.14 to 2.17
//[
//[----------------------------------------------------------------------------]

#ifndef MESCALERO_H
#define MESCALERO_H

#include <QtCore/QtGlobal>

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

// Interface version 0.22.0
#define MESCALERO_VER_STR "0.22.0"
#define MESCALERO_VER_MAJOR 0    // New API
#define MESCALERO_VER_MINOR 22   // Additional methods
#define MESCALERO_VER_PATCH 0    // Just patches

//[----------------------------------------------------------------------------]
//[ Common part
//[----------------------------------------------------------------------------]

typedef enum {

 msclPartTypeAbsent = -1,

 msclPartTypeMSCL   = 0,
 msclPartTypeICC    = 1,
 msclPartTypeRAW    = 2,
 msclPartTypeTRACE  = 3,

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
#else
#define MRAW_FNTYPE    char*
#endif

class MSCLAPI mrawClass
{
  private:

     void*                m_processor;
     mrawImageData        m_data;

     void                 resetProcessorData();
     void                 getProcessorData();

  public:
                          mrawClass();
                         ~mrawClass();

     // RAW files options
     static const char**  getFormats();
     static const char**  getCameras(int& amount);
     static bool          isThumbnailSupported();
     static bool          isExtendedParamsSupported();
     static bool          isProgressHandlerSupported();

     const void*          getProcessor() {return const_cast<const void*>(m_processor);}
     const mrawImageData& getImageData() {return const_cast<const mrawImageData&>(m_data);}

     void                 resetImageData(mrawOParams& params);
     void                 setupImageData(mrawOParams& params);

     mrawErrors           openFile(const MRAW_FNTYPE fname);
     mrawErrors           unpack(const MRAW_FNTYPE fname);
     mrawErrors           unpackThumb();
     void                 recycle();

     mrawErrors           dcrawProcess();
     mrawErrors           dcrawMakeMemImage(mrawProcessedImage& processedImage);
     static void          dcrawClearMem(mrawProcessedImage& processedImage);


     void                 setProgressHandler(mrawProgressCallback pcb, void* data);

};

//[----------------------------------------------------------------------------]
//[ TRACE part
//[----------------------------------------------------------------------------]

#define MTRACE_WORDSIZE          ((int) sizeof(msclULong))
#define MTRACE_WORDBITS          (8 * MTRACE_WORDSIZE)
#define MTRACE_HIBIT             (((msclULong)1) << (MTRACE_WORDBITS - 1))

#define mtrace_scanline(bm, y)   ((bm)->map + (y)*(bm)->dy)
#define mtrace_index(bm, x, y)   (&mtrace_scanline(bm, y)[(x)/MTRACE_WORDBITS])
#define mtrace_mask(x)           (MTRACE_HIBIT >> ((x) & (MTRACE_WORDBITS-1)))
#define mtrace_range(x, a)       ((int)(x) >= 0 && (int)(x) < (a))
#define mtrace_safe(bm, x, y)    (mtrace_range(x, (bm)->w) && mtrace_range(y, (bm)->h))

#define MTRACE_USET(bm, x, y)    (*mtrace_index(bm, x, y) |= mtrace_mask(x))
#define MTRACE_UCLR(bm, x, y)    (*mtrace_index(bm, x, y) &= ~mtrace_mask(x))
#define MTRACE_UPUT(bm, x, y, b) ((b) ? MTRACE_USET(bm, x, y) : MTRACE_UCLR(bm, x, y))
#define MTRACE_PUT(bm, x, y, b)  (mtrace_safe(bm, x, y) ? MTRACE_UPUT(bm, x, y, b) : 0)


class MSCLAPI mtraceClass
{
 public:

    static mtraceParam*  paramCreate();
    static void          paramFree(mtraceParam*);

    static mtraceState*  traceCreate(const mtraceParam* param, const mtraceBitmap* bm);
    static void          traceFree(mtraceState* st);

    static mtraceBitmap* bitmapCreate(int w, int h);
    static void          bitmapFree(mtraceBitmap*);
};

//[----------------------------------------------------------------------------]

#endif // MESCALERO_H
