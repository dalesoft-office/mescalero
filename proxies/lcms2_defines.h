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
//[ File:                       lcms2_defines.h
//[ Author:                     Igor Belyakov (igor@dalesoft.ru)
//[ Description:                Little CMS library definitions substitutes
//[ History:
//[
//[ 15.10.22 /IB/ Created...
//[ 24.11.22 /IB/ Methods were grouped into classes
//[
//[----------------------------------------------------------------------------]

#ifndef LCMS2_DEFINES_H
#define LCMS2_DEFINES_H

// Typedefs and defines

using cmsUInt32Number = msclUInt32Number;
using cmsBool         = miccBool;

using cmsHPROFILE     = miccHPROFILE;
using cmsHTRANSFORM   = miccHTRANSFORM;
using cmsHANDLE       = miccHANDLE;

using cmsColorSpaceSignature = miccColorSpaceSignature;

#define INTENT_PERCEPTUAL 0
#define cmsNoLanguage "\0\0"
#define cmsNoCountry  "\0\0"
#define TYPE_BGRA_8  (1|(4 << 16)|(1 << 7)|(3 << 3)|(1 << 10)|(1 << 14))

// Access header data

#define cmsGetColorSpace miccClass::getColorSpace

// Localized info

#define cmsGetProfileInfoASCII(p1,p2,p3,p4,p5,p6) miccClass::getProfileInfo(p1,p5,p6)

// Profile

#define cmsOpenProfileFromMem miccClass::openProfileFromMem
#define cmsCloseProfile miccClass::closeProfile
#define cmsSaveProfileToMem miccClass::saveProfileToMem

// Transforms

#define cmsCreateTransform miccClass::createTransform
#define cmsDeleteTransform miccClass::deleteTransform
#define cmsDoTransform miccClass::doTransform

#endif // LCMS2_DEFINES_H
