const GTKWidget = require('bare-gtk').Widget
const binding = require('../binding')

module.exports = exports = class WebKitGTKWebView extends GTKWidget {
  constructor(opts = {}) {
    super()

    this._handle = binding.webViewInit(this)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WebKitGTKWebView }
    }
  }
}
