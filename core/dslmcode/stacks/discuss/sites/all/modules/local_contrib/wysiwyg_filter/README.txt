;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; WYSIWYG Filter module for Drupal
;;
;; Original author: markus_petrux at drupal.org (October 2008)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

OVERVIEW
========

The WYSIWYG Filter module provides an input filter that allows site
administrators configure which HTML elements, attributes and style properties
are allowed. It also may add rel="nofollow" to posted links based on filter
options. It can do so with no additional parsing on user input. That is, it may
apply nofollow rules while parsing HTML elements and attributes.

The filter is based on whitelists that can be defined from the filter settings
panel. Rules for HTML element and attributes are defined using the same syntax
of the TinyMCE valid_elements option.

The following elements cannot be whitelisted due to security reasons, to
prevent users from breaking site layout and/or to avoid posting invalid HTML.
Forbidden elements: applet, area, base, basefont, body, button, embed, form,
frame, frameset, head, html, iframe, input, isindex, label, link, map, meta,
noframes, noscript, object, optgroup, option, param, script, select, style,
textarea, title.

The section used to whitelist style properties is pretty simple. You just check
the properties you need from a list where almost all style properties are
organized into logical groups (Color and Background properties, Font, Text,
Box, Table, List, ...). The WYSIWYG Filter will strip out style properties not
explicitly enabled. On the other hand, for allowed style properties the WYSIWYG
Filter will check their values for strict CSS syntax (based on regular
expressions) and strip out those that do not match. Additional matching rules
are explicitly required for properties that may contain URLs in their values
("background", "background-image", "list-style" and "list-style-image"). If
rules don't match, these style properties will be ignored from user input.

When the "id" and "class" attributes have been whitelisted, it is also required
to specify explicit rules that will be used to validate user input, and again,
those that don't match will be stripped out.

As a measure to reduce the effectiveness of spam links, it is often recommended
to add rel="nofollow" to posted links leading to external sites. The WYSIWYG
Filter can easily do this for you while HTML is being processed with almost no
additional performance impact. There is a section in the filter settings panel
where a white/back list policy can be defined per domain name (the host part in
the URLs).


INSTALLATION
============

- Copy all contents of this package to your modules directory preserving
  subdirectory structure.

- Goto admin/build/modules to install the module.

- Goto admin/settings/filters and create a new input format as follows:

  - Input format name: WYSIWYG Filter (or something similar of your choice).
  - Check the filters: WYSIWYG Filter and HTML Corrector. Save.
  - Goto Rearrange tab.
  - Drag the WYSIWYG Filter on top of the HTML Corrector. Save.
  - Goto the Configure tab of your newly created WYSIWYG Filter and setup the
    available options to suit your needs.


SECURITY ISSUES
===============

- To report security issues, do not use the issue tracker of the module.
  Instead, please contact the Drupal Security Team or the WYSIWYG Filter
  module developer (preferred).

- To contact the WYSIWYG Filter module developer:
  http://drupal.org/user/39593
  http://drupal.org/user/39593/contact

- To contact the Drupal Security Team:
  http://drupal.org/security-team

- For any other kind of issue (support or feature requests, bug reports,
  translations, etc.), please, use the issue tracker of the module:
  http://drupal.org/project/issues/wysiwyg_filter
