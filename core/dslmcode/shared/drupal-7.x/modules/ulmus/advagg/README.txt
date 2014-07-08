
----------------------------------
ADVANCED CSS/JS AGGREGATION MODULE
----------------------------------


CONTENTS OF THIS FILE
---------------------

 - Features & benefits
 - Configuration
 - JSMin PHP Extension
 - JavaScript Bookmarklet
 - Technical Details & Hooks
 - How to get a high PageSpeed score
 - nginx Configuration
 - Troubleshooting


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
 - Url query string to turn off aggregation for that request. ?advagg=0 will
   turn off file aggregation if the user has the "bypass advanced aggregation"
   permission. ?advagg=-1 will completely bypass all of Advanced CSS/JS
   Aggregations modules and submodules. ?advagg=1 will enable Advanced CSS/JS
   Aggregation if it is currently disabled.
 - Button on the admin page for dropping a cookie that will turn off file
   aggregation. Useful for theme development.
 - Gzip support. All aggregated files can be pre-compressed into a .gz file and
   served from Apache. This is faster then gzipping the file on each request.

**Included submodules**

 - advagg_bundler:
   Smartly groups files together - given a target number of CSS/JS aggregates,
   this will try very hard to meet that goal.
 - advagg_css_cdn:
   Load CSS libraries from a public CDN; currently only supports Google's CDN.
 - advagg_css_compress:
   Compress the compiled CSS files using a 3rd party compressor; currently
   supports YUI (included).
 - advagg_js_cdn:
   Load JavaScript libraries from a public CDN; currently only supports Google's
   CDN.
 - advagg_js_compress:
   Compress the compiled JavaScript files using a 3rd party compressor;
   currently supports JSMin+ (included).
 - advagg_mod:
   Includes additional tweaks that may not work for all sites:
   - Force preprocessing for all CSS/JS.
   - Move JS to footer.
   - Add defer tag to all JS.
   - Inline all CSS/JS for given paths.
   - Use a shared directory for a unified multisite.
 - advagg_validator:
   Validate all CSS files using jigsaw.w3.org. Check all CSS files with CSSLint.
   Check all JS files with JSHint.


CONFIGURATION
-------------

Settings page is located at:
`admin/config/development/performance/advagg`

**Global Options**

 - Enable Advanced Aggregation: Check this to start using this module. You can
   also quickly disable the module here. For testing purposes, this has the same
   effect as placing ?advagg=-1 in the URL. Disabled by default.
 - Create .gz files: Check this by default as it will improve your performance.
   For every Aggregated file generated, this will create a gzip version of file
   and then only serve it out if the browser accepts gzip files compression.
   Enabled by default.
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
 - AdvAgg Cache Settings: As a reference, core takes about 7 ms to run.
   Development will scan all files for a change on every page load ~ 100ms.
   Normal is should be fine for all use cases ~ 10ms. Aggressive might break
   depending on how various hook_alter's for CSS/JS are implemented ~ 4ms; to
   see what modules are using css/js_alter you can go to the Information Page
   and under 'AdvAgg CSS/JS hooks implemented by modules' modules using both of
   these hooks will be listed near the bottom of that section; more information
   about the Aggressive setting can be found in Technical Details under
   Aggressive Cache Setting in this document.

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
 - Hook Theme Info: Displays the process_html order. Used for debugging.
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
      session. It acts almost the same as adding ?advagg=0 to every URL.

 - Cron Maintenance Tasks
   - Remove All Stale Files: Scan all files in the advagg_css/js directories and
     remove the ones that have not been accessed in the last 30 days.
   - Clear Missing Files From the Database: Scan for missing files and remove
     the associated entries in the database.
   - Delete Unused Aggregates from Database: Delete aggregates that have not
     been accessed in the last 6 weeks.
   - Delete orphaned/expired advagg locks from the semaphore database table.

 - Drastic Measures
   - Clear All Caches: Remove all data stored in the advagg cache bins.
   - Remove All Generated Files. Remove all files in the advagg_css/js
     directories.
   - Increment Global Counter: Force the creation of all new aggregates by
     incrementing a global counter.

**Hidden Settings**

