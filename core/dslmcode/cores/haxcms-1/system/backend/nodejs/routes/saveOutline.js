const fs = require('fs-extra');
const HAXCMS = require('../lib/HAXCMS.js');
const JSONOutlineSchemaItem = require('../lib/JSONOutlineSchemaItem.js');
/**
   * @OA\Post(
   *    path="/saveOutline",
   *    tags={"cms","authenticated","site"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Save an entire site outline"
   *   )
   * )
   */
  async function saveOutline(req, res) {
    let site = await HAXCMS.loadSite(req.body['site']['name']);
    let original = site.manifest.items;
    let items = req.body['items'];
    let itemMap = [];
    // items from the POST
    for (var key in items) {
      let item = items[key];
      // get a fake item
      let page = site.loadNode(item.id);
      if (!page) {
          page = new JSONOutlineSchemaItem();
          itemMap[item.id] = page.id;
      }
      else {
        page.id = item.id;
      }
      // set a crappy default title
      page.title = item.title;
      if (item.parent == null) {
          page.parent = null;
          page.indent = 0;
      } else {
          // check the item map as backend dictates unique ID
          if ((itemMap[item.parent])) {
              page.parent = itemMap[item.parent];
          } else {
              // set to the parent id
              page.parent = item.parent;
          }
          // move it one indentation below the parent; this can be changed later if desired
          page.indent = item.indent;
      }
      if ((item.order)) {
          page.order = item.order;
      } else {
          page.order = key;
      }
      // keep location if we get one already
      if ((item.location) && item.location != '') {
          // force location to be in the right place
          cleanTitle = HAXCMS.cleanTitle(item.location);
          page.location = 'pages/' + cleanTitle + '/index.html';
          page.slug = cleanTitle;
      } else {
          cleanTitle = HAXCMS.cleanTitle(page.title);
          // generate a logical page location
          page.location = 'pages/' + cleanTitle + '/index.html';
          page.slug = cleanTitle;
      }
      // verify this exists, front end could have set what they wanted
      // or it could have just been renamed
      siteDirectory =
          site.directory + '/' + site.manifest.metadata.site.name;
      // if it doesn't exist currently make sure the name is unique
      if (!site.loadNode(page.id)) {
          // ensure this location doesn't exist already
          tmpTitle = site.getUniqueSlugName(cleanTitle, page);
          page.location = 'pages/' + tmpTitle + '/index.html';
          page.slug = tmpTitle;
          await site.recurseCopy(
              HAXCMS.HAXCMS_ROOT + '/system/boilerplate/page/default',
              siteDirectory + '/pages/' + tmpTitle
          );
      }
      // this would imply existing item, lets see if it moved or needs moved
      else {
          moved = false;
          for (var key in original) {
              let tmpItem = original[key];
              // see if this is something moving as opposed to brand new
              if (
                  tmpItem.id == page.id &&
                  tmpItem.location != ''
              ) {
                  // core support for automatically managing paths to make them nice
                  if ((site.manifest.metadata.site && site.manifest.metadata.site.settings && site.manifest.metadata.site.settings.pathauto) && site.manifest.metadata.site.settings.pathauto) {
                      moved = true;
                      let newPath = 'pages/' + site.getUniqueSlugName(HAXCMS.cleanTitle(page.title), page) + '/index.html';
                      await site.renamePageLocation(
                          page.location,
                          newPath
                      );
                      page.location = newPath;
                  }
                  else if (tmpItem.location != page.location) {
                      moved = true;
                      // @todo might want something to rebuild the path based on new parents
                      await site.renamePageLocation(
                          tmpItem.location,
                          page.location
                      );
                  }
              }
          }
          // it wasn't moved and it doesn't exist... let's fix that
          // this is beyond an edge case
          if (
              !moved &&
              !fs.lstatSync(siteDirectory + '/' + page.location).isFile()
          ) {
              // ensure this location doesn't exist already
              let tmpTitle = site.getUniqueSlugName(cleanTitle, page);
              page.location = 'pages/' + tmpTitle + '/index.html';
              page.slug = tmpTitle;
              await site.recurseCopy(
                  HAXCMS.HAXCMS_ROOT + '/system/boilerplate/page/default',
                  siteDirectory + '/pages/' + tmpTitle
              );
          }
      }
      // check for any metadata keys that did come over
      for (var key in item.metadata) {
          let value = item.metadata[key];
          page.metadata[key] = value;
      }
      // safety check for new things
      if (!(page.metadata.created)) {
          page.metadata.created = Date.now();
      }
      // always update at this time
      page.metadata.updated = Date.now();
      if (site.loadNode(page.id)) {
          await site.updateNode(page);
      } else {
          await site.manifest.addItem(page);
      }
    }
    site.manifest.metadata.site.updated = Date.now();
    await site.manifest.save();
    await site.gitCommit('Outline updated in bulk');
    res.send(site.manifest.items);
  }
  module.exports = saveOutline;