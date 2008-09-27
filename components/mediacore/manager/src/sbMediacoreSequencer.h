/* vim: set sw=2 :miv */
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

#include <sbIMediacoreSequencer.h>

#include <nsIClassInfo.h>
#include <nsIMutableArray.h>
#include <nsIStringEnumerator.h>
#include <nsITimer.h>
#include <nsIURI.h>
#include <nsIWeakReference.h>

#include <nsCOMPtr.h>
#include <nsHashKeys.h>
#include <nsTHashtable.h>
#include <prmon.h>

#include <sbIDataRemote.h>
#include <sbIMediacoreEventListener.h>
#include <sbIMediacoreManager.h>
#include <sbIMediacoreStatus.h>
#include <sbIMediacoreSequenceGenerator.h>
#include <sbIMediaListListener.h>
#include <sbIMediaListView.h>

#include <vector>

class sbMediacoreSequencer : public sbIMediacoreSequencer,
                             public sbIMediacoreEventListener,
                             public sbIMediacoreStatus,
                             public nsIClassInfo,
                             public nsITimerCallback
{
public:
  NS_DECL_ISUPPORTS

  NS_DECL_SBIMEDIACORESEQUENCER
  NS_DECL_SBIMEDIACOREEVENTLISTENER
  NS_DECL_SBIMEDIACORESTATUS
  NS_DECL_NSICLASSINFO
  NS_DECL_NSITIMERCALLBACK

  sbMediacoreSequencer();

  typedef std::vector<PRUint32> sequence_t;

  nsresult Init();

  // Sequence Processor (timer driven)
  nsresult StartSequenceProcessor();
  nsresult StopSequenceProcessor();

  // DataRemotes
  nsresult BindDataRemotes();
  nsresult UnbindDataRemotes();

  // Faceplate Playback Status DataRemotes
  nsresult UpdatePlayStateDataRemotes();
  nsresult UpdatePositionDataRemotes(PRUint64 aPosition);
  nsresult UpdateDurationDataRemotes(PRUint64 aDuration);
  nsresult UpdateURLDataRemotes(nsIURI *aURI);
  nsresult UpdateShuffleDataRemote(PRUint32 aMode);
  nsresult UpdateRepeatDataRemote(PRUint32 aRepeatMode);

  // Metadata Event & DataRemote
  nsresult HandleMetadataEvent(sbIMediacoreEvent *aEvent);
  nsresult SetMetadataDataRemote(const nsAString &aId, 
                                 const nsAString &aValue);
  nsresult ResetMetadataDataRemotes();

  // Sequence management
  nsresult RecalculateSequence(PRUint32 *aViewPosition = nsnull);

  // Fetching of items, item manipulation.
  nsresult GetItem(const sequence_t &aSequence,
                   PRUint32 aPosition, 
                   sbIMediaItem **aItem);

  // Setup for playback
  nsresult ProcessNewPosition();
  nsresult Setup();

  // Set view with optional view position
  nsresult SetViewWithViewPosition(sbIMediaListView *aView, 
                                   PRUint32 *aViewPosition = nsnull);

private:
  virtual ~sbMediacoreSequencer();

  nsresult DispatchMediacoreEvent(sbIMediacoreEvent *aEvent, 
                                  PRBool aAsync = PR_FALSE);

protected:
  PRMonitor *mMonitor;
  
  PRUint32                       mStatus;
  PRPackedBool                   mIsWaitingForPlayback;
  PRPackedBool                   mSeenPlaying;
  
  PRUint32                       mChainIndex;
  nsCOMPtr<nsIArray>             mChain;
  
  nsCOMPtr<sbIMediacore>                mCore;
  nsCOMPtr<sbIMediacorePlaybackControl> mPlaybackControl;

  PRUint32                       mMode;
  PRUint32                       mRepeatMode;

  nsCOMPtr<sbIMediaListView>     mView;
  sequence_t                     mSequence;
  sequence_t                     mViewIndexToSequenceIndex;
  PRUint32                       mPosition;
  PRUint32                       mViewPosition;

  nsCOMPtr<sbIMediacoreSequenceGenerator> mCustomGenerator;
  nsCOMPtr<sbIMediacoreSequenceGenerator> mShuffleGenerator;

  nsCOMPtr<nsIWeakReference> mMediacoreManager;

  nsCOMPtr<sbIDataRemote> mDataRemoteFaceplateBuffering;
  nsCOMPtr<sbIDataRemote> mDataRemoteFaceplatePaused;
  nsCOMPtr<sbIDataRemote> mDataRemoteFaceplatePlaying;
  nsCOMPtr<sbIDataRemote> mDataRemoteFaceplateSeenPlaying;
  nsCOMPtr<sbIDataRemote> mDataRemoteFaceplateURL;

  nsCOMPtr<sbIDataRemote> mDataRemoteMetadataAlbum;
  nsCOMPtr<sbIDataRemote> mDataRemoteMetadataArtist;
  nsCOMPtr<sbIDataRemote> mDataRemoteMetadataTitle;
  nsCOMPtr<sbIDataRemote> mDataRemoteMetadataGenre;

  nsCOMPtr<sbIDataRemote> mDataRemoteMetadataDuration;
  nsCOMPtr<sbIDataRemote> mDataRemoteMetadataDurationStr;
  nsCOMPtr<sbIDataRemote> mDataRemoteMetadataPosition;
  nsCOMPtr<sbIDataRemote> mDataRemoteMetadataPositionStr;

  nsCOMPtr<sbIDataRemote> mDataRemoteMetadataURL;

  nsCOMPtr<sbIDataRemote> mDataRemotePlaylistShuffle;
  nsCOMPtr<sbIDataRemote> mDataRemotePlaylistRepeat;

  nsCOMPtr<nsITimer> mSequenceProcessorTimer;
};
