<?php
$color = "#009d75";
if (function_exists('variable_get')) {
  $color = variable_get("haxcms_settings_hexCode", "#009d75");
}
/**
 * @file
 * Default theme implementation to display the basic html structure of a single
 * Drupal page.
*/
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN"
  "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" version="XHTML+RDFa 1.0" dir="<?php print $language->dir; ?>"<?php print $rdf_namespaces; ?>>

<head profile="<?php print $grddl_profile; ?>">
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>
<body no-js class="<?php print $classes; ?>" <?php print $attributes;?>>
<style>
    body {
      margin: 0;
      min-height: 98vh;
    }
  </style>
  <style id="loadingstyles">
    haxcms-site-builder {
      display: block;
    }
    body[no-js] haxcms-site-builder {
      display: none !important;
    }
    #loading {
      background-color: white;
      bottom: 0px;
      left: 0px;
      opacity: 1;
      position: absolute;
      right: 0px;
      top: 0px;
      transition: all linear 300ms;
      -webkit-transition: all linear 300ms;
      z-index: 99999999;
    }

    #loading.loaded {
      animation: fade-out .7s ease-in-out;
      animation-fill-mode: forwards;
    }
    #loading div.messaging {
      color: rgba(255,255,255, 0.7);
      font-family: Roboto;
      left: 0px;
      margin-top: -75px;
      position: absolute;
      right: 0px;
      text-align: center;
      top: 50%;
      transform: translateY(-50%);
    }
    #loading div.messaging h1 {
      color: white;
      font-family: 'Open Sans', 'arial', 'serif';
      font-size: 40px;
      background-color: var(--haxcms-color,<?php print $color; ?>);
      transition: .4s ease-in-out all;
    }
    #loading img {
      transition: .4s all ease-in-out;
      width: 300px;
      height: 300px;
      margin-bottom: 50px;
      border-radius: 50%;
      border: 8px solid var(--haxcms-color,<?php print $color; ?>);
      box-shadow: 0 4px 12px 0 rgba(0, 0, 0, 0.45);
      -moz-box-shadow: 0 4px 12px 0 rgba(0, 0, 0, 0.45);
	    -webkit-box-shadow: 0 4px 12px 0 rgba(0, 0, 0, 0.45);
      -ms-filter: "progid:DXImageTransform.Microsoft.Shadow(Strength=4, Direction=135, Color='#444444')";
    }
    .progress-line,
    .progress-line:before {
      height: 8px;
      width: 100%;
      margin: auto;
    }
    .progress-line {
      background-color: rgba(0,0,0, 0.05);
      display: -webkit-flex;
      display: flex;
      width: 300px;
    }
    .progress-line:before {
      background-color: var(--haxcms-color,<?php print $color; ?>);
      content: '';
      animation: running-progress 2s cubic-bezier(0.4, 0, 0.2, 1) infinite;
    }
    @keyframes running-progress {
      0% {
        margin-left: 0px;
        margin-right: 100%;
      }
      50% {
        margin-left: 25%;
        margin-right: 0%;
      }
      100% {
        margin-left: 100%;
        margin-right: 0;
      }
    }
    @keyframes fade-out {
      0% {
        opacity: 1;
      }
      99% {
        opacity: 0;
      }
      100% {
        opacity: 0;
      }
    }
    </style>
    <script id="loadingscript">
    window.addEventListener('haxcms-ready', function(e) {
      // give the web components a second to build
      setTimeout(function() {
        document.querySelector('#loading').classList.add('loaded');
        setTimeout(function() {
          document.querySelector('#loading').parentNode.removeChild(document.querySelector('#loading'));
          document.querySelector('#loadingstyles').parentNode.removeChild(document.querySelector('#loadingstyles'));
          document.querySelector('#loadingscript').parentNode.removeChild(document.querySelector('#loadingscript'));
        }, 600);
      }, 1000);
    });
  </script>
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
</body>
</html>
