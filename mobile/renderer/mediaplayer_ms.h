// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef XWALK_TIZEN_RENDERER_MEDIAPLAYER_MS_H_
#define XWALK_TIZEN_RENDERER_MEDIAPLAYER_MS_H_

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "content/renderer/media/webmediaplayer_ms.h"
#include "xwalk/mobile/renderer/renderer_mediaplayer_manager.h"

namespace blink {
class WebMediaPlayerClient;
}

namespace tizen {

// Substitute for WebMediaPlayerMS to be used in Tizen.
class MediaPlayerMS : public content::WebMediaPlayerMS,
                      public MediaPlayerObserver {
 public:
  MediaPlayerMS(blink::WebFrame* frame,
                blink::WebMediaPlayerClient* client,
                base::WeakPtr<content::WebMediaPlayerDelegate> delegate,
                content::MediaStreamClient* media_stream_client,
                media::MediaLog* media_log,
                RendererMediaPlayerManager* manager);
  virtual ~MediaPlayerMS();

  // WebMediaPlayerMS method.
  virtual void load(LoadType load_type,
                    const blink::WebURL& url,
                    CORSMode cors_mode) OVERRIDE;

  // Playback controls.
  virtual void play();
  virtual void pause();

  // Detach the player from its manager.
  void Detach();

  // Functions called when media player status changes.
  void OnMediaPlayerPlay();
  void OnMediaPlayerPause();

 private:
  void InitializeMediaPlayer(const blink::WebURL& url);

  // Manager for managing this object and for delegating method calls on
  // Render Thread.
  RendererMediaPlayerManager* manager_;

  // Player ID assigned by the |manager_|.
  MediaPlayerID player_id_;

  blink::WebMediaPlayerClient* client_;

  DISALLOW_COPY_AND_ASSIGN(MediaPlayerMS);
};

}  // namespace tizen

#endif  // XWALK_TIZEN_RENDERER_MEDIAPLAYER_MS_H_
