
Description
-----------
This module provide easy Content Delivery Network integration for Drupal sites.
It alters file URLs, so that files are downloaded from a CDN instead of your
web server.

It provides two modes: "Origin Pull" and "File Conveyor".

In "Origin Pull" mode, only "Origin Pull" CDNs are supported (hence the name).
These are CDNs that only require you to replace the domain name with another
domain name. The CDN will then automatically fetch (pull) the files from your
server (the origin).

In "File Conveyor" mode, this module integrates with the File Conveyor [1]
daemon. This allows for much more advanced setups: files can be processed
(e.g. optimize images like smush.it [2], minify CSS with YUI Compressor [3],
minify JS with YUI compressor or Google Closure Compiler [4], and it's easy to
add your own!), before they are synced and your CDN doesn't *have* to support
Origin Pull, any push method is fine (supported transfer protocols: FTP,
Amazon S3, Rackspace CloudFiles). File Conveyor is flexible enough to be used
with *any* CDN, thus it enables you to avoid vendor lock-in.

If you're not sure which mode to use, use "Origin Pull". It's easier and more
reliable. The only common CDN today (2011–2012) that doesn't support it is
Rackspace Cloud Files.

_Note:_ It is essential that you understand the key properties of a CDN, most
importantly the differences between an Origin Pull CDN and a Push CDN. A good
(and compact!) reference is the "Key Properties of a CDN" article [5].

The CDN module aims to do only one thing and do it well: altering URLs to
point to files on CDNs.
However, in later versions, it does as much as possible to make CDN
integration frictionless:
    • Any sort of CDN mapping
    • optimal Far Future expiration (http://drupal.org/node/974350)
        - CORS (http://drupal.org/node/982188)
        - signed URLs prevent abuse
        - disabled by default, automatically disabled when in maintenance mode
        - *requires* a CDN or reverse proxy, not Apache/nginx/lighttpd/…!
    • Advanced Help integration to guide you (http://drupal.org/node/1413162)
    • DNS prefetching (http://drupal.org/node/982188)
    • CSS aggregation (http://drupal.org/node/1428530)
    • auto-balance files over multiple CDNs (http://drupal.org/node/1452092)
    • … and many more details that are taken care of automatically

But in some cases, simply altering the URL is not enough, that's where the
AdvAgg module comes in:

    If you've ever had any issues with CSS or JS files not behaving as
    desired, check out AdvAgg. The "Advanced CSS/JS Aggregation" module solves
    all issues that arise from having CSS/JS served from a CDN. Keeping track
    of changes to CSS/JS files, smart aggregate names, 404 protection,
    on-demand generation, works with private file system, Google CDN
    integration, CSS/JS compression, GZIP compression, caching, and smart
    bundling are some of the things AdvAgg does. It's also faster then core's
    file aggregation.

[1] http://fileconveyor.org/
[2] http://smushit.com/
[3] http://developer.yahoo.com/yui/compressor/
[4] http://code.google.com/closure/compiler/
[5] http://wimleers.com/article/key-properties-of-a-cdn


Supported CDNs
--------------
- Origin Pull mode: any Origin Pull CDN (or alternatively: domains that point
  to your main domain, by using so called "CNAME" DNS records).
- File Conveyor mode: any Origin Pull CDN and any push CDN that supports FTP.
  Support for other transfer protocols is welcomed and encouraged: your
  patches are welcome! Amazon S3, Amazon CloudFront and Rackspace CloudFiles
  are also supported.


Installation
------------
1) Place this module directory in your "modules" folder (this will usually be
   "sites/all/modules/"). Don't install your module in Drupal core's "modules"
   folder, since that will cause problems and is bad practice in general. If
   "sites/all/modules" doesn't exist yet, just create it.

2) Enable the module.

3) Visit "admin/config/development/cdn" to learn about the various settings.

4) Go to your CDN provider's control panel and set up a "CDN instance" (Amazon
   CloudFront calls this a "distribution"). There, you will have to specify
   the origin server (Amazon CloudFront calls this a "custom origin"), which
   is simply the domain name of your Drupal site.
   The CDN will provide you with a "delivery address", this is the address
   that we'll use to download files from the CDN instead of the Drupal server.
   Suppose this is `http://d85nwn7m5gl3y.cloudfront.net`.
   (It acts like a globally distributed, super fast proxy server.)

   Relevant links:
   - Amazon CloudFront: http://docs.amazonwebservices.com/AmazonCloudFront/latest/DeveloperGuide/CreatingDistributions.html?r=4212

5) Optionally, you can create a CNAME alias to the delivery address on your
   DNS server. This way, it's not immediately obvious from the links in the
   HTMl that you're using an external service (that's why it's also called a
   vanity domain name).
   However, if you're going to use your CDN in HTTPS mode, then using vanity
   domains will break things (because SSL certificates are bound to domain
   names).

