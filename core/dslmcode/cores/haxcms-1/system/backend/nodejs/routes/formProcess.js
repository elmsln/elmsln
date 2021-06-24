const HAXCMS = require('../lib/HAXCMS.js');

/**
   * @OA\Post(
   *    path="/formProcess",
   *    tags={"cms","authenticated","form"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Process a form based on ID and input data"
   *   )
   * )
   */
  function formProcess(req, res) {
    if (HAXCMS.validateRequestToken(req.body['haxcms_form_token'], req.body['haxcms_form_id'])) {
      let context = {
        'site': [],
        'node': [],
      };
      if ((req.body['site'])) {
        context['site'] = req.body['site'];
      }
      if ((req.body['node'])) {
        context['node'] = req.body['node'];
      }
      let form = HAXCMS.processForm(req.body['haxcms_form_id'], req.body, context);
      if ((form.fields['__failed'])) {
        res.send(
          form.fields
        );
      }
      res.send({
        'status': 200,
        'data': form
      });
    }
    else {
      res.send(403);
    }
  }
  module.exports = formProcess;