<?php


namespace Drupal\xautoload\Tests\Util;


class HackyLog {

  /**
   * @throws \Exception
   */
  static function log() {
    $args = func_get_args();
    $err = fopen('php://stderr', 'w');
    fwrite($err, var_export($args, TRUE));
    fclose($err);
  }

  static function logx() {
    $args = func_get_args();
    throw new \Exception(var_export($args, TRUE));
  }
} 
