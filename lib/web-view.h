#include <assert.h>
#include <bare.h>
#include <js.h>

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
  BareWebView *self = (BareWebView *) object;

  G_OBJECT_CLASS(bare_web_view_parent_class)->finalize(object);
}

static void
bare_web_view_class_init(BareWebViewClass *class) {
  GObjectClass *object_class = G_OBJECT_CLASS(class);

  object_class->finalize = bare_web_view_finalize;
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
  err = js_create_external(env, web_view, NULL, NULL, &handle);
  assert(err == 0);

  return handle;
}
