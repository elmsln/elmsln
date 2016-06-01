/**
 * @file
 * Adapted from https://github.com/GoogleChrome/samples/tree/gh-pages/service-worker
 * and https://jakearchibald.com/2014/offline-cookbook/
 */

"use strict";

// If at any point you want to force pages that use this service worker to start using a fresh
// cache, then increment the CACHE_VERSION value. It will kick off the service worker update
// flow and the old cache(s) will be purged as part of the activate event handler when the
// updated service worker is activated.
var CACHE_VERSION = 1/*cacheVersion*/;
var CACHE_EXCLUDE = [/*cacheConditionsExclude*/].map(function (r) {return new RegExp(r);});
var CACHE_URLS = [/*cacheUrls*/];
var CACHE_URLS_ASSETS = [/*cacheUrlsAssets*/];
var CACHE_OFFLINE_IMAGE = 'offline-image.png';
// @todo add all images from the manifest.
CACHE_URLS.push(CACHE_OFFLINE_IMAGE);

var CURRENT_CACHE = 'all-cache-v' + CACHE_VERSION;

// Perform install steps
self.addEventListener('install', function (event) {
  // Use the service woker ASAP.
  var tasks = [self.skipWaiting()];
  if (CACHE_URLS.length) {
    tasks.push(caches
      .open(CURRENT_CACHE)
      .then(function (cache) {
        return cache.addAll(CACHE_URLS.concat(CACHE_URLS_ASSETS));
      }));
  }
  event.waitUntil(Promise.all(tasks));
});

self.addEventListener('activate', function(event) {
  // Delete all caches that are not CURRENT_CACHE.
  var tasks = [
    self.clients.claim(),
    caches.keys().then(function(cacheNames) {
      return Promise.all(
        cacheNames.map(function(cacheName) {
          // Delete any cache that doesn't have our version.
          if (CURRENT_CACHE !== cacheName) {
            return caches.delete(cacheName);
          }
        })
      );
    })
  ];

  event.waitUntil(Promise.all(tasks));
});

/**
 * @todo move that when we start using plugins.
 *
 * @param {string} url
 *
 * @return {Function}
 */
function urlNotExcluded(url) {
  return function (condition) {
    return !condition.test(url);
  }
}

/**
 * Default offline page.
 *
 * @param {object} error
 *
 * @return {Response}
 */
function catchOffline(error) {
  return caches.match('/offline');
}

/**
 * Default offline Image.
 *
 * @param {object} error
 *
 * @return {Response}
 */
function catchOfflineImage(error) {
  return caches.match(CACHE_OFFLINE_IMAGE);
}

/**
 * Default catch callback.
 *
 * @param {Error} error
 */
function logError(error) {
  console.log(error);
  return Response.error();
}

/**
 * Test if an asset should be cached.
 *
 * @param {URL} assetUrl
 *
 * @return {boolean}
 */
function isCacheableAsset(assetUrl) {

  // Url is not an asset, don't cache.
  if (!isAssetUrl(assetUrl)) {
    return false;
  }
  // It's an asset but not an image, always cache.
  if (!isImageUrl(assetUrl)) {
    return true;
  }
  // If it looks like an image, only cache images that are part of
  // assets cached on install.
  var assetPath = assetUrl.href.replace(assetUrl.origin, '');
  return CACHE_URLS.concat(CACHE_URLS_ASSETS).some(function (url) { return assetPath === url; });
}

/**
 * Helper for Assets files.
 *
 * @param {URL} assetUrl
 *
 * @return {boolean}
 */
function isAssetUrl(assetUrl) {
  return /\.(js|css|jpe?g|png|gif|svg|webp|eot|woff2?|ttf|otf)\??/.test(assetUrl.href);
}

/**
 * Helper for image files.
 *
 * @param {URL} imageUrl
 *
 * @return {boolean}
 */
function isImageUrl(imageUrl) {
  return /\.(jpe?g|png|gif|svg|webp)\??/.test(imageUrl.href);
}


/**
 * Mix of several strategies:
 *  - only cache GET requests.
 *  - for js/css/fonts assets, use stale while revalidate.
 *  - for html pages, use network with cache fallback.
 *  - Do not cache images or HTTP errors and redirects.
 */
self.addEventListener('fetch', function (event) {

  /**
   * @param {Request} request
   *
   * @return {Promise}
   */
  function fetchRessourceFromCache(request) {
    return caches.match(request.url ? request : event.request);
  }

  /**
   * Returns the cached version or reject the promise.
   *
   * @param {undefined|Response} response
   *
   * @return {Promise}
   */
  function returnRessourceFromCache(response) {
    if (!response) {
      return Promise.reject(new Error('Ressource not in cache'));
    }
    return response;
  }

  /**
   *
   * @return {Promise}
   */
  function fetchRessourceFromNetwork() {
    return fetch(event.request);
  }

  /**
   * @param {Response} response
   *
   * @return {Promise}
   */
  function cacheNetworkResponse(response) {
    // Don't cache redirects or errors.
    if (response.ok) {
      // Copy now and not in the then() because by that time it's too late,
      // the request has already been used and can't be touched again.
      var copy = response.clone();
      caches
        .open(CURRENT_CACHE)
        .then(function (cache) {
          return cache.put(event.request, copy);
        })
        .catch(logError);
    }
    else {
      console.log("Response not cacheable: ", response);
    }
    return response;
  }

  var url = new URL(event.request.url);
  var isMethodGet = event.request.method === 'GET';
  var notExcludedPath = CACHE_EXCLUDE.every(urlNotExcluded(url.href));
  var includedProtocol = ['http:', 'https:'].indexOf(url.protocol) !== -1;
  // @todo cache views ajax request by igoring methods when putting in cache.

  var makeRequest = {
    networkWithOfflineImageFallback: function (request) {
      return fetch(request)
        .catch(catchOfflineImage)
        .catch(logError);
    },
    staleWhileRevalidate: function (request) {
      return fetchRessourceFromCache(request)
        .then(returnRessourceFromCache)
        .catch(fetchRessourceFromNetwork)
        .then(cacheNetworkResponse)
        .catch(logError);
    },
    networkWithCacheFallback: function (request) {
      return fetch(request)
        .then(cacheNetworkResponse)
        .catch(fetchRessourceFromCache)
        .then(returnRessourceFromCache)
        .catch(catchOffline);
    }
  };

  // Make sure the url is one we don't exclude from cache.
  if (isMethodGet && includedProtocol && notExcludedPath) {
    // If it's an asset: stale while revalidate.
    if (isCacheableAsset(url)) {
      event.respondWith(makeRequest.staleWhileRevalidate(event.request));
    }
    // Don't cache images.
    else if (isImageUrl(url)) {
      event.respondWith(makeRequest.networkWithOfflineImageFallback(event.request));
    }
    // Other ressources: network with cache fallback.
    else {
      event.respondWith(makeRequest.networkWithCacheFallback(event.request));
    }
  }
  else {
    console.log('Excluded URL: ', event.request.url);
  }
});

