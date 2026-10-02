#ifndef BARE_WEB_KIT_GTK_WEB_VIEW_H
#define BARE_WEB_KIT_GTK_WEB_VIEW_H

#include <assert.h>
#include <js.h>

#include <webkit/webkit.h>

#include "bridging.h"
#include "registry.h"

static js_value_t *
bare_web_kit_gtk_web_view_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_gobject_registry_t *registry;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &registry);
  assert(err == 0);

  GtkWidget *web_view = webkit_web_view_new();

  js_value_t *result;
  err = js_create_uint32(env, bare_gobject_tag(registry, web_view), &result);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_web_kit_gtk_web_view_load_uri(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  bare_gobject_registry_t *registry;
  err = js_get_callback_info(env, info, &argc, argv, NULL, (void **) &registry);
  assert(err == 0);

  assert(argc == 2);

  WebKitWebView *web_view;
  err = bare_gobject_read_tag(env, registry, argv[0], "webView", (gpointer *) &web_view);
  if (err < 0) return NULL;

  char *uri;
  err = bare_web_kit_gtk__read_string(env, argv[1], "uri", &uri);
  if (err < 0) return NULL;

  webkit_web_view_load_uri(web_view, uri);

  g_free(uri);

  return NULL;
}

static js_value_t *
bare_web_kit_gtk_web_view_load_html(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  bare_gobject_registry_t *registry;
  err = js_get_callback_info(env, info, &argc, argv, NULL, (void **) &registry);
  assert(err == 0);

  assert(argc == 3);

  WebKitWebView *web_view;
  err = bare_gobject_read_tag(env, registry, argv[0], "webView", (gpointer *) &web_view);
  if (err < 0) return NULL;

  char *html;
  err = bare_web_kit_gtk__read_string(env, argv[1], "html", &html);
  if (err < 0) return NULL;

  char *base_uri;
  err = bare_web_kit_gtk__read_string(env, argv[2], "baseURI", &base_uri);
  if (err < 0) {
    g_free(html);

    return NULL;
  }

  webkit_web_view_load_html(web_view, html, base_uri);

  g_free(html);
  g_free(base_uri);

  return NULL;
}

#endif // BARE_WEB_KIT_GTK_WEB_VIEW_H
