/** The settings of a web view, as a `WebKitSettings`. */
interface WebKitGTKSettings {
  /** Whether the web inspector can be opened from the context menu. Defaults to `false`. */
  enableDeveloperExtras: boolean
}

declare class WebKitGTKSettings {
  protected constructor()
}

export = WebKitGTKSettings