The following settings are not configurable from the admin UI and must be set in
settings.php. In general they are settings that should not be changed. The
current defaults are shown.

    // Display a message that the bypass cookie is set.
    $conf['advagg_show_bypass_cookie_message'] = TRUE;

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
    $conf['advagg_js_max_compress_ratio'] = 0.9;

    // Value for the compression ratio test.
    $conf['advagg_js_compress_ratio'] = 0.1;


JSMIN PHP EXTENSION
-------------------

The AdvAgg JS Compress module can take advantage of jsmin.c. JavaScript parsing
and minimizing will be done in C instead of PHP dramatically speeding up the
process. If using PHP 5.3.10 or higher https://github.com/sqmk/pecl-jsmin is
recommended. If using PHP 5.3.9 or lower
http://www.ypass.net/software/php_jsmin/ is recommended.


JAVASCRIPT BOOKMARKLET
----------------------

You can use this JS code as a bookmarklet for toggling the AdvAgg URL parameter.
See http://en.wikipedia.org/wiki/Bookmarklet for more details.

    javascript:(function(){var loc = document.location.href,qs = document.location.search,regex_off = /\&?advagg=-1/,goto = loc;if(qs.match(regex_off)) {goto = loc.replace(regex_off, '');} else {qs = qs ? qs + '&advagg=-1' : '?advagg=-1';goto = document.location.pathname + qs;}window.location = goto;})();


TECHNICAL DETAILS & HOOKS
-------------------------

**Technical Details**

 - There are five database tables and two cache table used by advagg.
   advagg_schema documents what they are used for.
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

       $hooks_hash = advagg_get_current_hooks_hash();
       $css_hash = drupal_hash_base64(serialize($variables['css']));
       $css_cache_id = 'advagg:css:full:' . $hooks_hash . ':' . $css_hash;

       $hooks_hash = advagg_get_current_hooks_hash();
       $js_hash = drupal_hash_base64(serialize($javascript));
       $js_cache_id = 'advagg:js:full:' . $hooks_hash . ':' . $js_hash;

   The second and final hash value in this cache id is the css/js_hash value.
   This takes the input from drupal_add_css/js() and creates a hash value from
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
   array. This is needed because the locale_css_alter and locale_js_alter
   functions both use the global $language variable in determining what css or
   js files need to be altered. To add in your own context you can use
   hook_advagg_current_hooks_hash_array_alter to do so. Be careful when doing so
   as including something like the user id will make every user have a different
   set of aggregate files.

**Hooks**

Modify file contents:
 - advagg_get_css_file_contents_alter. Modify the data of each file before it
   gets glued together into the bigger aggregate. Useful for minification.
 - advagg_get_js_file_contents_alter. Modify the data of each file before it
   gets glued together into the bigger aggregate. Useful for minification.
 - advagg_get_css_aggregate_contents_alter. Modify the data of the complete
   aggregate before it gets written to a file. Useful for minification.
 - advagg_get_js_aggregate_contents_alter. Modify the data of the complete
   aggregate before it gets written to a file.Useful for minification.
 - advagg_save_aggregate. Modify the data of the complete aggregate allowing one
   create multiple files from one base file. Useful for gzip compression.

Modify file names and aggregate bundles:
 - advagg_current_hooks_hash_array_alter. Add in your own settings and hooks
   allowing one to modify the 3rd base64 hash in a filename.
 - advagg_build_aggregate_plans_alter. Regroup files into different aggregates.
 - advagg_css_groups_alter. Allow other modules to modify $css_groups right
   before it is processed.
 - advagg_js_groups_alter. Allow other modules to modify $js_groups right before
   it is processed.

Others:
 - advagg_hooks_implemented_alter. Tell advagg about other hooks related to
   advagg.
 - advagg_changed_files. Let other modules know about the changed files.
 - advagg_get_root_files_dir_alter. Allow other modules to alter css and js
   paths.
 - advagg_modify_css_pre_render_alter. Allow other modules to modify $children
   & $elements before they are rendered.
 - advagg_modify_js_pre_render_alter. Allow other modules to modify $children
   & $elements before they are rendered.


HOW TO GET A HIGH PAGESPEED SCORE
---------------------------------

