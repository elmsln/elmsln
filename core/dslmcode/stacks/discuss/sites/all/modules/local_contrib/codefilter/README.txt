ABOUT
-----

This is a simple filter module. It handles <code></code> and <?php ?> tags so
that users can post code without having to worry about escaping with &lt; and
&gt;


INSTALLATION
------------

1. Copy the codefilter folder to your website's sites/all/modules directory.

2. Enable the codefilter.module on the Modules page.

3. Go to Configuration > Text formats. For each format you wish to add Code
   Filter to:

  a. Click the "configure" link.

  b. Under "Enabled filters", check the codefilter checkbox.

  c. Under "Filter processing order", rearrange the filtering chain to resolve
     any conflicts. For example, to prevent invalid XHTML in the form of
     '<p><div class="codefilter">' make sure "Code filter" comes before the
     "Convert line breaks into HTML" filter.

  d. Click the "Save configuration" button.

4. (optionally) Edit your theme to provide a div.codeblock style for blocks of
   code.


CREDITS
-------

This mini-module was originally made by Steven Wittens <unconed@drupal.org>,
based on the PHP filter in Kjartan Mannes's <kjartan@drupal.org> project.module.
