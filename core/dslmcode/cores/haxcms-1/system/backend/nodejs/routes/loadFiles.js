const HAXCMS = require('../lib/HAXCMS.js');

/**
   * @OA\Post(
   *    path="/loadFiles",
   *    tags={"hax","authenticated","file"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Load existing files for presentation in HAX find area"
   *   )
   * )
   */
  function loadFiles(req, res) {
    // @todo make this load the files out of the JSON outline schema and only return them
    return [];
  }
  module.exports = loadFiles;