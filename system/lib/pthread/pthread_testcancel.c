/*
 * Copyright 2021 The Emscripten Authors.  All rights reserved.
 * Emscripten is available under two separate licenses, the MIT license and the
 * University of Illinois/NCSA Open Source License.  Both these licenses can be
 * found in the LICENSE file.
 */

#define _GNU_SOURCE
#include "pthread_impl.h"
#include <pthread.h>

int _pthread_isduecanceled(struct pthread* pthread_ptr) {
  return pthread_ptr->threadStatus == 2 /*canceled*/;
}

void __pthread_testcancel() {
  struct pthread* self = pthread_self();
  if (self->canceldisable)
    return;
  if (_pthread_isduecanceled(self)) {
    EM_ASM(throw 'Canceled!');
  }
}

weak_alias(__pthread_testcancel, pthread_testcancel);
