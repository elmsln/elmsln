const HAXCMS = require('../lib/HAXCMS.js');
const explode = require('locutus/php/strings/explode');
const filter_var = require('../lib/filter_var.js');
/**
   * @OA\Post(
   *    path="/gitImportSite",
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
   *                      "git": {
   *                        "url": ""
   *                      }
   *                    },
   *                 }
   *             )
   *         )
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Create a new site from a git repo reference"
   *   )
   * )
   */
  async function gitImportSite(req, res) {
    if (HAXCMS.validateRequestToken()) {
      if ((req.body['site']['git']['url'])) {
        repoUrl = req.body['site']['git']['url'];
        // make sure there's a .git in the address
        if (filter_var(repoUrl, FILTER_VALIDATE_URL) !== false &&
            strpos(repoUrl, '.git')
          ) {
          ary = explode('/', repoUrl.replace('.git', ''));
          repo_path = ary.pop();
          git = new Git();
          // @todo check if this fails
          directory = HAXCMS.HAXCMS_ROOT + '/' + HAXCMS.sitesDirectory + '/' + repo_path;
          repo = git.create(directory);
          repo = git.open(directory, true);
          repo.set_remote("origin", repoUrl);
          repo.pull('origin', 'master');
          // load the site that we SHOULD have just pulled in
          if (site = await HAXCMS.loadSite(repo_path)) {
            res.send({
              'manifest': site.manifest
            });
          }
          else {
            res.send(500);
          }
        }
      }
      res.send(500);
    }
    else {
      res.send(403);
    }
  }
  module.exports = gitImportSite;