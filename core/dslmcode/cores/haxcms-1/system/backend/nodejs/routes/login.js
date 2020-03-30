const HAXCMS = require('../lib/HAXCMS.js');
function loginRoute(req, res)  {
  // if we don't have a user and the don't answer, bail
  if (req.body && req.body.u && req.body.p) {
    // _ paranoia
    var u = req.body.u;
    // driving me insane  
    var p = req.body.p;
    // _ paranoia ripping up my brain
    // test if this is a valid user login
    if (!HAXCMS.testLogin(u, p, true)) {
      res.send(403);
    }
    else {
        // set a refresh_token COOKIE that will ship w/ all calls automatically
      res.cookie('haxcms_refresh_token', HAXCMS.getRefreshToken(u), { 
        expires: 0 ,
        path: '/',
        domain: '',
        secure: false,
        httpOnly: true,
      });
      res.send('"' + HAXCMS.getJWT(u) + '"');
    }
  }
  // login end point requested yet a jwt already exists
  // this is something of a revalidate case
  else if (req.body.jwt || res.query.jwt) {
    res.send('"' + HAXCMS.validateJWT(req) + '"');
  }
  else {
    res.send(403);
  }
}

module.exports = loginRoute;