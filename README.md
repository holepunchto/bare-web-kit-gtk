# bare-web-kit-gtk

WebKitGTK for Bare on Linux. It gives you a web view that is an ordinary `bare-gtk` widget, so you can put it anywhere a widget goes.

```
npm i bare-web-kit-gtk
```

## Usage

```js
const { Window } = require('bare-gtk')
const { WebView } = require('bare-web-kit-gtk')

const window = new Window()

window.title = 'Browser'
window.defaultSize = [800, 600]

const webView = new WebView()

window.child = webView
window.visible = true

webView.loadURI('https://example.com')
```

## License

Apache-2.0
