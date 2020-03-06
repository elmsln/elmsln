<?php
/**
 * Class for implementing web component polyfills and other header aspects in a uniform manner
 */
class WebComponentsService {
  /**
   * This applies all pieces of a standard build appended to the header
   */
  public function applyWebcomponents($directory = '/') {
    return $this->getBuild($directory);
  }
  /**
   * Front end logic for ES5-AMD, ES6-AMD, ES6 version to deliver
   */
  public function getBuild($directory  = '/', $forceUpgrade = "false") {
    return '
    <script>
      window.__appCDN="' . $directory . '";
      window.__appForceUpgrade=' . $forceUpgrade . ';
    </script>
    <script src="' . $directory . 'build.js"></script>  
    <style>hax-tray { z-index:1251;}</style>';
  }
}