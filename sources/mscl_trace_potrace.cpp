//[----------------------------------------------------------------------------]
//[
//[ Copyright 2024 DaleSoft (email: office@dalesoft.ru)
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
//[ File:                       mscl_trace_potrace.cpp
//[ Author:                     Igor Belyakov (igor@dalesoft.ru)
//[ Description:                Mescalero implementation (POTRACE as TRACE)
//[ History:
//[
//[ 16.01.24 /IB/ Created...
//[
//[----------------------------------------------------------------------------]

#include <mscl.h>
#include <libraries/potrace/potracelib.h>

//[----------------------------------------------------------------------------]
//[ TRACE methods
//[----------------------------------------------------------------------------]

mtraceParam* mtraceClass::paramCreate()
{
 return (mtraceParam*) potrace_param_default();
}

//[----------------------------------------------------------------------------]

void mtraceClass::paramFree(mtraceParam* p)
{
 potrace_param_free((potrace_param_t*)p);
}

//[----------------------------------------------------------------------------]

mtraceState* mtraceClass::traceCreate(const mtraceParam* param, const mtraceBitmap* bm)
{
 return (mtraceState*) potrace_trace((const potrace_param_t*) param, (const potrace_bitmap_t *) bm);
}

//[----------------------------------------------------------------------------]

void mtraceClass::traceFree(mtraceState* st)
{
 potrace_state_free((potrace_state_t *) st);
}

//[----------------------------------------------------------------------------]

mtraceBitmap* mtraceClass::bitmapCreate(int w, int h)
{
 mtraceBitmap* bm;

 int dy = (w + MTRACE_WORDBITS - 1) / MTRACE_WORDBITS;

 bm = (mtraceBitmap *) malloc(sizeof(mtraceBitmap));
 if(!bm)
   return nullptr;

 bm->w = w;
 bm->h = h;
 bm->dy = dy;
 bm->map = (msclULong *) calloc(h, dy * MTRACE_WORDSIZE);
 if(!bm->map)
   {
    free(bm);
    return nullptr;
   }

 return bm;
}

//[----------------------------------------------------------------------------]

void mtraceClass::bitmapFree(mtraceBitmap* bm)
{
 if(bm != nullptr)
   free(bm->map);

 free(bm);
}

//[----------------------------------------------------------------------------]
