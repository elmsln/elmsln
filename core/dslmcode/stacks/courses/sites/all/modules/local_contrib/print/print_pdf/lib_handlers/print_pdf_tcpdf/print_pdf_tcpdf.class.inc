<?php

/**
 * @file
 * Extend the TCPDF class to be able to customize the Footer.
 *
 * This file is included by the _print_pdf_tcpdf function.
 *
 * @ingroup print
 */

class PrintTCPDF extends TCPDF {
  public $footer;

  /**
   * Display invisible link at the bottom of all pages.
   *
   * @param string $tcpdflink
   *   TCPDF link.
   */
  public function setTcpdfLink($tcpdflink) {
    $this->tcpdflink = $tcpdflink;
  }

  /**
   * Page footer data.
   *
   * @param string $arg
   *   Footer contents.
   */
  public function setFooterContent($arg = '') {
    $this->footer = $arg;
  }

  /**
   * Page footer.
   */
  public function Footer() {
    theme('print_pdf_tcpdf_footer2', array('pdf' => $this));
  }

}
