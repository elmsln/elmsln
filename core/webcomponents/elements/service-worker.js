/**
 * Copyright 2016 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

// DO NOT EDIT THIS GENERATED OUTPUT DIRECTLY!
// This file should be overwritten as part of your build process.
// If you need to extend the behavior of the generated service worker, the best approach is to write
// additional code and include it using the importScripts option:
//   https://github.com/GoogleChrome/sw-precache#importscripts-arraystring
//
// Alternatively, it's possible to make changes to the underlying template file and then use that as the
// new base for generating output, via the templateFilePath option:
//   https://github.com/GoogleChrome/sw-precache#templatefilepath-string
//
// If you go that route, make sure that whenever you update your sw-precache dependency, you reconcile any
// changes made to this original template file with your modified copy.

// This generated service worker JavaScript will precache your site's resources.
// The code needs to be saved in a .js file at the top-level of your site, and registered
// from your pages in order to be used. See
// https://github.com/googlechrome/sw-precache/blob/master/demo/app/js/service-worker-registration.js
// for an example of how you can register this script and handle various service worker events.

/* eslint-env worker, serviceworker */
/* eslint-disable indent, no-unused-vars, no-multiple-empty-lines, max-nested-callbacks, space-before-function-paren, quotes, comma-spacing */
'use strict';

var precacheConfig = [["bower_components/a11y-behaviors/a11y-behaviors.html","3b7d7c4201c2fe8540ea7dd472b6dd9e"],["bower_components/a11y-media-player/screenfull-lib.html","949631786f4d54f1b11c10d63b452f5c"],["bower_components/ace-builds/src-min-noconflict/ace.js","01097c38aa87f4a3d6e6b2227ff25f8a"],["bower_components/ace-builds/src-min-noconflict/ext-searchbox.js","26bedf81fbd581dc2eb22a024d252098"],["bower_components/app-route/app-route-converter-behavior.html","ab302160ad8b1bdf4e06d29b674751f2"],["bower_components/chartist-render/chartist-lib.html","fd5322879ff1c1c67697708927420e2e"],["bower_components/chartist/dist/chartist.min.css","2d7704eae3ea09f0509e321d38cf0ce7"],["bower_components/chartist/dist/chartist.min.js","cced1dd6ecf55148e3c3760563e88ccc"],["bower_components/document-register-element/build/document-register-element.js","5f5159c8060023f40525b20310a27658"],["bower_components/font-roboto/roboto.html","3dd603efe9524a774943ee9bf2f51532"],["bower_components/hax-body-behaviors/hax-body-behaviors.html","58bf7ca334f697d4c9228020320d1d33"],["bower_components/img-pan-zoom/openseadragon-import.html","4ba3c9b7001851e85a58ff3845f356be"],["bower_components/img-pan-zoom/openseadragon/openseadragon.min.js","1b81fb8be5624086946b3f5cf3df732c"],["bower_components/intl-messageformat/dist/intl-messageformat.min.js","a490f83a6cb5b12763adb727d9358184"],["bower_components/jarallax/dist/jarallax-element.min.js","556c9e7cf774651d6faed7ff732a4197"],["bower_components/jarallax/dist/jarallax-video.min.js","20caf2c15d19f686805c22962f9f5636"],["bower_components/jarallax/dist/jarallax.min.js","7ff4ebeec329e6b5157fdb063eae600e"],["bower_components/juicy-ace-editor/juicy-ace-editor.html","35e7ddc2f6f48a662f142d91a8f98967"],["bower_components/marked-element/marked-import.html","0350f69e2dab93972162fcaaf3a1c5ce"],["bower_components/marked/lib/marked.js","ac67331ad97a7ead5c21b29adc1b69a9"],["bower_components/materializecss-styles/colors.html","3b32e88f3a78757033bc534c39c7de7b"],["bower_components/materializecss-styles/materializecss-styles.html","4c5e2198659d1978964021c1cba870da"],["bower_components/materializecss-styles/shapes.html","b26fba499cc9920bc92bf2fcbf4104f5"],["bower_components/media-behaviors/media-behaviors.html","44ab13c9349e85b2120845597fd8a08f"],["bower_components/moment-element/moment-import.html","0b56a3d391fc4105c21227fdcbd0c782"],["bower_components/moment/min/moment.min.js","5bdfb7b94c25996eaea264dda65fc931"],["bower_components/neon-animation/web-animations.html","aa5266664b17a9a7d7ebf0c4e6fcf8c9"],["bower_components/paper-avatar/lib/jdenticon-1.4.0.min.js","8512e389c2ab6409b18b113aec4a64d0"],["bower_components/paper-avatar/lib/md5.min.js","a1c239706f9310dc6068257cc9de9247"],["bower_components/paper-spinner/paper-spinner-styles.html","f6b2d42a9d2262fafb034ea0f802fc80"],["bower_components/polymer/polymer-micro.html","c1b5414d9c75907d0a59e76e6fb4ede9"],["bower_components/polymer/polymer-mini.html","31d343f6a4c3b29de798efa109698218"],["bower_components/q-r/q-r-import.html","f4cec2661bdad867e58d4498743eb02a"],["bower_components/qr-code/src/qr-code.js","826a5161d42b49aeeb79ec6a3354d14e"],["bower_components/qrjs/qr.js","4424f3b5fa571d087ce4ddec45f2cd01"],["bower_components/schema-behaviors/schema-behaviors.html","37a0a314770647564accbd99c6bda650"],["bower_components/screenfull/dist/screenfull.js","c0ab7240cf702369562bcbb9b31a14e2"],["bower_components/secure-request/secure-request.html","533cddeaed267695907319c5e367d520"],["bower_components/vaadin-grid/vaadin-grid-active-item-behavior.html","9964b513d0fe798a3788fd9beb7b41a2"],["bower_components/vaadin-grid/vaadin-grid-array-data-provider-behavior.html","7fad841b15ae079ef49ace58f32fcd3e"],["bower_components/vaadin-grid/vaadin-grid-cell-click-behavior.html","8ba86e96a4a5292f945f86a4feb53ccc"],["bower_components/vaadin-grid/vaadin-grid-column-reordering-behavior.html","02e5138ff1befdc27535c42a8d4f6e9a"],["bower_components/vaadin-grid/vaadin-grid-data-provider-behavior.html","4dba0b60b5c204e639e8f3814511f303"],["bower_components/vaadin-grid/vaadin-grid-dynamic-columns-behavior.html","85bc7f6f102afe8cfd98fc4c2fcf3597"],["bower_components/vaadin-grid/vaadin-grid-filter-behavior.html","7a914656065295d11ec8efe2e086a676"],["bower_components/vaadin-grid/vaadin-grid-focusable-cell-container-behavior.html","42a6af7ac8b913baa5fd02e7f4e79b39"],["bower_components/vaadin-grid/vaadin-grid-selection-behavior.html","b63569159f20e47fc7ae4343eef31e99"],["bower_components/vaadin-grid/vaadin-grid-sort-behavior.html","daf4d101ba27287805f089cf5ab5dd9b"],["bower_components/vaadin-grid/vaadin-grid-table-header-footer.html","d39d6ef287264aa2578d483d23ed4de2"],["bower_components/wave-player/wavesurferimport.html","75d3227c2d7f6cf8037d87250b3284a4"],["bower_components/wavesurfer.js/dist/wavesurfer.min.js","ca2262381009ed83e0288b12fea85a52"],["bower_components/web-animations-js/web-animations-next-lite.min.html","97a672e5f554d9e7ac9971e5c7fda866"],["bower_components/web-animations-js/web-animations-next-lite.min.js","6987153fb85077d06d0471fd317650a3"],["index.html","baa806f12226c9b2b3de2b73854a854b"],["src/build-app/build-app.html","dab280551e9615391690747f08b0ee76"]];
var cacheName = 'sw-precache-v3--' + (self.registration ? self.registration.scope : '');


