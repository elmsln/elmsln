const HAXCMS = require('../lib/HAXCMS.js');
/**
 * @OA\Post(
 *    path="/getUserData",
 *    tags={"cms","authenticated","user","settings"},
 *    @OA\Parameter(
 *         name="jwt",
 *         description="JSON Web token, obtain by using  /login",
 *         in="query",
 *         required=true,
 *         @OA\Schema(type="string")
 *    ),
 *    @OA\Response(
 *        response="200",
 *        description="Load data about the logged in user"
 *   )
 * )
 */
  function getUserData(req, res) {
    const returnData = {
      status: 200,
      data: HAXCMS.userData
    };
    res.send(returnData);
  }

module.exports = getUserData;