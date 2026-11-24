const test = require('brittle')
const { WebView } = require('.')

test('rejects a URI or base URI with a NUL', (t) => {
  const view = new WebView()

  t.exception.all(() => view.loadURI('https://attacker.example\0.trusted.example'), TypeError)
  t.exception.all(
    () => view.loadHTML('<p>hello</p>', 'https://attacker.example\0.trusted.example'),
    TypeError
  )
})
