<?php
/**
 * Class for implementing web component polyfills and other header aspects in a uniform manner
 */
class WebComponentsService {
  /**
   * This applies all pieces of a standard build appended to the header
   */
  public function applyWebcomponents($directory = '/') {
    return 
      $this->getPolyfill($directory) .
      $this->getBabel($directory) .
      $this->getBuild($directory);
  }
  /**
   * Return the polyfill standard method of application
   */
  public function getPolyfill($directory = '/') {
    return '<!-- cross platform polyfill -->
    <script>if (!window.customElements) { document.write("<!--") }</script>
    <script defer="defer" type="text/javascript" src="' . $directory . 'build/es6/node_modules/@webcomponents/webcomponentsjs/custom-elements-es5-adapter.js"></script>
    <!--! do not remove -->
    <script defer="defer" src="' . $directory . 'build/es6/node_modules/@webcomponents/webcomponentsjs/webcomponents-loader.js"></script>
    <script defer="defer" src="' . $directory . 'build/es6/node_modules/web-animations-js/web-animations-next-lite.min.js"></script>
    <!-- / cross platform polyfill -->';  
  }
  /**
   * Get babel helpers to ensure compiled versions have appropriate functions
   */
  public function getBabel($directory = '/') {
    return '<!-- babel -->
    <script src="' . $directory . 'babel/babel-top.js"></script>
    <script src="' . $directory . 'babel/babel-bottom.js"></script>
    <!-- / babel -->';
  }

  /**
   * Front end logic for ES5 or ES6 version to deliver
   */
  public function getBuild($directory  = '/') {
    return '<!-- web component build -->
    <script nomodule>window.nomodule = true;</script>
    <script>
      function __supportsImports() { try { new Function(\'import("")\'); return true; } catch (err) { return false; } }
      // lack of es modules or dynamic imports requires amd-es5 bundle
      if (window.nomodule || !__supportsImports()) {
        define(["' . $directory . 'build/es5-amd/build.js"], function () { "use strict" });
        document.write("<!--")
      }
    </script>
    <script type="module" defer="defer" src="' . $directory . 'build/es6/build.js"></script>
    <!--! do not remove -->
    <!-- / web component build -->';
  }
}