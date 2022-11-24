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
//[ File:                       libraw_defines.h
//[ Author:                     Igor Belyakov (igor@dalesoft.ru)
//[ Description:                LibRAW library definitions substitutes
//[ History:
//[
//[ 25.10.22 /IB/ Created...
//[
//[----------------------------------------------------------------------------]

#ifndef LIBRAW_DEFINES_H
#define LIBRAW_DEFINES_H

// Typedefs and defines

#define LibRaw mrawClass

using LibRaw_progress = mrawProgress;
#define LIBRAW_PROGRESS_LOAD_RAW mrawProgressLoadRow
#define LIBRAW_PROGRESS_START    mrawProgressStart

using LibRaw_errors = mrawErrors;
#define LIBRAW_SUCCESS               mrawSuccess
#define LIBRAW_FILE_UNSUPPORTED      mrawErrorFileUnsupported
#define LIBRAW_UNSUFFICIENT_MEMORY   mrawErrorUnsufficientMemory
#define LIBRAW_IO_ERROR              mrawErrorIO
#define LIBRAW_CANCELLED_BY_CALLBACK mrawErrorCancelledByCallback

using LibRaw_image_formats = mrawImageFormats;

using LibRaw_thumbnail_formats = mrawThumbnailFormats;
#define LIBRAW_THUMBNAIL_UNKNOWN  mrawThumbnailFormatUnknown
#define LIBRAW_THUMBNAIL_JPEG     mrawThumbnailFormatJpeg
#define LIBRAW_THUMBNAIL_BITMAP   mrawThumbnailFormatBitmap
#define LIBRAW_THUMBNAIL_BITMAP16 mrawThumbnailFormatBmp16
#define LIBRAW_THUMBNAIL_LAYER    mrawThumbnailFormatLayer
#define LIBRAW_THUMBNAIL_ROLLEI   mrawThumbnailFormatRollei

using libraw_processed_image_t = mrawProcessedImage;

#endif // LIBRAW_DEFINES_H
