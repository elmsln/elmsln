DESCRIPTION
-----------

This module allows you to generate the following printer-friendly versions
of any node:

    * Web page printer-friendly version (at www.example.com/print/nid)
    * PDF version (at www.example.com/printpdf/nid)
    * Send by-email (at www.example.com/printmail/nid)

where nid is the node id of content to render.

A link is inserted in the each node (configurable in the content type
settings), that opens a version of the page with no sidebars, search boxes,
navigation pages, etc.

INSTALLATION
------------

Follow the instructions in the provided INSTALL.txt file.

CONFIGURATION
-------------

- There are several settings that can be configured in the following places:

  Administration > Modules (admin/modules)
    Enable or disable the module. (default: disabled)

  Administration > People > Permissions (admin/people/permissions)
    Under print module:
    access print: Enable access to the PF page and display of the PF link in
    other pages. (default: disabled)
    administer print: Enable access to the module settings page. (default:
    disabled)

  Administration > Structure > Content types (admin/structure/types)
    For each content type it is possible to enable or disable the PF link
    via the "Show printer-friendly version link" checkbox. (default:
    enabled)
    It is also possible to enable or disable the PF link in individual
    comments via the "Show printer-friendly version link in individual
    comments" checkbox. (default: disabled)

  Administration > Configuration > User interface > Printer, email and PDF versions (admin/config/user-interface/print)
    This is where all the module-specific configuration options can be set.

- To modify the template of printer friendly pages, simply edit the
print.tpl.php or the css/print.css files.

- It is possible to set per-content-type and/or theme-specific templates
  which are searched for in the following order: 
   1. print--[format]--node--[type].tpl.php in the theme directory
   2. print--[format].tpl.php in the theme directory
   3. print--node--[type].tpl.php in the theme directory
   4. print.tpl.php in the theme directory
   5. print.tpl.php in the module directory (supplied by the module)

  format is either html, mail or pdf, and type is Drupal's node type (e.g.
  page, story, etc.)

API
---

print_insert_link(), print_mail_insert_link(), print_pdf_insert_link()

The *_insert_link functions are available to content developers that prefer
to place the printer-friendly link in a custom location. It is advisable to
disable the regular Printer-friendly link so that it is not shown in both
locations.

Calling the function like this:

  print_insert_link()

will return the HTML for a link pointing to a Printer-friendly version of
the current page.

It is also possible to specify the link to the page yourself:

  print_insert_link("print/42")

will return the HTML pointing to the printer-friendly version of node 42.

THEMEABLE FUNCTIONS
-------------------

The following themeable functions are defined:

  * theme_print_format_link()
  * theme_print_mail_format_link()
  * theme_print_pdf_format_link()
      Returns an array of formatted attributes for the Printer-friendly
      link.

  * print_pdf_dompdf_footer($html)
    Format the dompdf footer contents

  * print_pdf_tcpdf_header($pdf, $html, $font)
    Format the TCPDF header

  * print_pdf_tcpdf_page($pdf)
    Format the TCPDF page settings (margins, etc)

  * print_pdf_tcpdf_content($pdf, $html, $font)
    Format the TCPDF page content

  * print_pdf_tcpdf_footer($pdf, $html, $font)
    Format the TCPDF footer contents

  * print_pdf_tcpdf_footer2($pdf)
    Format the TCPDF footer layout

MORE INFORMATION
----------------

For more information, consult the modules' documentation at
http://drupal.org/node/190171.

ACKNOWLEDGMENTS
---------------
The print, pdf and mail icons are copyright Plone Foundation. Thanks for
letting me use them!

