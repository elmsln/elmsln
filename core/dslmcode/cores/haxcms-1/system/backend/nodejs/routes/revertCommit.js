const HAXCMS = require('../lib/HAXCMS.js');

/**
   * @OA\Post(
   *    path="/revertCommit",
   *    tags={"cms","authenticated","meta","git","site"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Revert the last commit to the git repo backing the site"
   *   )
   * )
   */
  async function revertCommit(req, res) {
    let site = await HAXCMS.loadSite(req.body['site']['name']);
    // this will revert the top commit
    await site.gitRevert();
    res.send(true);
  }
  module.exports = revertCommit;