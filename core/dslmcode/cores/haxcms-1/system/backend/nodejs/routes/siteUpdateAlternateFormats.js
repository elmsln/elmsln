const HAXCMS = require('../lib/HAXCMS.js');

/**
   * @OA\Post(
   *    path="/siteUpdateAlternateFormats",
   *    tags={"cms","authenticated","meta"},
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
  async function siteUpdateAlternateFormats(req, res) {
    let format = null;
    let site = await HAXCMS.loadSite(req.body['site']['name']);
    if ((req.body['format'])) {
      format = req.body['format'];
    }
    await site.updateAlternateFormats(format);
    res.send(true);
  }
  module.exports = siteUpdateAlternateFormats;