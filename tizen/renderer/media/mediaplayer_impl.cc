// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "xwalk/tizen/renderer/media/mediaplayer_impl.h"

#include "content/public/renderer/render_view.h"
#include "third_party/WebKit/public/platform/WebURL.h"

namespace tizen {

MediaPlayerImpl::MediaPlayerImpl(
    blink::WebLocalFrame* frame,
    blink::WebMediaPlayerClient* client,
    base::WeakPtr<media::WebMediaPlayerDelegate> delegate,
    RendererMediaPlayerManager* manager,
    const media::WebMediaPlayerParams& params)
    : WebMediaPlayerImpl(frame, client, delegate, nullptr, params),
      client_(client),
      manager_(manager) {
  DCHECK(manager_);

  player_id_ = manager_->RegisterMediaPlayer(this);
}

MediaPlayerImpl::~MediaPlayerImpl() {
  if (manager_) {
    manager_->DestroyPlayer(player_id_);
    manager_->UnregisterMediaPlayer(player_id_);
  }
}

void MediaPlayerImpl::Detach() {
  manager_ = NULL;
}

void MediaPlayerImpl::load(LoadType load_type, const blink::WebURL& url,
                           CORSMode cors_mode) {
  InitializeMediaPlayer(url);
  WebMediaPlayerImpl::load(load_type, url, cors_mode);
}

void MediaPlayerImpl::InitializeMediaPlayer(const blink::WebURL& url) {
  if (manager_)
    manager_->Initialize(player_id_, getpid(), url);
}

void MediaPlayerImpl::play() {
  if (manager_)
    manager_->Start(player_id_);
  WebMediaPlayerImpl::play();
}

void MediaPlayerImpl::pause() {
  if (manager_)
    manager_->Pause(player_id_);
  WebMediaPlayerImpl::pause();
}

void MediaPlayerImpl::OnMediaPlayerPlay() {
  WebMediaPlayerImpl::play();
  client_->playbackStateChanged();
}

void MediaPlayerImpl::OnMediaPlayerPause() {
  WebMediaPlayerImpl::pause();
  client_->playbackStateChanged();
}

}  // namespace tizen
