const fs = require('fs-extra');
const path = require('path');
const HAXCMS = require('./lib/HAXCMS.js');
const mime = require('mime');
const sharp = require('sharp');
// a site object
class HAXCMSFIle
{
  /**
   * Save file into this site, optionally updating reference inside the page
   */
  async save(req, site, page = null, imageOps = null)
  {
    var returnData = {};
    // check for a file upload
    if (req.files['tmp_name']) {
      // get contents of the file if it was uploaded into a variable
      let filedata = req.files['tmp_name'];
      let pathPart = HAXCMS.sitesDirectory + '/' + site.name + '/files/';
      // attempt to save the file either to site or system level
      if (site == 'system/user/files') {
        pathPart = HAXCMS.configDirectory.replace(HAXCMS.HAXCMS_ROOT + '/', '') + '/user/files/';
      }
      else if (site == 'system/tmp') {
        pathPart = HAXCMS.configDirectory.replace(HAXCMS.HAXCMS_ROOT + '/', '') + '/tmp/';
      }
      let path = HAXCMS.HAXCMS_ROOT + '/' + pathPart;
      // ensure this path exists
      fs.mkdir(path);
      let fullpath = path + req.files['name'];
      filedata.mv(fullpath ,  function(err) {
        if (err) {
          console.log(err);
          resp.send(500);
        }
        else {
          //@todo make a way of defining these as returns as well as number to take
          // specialized support for images to do scale and crop stuff automatically
          if (['image/png',
            'image/jpeg',
            'image/gif'
            ].includes(mime.getType(fullpath))
          ) {
            // ensure folders exist
            // @todo comment this all in once we have a better way of doing it
            // front end should dictate stuff like this happening and probably
            // can actually accomplish much of it on its own
            /*try {
                fs.mkdir(path + 'scale-50');
                fs.mkdir(path + 'crop-sm');
            } catch (IOExceptionInterface exception) {
                echo "An error occurred while creating your directory at " +
                    exception.getPath();
            }
            image = new ImageResize(fullpath);
            image
                .scale(50)
                .save(path + 'scale-50/' + upload['name'])
                .crop(100, 100)
                .save(path + 'crop-sm/' + upload['name']);*/
            // fake the file object creation stuff from CMS land
            returnData = {
              'file': {
                'path': path + req.files['name'],
                'fullUrl':
                    HAXCMS.basePath +
                    pathPart +
                    req.files['name'],
                'url' : 'files/' + req.files['name'],
                'type' : mime.getType(fullpath),
                'name' : req.files['name'],
                'size' : size
              }
            };
          }
          else {
            // fake the file object creation stuff from CMS land
            returnData = {
                'file':{
                    'path':path + req.files['name'],
                    'fullUrl' :
                        HAXCMS.basePath +
                        pathPart +
                        req.files['name'],
                    'url': 'files/' + req.files['name'],
                    'type': mime.getType(fullpath),
                    'name': req.files['name'],
                    'size': size
                }
            };
          }
          // perform page level reference saving if available
          if (page != null) {
            // now update the page's metadata to suggest it uses this file. FTW!
            if (!(page.metadata.files)) {
              page.metadata.files = [];
            }
            page.metadata.files.push(returnData['file']);
            await site.updateNode(page);
          }
          // perform scale / crop operations if requested
          if (imageOps != null) {
            switch (imageOps) {
              case 'thumbnail':
                const image = await sharp(fullpath)
                .metadata()
                .then(({ width }) => sharp(fullpath)
                  .resize({
                    width: 250,
                    height: 250,
                    fit: sharp.fit.cover,
                    position: sharp.strategy.entropy
                  })
                  .toFile(fullpath)
                );
              break;
            }
          }
          resp.send({
              'status': 200,
              'data': returnData
          });
        }
      });
    }
  }
}
