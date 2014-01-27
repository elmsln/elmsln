/**
 * If site is not being framed or being framed within the same host,
 * start commenting out seckit.no_body.css.
 */
if (top === self || top.location.hostname === self.location.hostname) {
  document.write('<!--');
}
