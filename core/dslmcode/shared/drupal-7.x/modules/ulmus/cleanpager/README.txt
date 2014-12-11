
Clean Pagination module:
-------------------------
Author - Chris Shattuck (www.impliedbydesign.com)
License - GPL

Drupal 7 port - JC Tenney (sponsored by byronbay.com Pty Ltd.)


Overview:
-------------------------
The Clean Pagination is a really simple module that helps get around the way Drupal
structures paginated URLs, which is by adding a query string, such as 'my-view?page=2'.
Clean Pagination will let you set which pages you would like to have clean URL
pagination, which looks like 'my-view/2'.

There is also an option to use search-engine-friendly links, which will add the URL of the page
to the pagination links, and will remove the extra text after the page loads. That way,
users see the typical '1 2 3' pagination, but search engines see 'View my-view Page 1
View my-view Page 2  View my-view Page 3'. If your URL is keyword-rich, having the
keywords in the hyperlink can be beneficial.

Theme Override:
-------------------------
This module overrides theme_pager_link in order to correctly theme the links for
the pager. The module returns the html for the link. If your theme needs to have
the link returned as an array then you will need to manually set the variable
cleanpager_array_themes with your theme name. Currently the tao theme is supported
out of the box.  variable_get('cleanpager_array_themes', array('tao'))

Setup:
-------------------------
- Place module in correct directory (sites/all/modules)
- Visit modules page, and install
- Go to settings 'admin/config/system/cleanpage' and turn on cleanpager for pages you want.
- Turn on any other settings. Recommnded settings to turn on:
  "Use 301 Redirects",
  "Add next/prev links to head"