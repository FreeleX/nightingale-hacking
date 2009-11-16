/*
//
// BEGIN SONGBIRD GPL
//
// This file is part of the Songbird web player.
//
// Copyright(c) 2005-2008 POTI, Inc.
// http://songbirdnest.com
//
// This file may be licensed under the terms of of the
// GNU General Public License Version 2 (the "GPL").
//
// Software distributed under the License is distributed
// on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, either
// express or implied. See the GPL for the specific language
// governing rights and limitations.
//
// You should have received a copy of the GPL along with this
// program. If not, go to http://www.gnu.org/licenses/gpl.html
// or write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
//
// END SONGBIRD GPL
//
*/

#ifndef __SBDEVICECAPABILITIES_H__
#define __SBDEVICECAPABILITIES_H__

#include <sbIDeviceCapabilities.h>

#include <nsIArray.h>
#include <nsIClassInfo.h>
#include <nsCOMPtr.h>
#include <nsClassHashtable.h>
#include <nsInterfaceHashtable.h>
#include <nsTArray.h>
#include "nsMemory.h"
#include <nsIVariant.h>

class sbDeviceCapabilities : public sbIDeviceCapabilities, nsIClassInfo
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_SBIDEVICECAPABILITIES
  NS_DECL_NSICLASSINFO

  sbDeviceCapabilities();

private:
  ~sbDeviceCapabilities();

protected:
  PRBool isInitialized;
  typedef nsClassHashtable<nsUint32HashKey, nsTArray<PRUint32> > ContentTypes;
  typedef nsClassHashtable<nsUint32HashKey, nsTArray<nsCString> > SupportedFormats;
  typedef nsInterfaceHashtable<nsStringHashKey, nsISupports> FormatTypes;
  nsTArray<PRUint32> mFunctionTypes;
  ContentTypes mContentTypes;
  SupportedFormats mSupportedFormats;
  FormatTypes mFormatTypes;
  nsTArray<PRUint32> mSupportedEvents;
};

/**
 * Implementation of @see sbIImageSize
 */
class sbImageSize : public sbIImageSize, nsIClassInfo
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_SBIIMAGESIZE
  NS_DECL_NSICLASSINFO

  sbImageSize() :
    mWidth(0),
    mHeight(0) {}

private:
  ~sbImageSize();

  PRInt32 mWidth;
  PRInt32 mHeight;
};

/**
 * Implementation of @see sbIDevCapRange
 */
class sbDevCapRange : public sbIDevCapRange, nsIClassInfo
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_SBIDEVCAPRANGE
  NS_DECL_NSICLASSINFO

  sbDevCapRange() : mMin(0),
                    mMax(0),
                    mStep(0),
                    mValues(nsnull) {}

private:
  ~sbDevCapRange();

  PRInt32 mMin;
  PRInt32 mMax;
  PRInt32 mStep;
  nsTArray<PRInt32> mValues;
};

/**
 * Implementation of @see sbIFormatTypeConstraint
 */
class sbFormatTypeConstraint : public sbIFormatTypeConstraint, nsIClassInfo
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_SBIFORMATTYPECONSTRAINT
  NS_DECL_NSICLASSINFO

private:
  ~sbFormatTypeConstraint();

  typedef nsCOMPtr<nsIVariant> Value;

  nsString mConstraintName;
  Value mMinValue;
  Value mMaxValue;
};

/**
 * Implementation of @see sbIImageFormatType
 */
class sbImageFormatType : public sbIImageFormatType, nsIClassInfo
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_SBIIMAGEFORMATTYPE
  NS_DECL_NSICLASSINFO

private:
  ~sbImageFormatType();

  typedef nsCOMPtr<nsIArray> Sizes;
  typedef nsCOMPtr<sbIDevCapRange> Widths;
  typedef nsCOMPtr<sbIDevCapRange> Heights;

  nsCString mImageFormat;
  Sizes mSupportedExplicitSizes;
  Widths mSupportedWidths;
  Heights mSupportedHeights;
};

/**
 * Implementation of @see sbIAudioFormatType
 */
class sbAudioFormatType : public sbIAudioFormatType, nsIClassInfo
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_SBIAUDIOFORMATTYPE
  NS_DECL_NSICLASSINFO

private:
  ~sbAudioFormatType();

  typedef nsCOMPtr<sbIDevCapRange> Bitrates;
  typedef nsCOMPtr<sbIDevCapRange> SampleRates;
  typedef nsCOMPtr<sbIDevCapRange> SupportedChannels;
  typedef nsCOMPtr<nsIArray> FormatConstraints;

  nsCString mContainerFormat;
  nsCString mAudioCodec;
  Bitrates mSupportedBitrates;
  SampleRates mSupportedSampleRates;
  SupportedChannels mSupportedChannels;
  FormatConstraints mFormatSpecificConstraints;
};

/**
 * Implementation of @see sbIVideoFormatType
 */
class sbVideoFormatType : public sbIVideoFormatType, nsIClassInfo
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_SBIVIDEOFORMATTYPE
  NS_DECL_NSICLASSINFO

private:
  ~sbVideoFormatType();

  typedef nsCOMPtr<sbIDevCapRange> Bitrates;
  typedef nsCOMPtr<sbIDevCapRange> SampleRates;
  typedef nsCOMPtr<sbIDevCapRange> SupportedChannels;
  typedef nsCOMPtr<nsIArray> FormatConstraints;

  nsCString mContainerFormat;
  nsCString mVideoCodec;
  Bitrates mSupportedBitrates;
  SampleRates mSupportedSampleRates;
  SupportedChannels mSupportedChannels;
  FormatConstraints mFormatSpecificConstraints;
};

#endif /* __SBDEVICECAPABILITIES_H__ */

