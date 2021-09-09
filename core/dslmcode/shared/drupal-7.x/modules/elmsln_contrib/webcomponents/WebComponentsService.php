<?php
/**
 * Class for implementing web component polyfills and other header aspects in a uniform manner
 */
class WebComponentsService {
  /**
   * This applies all pieces of a standard build appended to the header
   */
  public function applyWebcomponents($directory = '/', $cdn = '/', $include_dedup = true) {
    return $this->getBuild($directory, "false", $cdn, $include_dedup);
  }
  /**
   * Front end logic for ES5-AMD, ES6-AMD, ES6 version to deliver
   */
  public function getBuild($directory  = '/', $forceUpgrade = "false", $cdn = '/', $include_dedup = true) {
    return '
    <script>
      window.__appCDN="' . $cdn . '";
      window.__appForceUpgrade=' . $forceUpgrade . ';' .
      ($include_dedup ? '
      // overload how define works so that we can prevent bricking issues
      // when classes get loaded from multiple sources with the same name space
      // this is a copy of the dedup-fix.js script we use in local testing / es5 routines
      const _customElementsDefine = window.customElements.define;
      window.customElements.define = (name, cl, conf) => {
        if (!customElements.get(name)) {
          _customElementsDefine.call(window.customElements, name, cl, conf);
        } else {
          console.warn(`${name} has been defined twice`);
        }
      };' : '') .'
    </script>
    <script src="' . $directory . 'build.js"></script>';
  }
}