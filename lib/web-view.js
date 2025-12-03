const GTKWidget = require('bare-gtk').Widget
const binding = require('../binding')

module.exports = exports = class WebKitGTKWebView extends GTKWidget {
  constructor(opts = {}) {
    super()

    this._handle = binding.webViewInit(this)
  }

  loadURI(uri) {
    binding.webViewLoadURI(this._handle, uri)
    return this
  }

  loadHTML(html, baseURI = 'about:blank') {
    binding.webViewLoadHTML(this._handle, html, baseURI)
    return this
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WebKitGTKWebView }
    }
  }
}
