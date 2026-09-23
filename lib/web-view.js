const GTKWidget = require('bare-gtk').Widget
const binding = require('../binding')

module.exports = exports = class WebKitGTKWebView extends GTKWidget {
  _init(opts) {
    this._webView = binding.webViewInit()

    this._webViewToken = binding.claim(this._webView, this)

    return binding.handle(this._webView)
  }

  loadURI(uri) {
    binding.webViewLoadURI(this._webView, uri)

    return this
  }

  loadHTML(html, baseURI = 'about:blank') {
    binding.webViewLoadHTML(this._webView, html, baseURI)

    return this
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WebKitGTKWebView }
    }
  }
}
