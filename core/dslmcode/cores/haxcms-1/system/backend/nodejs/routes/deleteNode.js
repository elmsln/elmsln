const HAXCMS = require('../lib/HAXCMS.js');

/**
   * @OA\Post(
   *    path="/deleteNode",
   *    tags={"cms","authenticated","node"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Delete a node"
   *   )
   * )
   */
  async function deleteNode(req, res) {
    let site = await HAXCMS.loadSite(req.body['site']['name']);
    // update the page's content, using manifest to find it
    // this ensures that writing is always to what the file system
    // determines to be the correct page
    if (page = site.loadNode(req.body['node']['id'])) {
        if (await site.deleteNode(page) === false) {
          res.send(500);
        } else {
          await site.gitCommit(
            'Page deleted: ' + page.title + ' (' + page.id + ')'
          );
          res.send(page);
        }
    } else {
        res.send(500);
    }
  }
  module.exports = deleteNode;