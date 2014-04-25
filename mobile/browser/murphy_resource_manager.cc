// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "murphy_mainloop.h"
#include "murphy_resource_manager.h"

#include "xwalk/mobile/browser/browser_mediaplayer_manager.h"

namespace tizen {

MurphyResourceManager::MurphyResourceManager(BrowserMediaPlayerManager* manager)
    : manager_(manager),
      mainloop_(new MurphyMainloop()),
      ml_(NULL),
      ctx_(NULL),
      reconnect_(NULL)
 {
  ml_ = mainloop_->getMainloop();
  connectToMurphy();
}

MurphyResourceManager::~MurphyResourceManager() {
  disconnectFromMurphy();

  if (ctx_)
    mrp_res_destroy(ctx_);

  delete mainloop_;
}


static void state_cb(mrp_res_context_t *cx, mrp_res_error_t err, void *userdata)
{
  MurphyResourceManager *m = static_cast<MurphyResourceManager *>(userdata);

  if (err) {
    printf("*** %s: resource connection down (error %d)\n", __FUNCTION__,
           err);
    m->startReconnect();
  }
  else {
    printf("*** %s: resource connection up\n", __FUNCTION__);
    m->stopReconnect();
  }

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


static void reconnect_cb(mrp_timer_t *t, void *user_data)
{
  MurphyResourceManager *m = static_cast<MurphyResourceManager *>(user_data);

  m->connectToMurphy();
}


bool MurphyResourceManager::startReconnect()
{
  if (reconnect_)
    return true;

  reconnect_ = mrp_add_timer(ml_, 5000, reconnect_cb, this);

  return reconnect_ != NULL;
}


void MurphyResourceManager::stopReconnect()
{
  mrp_del_timer(reconnect_);
  reconnect_ = NULL;
}


bool MurphyResourceManager::connectToMurphy()
{
  if (ctx_) {
    mrp_res_destroy(ctx_);
    ctx_ = NULL;
  }

  if (!ctx_)
    ctx_ = mrp_res_create(ml_, state_cb, this);

  return ctx_ != NULL;
}

bool MurphyResourceManager::isConnected()
{
  if (!ctx_)
    return FALSE;

  return ctx_->state == MRP_RES_CONNECTED;
}


void MurphyResourceManager::disconnectFromMurphy()
{
  if (!ctx_)
    return;

  mrp_res_destroy(ctx_);
  ctx_ = NULL;
}

mrp_res_context_t * MurphyResourceManager::getContext()
{
    return ctx_;
}

}
