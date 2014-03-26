// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef XWALK_TIZEN_BROWSER_MURPHY_RESOURCE_H_
#define XWALK_TIZEN_BROWSER_MURPHY_RESOURCE_H_

#include "base/logging.h"
#include "murphy_resource_manager.h"

namespace tizen {

enum MurphyResourceState {
    MURPHY_RESOURCE_LOST,
    MURPHY_RESOURCE_PENDING,
    MURPHY_RESOURCE_ACQUIRED,
    MURPHY_RESOURCE_AVAILABLE,
};

class MurphyResource {
public:
    MurphyResource(BrowserMediaPlayerManager* manager, MurphyResourceManager* resource_manager);
    ~MurphyResource();

    void acquireResource();
    void releaseResource();

    MurphyResourceState getResourceState();

private:
    BrowserMediaPlayerManager*  manager_;
    MurphyResourceManager* resource_manager_;

    mrp_res_resource_set_t *m_rset_;
    mrp_res_resource_t *m_resource_;

};

}

#endif // XWALK_TIZEN_BROWSER_MURPHY_RESOURCE_H_
