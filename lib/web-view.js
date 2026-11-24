const GTKWidget = require('bare-gtk/widget')
const binding = require('../binding')
const WebKitGTKSettings = require('./settings')

module.exports = exports = class WebKitGTKWebView extends GTKWidget {
  _init(opts) {
    this._webView = binding.webViewInit()

    this._webViewToken = binding.claim(this._webView, this)

    return binding.handle(this._webView)
  }

  get settings() {
    const tag = binding.webViewSettings(this._webView)

    return binding.wrapper(tag) || new WebKitGTKSettings({ tag })
  }

  loadURI(uri) {
    validateNoNullBytes(uri, 'uri')

    binding.webViewLoadURI(this._webView, uri)

    return this
  }

  loadHTML(html, baseURI = 'about:blank') {
    validateNoNullBytes(html, 'html')
    validateNoNullBytes(baseURI, 'baseURI')

    binding.webViewLoadHTML(this._webView, html, baseURI)

    return this
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WebKitGTKWebView }
    }
  }
}

// The value is passed on as a C string, so a NUL would cut it short.
function validateNoNullBytes(value, name) {
  if (typeof value === 'string' && value.includes('\0')) {
    throw new TypeError(`The "${name}" argument must not contain null bytes`)
  }
}
