<?php

/**
 * @file
 * Main API entry point for the Printer, email and PDF versions
 *
 * @ingroup print
 */

/**
 * @defgroup print Files
 *
 * Files used by the print module, grouped by sub-module
 *
 * - Printer-friendly pages
 *   - @link print.api.php API @endlink
 *   - @link print.module Module main file @endlink
 *   - @link print.pages.inc HTML generation @endlink
 *   - @link print.admin.inc Settings form @endlink
 *   - @link print.install (Un)Install routines @endlink
 *   - @link print.tpl.php Page generation template @endlink
 *   - @link print.views.inc Views integration @endlink
 *   - @link print_join_page_counter.inc Views join handler @endlink
 * - Send by email
 *   - @link print_mail.module Module main file @endlink
 *   - @link print_mail.inc Mail form and send mail routine @endlink
 *   - @link print_mail.admin.inc Settings form @endlink
 *   - @link print_mail.install (Un)Install routines @endlink
 *   - @link print_mail.views.inc Views integration @endlink
 * - PDF version
 *   - @link print_pdf.api.php API @endlink
 *   - @link print_pdf.module Module main file @endlink
 *   - @link print_pdf.pages.inc PDF generation @endlink
 *   - @link print_pdf.admin.inc Settings form @endlink
 *   - @link print_pdf.install (Un)Install routines @endlink
 *   - @link print_pdf.drush.inc Drush commands @endlink
 *   - @link print_pdf.views.inc Views integration @endlink
 *   - PDF library handlers:
 *     - dompdf
 *       - @link print_pdf_dompdf.module Module main file @endlink
 *       - @link print_pdf_dompdf.pages.inc PDF generation @endlink
 *       - @link print_pdf_dompdf.admin.inc Settings form @endlink
 *       - @link print_pdf_dompdf.install (Un)Install routines @endlink
 *       - @link print_pdf_dompdf.drush.inc Drush commands @endlink
 *     - mPDF
 *       - @link print_pdf_mpdf.module Module main file @endlink
 *       - @link print_pdf_mpdf.pages.inc PDF generation @endlink
 *       - @link print_pdf_mpdf.drush.inc Drush commands @endlink
 *     - TCPDF
 *       - @link print_pdf_tcpdf.module Module main file @endlink
 *       - @link print_pdf_tcpdf.pages.inc PDF generation @endlink
 *       - @link print_pdf_tcpdf.admin.inc Settings form @endlink
 *       - @link print_pdf_tcpdf.install (Un)Install routines @endlink
 *       - @link print_pdf_tcpdf.class.inc Auxiliary PHP5 class @endlink
 *       - @link print_pdf_tcpdf.drush.inc Drush commands @endlink
 *     - wkhtmltopdf
 *       - @link print_pdf_wkhtmltopdf.module Module main file @endlink
 *       - @link print_pdf_wkhtmltopdf.pages.inc PDF generation @endlink
 *       - @link print_pdf_wkhtmltopdf.admin.inc Settings form @endlink
 *       - @link print_pdf_wkhtmltopdf.install (Un)Install routines @endlink
 *       - @link print_pdf_wkhtmltopdf.drush.inc Drush commands @endlink
 * - EPUB version
 *   - @link print_epub.api.php API @endlink
 *   - @link print_epub.module Module main file @endlink
 *   - @link print_epub.pages.inc EPUB generation @endlink
 *   - @link print_epub.admin.inc Settings form @endlink
 *   - @link print_epub.install (Un)Install routines @endlink
 *   - @link print_epub.drush.inc Drush commands @endlink
 *   - @link print_epub.views.inc Views integration @endlink
 *   - EPUB library handlers:
 *     - phpepub
 *       - @link print_epub_phpepub.module Module main file @endlink
 *       - @link print_epub_phpepub.pages.inc EPUB generation @endlink
 *       - @link print_epub_phpepub.drush.inc Drush commands @endlink
 * - User Interface (Links)
 *   - @link print_ui.api.php API @endlink
 *   - @link print_ui.module Module main file @endlink
 *   - @link print_ui.admin.inc Settings form @endlink
 */

/**
 * @defgroup print_hooks Hooks
 *
 * Hooks used in the print module
 */

/**
 * @defgroup print_themeable Themeable functions
 *
 * Default theme implementations of the print module
 */

/**
 * @defgroup print_api API
 *
 * Functions that are provided for use by third-party code.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Alters the URL in the URL list.
 *
 * This hook is useful for third-party modules that would prefer to display
 * something other than the naked URL in the URL list (e.g. glossary terms,
 * etc.).
 *
 * @param string $url
 *   the url to be modified.
 *
 * @ingroup print_hooks
 */
function hook_print_url_list_alter(&$url) {
  $url = 'foo';
}

/**
 * @} End of "addtogroup hooks".
 */
