<?php

/**
 * @file Include this file whenever you have to use imageconvolution.
 *
 * You can use in your project, but keep the comment below:
 *   Great for any image manipulation library
 *   Made by Chao Xu(Mgccl) 3/1/07
 *   www.webdevlogs.com
 *   V 1.0
 */
if (!function_exists('imagefilter')) {
  /**
   * Applies a filter to an image.
   *
   * @link http://php.net/manual/en/function.imagefilter.php
   *
   * @param resource $image
   * @param int $filtertype
   *   One of the IMG_FILTER_ constants
   * @param int $arg1
   *   [optional] IMG_FILTER_BRIGHTNESS: Brightness level.
   * @param int $arg2
   *   [optional] IMG_FILTER_COLORIZE: Value of green component.
   * @param int $arg3
   *   [optional] IMG_FILTER_COLORIZE: Value of blue component.
   * param int $arg4
   *   [optional] IMG_FILTER_COLORIZE: Alpha channel, A value between 0 and 127.
   *   0 indicates completely opaque while 127 indicates completely transparent.
   *   This implementation does not use this parameter.
   *
   * @return bool
   *   true on success or false on failure.
   */
  function imagefilter($image, $filtertype, $arg1 = NULL, $arg2 = NULL, $arg3 = NULL) {
    // define('IMAGE_FILTER_NEGATE', 0);
    // define('IMAGE_FILTER_GRAYSCALE', 1);
    // define('IMAGE_FILTER_BRIGHTNESS', 2);
    // define('IMAGE_FILTER_CONTRAST', 3);
    // define('IMAGE_FILTER_COLORIZE', 4);
    // define('IMAGE_FILTER_EDGEDETECT', 5);
    // define('IMAGE_FILTER_EMBOSS', 6);
    // define('IMAGE_FILTER_GAUSSIAN_BLUR', 7);
    // define('IMAGE_FILTER_SELECTIVE_BLUR', 8);
    // define('IMAGE_FILTER_MEAN_REMOVAL', 9);
    // define('IMAGE_FILTER_SMOOTH', 10);
    // define('IMG_FILTER_PIXELATE', 11);
    $max_y = imagesy($image);
    $max_x = imagesx($image);
    switch ($filtertype) {
      case 0:
        $y = 0;
        while ($y < $max_y) {
          $x = 0;
          while ($x < $max_x) {
            $rgb = imagecolorat($image, $x, $y);
            $r = 255 - (($rgb >> 16) & 0xFF);
            $g = 255 - (($rgb >> 8) & 0xFF);
            $b = 255 - ($rgb & 0xFF);
            $a = $rgb >> 24;
            $new_pxl = imagecolorallocatealpha($image, $r, $g, $b, $a);
            if ($new_pxl == FALSE) {
              $new_pxl = imagecolorclosestalpha($image, $r, $g, $b, $a);
            }
            imagesetpixel($image, $x, $y, $new_pxl);
            ++$x;
          }
          ++$y;
        }
        return TRUE;

      case 1:
        $y = 0;
        while ($y < $max_y) {
          $x = 0;
          while ($x < $max_x) {
            $rgb = imagecolorat($image, $x, $y);
            $a = $rgb >> 24;
            $r = ((($rgb >> 16) & 0xFF) * 0.299) + ((($rgb >> 8) & 0xFF) * 0.587) + (($rgb & 0xFF) * 0.114);
            $new_pxl = imagecolorallocatealpha($image, $r, $r, $r, $a);
            if ($new_pxl == FALSE) {
              $new_pxl = imagecolorclosestalpha($image, $r, $r, $r, $a);
            }
            imagesetpixel($image, $x, $y, $new_pxl);
            ++$x;
          }
          ++$y;
        }
        return TRUE;

      case 2:
        $y = 0;
        while ($y < $max_y) {
          $x = 0;
          while ($x < $max_x) {
            $rgb = imagecolorat($image, $x, $y);
            $r = (($rgb >> 16) & 0xFF) + $arg1;
            $g = (($rgb >> 8) & 0xFF) + $arg1;
            $b = ($rgb & 0xFF) + $arg1;
            $a = $rgb >> 24;
            $r = ($r > 255) ? 255 : (($r < 0) ? 0 : $r);
            $g = ($g > 255) ? 255 : (($g < 0) ? 0 : $g);
            $b = ($b > 255) ? 255 : (($b < 0) ? 0 : $b);
            $new_pxl = imagecolorallocatealpha($image, $r, $g, $b, $a);
            if ($new_pxl == FALSE) {
              $new_pxl = imagecolorclosestalpha($image, $r, $g, $b, $a);
            }
            imagesetpixel($image, $x, $y, $new_pxl);
            ++$x;
          }
          ++$y;
        }
        return TRUE;

      case 3:
        $contrast = pow((100 - $arg1) / 100, 2);
        $y = 0;
        while ($y < $max_y) {
          $x = 0;
          while ($x < $max_x) {
            $rgb = imagecolorat($image, $x, $y);
            $a = $rgb >> 24;
            $r = (((((($rgb >> 16) & 0xFF) / 255) - 0.5) * $contrast) + 0.5) * 255;
            $g = (((((($rgb >> 8) & 0xFF) / 255) - 0.5) * $contrast) + 0.5) * 255;
            $b = ((((($rgb & 0xFF) / 255) - 0.5) * $contrast) + 0.5) * 255;
            $r = ($r > 255) ? 255 : (($r < 0) ? 0 : $r);
            $g = ($g > 255) ? 255 : (($g < 0) ? 0 : $g);
            $b = ($b > 255) ? 255 : (($b < 0) ? 0 : $b);
            $new_pxl = imagecolorallocatealpha($image, $r, $g, $b, $a);
            if ($new_pxl == FALSE) {
              $new_pxl = imagecolorclosestalpha($image, $r, $g, $b, $a);
            }
            imagesetpixel($image, $x, $y, $new_pxl);
            ++$x;
          }
          ++$y;
        }
        return TRUE;

      case 4:
        $x = 0;
        while ($x < $max_x) {
          $y = 0;
          while ($y < $max_y) {
            $rgb = imagecolorat($image, $x, $y);
            $r = (($rgb >> 16) & 0xFF) + $arg1;
            $g = (($rgb >> 8) & 0xFF) + $arg2;
            $b = ($rgb & 0xFF) + $arg3;
            $a = $rgb >> 24;
            $r = ($r > 255) ? 255 : (($r < 0) ? 0 : $r);
            $g = ($g > 255) ? 255 : (($g < 0) ? 0 : $g);
            $b = ($b > 255) ? 255 : (($b < 0) ? 0 : $b);
            $new_pxl = imagecolorallocatealpha($image, $r, $g, $b, $a);
            if ($new_pxl == FALSE) {
              $new_pxl = imagecolorclosestalpha($image, $r, $g, $b, $a);
            }
            imagesetpixel($image, $x, $y, $new_pxl);
            ++$y;
          }
          ++$x;
        }
        return TRUE;

      case 5:
        return imageconvolution($image, array(
          array(-1, 0, -1),
          array(0, 4, 0),
          array(-1, 0, -1),
        ), 1, 127);

      case 6:
        return imageconvolution($image, array(
          array(1.5, 0, 0),
          array(0, 0, 0),
          array(0, 0, -1.5),
        ), 1, 127);

      case 7:
        return imageconvolution($image, array(
          array(1, 2, 1),
          array(2, 4, 2),
          array(1, 2, 1),
        ), 16, 0);

      case 8:
        for ($y = 0; $y < $max_y; $y++) {
          for ($x = 0; $x < $max_x; $x++) {
            $flt_r_sum = $flt_g_sum = $flt_b_sum = 0;
            $cpxl = imagecolorat($image, $x, $y);
            for ($j = 0; $j < 3; $j++) {
              for ($i = 0; $i < 3; $i++) {
                if (($j == 1) && ($i == 1)) {
                  $flt_r[1][1] = $flt_g[1][1] = $flt_b[1][1] = 0.5;
                }
                else {
                  $pxl = imagecolorat($image, $x - (3 >> 1) + $i, $y - (3 >> 1) + $j);

                  $new_a = $pxl >> 24;
                  // $r = (($pxl >> 16) & 0xFF);
                  // $g = (($pxl >> 8) & 0xFF);
                  // $b = ($pxl & 0xFF);
                  $new_r = abs((($cpxl >> 16) & 0xFF) - (($pxl >> 16) & 0xFF));
                  if ($new_r != 0) {
                    $flt_r[$j][$i] = 1 / $new_r;
                  }
                  else {
                    $flt_r[$j][$i] = 1;
                  }

                  $new_g = abs((($cpxl >> 8) & 0xFF) - (($pxl >> 8) & 0xFF));
                  if ($new_g != 0) {
                    $flt_g[$j][$i] = 1 / $new_g;
                  }
                  else {
                    $flt_g[$j][$i] = 1;
                  }

                  $new_b = abs(($cpxl & 0xFF) - ($pxl & 0xFF));
                  if ($new_b != 0) {
                    $flt_b[$j][$i] = 1 / $new_b;
                  }
                  else {
                    $flt_b[$j][$i] = 1;
                  }
                }

                $flt_r_sum += $flt_r[$j][$i];
                $flt_g_sum += $flt_g[$j][$i];
                $flt_b_sum += $flt_b[$j][$i];
              }
            }

            for ($j = 0; $j < 3; $j++) {
              for ($i = 0; $i < 3; $i++) {
                if ($flt_r_sum != 0) {
                  $flt_r[$j][$i] /= $flt_r_sum;
                }
                if ($flt_g_sum != 0) {
                  $flt_g[$j][$i] /= $flt_g_sum;
                }
                if ($flt_b_sum != 0) {
                  $flt_b[$j][$i] /= $flt_b_sum;
                }
              }
            }

            $new_r = $new_g = $new_b = 0;

            for ($j = 0; $j < 3; $j++) {
              for ($i = 0; $i < 3; $i++) {
                $pxl = imagecolorat($image, $x - (3 >> 1) + $i, $y - (3 >> 1) + $j);
                $new_r += (($pxl >> 16) & 0xFF) * $flt_r[$j][$i];
                $new_g += (($pxl >> 8) & 0xFF) * $flt_g[$j][$i];
                $new_b += ($pxl & 0xFF) * $flt_b[$j][$i];
              }
            }

            $new_r = ($new_r > 255) ? 255 : (($new_r < 0) ? 0 : $new_r);
            $new_g = ($new_g > 255) ? 255 : (($new_g < 0) ? 0 : $new_g);
            $new_b = ($new_b > 255) ? 255 : (($new_b < 0) ? 0 : $new_b);
            $new_pxl = imagecolorallocatealpha($image, (int) $new_r, (int) $new_g, (int) $new_b, $new_a);
            if ($new_pxl == FALSE) {
              $new_pxl = imagecolorclosestalpha($image, (int) $new_r, (int) $new_g, (int) $new_b, $new_a);
            }
            imagesetpixel($image, $x, $y, $new_pxl);
          }
        }
        return TRUE;

      case 9:
        return imageconvolution($image, array(
          array(-1, -1, -1),
          array(-1, 9, -1),
          array(-1, -1, -1),
        ), 1, 0);

      case 10:
        return imageconvolution($image, array(
          array(1, 1, 1),
          array(1, $arg1, 1),
          array(1, 1, 1),
        ), $arg1 + 8, 0);

      case 11:
      default:
        watchdog('imagecache_actions', 'Image filter failed: unknown filter type: %filtertype',
          array('%filtertype' => $filtertype),
          WATCHDOG_ERROR);
        return FALSE;
    }
  }
}
