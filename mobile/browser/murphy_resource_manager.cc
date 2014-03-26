// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "murphy_resource_manager.h"

#include "xwalk/mobile/browser/browser_mediaplayer_manager.h"

namespace tizen {

MurphyResourceManager::MurphyResourceManager(BrowserMediaPlayerManager* manager)
    : manager_(manager),
      m_ctx(NULL) {
  m_ml = mrp_mainloop_glib_get(NULL);
}

MurphyResourceManager::~MurphyResourceManager() {
  disconnectFromMurphy();

  if (m_ctx)
    mrp_res_destroy(m_ctx);
}

static void state_cb(mrp_res_context_t *cx, mrp_res_error_t err, void *userdata)
{
  printf("===%s==\n", __FUNCTION__);
#if 0
    MurphyResourceManager *m = (MurphyResourceManager *) userdata;
    Vector<MurphyObserver *> observers = m->getObservers();

    if (err != MRP_RES_ERROR_NONE) {
        // TODO: better error handling
        return;
    }

    for (uint i = 0; i < observers.size(); i++) {
        MurphyObserver *observer = observers[i];
        enum MurphyConnectionEvent evt = MURPHY_DISCONNECTED;
        switch(cx->state) {
            case MRP_RES_CONNECTED:
                evt = MURPHY_CONNECTED;
                break;
            case MRP_RES_DISCONNECTED:
                evt = MURPHY_DISCONNECTED;
                break;
        }
        observer->murphyNotify(evt);
    }
#endif
}

bool MurphyResourceManager::connectToMurphy()
{
  if (!m_ml)
    return FALSE;

  if (!m_ctx)
    m_ctx = mrp_res_create(m_ml, state_cb, this);

  return m_ctx != NULL;
}

bool MurphyResourceManager::isConnected()
{
  if (!m_ctx)
    return FALSE;

  return m_ctx->state == MRP_RES_CONNECTED;
}


void MurphyResourceManager::disconnectFromMurphy()
{
  if (!m_ctx)
    return;

  mrp_res_destroy(m_ctx);
  m_ctx = NULL;
}

mrp_res_context_t * MurphyResourceManager::getContext()
{
    return m_ctx;
}

}
