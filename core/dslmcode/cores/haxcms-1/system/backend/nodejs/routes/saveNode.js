const HAXCMS = require('../lib/HAXCMS.js');
const gettype = require('locutus/php/var/gettype');
const filter_var = require('../lib/filter_var.js');
/**
   * @OA\Post(
   *    path="/saveNode",
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
   *        description="Save a node"
   *   )
   * )
   */
  async function saveNode(req, res) {
    let site = await HAXCMS.loadSite(req.body['site']['name']);
    let schema = [];
    if ((req.body['node']['body'])) {
      var body = req.body['node']['body'];
      // we ship the schema with the body
      if ((req.body['node']['schema'])) {
        schema = req.body['node']['schema'];
      }
    }
    if ((req.body['node']['details'])) {
      var details = req.body['node']['details'];
    }    
    // update the page's content, using manifest to find it
    // this ensures that writing is always to what the file system
    // determines to be the correct page
    var page = site.loadNode(req.body['node']['id']);
    if (page) {
      // convert web location for loading into file location for writing
      if ((body)) {
        let writeSuccessful = await page.writeLocation(
          body,
          HAXCMS.HAXCMS_ROOT +
          '/' +
          HAXCMS.sitesDirectory +
          '/' +
          site.name +
          '/'
        );
        if (writeSuccessful === false) {
          res.send(500);
        } else {
            // sanity check
            if (!(page.metadata)) {
              page.metadata = {};
            }
            // update the updated timestamp
            page.metadata.updated = Date.now();
            // auto generate a text only description from first 200 chars
            let clean = body.replace(/<\/?[^>]+(>|$)/g, "");
            page.description = clean.substr(0, 200).replace(
                "\n",
                ''
            );
            
            let readtime = Math.round(countWords(clean) / 200);
            // account for uber small body
            if (readtime == 0) {
              readtime = 1;
            }
            page.metadata.readtime = readtime;
            // assemble other relevent content detail by skimming it off
            let contentDetails = {};
            contentDetails.headings = 0;
            contentDetails.paragraphs = 0;
            contentDetails.schema = [];
            contentDetails.tags = [];
            contentDetails.elements = schema.length;
            // pull schema apart and store the relevent pieces
            for(var key in schema) {
              let element = schema[key];
              switch(element['tag']) {
                case 'h1':
                case 'h2':
                case 'h3':
                case 'h4':
                case 'h5':
                case 'h6':
                    contentDetails.headings++;
                break;
                case 'p':
                    contentDetails.paragraphs++;
                break;
              }
              if (!(contentDetails.tags[element['tag']])) {
                  contentDetails.tags[element['tag']] = 0;
              }
              contentDetails.tags[element['tag']]++;
              let newItem = {};
              let hasSchema = false;
              if ((element['properties']['property'])) {
                hasSchema = true;
                newItem.property = element['properties']['property'];
              }
              if ((element['properties']['typeof'])) {
                hasSchema = true;
                newItem.typeof = element['properties']['typeof'];
              }
              if ((element['properties']['resource'])) {
                hasSchema = true;
                newItem.resource = element['properties']['resource'];
              }
              if ((element['properties']['prefix'])) {
                hasSchema = true;
                newItem.prefix = element['properties']['prefix'];
              }
              if ((element['properties']['vocab'])) {
                hasSchema = true;
                newItem.vocab = element['properties']['vocab'];
              }
              if (hasSchema) {
                contentDetails.schema.push(newItem);
              }
            }
            page.metadata.contentDetails = contentDetails;
            await site.updateNode(page);
            await site.gitCommit(
              'Page updated: ' + page.title + ' (' + page.id + ')'
            );
            res.send(page);
        }
      } else if ((details)) {
        // update the updated timestamp
        page.metadata.updated = Date.now();
        for (var key in details) {
            let value = details[key];
            // sanitize both sides
            key = filter_var(key, FILTER_SANITIZE_STRING);
            switch (key) {
                case 'location':
                    // check on name
                    value = filter_var(value, FILTER_SANITIZE_STRING);
                    let cleanTitle = HAXCMS.cleanTitle(value);
                    if ((site.manifest.metadata.site.settings.pathauto) && site.manifest.metadata.site.settings.pathauto) {
                        let newPath = 'pages/' + site.getUniqueSlugName(HAXCMS.cleanTitle(filter_var(details['title'], FILTER_SANITIZE_STRING)), page) + '/index.html';
                        site.renamePageLocation(
                            page.location,
                            newPath
                        );
                        page.location = newPath;
                    }
                    else if (
                        cleanTitle !=
                        page.location.replace(
                            'pages/',
                            '',
                        ).replace('/index.html', '')
                        
                    ) {
                        tmpTitle = site.getUniqueSlugName(
                            cleanTitle, page
                        );
                        location = 'pages/' + tmpTitle + '/index.html';
                        // move the folder
                        site.renamePageLocation(
                            page.location,
                            location
                        );
                        page.location = location;
                    }
                    break;
                case 'title':
                case 'description':
                    value = filter_var(value, FILTER_SANITIZE_STRING);
                    page[key] = value;
                    break;
                case 'created':
                    value = filter_var(value, FILTER_VALIDATE_INT);
                    page.metadata.created = value;
                    break;
                case 'published':
                    value = filter_var(value, FILTER_VALIDATE_BOOLEAN);
                    page.metadata.published = value;
                case 'theme':
                    themes = HAXCMS.getThemes();
                    value = filter_var(value, FILTER_SANITIZE_STRING);
                    if ((themes[value])) {
                        page.metadata.theme = themes[value];
                        page.metadata.theme.key = value;
                    }
                    break;
                default:
                    // ensure ID is never changed
                    if (key != 'id') {
                        // support for saving fields
                        if (!(page.metadata.fields)) {
                            page.metadata.fields = {};
                        }
                        switch (gettype(value)) {
                            case 'array':
                            case 'object':
                                page.metadata.fields[key] = {};
                                for(var key2 in value) {
                                  let val = value[key2];
                                    page.metadata.fields[key][key2] = {};
                                    key2 = filter_var(
                                        key2,
                                        FILTER_VALIDATE_INT
                                    );
                                    for (var key3 in val) {
                                      let deepVal = val[key3];
                                        key3 = filter_var(
                                            key3,
                                            FILTER_SANITIZE_STRING
                                        );
                                        deepVal = filter_var(
                                            deepVal,
                                            FILTER_SANITIZE_STRING
                                        );
                                        page.metadata.fields[key][key2][key3] = deepVal;
                                    }
                                }
                                break;
                            case 'integer':
                            case 'double':
                                value = filter_var(
                                    value,
                                    FILTER_VALIDATE_INT
                                );
                                page.metadata.fields[key] = value;
                                break;
                            default:
                                value = filter_var(
                                    value,
                                    FILTER_SANITIZE_STRING
                                );
                                page.metadata.fields[key] = value;
                                break;
                        }
                    }
                    break;
            }
        }
        await site.updateNode(page);
        await site.gitCommit(
            'Page details updated: ' + page.title + ' (' + page.id + ')'
        );
        res.send(page);
      }
    }
  }
  function countWords(str) {
    return str.trim().split(/\s+/).length;
  }
  module.exports = saveNode;