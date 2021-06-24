const HAXCMS = require('../lib/HAXCMS.js');

/**
   * @OA\Post(
   *    path="/setUserPhoto",
   *    tags={"cms","authenticated","user"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Set the user's uploaded photo"
   *   )
   * )
   */
  function setUserPhoto(req, res) {
    // @todo might want to scrub prior to this level but not sure
    if (($_FILES['file-upload'])) {
      upload = $_FILES['file-upload'];
      let file = new HAXCMSFile();
      fileResult = file.save(upload, 'system/user/files', null, 'thumbnail');
      if (fileResult['status'] == 500) {
        res.send(500);
      }
      // save this back to the user data object
      values = {};
      values.userPicture = fileResult['data']['file']['fullUrl'];
      HAXCMS.setUserData(values);
      res.send(fileResult);
    }
  }
  module.exports = setUserPhoto;