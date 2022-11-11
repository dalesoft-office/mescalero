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
//[ File:                       mscl_icc_littlecms.cpp 
//[ Author:                     Igor Belyakov (igor@dalesoft.ru)
//[ Description:                Mescalero implementation (LittleCMS as ICC)
//[ History:
//[
//[ 06.11.22 /IB/ Created...
//[
//[----------------------------------------------------------------------------]


#include "interface/mscl_defines.h"
#include "interface/mscl.h"

#define register // Deprecated in C++17 but used in Little CMS
#include "libraries/lcms/lcms2.h"

//[----------------------------------------------------------------------------]
//[ ICC methods
//[----------------------------------------------------------------------------]

MSCLAPI miccColorSpaceSignature miccGetColorSpace(miccHPROFILE hProfile)
{
 return (miccColorSpaceSignature) cmsGetColorSpace(hProfile);
}

//[----------------------------------------------------------------------------]

MSCLAPI msclUInt32Number miccGetProfileInfoASCII(miccHPROFILE hProfile, miccInfoType Info,
                                                 const char LanguageCode[3], const char CountryCode[3],
                                                 char* Buffer, msclUInt32Number BufferSize)
{
 return cmsGetProfileInfoASCII(hProfile, (cmsInfoType) Info, LanguageCode, CountryCode, Buffer, BufferSize);
}

//[----------------------------------------------------------------------------]

MSCLAPI miccHPROFILE miccOpenProfileFromMem(const void* MemPtr, msclUInt32Number dwSize)
{
 return cmsOpenProfileFromMem(MemPtr, dwSize);
}

//[----------------------------------------------------------------------------]

MSCLAPI miccBool miccCloseProfile(miccHPROFILE hProfile)
{
 return cmsCloseProfile(hProfile);
}

//[----------------------------------------------------------------------------]

MSCLAPI miccBool miccSaveProfileToMem(miccHPROFILE hProfile, void* MemPtr, msclUInt32Number* BytesNeeded)
{
 return cmsSaveProfileToMem(hProfile, MemPtr, BytesNeeded);
}

//[----------------------------------------------------------------------------]

MSCLAPI miccHTRANSFORM miccCreateTransform(miccHPROFILE Input, msclUInt32Number InputFormat,
                                           miccHPROFILE Output, msclUInt32Number OutputFormat,
                                           msclUInt32Number Intent, msclUInt32Number dwFlags)
{
 return cmsCreateTransform(Input,InputFormat, Output, OutputFormat, Intent, dwFlags);
}

//[----------------------------------------------------------------------------]

MSCLAPI void miccDeleteTransform(miccHTRANSFORM hTransform)
{
 cmsDeleteTransform(hTransform);
}

//[----------------------------------------------------------------------------]

MSCLAPI void miccDoTransform(miccHTRANSFORM Transform, const void* InputBuffer, void* OutputBuffer, msclUInt32Number Size)
{
 cmsDoTransform(Transform, InputBuffer, OutputBuffer, Size);
}

//[----------------------------------------------------------------------------]
