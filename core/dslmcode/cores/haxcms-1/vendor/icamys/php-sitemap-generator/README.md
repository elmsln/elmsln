PHP Sitemap Generator
=====================

This class can be used to generate sitemaps.

Internally uses SplFixedArrays, thus is faster and uses less memory.

Usage example:

```php
<?php

include "src/SitemapGenerator.php";

$generator = new \Icamys\SitemapGenerator\SitemapGenerator('example.com');

// will create also compressed (gzipped) sitemap
$generator->createGZipFile = true;

// determine how many urls should be put into one file
// according to standard protocol 50000 is maximum value (see http://www.sitemaps.org/protocol.html)
$generator->maxURLsPerSitemap = 50000;

// sitemap file name
$generator->sitemapFileName = "sitemap.xml";

// sitemap index file name
$generator->sitemapIndexFileName = "sitemap-index.xml";

// adding url `loc`, `lastmodified`, `changefreq`, `priority`
$generator->addUrl('http://example.com/url/path/', new DateTime(), 'always', '0.5');

// generating internally a sitemap
$generator->createSitemap();

// writing early generated sitemap to file
$generator->writeSitemap();
```

Inspired by @pawelantczak.