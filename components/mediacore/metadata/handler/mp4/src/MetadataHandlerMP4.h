/*
//
// BEGIN SONGBIRD GPL
// 
// This file is part of the Songbird web player.
//
// Copyright 2006 Pioneers of the Inevitable LLC
// http://songbirdnest.com
// 
// This file may be licensed under the terms of of the
// GNU General Public License Version 2 (the GPL).
// 
// Software distributed under the License is distributed 
// on an AS IS basis, WITHOUT WARRANTY OF ANY KIND, either 
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

/**
* \file MetadataHandlerMP4.h
* \brief 
*/

#pragma once

// INCLUDES ===================================================================
#include <nscore.h>
#include <necko/nsIChannel.h>
#include <necko/nsIResumableChannel.h>
#include <xpcom/nsXPCOM.h>
#include <xpcom/nsCOMPtr.h>
#include <xpcom/nsServiceManagerUtils.h>
#include <xpcom/nsComponentManagerUtils.h>

#include "sbIMetadataHandler.h"
#include "sbIMetadataValues.h"
#include "sbIMetadataChannel.h"

// DEFINES ====================================================================
#define SONGBIRD_METADATAHANDLERMP4_CONTRACTID  "@songbird.org/Songbird/MetadataHandler/MP4;1"
#define SONGBIRD_METADATAHANDLERMP4_CLASSNAME   "Songbird MP4 Metadata Handler Interface"

// {39B0F740-5E3B-4016-8834-CEC55B6E2967}
#define SONGBIRD_METADATAHANDLERMP4_CID { 0x39b0f740, 0x5e3b, 0x4016, { 0x88, 0x34, 0xce, 0xc5, 0x5b, 0x6e, 0x29, 0x67 } }

// FUNCTIONS ==================================================================

// CLASSES ====================================================================
class sbMetadataHandlerMP4 : public sbIMetadataHandler
{
  NS_DECL_ISUPPORTS
  NS_DECL_SBIMETADATAHANDLER

  sbMetadataHandlerMP4();
  virtual ~sbMetadataHandlerMP4();

protected:
  nsCOMPtr<sbIMetadataValues> m_Values;
  nsCOMPtr<sbIMetadataChannel> m_ChannelHandler;
  nsCOMPtr<nsIChannel> m_Channel;
  PRBool               m_Completed;
};