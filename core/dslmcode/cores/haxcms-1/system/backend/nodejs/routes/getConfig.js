const HAXCMS = require('../lib/HAXCMS.js');

/**
   * @OA\Post(
   *    path="/getConfig",
   *    tags={"cms","authenticated","settings"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Get configuration for HAXcms itself"
   *   )
   * )
   */
  function getConfig(req, res) {
    response = {};
    response.schema = HAXCMS.getConfigSchema();
    response.values = HAXCMS.config;
    for(var key in response.values.appStore) {
      let val = response.values.appStore[key];
      if (key !== 'apiKeys') {
        delete (response.values.appStore[key]);
      }
    }
    retres.send(response);
  }
  module.exports = getConfig;