#ifndef BARE_WEB_KIT_GTK_SETTINGS_H
#define BARE_WEB_KIT_GTK_SETTINGS_H

#include <assert.h>
#include <js.h>

#include <webkit/webkit.h>

#include "bridging.h"
#include "registry.h"

static js_value_t *
bare_web_kit_gtk_settings_enable_developer_extras(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  bare_gobject_registry_t *registry;
  err = js_get_callback_info(env, info, &argc, argv, NULL, (void **) &registry);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  WebKitSettings *settings;
  err = bare_gobject_read_type(env, registry, argv[0], "settings", WEBKIT_TYPE_SETTINGS, (gpointer *) &settings);
  if (err < 0) return NULL;

  js_value_t *result = NULL;

  if (argc == 1) {
    err = js_get_boolean(env, webkit_settings_get_enable_developer_extras(settings), &result);
    assert(err == 0);
  } else {
    bool enabled;
    err = bare_web_kit_gtk__read_bool(env, argv[1], "enableDeveloperExtras", &enabled);
    if (err < 0) return NULL;

    webkit_settings_set_enable_developer_extras(settings, enabled);
  }

  return result;
}

#endif // BARE_WEB_KIT_GTK_SETTINGS_H