6) Enter the domain name (`http://d85nwn7m5gl3y.cloudfront.net`, or the vanity
   domain/CNAME if you used that instead) at admin/settings/cdn/details. If
   you want to support HTTPS transparently, it is recommended to enter it as
   `//d85nwn7m5gl3y.cloudfront.net` instead — this is a protocol-relative URL.

7) Go to "admin/reports/status". The CDN module will report its status here.

8) Enable the display of statistics at "admin/config/development/cdn", browse
   your site with your root/admin (user id 1) account. The statistics will
   show which files are served from the CDN!


File Conveyor mode
------------------

1) If you want to use File Conveyor mode, install and configure the File
   Conveyor first. You can download it at http://fileconveyor.org/
   Then follow the instructions in the included INSTALL.txt and README.txt.
   Use the sample config.xml file that is included in this module, copy it to
   your File Conveyor installation and modify it to comply with your setup and
   to suit your needs. You will always need to modify this file to suit your
   needs.
   Note: the CDN integration module requires PDO extension for PHP to be
   installed, as well as the PDO SQLite driver.

2) Go to "admin/reports/status". The CDN module will report its status here.
   If you've enabled File Conveyor mode and have set up File Conveyor daemon,
   you will see some basic stats here as well, and you can check here to see
   if File Conveyor is currently running.
   You can also see here if you've applied the patches correctly!


Cross-Origin Resource Sharing (CORS)
------------------------------------
By integrating a CDN, and depending on your actual configuration, resources
might be served from (a) domain(s) different than your site's domain. This
could cause browsers to refuse to use certain resources since they violate the
same-origin policy. This primarily affects font and JavaScript files.

To circumvent this, you can configure your server to serve those files with an
additional Access-Control-Allow-Origin header, containing a space-separated
list of domains that are allowed to make cross-domain use of a resource. Note
that this will only work if your CDN provider does not strip this header.

For server-specific instructions on adding this header, see
http://www.w3.org/wiki/CORS_Enabled#At_the_HTTP_Server_level...

