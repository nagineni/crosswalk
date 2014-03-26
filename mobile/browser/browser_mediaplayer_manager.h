// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef XWALK_TIZEN_BROWSER_BROWSER_MEDIAPLAYER_MANAGER_H_
#define XWALK_TIZEN_BROWSER_BROWSER_MEDIAPLAYER_MANAGER_H_

#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "content/public/browser/web_contents_observer.h"
#include "url/gurl.h"
#include "xwalk/mobile/browser/murphy_resource_manager.h"
#include "xwalk/mobile/browser/murphy_resource.h"


namespace tizen {

// This class manages all AudioSessionManager objects in the browser
// process. It receives control operations from the render process, and
// forwards them to corresponding AudioSessionManager object. Callbacks
// from AudioSessionManager objects are converted to IPCs and then sent
// to the render process.
class CONTENT_EXPORT BrowserMediaPlayerManager
    : public content::WebContentsObserver {
 public:
  virtual ~BrowserMediaPlayerManager();

  // Returns a new instance.
  static BrowserMediaPlayerManager* Create(
      content::RenderViewHost* render_view_host);

 protected:
  explicit BrowserMediaPlayerManager(content::RenderViewHost* render_view_host);


 private:
  scoped_ptr<MurphyResourceManager> m_resource_manager_;
  scoped_ptr<MurphyResource> m_resource_;

  DISALLOW_COPY_AND_ASSIGN(BrowserMediaPlayerManager);
};

}  // namespace tizen

#endif  // XWALK_TIZEN_BROWSER_BROWSER_MEDIAPLAYER_MANAGER_H_