var ignoreUrlParametersMatching = [/^utm_/];



var addDirectoryIndex = function (originalUrl, index) {
    var url = new URL(originalUrl);
    if (url.pathname.slice(-1) === '/') {
      url.pathname += index;
    }
    return url.toString();
  };

var cleanResponse = function (originalResponse) {
    // If this is not a redirected response, then we don't have to do anything.
    if (!originalResponse.redirected) {
      return Promise.resolve(originalResponse);
    }

    // Firefox 50 and below doesn't support the Response.body stream, so we may
    // need to read the entire body to memory as a Blob.
    var bodyPromise = 'body' in originalResponse ?
      Promise.resolve(originalResponse.body) :
      originalResponse.blob();

    return bodyPromise.then(function (body) {
      // new Response() is happy when passed either a stream or a Blob.
      return new Response(body, {
        headers: originalResponse.headers,
        status: originalResponse.status,
        statusText: originalResponse.statusText
      });
    });
  };

var createCacheKey = function (originalUrl, paramName, paramValue,
                           dontCacheBustUrlsMatching) {
    // Create a new URL object to avoid modifying originalUrl.
    var url = new URL(originalUrl);

    // If dontCacheBustUrlsMatching is not set, or if we don't have a match,
    // then add in the extra cache-busting URL parameter.
    if (!dontCacheBustUrlsMatching ||
        !(url.pathname.match(dontCacheBustUrlsMatching))) {
      url.search += (url.search ? '&' : '') +
        encodeURIComponent(paramName) + '=' + encodeURIComponent(paramValue);
    }

    return url.toString();
  };

var isPathWhitelisted = function (whitelist, absoluteUrlString) {
    // If the whitelist is empty, then consider all URLs to be whitelisted.
    if (whitelist.length === 0) {
      return true;
    }

    // Otherwise compare each path regex to the path of the URL passed in.
    var path = (new URL(absoluteUrlString)).pathname;
    return whitelist.some(function (whitelistedPathRegex) {
      return path.match(whitelistedPathRegex);
    });
  };