Go to `admin/config/development/performance/advagg`
 - uncheck "Use cores grouping logic"
 - check "Combine CSS files by using media queries"

Install AdvAgg Modifier if not enabled and go to
`admin/config/development/performance/advagg/mod`
 - Under "Move JS to the footer" Select "All"
 - set "Enable preprocess on all JS/CSS"
 - set "Move JavaScript added by drupal_add_html_head() into drupal_add_js()"
 - set "Move CSS added by drupal_add_html_head() into drupal_add_css()"
 - Enable every checkbox under "Optimize JavaScript/CSS Ordering"

Install AdvAgg Compress Javascript if not enabled and go to
`admin/config/development/performance/advagg/js-compress`
 - Select JSMin if available; otherwise select JSMin+

**Other things to consider**

On the `admin/config/development/performance/advagg/mod` page there is the setting
"Remove unused JavaScript tags if possible". This is a backport of D8 where it
will not add any JS to the page if it is not being used.
https://drupal.org/node/1279226

The AdvAgg Bundler module on the
`admin/config/development/performance/advagg/bundler` page. The bundler provides
intelligent bundling of CSS and JS files by grouping files that belong together.
This does what core tried to do; group CSS & JS files together that get used
together. Using this will make your pagespeed score go down as there will be
more css/js files to download but if different css/js files are used on
different pages of your site this will be a net win as a new full aggregate will
not have to be downloaded, instead a smaller aggregate can be downloaded,
ideally with only the css/js that is different on that page. You can select how
many bundles to create and the bundler will do it's best to meet that goal; if
using browser css/js conditionals (js browser conditionals backported from D8
https://drupal.org/node/865536) then the bundler might not meet your set value.


NGINX CONFIGURATION
-------------------

http://drupal.org/node/1116618
Note that @drupal might be @rewrite depending on your servers configuration.

    ###
    ### advagg_css and advagg_js support
    ###
    location ~* files/advagg_(?:css|js)/ {
      gzip_static on;
      access_log  off;
      expires     max;
      add_header  ETag "";
      add_header  Cache-Control "max-age=31449600, no-transform, public";
      try_files   $uri @drupal;
    }


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
to fit your setup. services/* is the default (CAS_EXCLUDE) and
httprl_async_function_callback is needed if httprl will be used.

    services/*
    sites/default/files/advagg_css/*
    sites/default/files/advagg_js/*
    httprl_async_function_callback

In the example of CAS this setting can be found on the `admin/config/people/cas`
page and under Redirection there should be a setting called "Excluded Pages".


If Far-Future headers are not being sent out and you are using Apache here are
some tips to hopefully get it working. For Apache enable mod_rewrite,
mod_headers, and mod_expires. Add the following code to the bottom of Drupal's
core .htaccess file (located at the webroot level).

    <FilesMatch "^(css|js)__[A-Za-z0-9-_]{43}__[A-Za-z0-9-_]{43}__[A-Za-z0-9-_]{43}.(css|js)(\.gz)?">
      # No mod_headers
      <IfModule !mod_headers.c>
        # No mod_expires
        <IfModule !mod_expires.c>
          # Use ETags.
          FileETag MTime Size
        </IfModule>
      </IfModule>

      # Use Expires Directive.
      <IfModule mod_expires.c>
        # Do not use ETags.
        FileETag None
        # Enable expirations.
        ExpiresActive On
        # Cache all aggregated css/js files for 52 weeks after access (A).
        ExpiresDefault A31449600
      </IfModule>

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
    <FilesMatch "^js__[A-Za-z0-9-_]{43}__[A-Za-z0-9-_]{43}__[A-Za-z0-9-_]{43}.js(\.gz)?">
      ForceType application/javascript
    </FilesMatch>


If pages on the site stop working correctly or looks broken after Advanced
CSS/JS Aggregation is enabled, the first step should be to validate the
individual CSS and/or JS files using the included advagg_validator module -
something as simple as an errant unfinished comment in one file may cause entire
aggregates of files to be ignored.


If AdvAgg was installed via drush sometimes directory permissions need to be
fixed. Using `chown -R` on the advagg directories usually solves this issue.
