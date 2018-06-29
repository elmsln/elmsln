
ADVANCED CSS/JS AGGREGATION MODULE
==================================


CONTENTS OF THIS FILE
---------------------

 - Introduction
 - Requirements
 - Recommended modules
 - Installation
 - How to get a high PageSpeed score
 - JSMin PHP Extension
 - Brotli PHP Extension
 - Zopfli PHP Extension
 - nginx Configuration
 - JavaScript Bookmarklet
 - Troubleshooting
 - Features & benefits
 - Configuration
 - Additional options for `drupal_add_css/js` functions
 - Technical Details & Hooks


INTRODUCTION
------------

The Advanced CSS/JS Aggregation allows you to improve the frontend performance
of your site. Be sure to do a before and after comparison by using Google's
PageSpeed Insights and WebPagetest.org.
https://developers.google.com/speed/pagespeed/insights/
http://www.webpagetest.org/easy


REQUIREMENTS
------------

No special requirements.


RECOMMENDED MODULES
-------------------

 - Libraries (https://www.drupal.org/project/libraries)
   Allows for 3rd party code for minification to be used by AdvAgg.


INSTALLATION
------------

 - Install as you would normally install a contributed Drupal module. Visit:
   https://drupal.org/documentation/install/modules-themes/modules-7
   for further information.


HOW TO GET A HIGH PAGESPEED SCORE
---------------------------------

Be sure to check the site after every section to make sure the change didn't
mess up your site. The changes under AdvAgg Modifier are usually the most
problematic but they offer the biggest improvements.

#### Advanced CSS/JS Aggregation ####
Go to `admin/config/development/performance/advagg`

Select "Use recommended (optimized) settings"

#### AdvAgg Compress Javascript ####
Install AdvAgg Compress Javascript if not enabled and go to
`admin/config/development/performance/advagg/js-compress`

 - Select JSMin if available; otherwise select JSMin+
 - Select Strip everything (smallest files)
 - Save configuration
 - Click the batch compress link to process these files at the top.

#### AdvAgg Async Font Loader ####
Install AdvAgg Async Font Loader if not enabled and go to
`admin/config/development/performance/advagg/font`

 - Select Local file included in aggregate (version: X.X.X). If this option is
   not available follow the directions right below the options on how to install
   it.

Keep the 2 checkboxes checked.

#### AdvAgg Bundler ####
Install AdvAgg Bundler if not enabled and go to
`admin/config/development/performance/advagg/bundler`

If your server supports HTTP 2 then select "Use HTTP 2.0 settings"; otherwise
leave it at the "Use HTTP 1.1 settings".

#### AdvAgg Relocate ####
Install AdvAgg Relocate if not enabled and go to
`admin/config/development/performance/advagg/relocate`

Select "Use recommended (optimized) settings"

#### AdvAgg Modifier ####
Install AdvAgg Modifier if not enabled and go to
`admin/config/development/performance/advagg/mod`

Select "Use recommended (optimized) settings"

#### AdvAgg Critical CSS module ####
Install AdvAgg Critical CSS if not enabled and go to
`admin/config/development/performance/advagg/critical-css`

These are the directions for the front page of your site.

Under Add Critical CSS
- Select the theme that is your front page; usually the default is correct.
- User type should be set to 'anonymous' under most circumstances.
- Type of lookup, select URL
- Value to lookup, type in `<front>`
- Critical CSS, paste in the generated CSS from running your homepage url
through https://www.sitelocity.com/critical-path-css-generator which is inside
of the 'Critical Path CSS' textarea on the sitelocity page.
- Click Save Configuration.

Other landing pages should have their critical CSS added as well. If you have
Google Analytics this will show you how to find your top landing pages
https://developers.google.com/analytics/devguides/reporting/core/v3/common-queries#top-landing-pages
or for Piwik https://piwik.org/faq/how-to/faq_160/. You can also use this
chrome browser plugin to generate critical CSS
https://chrome.google.com/webstore/detail/critical-style-snapshot/gkoeffcejdhhojognlonafnijfkcepob?hl=en


JSMIN PHP EXTENSION
-------------------

The AdvAgg JS Compress module can take advantage of jsmin.c. JavaScript parsing
and minimizing will be done in C instead of PHP dramatically speeding up the
process. If using PHP 5.3.10 or higher https://github.com/sqmk/pecl-jsmin is
recommended. If using PHP 5.3.9 or lower
http://www.ypass.net/software/php_jsmin/ is recommended.


BROTLI PHP EXTENSION
--------------------

The AdvAgg module can take advantage of Brotli compression. Install this
extension to take advantage of it. Should reduce CSS/JS files by 20%.
https://github.com/kjdev/php-ext-brotli


ZOPFLI PHP EXTENSION
--------------------

The AdvAgg module can take advantage of the Zopfli compression algorithm.
Install this extension to take advantage of it. This gives higher gzip
compression ratios compared to stock PHP.
https://github.com/kjdev/php-ext-zopfli


NGINX CONFIGURATION
-------------------

https://drupal.org/node/1116618
Note that @drupal (last line of code below) might be @rewrite or @rewrites
depending on your servers configuration. If there are image style rules in your
Nginx configuration add this right below that. If you want to have brotli
support https://github.com/google/ngx_brotli is how to install that; add
`brotli_static on;` right above `gzip_static on;` in the configuration below.

    ###
    ### advagg_css and advagg_js support
    ###
    location ~* files/advagg_(?:css|js)/ {
      gzip_static on;
      access_log  off;
      expires     max;
      add_header  ETag "";
      add_header  Cache-Control "max-age=31449600, no-transform, public";
      try_files   $uri $uri/ @drupal;
    }

Also noted that some ready made nginx configurations add in a Last-Modified
header inside the advagg directories. These should be removed.


JAVASCRIPT BOOKMARKLET
----------------------

You can use this JS code as a bookmarklet for toggling the AdvAgg URL parameter.
See http://en.wikipedia.org/wiki/Bookmarklet for more details.

    javascript:(function(){var loc = document.location.href,qs = document.location.search,regex_off = /\&?advagg=-1/,goto = loc;if(qs.match(regex_off)) {goto = loc.replace(regex_off, '');} else {qs = qs ? qs + '&advagg=-1' : '?advagg=-1';goto = document.location.pathname + qs;}window.location = goto;})();


TROUBLESHOOTING
---------------

If the core Fast 404 Pages functionality is enabled via settings.php, the
settings must be changed in order for the on-demand file compilation to work.
Change this:

    $conf['404_fast_paths_exclude'] = '/\/(?:styles)\//';

to this:

    $conf['404_fast_paths_exclude'] = '/\/(?:styles|advagg_(cs|j)s)\//';

Similarly, if the Fast_404 module is enabled, the 'fast_404_string_whitelisting'
variable must be set inside of settings.php. Add this to your settings.php file:

    $conf['fast_404_string_whitelisting'][] = '/advagg_';


Modules like the Central Authentication Services https://drupal.org/project/cas
will redirect all anonymous requests to a login page. Most of the time there is
a setting that allows certain pages to be excluded from the redirect. You should
add the following to those exclusions. Note that sites/default/files is the
location of you public file system (public://) so you might have to adjust this
to fit your setup. services/* is the default (`CAS_EXCLUDE`) and
`httprl_async_function_callback` is needed if httprl will be used.

    services/*
    sites/default/files/advagg_css/*
    sites/default/files/advagg_js/*
    httprl_async_function_callback

In the example of CAS this setting can be found on the `admin/config/people/cas`
page and under Redirection there should be a setting called "Excluded Pages".


If Far-Future headers are not being sent out and you are using Apache here are
some tips to hopefully get it working. For Apache enable `mod_rewrite`,
`mod_headers`, and `mod_expires`. Add the following code to the bottom of
Drupal's core .htaccess file (located at the webroot level).

    <FilesMatch "^(css|js)__[A-Za-z0-9-_]{43}__[A-Za-z0-9-_]{43}__[A-Za-z0-9-_]{43}.(css|js)(\.gz|\.br)?">
      # No mod_headers. Apache module headers is not enabled.
      <IfModule !mod_headers.c>
        # No mod_expires. Apache module expires is not enabled.
        <IfModule !mod_expires.c>
          # Use ETags.
          FileETag MTime Size
        </IfModule>
      </IfModule>

      # Use Expires Directive if apache module expires is enabled.
      <IfModule mod_expires.c>
        # Do not use ETags.
        FileETag None
        # Enable expirations.
        ExpiresActive On
        # Cache all aggregated css/js files for 52 weeks after access (A).
        ExpiresDefault A31449600
      </IfModule>

      # Use Headers Directive if apache module headers is enabled.
      <IfModule mod_headers.c>
        # Do not use etags for cache validation.
        Header unset ETag
        <IfModule !mod_expires.c>
          # Set a far future Cache-Control header to 52 weeks.
          Header set Cache-Control "max-age=31449600, no-transform, public"
        </IfModule>
        <IfModule mod_expires.c>
          Header append Cache-Control "no-transform, public"
        </IfModule>
      </IfModule>
    </FilesMatch>
    # Force advagg .js file to have the type of application/javascript.
    <FilesMatch "^js__[A-Za-z0-9-_]{43}__[A-Za-z0-9-_]{43}__[A-Za-z0-9-_]{43}.js(\.gz|\.br)?">
      ForceType application/javascript
    </FilesMatch>


If pages on the site stop working correctly or looks broken after Advanced
CSS/JS Aggregation is enabled, the first step should be to validate the
individual CSS and/or JS files using the included `advagg_validator` module -
something as simple as an errant unfinished comment in one file may cause entire
aggregates of files to be ignored.


If AdvAgg was installed via drush sometimes directory permissions need to be
fixed. Using `chown -R` on the advagg directories usually solves this issue.


If hosting on Pantheon, you might need to add this to your settings.php file if
you get Numerous login prompts after enabling Adv Agg module on Pantheon Test
and Live instances.

    if (isset($_SERVER['PANTHEON_ENVIRONMENT'])) {
      // NO trailing slash when setting the $base_url variable.
      switch ($_SERVER['PANTHEON_ENVIRONMENT']) {
        case 'dev':
          $base_url = 'http://dev-sitename.gotpantheon.com';
          break;

        case 'test':
          $base_url = 'http://test-sitename.gotpantheon.com';
          break;

        case 'live':
          $base_url = 'http://www.domain.tld';
          break;
      }
      // Remove a trailing slash if one was added.
      if (!empty($base_url)) {
        $base_url = rtrim($base_url, '/');
      }
    }


If you're getting the "HTTP requests to advagg are not getting though" error,
you can try to fix it by making sure the `$base_url` is correctly set for
production and not production environments.


If you're getting mixed content error for CSS JS files over HTTPS then you can
try to redirect all http traffic to be https.

    RewriteCond %{HTTPS} off
    RewriteCond %{HTTP:X-Forwarded-Proto} !https
    RewriteRule ^(.*)$ https://%{HTTP_HOST}%{REQUEST_URI} [L,R=301]


If brotli compression is not working and you are using Apache here are some tips
to hopefully get it working. For Apache enable `mod_rewrite`, `mod_headers`, and
`mod_expires`. Add the following code right above this line `# Rules to
correctly serve gzip compressed CSS and JS files.`

      <IfModule mod_headers.c>
        # Serve brotli compressed CSS if they exist and the client accepts br.
        RewriteCond %{HTTP:Accept-encoding} br
        RewriteCond %{REQUEST_FILENAME}\.br -s
        RewriteRule ^(.*)\.css $1\.css\.br [QSA]
        RewriteRule \.css\.br$ - [T=text/css,E=no-gzip:1]

        # Serve brotli compressed JS if they exist and the client accepts br.
        RewriteCond %{HTTP:Accept-encoding} br
        RewriteCond %{REQUEST_FILENAME}\.br -s
        RewriteRule ^(.*)\.js $1\.js\.br [QSA]
        RewriteRule \.js\.br$ - [T=application/javascript,E=no-gzip:1]

        <FilesMatch "(\.js\.br|\.css\.br)$">
          # Serve correct encoding type.
          Header set Content-Encoding br
          # Force proxies to cache compressed and non-compressed css/js files
          # separately.
          Header append Vary Accept-Encoding
        </FilesMatch>
      </IfModule>


If you are having 5 minute or longer timeouts on the admin/reports/status page
then you might need to use an alternative to drupal_httP_request(). The cURL
HTTP Request module https://www.drupal.org/project/chr might fix this issue.


FEATURES & BENEFITS
-------------------

**Advanced CSS/JS Aggregation core features**

 - On demand generation of CSS/JS Aggregates. If the file doesn't exist it will
   be generated on demand.
 - Stampede protection for CSS and JS aggregation. Uses locking so multiple
   requests for the same thing will result in only one thread doing the work.
 - Fully cached CSS/JS assets allow for zero file I/O if the Aggregated file
   already exists. Results in better page generation performance.
 - Smarter aggregate deletion. CSS/JS aggregates only get removed from the
   folder if they have not been used/accessed in the last 30 days.
 - Smarter cache flushing. Scans all CSS/JS files that have been added to any
   aggregate; if that file has changed then flush the correct caches so the
   changes go out. The new name ensures changes go out when using CDNs.
 - One can add JS to any region of the theme & have it aggregated.
 - Url query string to turn off aggregation for that request. `?advagg=0` will
   turn off file aggregation if the user has the "bypass advanced aggregation"
   permission. `?advagg=-1` will completely bypass all of Advanced CSS/JS
   Aggregations modules and submodules. `?advagg=1` will enable Advanced CSS/JS
   Aggregation if it is currently disabled.
 - Button on the admin page for dropping a cookie that will turn off file
   aggregation. Useful for theme development.
 - Gzip support. All aggregated files can be pre-compressed into a .gz file and
   served from Apache. This is faster then gzipping the file on each request.

**Included submodules**

 - `advagg_bundler`:
   Smartly groups files together - given a target number of CSS/JS aggregates,
   this will try very hard to meet that goal.
 - `advagg_css_cdn`:
   Load CSS libraries from a public CDN; currently only supports Google's CDN.
 - `advagg_css_compress`:
   Compress the compiled CSS files using a 3rd party compressor; currently
   supports YUI (included).
 - `advagg_js_cdn`:
   Load JavaScript libraries from a public CDN; currently only supports Google's
   CDN.
 - `advagg_js_compress`:
   Compress the compiled JavaScript files using a 3rd party compressor;
   currently supports JSMin+ (included).
 - `advagg_mod`:
   Includes additional tweaks that may not work for all sites:
   - Force preprocessing for all CSS/JS.
   - Move JS to footer.
   - Add defer tag to all JS.
   - Defer loading of CSS.
   - Inline all CSS/JS for given paths.
   - Use a shared directory for a unified multisite.
 - `advagg_validator`:
   Validate all CSS files using jigsaw.w3.org. Check all CSS files with CSSLint.
   Check all JS files with JSHint.


CONFIGURATION
-------------

Settings page is located at:
`admin/config/development/performance/advagg`

**Global Options**

 - Enable Advanced Aggregation: Check this to start using this module. You can
   also quickly disable the module here. For testing purposes, this has the same
   effect as placing `?advagg=-1` in the URL. Disabled by default.
 - Use Cores Grouping Logic: Leave this checkbox enabled until you are ready to
   begin exploring the AdvAgg Bundler sub-module which overrides Core's
   functionality. This groups files just like Core does so should just work.
   Enabled by default. You will also have to disable this checkbox if you wish
   to enable some of the CSS Options below on this settings page.
 - Use HTTPRL to generate aggregates: If the HTTPRL module is enabled -
   https://drupal.org/project/httprl - advagg will use it to generate aggregates
   on the fly in a background parallel process. Enabling HTTPRL will improve
   page generation speeds when a new aggregate is created because the CSS/JS
   file creation will happen in a different process. If HTTPRL is installed it
   is Enabled by default; otherwise is it Disabled.
 - AdvAgg Cache Settings: As a reference, core takes about 25 ms to run.
   Development will scan all files for a change on every page load. Normal is
   fine for all use cases. Aggressive should be fine in almost all use cases;
   if your inline css/js changes based off of a variable then the aggressive
   cache hit ratio will be low; if that is the case consider using
   Drupal.settings for a better cache hit ratio.

**Resource Hints**

Preemptively get resources (CSS/JS & sub requests). This will set tags in the
document head telling the browser to open up connections before they are needed.

 - DNS Prefetch: Start the DNS lookup for external CSS and JavaScript files as
   soon as possible.
 - Preconnect: Start the connection to external resources before an HTTP request
   is actually sent to the server. On HTTPS this can have a dramatic effect.
 - Location of resource hints: This only needs to be changed if the above
   settings are not working.
 - Preload link http headers: If your server supports HTTP/2 push then this
   allows for resources to be sent before the browser knows it needs it.

**Cron Options**

Adjusting the frequency of how often something happens on cron.

**Obscure Options**

 - Create .gz files: Check this by default as it will improve your performance.
   For every Aggregated file generated, this will create a gzip version of file
   and then only serve it out if the browser accepts gzip files compression.
   Enabled by default.
 - Create .br files: Check this by default as it will improve your performance.
   For every Aggregated file generated, this will create a brotli version of
   file and then only serve it out if the browser accepts gzip files
   compression. Enabled by default IF the Brotli Extension for PHP is installed.
   See https://github.com/kjdev/php-ext-brotli
 - Run advagg_ajax_render_alter(): Turn this off if you're having issues with
   ajax. Also keep in mind that the max_input_vars setting can cause issues if
   you are submitting a lot of data.
 - Include the base_url variable in the hooks hash array: Enabled only if you
   know you need it.
 - Convert absolute paths to be self references: Turn on unless pages are used
   inside of an iframe.
 - Convert absolute paths to be protocol relative paths: Safe to use unless you
   need to support IE6.
 - Convert http:// to https://: Usually not needed, but here in case you do.
 - Do not run CSS url() values through file_create_url(): Usually not needed,
   but here in case you do.


**CSS Options & JS Options**

 - Combine CSS files by using media queries: "Use cores grouping logic" needs to
   be unchecked in order for this to work. Also noted is that due to an issue
   with IE9, compatibility mode is forced off if this is enabled by adding this
   tag in the html head:

        <!--[if IE]>
        <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" />
        <![endif]-->

   Disabled by default.
 - Prevent more than 4095 CSS selectors in an aggregated CSS file: Internet
   Explorer before version 10; IE9, IE8, IE7, & IE6 all have 4095 as the limit
   for the maximum number of css selectors that can be in a file. Enabling this
   will prevent CSS aggregates from being created that exceed this limit. For
   more information see
   http://blogs.msdn.com/b/ieinternals/archive/2011/05/14/10164546.aspx Disabled
   by default.
 - Fix improperly set type (CSS/JS): If type is external but does not start with
   http, https, or // change it to be type file. If type is file but it starts
   with http, https, or // change type to be external.

**Information page**

located at `admin/config/development/performance/advagg/info`. This page
provides debugging information. There are no configuration options here.

 - Hook Theme Info: Displays the `process_html` order. Used for debugging.
 - Hook Render Info: Displays the scripts and styles render callbakcs. Used for
   debugging.
 - CSS files: Displays how often a file has changed.
 - JS files: Displays how often a file has changed.
 - Modules implementing AdvAgg CSS/JS hooks: Lets you know what modules are
   using advagg.
 - AdvAgg CSS/JS hooks implemented by modules: Lets you know what advagg hooks
   are in use.
 - Hooks And Variables Used In Hash: Show what is used to calculate the 3rd hash
   of an aggregates filename.
 - Get detailed info about an aggregate file: Look up detailed array about any
   CSS or JS file listed.

**Operations page**

located at `admin/config/development/performance/advagg/operations`. This is a
collection of commands to control the cache and to manage testing of this
module. In general this page is useful when troubleshooting some aggregation
issues. For normal operations, you do not need to do anything on this page below
the Smart Cache Flush. There are no configuration options here.

 - Smart Cache Flush
   - Flush AdvAgg Cache: Scan all files referenced in aggregated files. If
     any of them have changed, increment the counters containing that file and
     rebuild the bundle.

 - Aggregation Bypass Cookie
    - Toggle The "aggregation bypass cookie" For This Browser: This will set or
      remove a cookie that disables aggregation for the remainder of the browser
      session. It acts almost the same as adding `?advagg=0` to every URL.

 - Cron Maintenance Tasks
   - Clear All Stale Files: Scan all files in the `advagg_css/js` directories
     and remove the ones that have not been accessed in the last 30 days.
   - Delete Orphaned Aggregates: Scan CSS/JS advagg dir and remove file if
     there is no associated db record.
   - Clear Missing Files From the Database: Scan for missing files and remove
     the associated entries in the database.
   - Delete Unused Aggregates from Database: Delete aggregates that have not
     been accessed in the last 6 weeks.
   - Delete orphaned/expired advagg locks from the semaphore database table.
   - Delete leftover temporary files: Delete old temporary files from the
     filesystem.

 - Drastic Measures
   - Clear All Caches: Remove all data stored in the advagg cache bins.
   - Clear All Files: Remove All Generated Files. Remove all files in the
     `advagg_(css|js)` directories.
   - Force New Aggregates: Increment Global Counter. Force the creation of all
     new aggregates by incrementing a global counter.
   - Rescan All Files: Force rescan all files and clear the cache. Useful if a
     css/js change from a deployment did not work.
   - Remove deleted files in the advagg_files table: Remove entries in the
     advagg_files table that have a filesize of 0 and delete the
     javascript_parsed variable. This gets around the grace period that the
     cron cleanup does.
   - Reset the AdvAgg Files table: Truncate the advagg_files table and delete
     the javascript_parsed variable. This may cause some 404s for CSS/JS assets
     for a short amount of time (seconds). Useful if you really want to reset
     some stuff. Might be best to put the site into maintenance mode before
     doing this.

**Hidden Settings**

The following settings are not configurable from the admin UI and must be set in
settings.php. In general they are settings that should not be changed. The
current defaults are shown.

    // Display a message that the bypass cookie is set.
    $conf['advagg_show_bypass_cookie_message'] = TRUE;

    // Display a message when a css/js file changed while in development mode.
    $conf['advagg_show_file_changed_message'] = TRUE;

    // Skip the 404 check on status page.
    $conf['advagg_skip_404_check'] = FALSE;

    // Force the scripts #aggregate_callback to always be _advagg_aggregate_js.
    $conf['advagg_enforce_scripts_callback'] = TRUE;

    // Default location of AdvAgg configuration items.
    $conf['advagg_admin_config_root_path'] = 'admin/config/development/performance';

    // Run advagg_url_inbound_alter().
    $conf['advagg_url_inbound_alter'] = TRUE;

    // Allow JavaScript insertion into any scope even if theme does not support
    // it.
    $conf['advagg_scripts_scope_anywhere'] = FALSE;

    // Empty the scripts key inside of template_process_html replacement
    // function.
    $conf['advagg_scripts_scope_anywhere'] = FALSE;

    // Do more file operations in main thread if the file system is fast. If
    // AdvAgg's directories are mounted on something like S3, you might want to
    // set this to FALSE.
    $conf['advagg_fast_filesystem'] = TRUE;

    // Pregenerate aggregate files. If disable the browser requesting the file
    // will cause the generation to happen. If advagg 404 handling is broken
    // then setting this to false will break your site in bad ways.
    $conf['advagg_pregenerate_aggregate_files'] = TRUE;

    // Set the jQuery UI version.
    $conf['advagg_css_cdn_jquery_ui_version'] = '1.8.7';

    // See if jQuery UI should be grabbed from the Google CDN.
    $conf['advagg_css_cdn_jquery_ui'] = TRUE;

    // Set the jQuery UI version.
    $conf['advagg_js_cdn_jquery_ui_version'] = '1.8.7';

    // Set the jQuery version.
    $conf['advagg_js_cdn_jquery_version'] = '1.4.4';

    // Use minification.
    $conf['advagg_js_cdn_compression'] = TRUE;

    // See if jQuery UI should be grabbed from the Google CDN.
    $conf['advagg_js_cdn_jquery_ui'] = TRUE;

    // See if jQuery should be grabbed from the Google CDN.
    $conf['advagg_js_cdn_jquery'] = TRUE;

    // Value for the compression ratio test.
    $conf['advagg_js_compress_max_ratio'] = 0.9;

    // Value for the compression ratio test.
    $conf['advagg_js_compress_ratio'] = 0.1;

    // Skip far future check on status page.
    $conf['advagg_skip_far_future_check'] = FALSE;

    // Skip preprocess and enabled checks.
    $conf['advagg_skip_enabled_preprocess_check'] = FALSE;

    // Default root dir for the advagg files; see advagg_get_root_files_dir().
    $conf['advagg_root_dir_prefix'] = 'public://';

    // How long to wait when writing the aggregate if a file is missing or the
    // hash doesn't match.
    $conf['advagg_file_read_failure_timeout'] = 3600;

    // If FALSE mtime of files will only trigger a change if they are in the
    // future.
    $conf['advagg_strict_mtime_check'] = TRUE;

    // Skip 304 check on status page.
    $conf['advagg_skip_304_check'] = FALSE;

    // Control how many bytes can be inlined.
    $conf['advagg_mod_css_defer_inline_size_limit'] = 12288;

    // Control how many bytes the preload header can use.
    $conf['advagg_resource_hints_preload_max_size'] = 3072;

    // If TRUE, only verify 1st hash instead of all 3 of the filename.
    $conf['advagg_weak_file_verification'] = FALSE;


ADDITIONAL OPTIONS FOR DRUPAL_ADD_CSS/JS FUNCTIONS
--------------------------------------------------

AdvAgg extends the available options inside of `drupal_add_css` and
`drupal_add_js`.

`drupal_add_js` - additional keys for $options.

 - `browsers`: Works the same as the one found in drupal_add_css.
 - `onload`: Run this js code when after the js file has loaded.
 - `onerror`: Run this js code when if the js file did not load.
 - `async`: TRUE - Load this file using async.
 - `no_defer`: TRUE - Never defer or async load this js file.

Both `drupal_add_js` + `drupal_add_css` - additional keys for $options.

 - `scope_lock`: TRUE - Make sure the scope of this will not ever change.
 - `movable`: FALSE - Make sure the ordering of this will not ever change.
 - `preprocess_lock`: TRUE - Make sure the preprocess key will not ever change.


TECHNICAL DETAILS & HOOKS
-------------------------

**Technical Details**

 - There are five database tables and two cache table used by advagg.
   `advagg_schema` documents what they are used for.
 - Files are generated by this pattern:

        css__[BASE64_HASH]__[BASE64_HASH]__[BASE64_HASH].css

   The first base64 hash value tells us what files are included in the
   aggregate. Changing what files get included will change this value.

   The second base64 hash value is used as a sort of version control; it changes
   if any of the base files contents have changed. Changing a base files content
   (like drupal.js) will change this value.

   The third base64 hash value records what settings were used when generating
   the aggregate. Changing a setting that affects how aggregates get built
   (like toggling "Create .gz files") will change this value.

 - To trigger scanning of the CSS / JS file cache to identify new files, run
   the following:

        // Trigger reloading the CSS and JS file cache in AdvAgg.
        if (module_exists('advagg')) {
          module_load_include('inc', 'advagg', 'advagg.cache');
          advagg_push_new_changes();
        }

 - Aggressive Cache Setting: This will fully cache the rendered html generated
   by AdvAgg. The cache ID is set by this code:

        // CSS.
        $hooks_hash = advagg_get_current_hooks_hash();
        $css_cache_id_full =
          'advagg:css:full:' . $hooks_hash . ':' .
          drupal_hash_base64(serialize($full_css));
        // JS.
        $hooks_hash = advagg_get_current_hooks_hash();
        $js_cache_id_full =
          'advagg:js:full:' . $hooks_hash . ':' .
          drupal_hash_base64(serialize($js_scope_array));

   The second and final hash value in this cache id is the css/js_hash value.
   This takes the input from `drupal_add_css/js()` and creates a hash value from
   it. If a different file is added and/or inline code changed, this hash value
   will be different.

   The first hash value will take the current_hooks_hash value which is the
   third base64 hash value listed above in this section (Technical Details) as
   the first part of the hash. This means that if any value is changed in this
   nested array a different cache id will be used. You can see the contents of
   this nested array by going to
   `admin/config/development/performance/advagg/info` under
   "Hooks And Variables Used In Hash". An example of this being properly used is
   if you enable the core locale module the language key will appear in the
   array. This is needed because the `locale_css_alter` and `locale_js_alter`
   functions both use the global $language variable in determining what css or
   js files need to be altered. To add in your own context you can use
   `hook_advagg_current_hooks_hash_array_alter` to do so. Be careful when doing
   so as including something like the user id will make every user have a
   different set of aggregate files.

**Hooks**

Modify file contents:

 - `advagg_get_css_file_contents_alter`. Modify the data of each file before it
   gets glued together into the bigger aggregate. Useful for minification.
 - `advagg_get_js_file_contents_alter`. Modify the data of each file before it
   gets glued together into the bigger aggregate. Useful for minification.
 - `advagg_get_css_aggregate_contents_alter`. Modify the data of the complete
   aggregate before it gets written to a file. Useful for minification.
 - `advagg_get_js_aggregate_contents_alter`. Modify the data of the complete
   aggregate before it gets written to a file.Useful for minification.
 - `advagg_save_aggregate_alter`. Modify the data of the complete aggregate
   allowing one create multiple files from one base file. Useful for gzip
   compression. Also useful for mirroring data.

Modify file names and aggregate bundles:

 - `advagg_current_hooks_hash_array_alter`. Add in your own settings and hooks
   allowing one to modify the 3rd base64 hash in a filename.
 - `advagg_build_aggregate_plans_alter`. Regroup files into different
   aggregates.
 - `advagg_css_groups_alter`. Allow other modules to modify `$css_groups` right
   before it is processed.
 - `advagg_js_groups_alter`. Allow other modules to modify `$js_groups` right
   before it is processed.

Others:

 - `advagg_hooks_implemented_alter`. Tell advagg about other hooks related to
   advagg.
 - `advagg_get_root_files_dir_alter`. Allow other modules to alter css and js
   paths.
 - `advagg_modify_css_pre_render_alter`. Allow other modules to modify $children
   & $elements before they are rendered.
 - `advagg_modify_js_pre_render_alter`. Allow other modules to modify $children
   & $elements before they are rendered.
 - `advagg_changed_files`. Let other modules know about the changed files.
 - `advagg_removed_aggregates`. Let other modules know about removed aggregates.
 - `advagg_scan_for_changes`. Let other modules see if files related to this
   file has changed. Useful for detecting changes to referenced images in css.
 - `advagg_get_info_on_files_alter`. Let other modules modify information about
   the base CSS/JS files.
 - `advagg_context_alter`. Allow other modules to swap important contextual
   information on generation.
 - `advagg_bundler_analysis`. If the bundler module is installed allow for other
   modules to change the bundler analysis.
