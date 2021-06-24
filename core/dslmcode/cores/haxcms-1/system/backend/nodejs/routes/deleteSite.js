const fs = require('fs-extra');
const HAXCMS = require('../lib/HAXCMS.js');

/**
   * @OA\Post(
   *    path="/deleteSite",
   *    tags={"cms","authenticated","site"},
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
   *                     property="site",
   *                     type="object"
   *                 ),
   *                 required={"site"},
   *                 example={
   *                    "site": {
   *                      "name": "mynewsite"
   *                    },
   *                 }
   *             )
   *         )
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Delete a site from the file system"
   *   )
   * )
   */
  async function deleteSite(req, res) {
    let site = await HAXCMS.loadSite(req.body['site']['name']);
    if (site.name) {
      await fs.unlink(
        site.directory + '/' + site.manifest.metadata.site.name
      );
      res.send({
        'name': site.name,
        'detail': 'Site deleted',
      });
    }
    else {
      res.send(500);
    }
  }
  module.exports = deleteSite;