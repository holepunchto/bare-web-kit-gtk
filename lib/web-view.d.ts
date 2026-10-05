import GTKWidget = require('bare-gtk/widget')
import WebKitGTKSettings = require('./settings')

/** A widget that shows web content with WebKitGTK, as a `WebKitWebView`. */
interface WebKitGTKWebView extends GTKWidget {
  readonly settings: WebKitGTKSettings

  /** Load `uri`. */
  loadURI(uri: string): this

  /**
   * Load `html` as the page. Relative links resolve against `baseURI`, which defaults to
   * `about:blank`.
   */
  loadHTML(html: string, baseURI?: string): this
}

declare class WebKitGTKWebView {
  /** Create a web view with nothing loaded. */
  constructor()
}

export = WebKitGTKWebView
