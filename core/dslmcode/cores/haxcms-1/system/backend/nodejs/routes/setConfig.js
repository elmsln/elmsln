const HAXCMS = require('../lib/HAXCMS.js');

/**
   * @OA\Post(
   *    path="/setConfig",
   *    tags={"cms","authenticated","form","settings"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\RequestBody(
   *        @OA\MediaType(
   *             mediaType="application/json",
   *             @OA\Schema(
   *                 @OA\Property(
   *                     property="values",
   *                     type="object"
   *                 ),
   *                 required={"site"},
   *                 example={
   *                    "values": {}
   *                 }
   *             )
   *         )
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Set configuration for HAXcms"
   *   )
   * )
   */
  function setConfig(req, res) {
    if (HAXCMS.validateRequestToken()) {
      values = this.rawParams['values'];
      val = {};
      if ((values.apis) && (values.appStore.apiKeys)) {
        val.apis = values.apis;
      }
      if ((values.publishing)) {
        val.publishing = values.publishing;
      }
      response = HAXCMS.setConfig(val);
      return response;
    } else {
        res.send(403);
    }
  }
  module.exports = setConfig;