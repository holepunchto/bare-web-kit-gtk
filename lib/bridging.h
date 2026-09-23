#ifndef BARE_WEB_KIT_GTK_BRIDGING_H
#define BARE_WEB_KIT_GTK_BRIDGING_H

#include <assert.h>
#include <glib.h>
#include <js.h>
#include <stdbool.h>
#include <utf.h>

static int
bare_web_kit_gtk__read_string(js_env_t *env, js_value_t *value, const char *name, char **result) {
  int err;

  bool is;
  err = js_is_string(env, value, &is);
  assert(err == 0);

  if (!is) {
    err = js_throw_type_errorf(env, NULL, "Expected '%s' to be a string", name);
    assert(err == 0);

    return -1;
  }

  size_t len;
  err = js_get_value_string_utf8(env, value, NULL, 0, &len);
  assert(err == 0);

  char *str = g_malloc(len + 1);

  err = js_get_value_string_utf8(env, value, (utf8_t *) str, len + 1, NULL);
  assert(err == 0);

  *result = str;

  return 0;
}

#endif // BARE_WEB_KIT_GTK_BRIDGING_H