var stripIgnoredUrlParameters = function (originalUrl,
    ignoreUrlParametersMatching) {
    var url = new URL(originalUrl);
    // Remove the hash; see https://github.com/GoogleChrome/sw-precache/issues/290
    url.hash = '';

    url.search = url.search.slice(1) // Exclude initial '?'
      .split('&') // Split into an array of 'key=value' strings
      .map(function (kv) {
        return kv.split('='); // Split each 'key=value' string into a [key, value] array
      })
      .filter(function (kv) {
        return ignoreUrlParametersMatching.every(function (ignoredRegex) {
          return !ignoredRegex.test(kv[0]); // Return true iff the key doesn't match any of the regexes.
        });
      })
      .map(function (kv) {
        return kv.join('='); // Join each [key, value] array into a 'key=value' string
      })
      .join('&'); // Join the array of 'key=value' strings into a string with '&' in between each

    return url.toString();
  };


var hashParamName = '_sw-precache';
var urlsToCacheKeys = new Map(
  precacheConfig.map(function (item) {
    var relativeUrl = item[0];
    var hash = item[1];
    var absoluteUrl = new URL(relativeUrl, self.location);
    var cacheKey = createCacheKey(absoluteUrl, hashParamName, hash, false);
    return [absoluteUrl.toString(), cacheKey];
  })
);

function setOfCachedUrls(cache) {
  return cache.keys().then(function (requests) {
    return requests.map(function (request) {
      return request.url;
    });
  }).then(function (urls) {
    return new Set(urls);
  });
}

self.addEventListener('install', function (event) {
  event.waitUntil(
    caches.open(cacheName).then(function (cache) {
      return setOfCachedUrls(cache).then(function (cachedUrls) {
        return Promise.all(
          Array.from(urlsToCacheKeys.values()).map(function (cacheKey) {
            // If we don't have a key matching url in the cache already, add it.
            if (!cachedUrls.has(cacheKey)) {
              var request = new Request(cacheKey, {credentials: 'same-origin'});
              return fetch(request).then(function (response) {
                // Bail out of installation unless we get back a 200 OK for
                // every request.
                if (!response.ok) {
                  throw new Error('Request for ' + cacheKey + ' returned a ' +
                    'response with status ' + response.status);
                }

                return cleanResponse(response).then(function (responseToCache) {
                  return cache.put(cacheKey, responseToCache);
                });
              });
            }
          })
        );
      });
    }).then(function () {
      
      // Force the SW to transition from installing -> active state
      return self.skipWaiting();
      
    })
  );
});

self.addEventListener('activate', function (event) {
  var setOfExpectedUrls = new Set(urlsToCacheKeys.values());

  event.waitUntil(
    caches.open(cacheName).then(function (cache) {
      return cache.keys().then(function (existingRequests) {
        return Promise.all(
          existingRequests.map(function (existingRequest) {
            if (!setOfExpectedUrls.has(existingRequest.url)) {
              return cache.delete(existingRequest);
            }
          })
        );
      });
    }).then(function () {
      
      return self.clients.claim();
      
    })
  );
});


self.addEventListener('fetch', function (event) {
  if (event.request.method === 'GET') {
    // Should we call event.respondWith() inside this fetch event handler?
    // This needs to be determined synchronously, which will give other fetch
    // handlers a chance to handle the request if need be.
    var shouldRespond;

    // First, remove all the ignored parameters and hash fragment, and see if we
    // have that URL in our cache. If so, great! shouldRespond will be true.
    var url = stripIgnoredUrlParameters(event.request.url, ignoreUrlParametersMatching);
    shouldRespond = urlsToCacheKeys.has(url);

    // If shouldRespond is false, check again, this time with 'index.html'
    // (or whatever the directoryIndex option is set to) at the end.
    var directoryIndex = '';
    if (!shouldRespond && directoryIndex) {
      url = addDirectoryIndex(url, directoryIndex);
      shouldRespond = urlsToCacheKeys.has(url);
    }

    // If shouldRespond is still false, check to see if this is a navigation
    // request, and if so, whether the URL matches navigateFallbackWhitelist.
    var navigateFallback = 'index.html';
    if (!shouldRespond &&
        navigateFallback &&
        (event.request.mode === 'navigate') &&
        isPathWhitelisted(["\\/[^\\/\\.]*(\\?|$)"], event.request.url)) {
      url = new URL(navigateFallback, self.location).toString();
      shouldRespond = urlsToCacheKeys.has(url);
    }

    // If shouldRespond was set to true at any point, then call
    // event.respondWith(), using the appropriate cache key.
    if (shouldRespond) {
      event.respondWith(
        caches.open(cacheName).then(function (cache) {
          return cache.match(urlsToCacheKeys.get(url)).then(function (response) {
            if (response) {
              return response;
            }
            throw Error('The cached response that was expected is missing.');
          });
        }).catch(function (e) {
          // Fall back to just fetch()ing the request if some unexpected error
          // prevented the cached response from being valid.
          console.warn('Couldn\'t serve response for "%s" from cache: %O', event.request.url, e);
          return fetch(event.request);
        })
      );
    }
  }
});







