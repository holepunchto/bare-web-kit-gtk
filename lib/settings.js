const binding = require('../binding')

module.exports = exports = class WebKitGTKSettings {
  constructor(opts = {}) {
    const { tag = null } = opts

    if (tag === null) throw new TypeError('WebKitGTKSettings cannot be constructed directly')

    this._settings = tag

    this._settingsToken = binding.claim(this._settings, this)
  }

  get enableDeveloperExtras() {
    return binding.settingsEnableDeveloperExtras(this._settings)
  }

  set enableDeveloperExtras(value) {
    binding.settingsEnableDeveloperExtras(this._settings, value)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WebKitGTKSettings },

      enableDeveloperExtras: this.enableDeveloperExtras
    }
  }
}
