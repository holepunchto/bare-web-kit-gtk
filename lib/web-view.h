#include <assert.h>
#include <bare.h>
#include <js.h>
#include <stdlib.h>

#include <webkit/webkit.h>

typedef struct {
  WebKitWebView handle;

  js_env_t *env;
  js_ref_t *ctx;
} BareWebView;

typedef struct {
  WebKitWebViewClass parent;
} BareWebViewClass;

G_DEFINE_TYPE(BareWebView, bare_web_view, WEBKIT_TYPE_WEB_VIEW)

static void
bare_web_view_init(BareWebView *self) {}

BareWebView *
bare_web_view_new(void) {
  return g_object_new(bare_web_view_get_type(), NULL);
}

static void
bare_web_view_finalize(GObject *object) {
  int err;

  BareWebView *self = (BareWebView *) object;

  js_env_t *env = self->env;

  err = js_delete_reference(env, self->ctx);
  assert(err == 0);

  G_OBJECT_CLASS(bare_web_view_parent_class)->finalize(object);
}

static void
bare_web_view_class_init(BareWebViewClass *class) {
  GObjectClass *object_class = G_OBJECT_CLASS(class);

  object_class->finalize = bare_web_view_finalize;
}

static void
bare_web_view__on_release(js_env_t *env, void *data, void *finalize_hint) {
  g_object_unref(data);
}

static js_value_t *
bare_web_kit_gtk_web_view_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  BareWebView *web_view = bare_web_view_new();

  web_view->env = env;

  err = js_create_reference(env, argv[0], 1, &web_view->ctx);
  assert(err == 0);

  js_value_t *handle;
  err = js_create_external(env, web_view, bare_web_view__on_release, NULL, &handle);
  assert(err == 0);

  return handle;
}

static js_value_t *
bare_web_kit_gtk_web_view_load_uri(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 2);

  BareWebView *web_view;
  err = js_get_value_external(env, argv[0], (void **) &web_view);
  assert(err == 0);

  size_t uri_len;
  err = js_get_value_string_utf8(env, argv[1], NULL, 0, &uri_len);
  assert(err == 0);

  uri_len += 1 /* NULL */;

  utf8_t *uri = malloc(uri_len);
  err = js_get_value_string_utf8(env, argv[1], uri, uri_len, NULL);
  assert(err == 0);

  webkit_web_view_load_uri(WEBKIT_WEB_VIEW(web_view), (gchar *) uri);

  free(uri);

  return NULL;
}

static js_value_t *
bare_web_kit_gtk_web_view_load_html(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 3);

  BareWebView *web_view;
  err = js_get_value_external(env, argv[0], (void **) &web_view);
  assert(err == 0);

  size_t html_len;
  err = js_get_value_string_utf8(env, argv[1], NULL, 0, &html_len);
  assert(err == 0);

  html_len += 1 /* NULL */;

  utf8_t *html = malloc(html_len);
  err = js_get_value_string_utf8(env, argv[1], html, html_len, NULL);
  assert(err == 0);

  size_t base_uri_len;
  err = js_get_value_string_utf8(env, argv[2], NULL, 0, &base_uri_len);
  assert(err == 0);

  base_uri_len += 1 /* NULL */;

  utf8_t *base_uri = malloc(base_uri_len);
  err = js_get_value_string_utf8(env, argv[2], base_uri, base_uri_len, NULL);
  assert(err == 0);

  webkit_web_view_load_html(WEBKIT_WEB_VIEW(web_view), (gchar *) html, (gchar *) base_uri);

  free(html);
  free(base_uri);

  return NULL;
}
