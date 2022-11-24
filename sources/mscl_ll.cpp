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
//[ File:                       mscl_ll.cpp
//[ Author:                     Igor Belyakov (igor@dalesoft.ru)
//[ Description:                Mescalero implementation (LittleCMS + LibRaw)
//[ History:
//[
//[ 13.10.22 /IB/ Created...
//[ 23.10.22 /IB/ RAW part added
//[
//[----------------------------------------------------------------------------]


#include "interface/mscl_defines.h"
#include "interface/mscl.h"

#include "libraries/lcms/lcms2.h"

#include "libraries/libraw/libraw.h"

//[----------------------------------------------------------------------------]
//[ Mescalero methods
//[----------------------------------------------------------------------------]

static msclPart msclParts[] = {

 {msclPartTypeMSCL, MESCALERO_VER_MAJOR, MESCALERO_VER_MINOR, MESCALERO_VER_PATCH, MESCALERO_VER_STR,
  "Mescalero",  "Apache 2.0", "http://www.apache.org/licenses/LICENSE-2.0"},
 {msclPartTypeICC, 2, 14, 0, "2.14.0",
  "LittleCMS", "LSMS license", "https://github.com/mm2/Little-CMS/blob/lcms2.14/COPYING"},
 {msclPartTypeRAW, LIBRAW_MAJOR_VERSION, LIBRAW_MINOR_VERSION, LIBRAW_PATCH_VERSION, "0.20.2",
  "LibRAW", "LGPL 2.1", "https://github.com/LibRaw/LibRaw/blob/0.19-stable/LICENSE.LGPL"}

};

//[----------------------------------------------------------------------------]
//[
//[  Method:     msclClass::msclGetVersion
//[
//[  Purpose:    Returns Mescalero version
//[  Parameters: msclPartType pType := Part code
//[  Returns:    msclPart* := Pointer to part description or nullptr
//[
//[----------------------------------------------------------------------------]

msclPart* msclClass::msclGetVersion(msclPartType pType)
{
 if((pType < 0) || (pType >= msclPartTypeCount))
   return nullptr;

 return &msclParts[pType];
}

//[----------------------------------------------------------------------------]
