const HAXCMS = require('../lib/HAXCMS.js');

/**
   * @OA\Post(
   *    path="/syncSite",
   *    tags={"cms","authenticated","git","site"},
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
   *        description="Sync the site using the git config settings in the site.json file"
   *   )
   * )
   */
  async function syncSite(req, res) {
    // ensure we have something we can load and ship back out the door
    if (site = await HAXCMS.loadSite(req.body['site']['name'])) {
      // local publishing options, then defer to system, then make some up...
      if ((site.manifest.metadata.site.git)) {
          gitSettings = site.manifest.metadata.site.git;
      } else if ((HAXCMS.config.site.git)) {
          gitSettings = HAXCMS.config.site.git;
      } else {
          gitSettings = {};
          gitSettings.vendor = 'github';
          gitSettings.branch = 'master';
          gitSettings.staticBranch = 'gh-pages';
          gitSettings.url = '';
      }
      if ((gitSettings)) {
          git = new Git();
          siteDirectoryPath = site.directory + '/' + site.manifest.metadata.site.name;
          repo = git.open(siteDirectoryPath, true);
          // ensure we're on branch, most likley master
          await repo.checkout(gitSettings.branch);
          await repo.pull('origin', gitSettings.branch);
          await repo.push('origin', gitSettings.branch);
          res.send(true);
      }
    } else {
      res.send(500);
    }
  }
  module.exports = syncSite;