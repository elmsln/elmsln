const HAXCMS = require('../lib/HAXCMS.js');

/**
   * @OA\Post(
   *    path="/cloneSite",
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
   *        description="Clone a site by copying and renaming the folder on file system"
   *   )
   * )
   */
  async function cloneSite(req, res) {
    let site = await HAXCMS.loadSite(req.body['site']['name']);
    let siteDirectoryPath = site.directory + '/' + site.manifest.metadata.site.name;
    let cloneName = HAXCMS.getUniqueName(site.name);
    // ensure the path to the new folder is valid
    await fs.mirror(
        HAXCMS.HAXCMS_ROOT + '/' + HAXCMS.sitesDirectory + '/' + site.name,
        HAXCMS.HAXCMS_ROOT + '/' + HAXCMS.sitesDirectory + '/' + cloneName
    );
    // we need to then load and rewrite the site name var or it will conflict given the name change
    let newSite = await HAXCMS.loadSite(cloneName);
    newSite.manifest.metadata.site.name = cloneName;
    await newSite.save();
    res.send({
      'link':
        HAXCMS.basePath +
        HAXCMS.sitesDirectory +
        '/' +
        cloneName,
      'name': cloneName
    });
  }
  module.exports = cloneSite;