If you are unable to add this header, or if your CDN provider ignores it, you
can add the files to the CDN module's blacklist to exclude them being served
by the CDN, or in the case of fonts, you can embed them in stylesheets via
data URIs (see https://developer.mozilla.org/en/data_URIs).

The Far Future expiration functionality takes care of this automatically!


FAQ
---
Q: Is the CDN module compatible with Drupal's page caching?
A: Yes.

Q: Is the CDN module compatible with Drupal's "private files" functionality?
A: Yes. The CDN module won't break private files, they will continue to work
   the same way. However, it cannot serve private files from a CDN. Not every
   CDN supports protected/secured/authenticated file access, and those that do
   each have their own way of doing this (there is no standard). So private
   files will continue to be served by Drupal, which may or may not be
   acceptable for your use case.

Q: Why are JavaScript files not being served from the CDN?
A: The answer can be found at "admin/config/development/cdn/other".

Q: Why are CSS files not being served from the CDN?
A: This may be caused by your theme: http://drupal.org/node/1061588.

Q: Does this module only work with Apache or also with nginx, lighttpd, etc.?
A: This module only affects HTML, so it doesn't matter which web server you
   use!

Q: What does the config.xml file of the CDN module do?
A: Nothing. It only serves as a sample for using File Conveyor. It's used for
   nothing and can safely be deleted.

Q: How to use different CDNs based on the domain name of an i18n site?
A: See http://drupal.org/node/1483962#comment-5744830.


No cookies should be sent to the CDN
------------------------------------
Please note though that you should ensure no cookies are sent to the CDN: this 
would slow down HTTP requests to the CDN (since the requests become larger:
they piggyback the cookie data).
You can achieve this in two ways:
  1) When you are using cookies that are bound to your www subdomain only
     (i.e. not an example.com, but on www.example.com), you can safely use
     another subdomain for your CDN.
  2) When you are using cookies on your main domain (example.com), you'll have 
     to use a completely different domain for the CDN if you don't want 
     cookies to be sent.
     So then you should use the CDN's URL (e.g. myaccount.cdn.com). But now 
     you should be careful to avoid JavaScript issues: you may run into "same 
     origin policy" problems. See admin/config/development/cdn/other for
     details.

Drupal 7 no longer sets cookies for anonymous users.

If you just use the CDN's URL (e.g. myaccount.cdn.com), all cookie issues are
avoided automatically.


When using multiple servers/CDNs: picking one based on advanced criteria
------------------------------------------------------------------------
You only need this when you're using multiple servers/CDNs and you can't rely
on picking a server/CDN based on the file extension, i.e. if you need more
advanced criteria than only file extension.

NOTE: this function is only called for file X if >1 server/CDN is available
for file X.

For this purpose, you can implement the cdn_pick_server() function:
  /**
   * Implements cdn_pick_server().
   */
  function cdn_pick_server($servers_for_file) {
    // The data that you get - one nested array per server from which the file
    // can be served:
    //   $servers_for_file[0] = array('url' => 'http://cdn1.com/image.jpg', 'server' => 'cdn1.com')
    //   $servers_for_file[1] = array('url' => 'http://cdn2.net/image.jpg', 'server' => 'cdn2.net')

    $which = your_logic_to_pick_a_server();

    // Return one of the nested arrays.
    return $servers_for_file[$which];
  }

So to get the default behavior (pick the first server found), one would write:
  /**
   * Implements cdn_pick_server().
   */
  function cdn_pick_server($servers_for_file) {
    return $servers_for_file[0];
  }

Or if you want to balance the number of files served by each CDN (i.e. on
average, each CDN serves the same amount of files on a page) instead of
picking the CDN based purely on filetype, one could write:
  /**
   * Implements cdn_pick_server().
   */
  function cdn_pick_server($servers_for_file) {
    $filename = basename($servers_for_file[0]['url']);
    $unique_file_id = hexdec(substr(md5($filename), 0, 5));
    return $servers_for_file[$unique_file_id % count($servers_for_file)];
  }

Note: if you don't want to create a small module for this function, or if you
      would just like to experiment with this function, you can also enter the
      body of this function at admin/settings/cdn/other — it will work exactly
      the same!
      If you don't know what the "body" of a function is, it's the part
      between the curly brackets:
        function doSomething() {
          BODY
        }
      So, in the case of the cdn_pick_server() function, this is the body that
      you would enter:
        $filename = basename($servers_for_file[0]['url']);
        $unique_file_id = hexdec(substr(md5($filename), 0, 5));
        return $servers_for_file[$unique_file_id % count($servers_for_file)];


Sponsors
--------
* Port of Far Future expiration functionality to Drupal 7:
   ONE Agency, http://www.one-agency.be.


Author
------
Wim Leers ~ http://wimleers.com/

Version 1 of this module (for Drupal 6) was written as part of the bachelor
thesis of Wim Leers at Hasselt University.

http://wimleers.com/tags/bachelor-thesis
http://uhasselt.be/
