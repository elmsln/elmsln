const HAXCMS = require('../lib/HAXCMS.js');

/**
   * @OA\Post(
   *    path="/getNodeFields",
   *    tags={"cms","authenticated","node","form"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Update the alternative formats surrounding a site"
   *   )
   * )
   */
  function getNodeFields(req, res) {
    if (HAXCMS.validateRequestToken(null, 'form')) {
      let site = HAXCMS.loadSite(req.body['site']['name']);
      if (page = site.loadNode(req.body['node']['id'])) {
        schema = site.loadNodeFieldSchema(page);
        return schema;
      }
    } else {
        req.send(403);
    }
  }
  module.exports = getNodeFields;