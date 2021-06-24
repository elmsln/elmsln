const HAXCMS = require('../lib/HAXCMS.js');
const json_decode = require('locutus/php/json/json_decode');

/**
   * Generate the swagger API documentation for this site
   * 
   * @OA\Post(
   *    path="/openapi/json",
   *    tags={"api"},
   *    @OA\Response(
   *        response="200",
   *        description="API documentation in JSON"
   *    )
   * )
   */
  function openapi(req, res) {
    // scan this document in order to build the Swagger docs
    // @todo make this scan multiple sources to surface user defined microservices
    // @todo MAKE THIS WORK
    //let openapi = \OpenApi\scan(dirname(__FILE__) + '/Operations.php');
    let openapi = HAXCMS.HAXCMS_ROOT + '/system/backends/php/lib/Operations.php';
    // dynamically add the version
    openapi.info.version = HAXCMS.getHAXCMSVersion();
    openapi.servers = [];
    openapi.servers[0] = {};
    // generate url dynamically w/ path to the API route
    openapi.servers[0].url = HAXCMS.protocol + '://' + HAXCMS.domain + HAXCMS.basePath + HAXCMS.systemRequestBase;
    openapi.servers[0].description = "Site list / dashboard for administrator user";
    // output, yaml we have to exit early or we'll get encapsulation
    if ((req.body['args']) && req.body['args'][1] == 'json') {
      res.send(json_decode(openapi.toJson()));
    }
    else {
      res.send(openapi.toYaml());
    }
  }
  module.exports = openapi;