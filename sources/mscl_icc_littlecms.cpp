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
//[ 24.11.22 /IB/ Methods were grouped into classes
//[ 10.12.22 /IB/ New methods were added, format of some old ones changed
//[
//[----------------------------------------------------------------------------]

#include <mscl.h>
#include <libraries/lcms/lcms2.h>

//[----------------------------------------------------------------------------]
//[ ICC methods
//[----------------------------------------------------------------------------]

miccColorSpaceSignature miccClass::getColorSpace(miccHPROFILE hProfile)
{
 return (miccColorSpaceSignature) cmsGetColorSpace(hProfile);
}

//[----------------------------------------------------------------------------]
//[ if Buffer is NULL, returns the size of the buffer
//[----------------------------------------------------------------------------]

msclUInt32Number miccClass::getProfileInfo(miccHPROFILE hProfile, char* Buffer, msclUInt32Number BufferSize)
{
 // cmsNoLanguage == cmsNoCountry == "\0\0"
 return cmsGetProfileInfoASCII(hProfile, cmsInfoDescription, "\0\0", "\0\0", Buffer, BufferSize);
}

//[----------------------------------------------------------------------------]

miccHPROFILE miccClass::openProfileFromMem(const void* MemPtr, msclUInt32Number dwSize)
{
 return cmsOpenProfileFromMem(MemPtr, dwSize);
}

//[----------------------------------------------------------------------------]

miccBool miccClass::closeProfile(miccHPROFILE hProfile)
{
 return cmsCloseProfile(hProfile);
}

//[----------------------------------------------------------------------------]

miccBool miccClass::saveProfileToMem(miccHPROFILE hProfile, void* MemPtr, msclUInt32Number* BytesNeeded)
{
 return cmsSaveProfileToMem(hProfile, MemPtr, BytesNeeded);
}

//[----------------------------------------------------------------------------]

miccHTRANSFORM miccClass::createTransform(miccHPROFILE Input, msclUInt32Number InputFormat,
                                          miccHPROFILE Output, msclUInt32Number OutputFormat,
                                          msclUInt32Number Intent, msclUInt32Number dwFlags)
{
 return cmsCreateTransform(Input,InputFormat, Output, OutputFormat, Intent, dwFlags);
}

//[----------------------------------------------------------------------------]

void miccClass::deleteTransform(miccHTRANSFORM hTransform)
{
 cmsDeleteTransform(hTransform);
}

//[----------------------------------------------------------------------------]

void miccClass::doTransform(miccHTRANSFORM Transform, const void* InputBuffer,
                            void* OutputBuffer, msclUInt32Number Size)
{
 cmsDoTransform(Transform, InputBuffer, OutputBuffer, Size);
}

//[----------------------------------------------------------------------------]
