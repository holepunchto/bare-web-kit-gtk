#include <assert.h>
#include <bare.h>
#include <js.h>
#include <utf.h>

#include <webkit/webkit.h>

#include "lib/web-view.h"

static js_value_t *
bare_web_kit_gtk_exports(js_env_t *env, js_value_t *exports) {
  int err;

#define V(name, fn) \
  { \
    js_value_t *val; \
    err = js_create_function(env, name, -1, fn, NULL, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }

  V("webViewInit", bare_web_kit_gtk_web_view_init)
#undef V

#define V(name, n) \
  { \
    js_value_t *val; \
    err = js_create_int32(env, n, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }
#undef V

  return exports;
}

BARE_MODULE(bare_web_kit_gtk, bare_web_kit_gtk_exports)
