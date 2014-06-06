// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "xwalk/mobile/renderer/mediaplayer_ms.h"

#include "content/public/renderer/render_view.h"
#include "third_party/WebKit/public/platform/WebMediaPlayerClient.h"
#include "third_party/WebKit/public/platform/WebURL.h"

namespace tizen {

MediaPlayerMS::MediaPlayerMS(
    blink::WebFrame* frame,
    blink::WebMediaPlayerClient* client,
    base::WeakPtr<content::WebMediaPlayerDelegate> delegate,
    content::MediaStreamClient* media_stream_client,
    media::MediaLog* media_log,
    RendererMediaPlayerManager* manager)
    : WebMediaPlayerMS(frame, client, delegate, media_stream_client, media_log),
      manager_(manager),
      client_(client) {
  DCHECK(manager_);

  player_id_ = manager_->RegisterMediaPlayer(this);
}

MediaPlayerMS::~MediaPlayerMS() {
  if (manager_) {
    manager_->DestroyPlayer(player_id_);
    manager_->UnregisterMediaPlayer(player_id_);
  }
}

void MediaPlayerMS::Detach() {
  manager_ = NULL;
}

void MediaPlayerMS::load(LoadType load_type, const blink::WebURL& url,
                           CORSMode cors_mode) {
  WebMediaPlayerMS::load(load_type, url, cors_mode);
  InitializeMediaPlayer(url);
}

void MediaPlayerMS::InitializeMediaPlayer(const blink::WebURL& url) {
  if (manager_)
    manager_->Initialize(player_id_, getpid(),
        url, WebMediaPlayerMS::hasVideo());
}

void MediaPlayerMS::play() {
  if (manager_)
    manager_->Start(player_id_);
  WebMediaPlayerMS::play();
}

void MediaPlayerMS::pause() {
  if (manager_)
    manager_->Pause(player_id_);
  WebMediaPlayerMS::pause();
}

void MediaPlayerMS::OnMediaPlayerPlay() {
  WebMediaPlayerMS::play();
  client_->playbackStateChanged();
}

void MediaPlayerMS::OnMediaPlayerPause() {
  WebMediaPlayerMS::pause();
  client_->playbackStateChanged();
}

}  // namespace tizen
