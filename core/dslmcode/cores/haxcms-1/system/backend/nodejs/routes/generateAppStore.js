const HAXCMS = require('../lib/HAXCMS.js');
const HAXAppStoreService = require('../lib/HAXAppStoreService.js');
const AppStoreService = new HAXAppStoreService();
/**
 * @OA\Get(
 *    path="/generateAppStore",
 *    tags={"hax","api"},
 *    @OA\Parameter(
 *         name="app-store-token",
 *         description="security token for appstore",
 *         in="query",
 *         required=true,
 *         @OA\Schema(type="string")
 *    ),
 *    @OA\Response(
 *        response="200",
 *        description="Generate the AppStore spec for HAX editor directions"
 *   )
 * )
 */
function generateAppStore(req, res) {
  let returnData = {};
  // test if this is a valid user login with this specialty token that HAX looks for
  if (
    req.query['app-store-token'] &&
    HAXCMS.validateRequestToken(req.query['app-store-token'], 'appstore', req.query)
  ) {
    let apikeys = {};
    let baseApps = AppStoreService.baseSupportedApps();
    for (var key in baseApps) {
      if (
        HAXCMS.config.appStore.apiKeys[key] &&
        HAXCMS.config.appStore.apiKeys[key] != ''
      ) {
        apikeys[key] = HAXCMS.config.appStore.apiKeys[key];
      }
    }
    let appStore = AppStoreService.loadBaseAppStore(apikeys);
    // pull in the core one we supply, though only upload works currently
    tmp = HAXCMS.siteConnectionJSON();
    appStore.push(tmp);
    let staxList,bloxList,autoloaderList;
    if (HAXCMS.config.appStore && HAXCMS.config.appStore.stax) {
        staxList = HAXCMS.config.appStore.stax;
    } else {
        staxList = AppStoreService.loadBaseStax();
    }
    if (HAXCMS.config.appStore && HAXCMS.config.appStore.blox) {
        bloxList = HAXCMS.config.appStore.blox;
    } else {
        bloxList = AppStoreService.loadBaseBlox();
    }
    if (HAXCMS.config.appStore && HAXCMS.config.appStore.autoloader) {
        autoloaderList = HAXCMS.config.appStore.autoloader;
    } else {
        autoloaderList = 
      [
        "video-player",
        "meme-maker",
        "lrn-aside",
        "grid-plate",
        "magazine-cover",
        "image-compare-slider",
        "license-element",
        "self-check",
        "multiple-choice",
        "oer-schema",
        "hero-banner",
        "task-list",
        "lrn-table",
        "media-image",
        "lrndesign-blockquote",
        "a11y-gif-player",
        "wikipedia-query",
        "lrn-vocab",
        "full-width-image",
        "person-testimonial",
        "citation-element",
        "stop-note",
        "place-holder",
        "lrn-math",
        "q-r",
        "lrndesign-gallery",
        "lrndesign-timeline"
      ];
    }
    returnData = {
        'status': 200,
        'apps': appStore,
        'stax': staxList,
        'blox': bloxList,
        'autoloader': autoloaderList
    };
  }
  res.send(returnData);
}
  module.exports = generateAppStore;