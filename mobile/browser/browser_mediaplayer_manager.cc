// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "xwalk/mobile/browser/browser_mediaplayer_manager.h"

#include "content/public/browser/render_view_host.h"
#include "content/public/browser/web_contents.h"

namespace tizen {

BrowserMediaPlayerManager::BrowserMediaPlayerManager(
    content::RenderViewHost* render_view_host)
    : content::WebContentsObserver(content::WebContents::FromRenderViewHost(
          render_view_host)) {

  m_resource_manager_.reset(new MurphyResourceManager(this));

  if (m_resource_manager_ && !m_resource_manager_->isConnected()) {
    if (m_resource_manager_->connectToMurphy()) {
      m_resource_.reset(new MurphyResource(this, m_resource_manager_.get()));
    }
  }
}

BrowserMediaPlayerManager::~BrowserMediaPlayerManager() {}

BrowserMediaPlayerManager* BrowserMediaPlayerManager::Create(
    content::RenderViewHost* render_view_host) {
  return new BrowserMediaPlayerManager(render_view_host);
}

}  // namespace content
