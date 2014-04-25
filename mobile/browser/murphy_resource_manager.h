// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef XWALK_TIZEN_BROWSER_MURPHY_RESOURCE_MANAGER_H_
#define XWALK_TIZEN_BROWSER_MURPHY_RESOURCE_MANAGER_H_

#include "base/logging.h"
#include <murphy/common.h>
#include <murphy/glib/glib-glue.h>
#include <murphy/plugins/resource-native/libmurphy-resource/resource-api.h>

#include "murphy_mainloop.h"

namespace tizen {
class BrowserMediaPlayerManager;

enum MurphyConnectionEvent {
    MURPHY_DISCONNECTED,
    MURPHY_CONNECTED
};

class MurphyResourceManager {

public:
    MurphyResourceManager(BrowserMediaPlayerManager* manager);
    virtual ~MurphyResourceManager();

    bool connectToMurphy();
    void disconnectFromMurphy();
    bool startReconnect();
    void stopReconnect();
    bool isConnected();
    mrp_res_context_t * getContext();

private:
    BrowserMediaPlayerManager*  manager_;
    MurphyMainloop *mainloop_;
    mrp_mainloop_t *ml_;
    mrp_res_context_t *ctx_;
    mrp_timer_t *reconnect_;
};

}

#endif // XWALK_TIZEN_BROWSER_MURPHY_RESOURCE_MANAGER_H_
