const HAXCMS = require('../lib/HAXCMS.js');

/**
   * @OA\Post(
   *    path="/saveFile",
   *    tags={"hax","authenticated","file"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Parameter(
   *         name="file-upload",
   *         description="File to upload",
   *         in="header",
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
   *                 @OA\Property(
   *                     property="node",
   *                     type="object"
   *                 ),
   *                 required={"site"},
   *                 example={
   *                    "site": {
   *                      "name": "mynewsite"
   *                    },
   *                    "node": {
   *                      "id": ""
   *                    }
   *                 }
   *             )
   *         )
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="User is uploading a file to present in a site"
   *   )
   * )
   */
  function saveFile(req, res) {
    // @todo might want to scrub prior to this level but not sure
    if (($_FILES['file-upload'])) {
      let site = HAXCMS.loadSite(req.body['site']['name']);
      // update the page's content, using manifest to find it
      // this ensures that writing is always to what the file system
      // determines to be the correct page
      page = site.loadNode(req.body['node']['id']);
      upload = $_FILES['file-upload'];
      file = new HAXCMSFile();
      fileResult = file.save(upload, site, page);
      if (fileResult['status'] == 500) {
        res.send(500);
      }
      site.gitCommit('File added: ' + upload['name']);
      return fileResult;
    }
  }
  module.exports = saveFile;