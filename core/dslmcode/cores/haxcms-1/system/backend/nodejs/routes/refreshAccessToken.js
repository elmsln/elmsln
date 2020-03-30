const HAXCMS = require('../lib/HAXCMS.js');
/**
 * @OA\Get(
 *    path="/refreshAccessToken",
 *    tags={"cms","user"},
 *    @OA\Response(
 *        response="200",
 *        description="User access token for refreshing JWT when it goes stale"
 *   )
 * )
 */
function refreshAccessToken(req, res) {
  // check that we have a valid refresh token
  const validRefresh = HAXCMS.validateRefreshToken(false, req);
  // if we have a valid refresh token then issue a new access token
  if (validRefresh) {
    res.send(HAXCMS.getJWT(validRefresh.user));
  }
  else {
    res.cookie('haxcms_refresh_token', '');
    res.send(401);
  }
}
module.exports = refreshAccessToken;