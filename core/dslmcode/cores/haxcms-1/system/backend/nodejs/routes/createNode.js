const HAXCMS = require('../lib/HAXCMS.js');
const JSONOutlineSchemaItem = require('../lib/JSONOutlineSchemaItem.js');
/**
 * @OA\Post(
 *     path="/createNode",
 *     tags={"cms","authenticated","node"},
 *     @OA\Parameter(
 *         name="jwt",
 *         description="JSON Web token, obtain by using  /login",
 *         in="query",
 *         required=true,
 *         @OA\Schema(type="string")
 *     ),
 *     @OA\RequestBody(
 *        @OA\MediaType(
 *             mediaType="application/json",
 *             @OA\Schema(
 *                 @OA\Property(
 *                     property="site",
 *                     type="object"
 *                 ),
 *                 @OA\Property(
 *                     property="node",
 *                     type="object"
 *                 ),
 *                 @OA\Property(
 *                     property="indent",
 *                     type="number"
 *                 ),
 *                 @OA\Property(
 *                     property="order",
 *                     type="number"
 *                 ),
 *                 @OA\Property(
 *                     property="parent",
 *                     type="string"
 *                 ),
 *                 @OA\Property(
 *                     property="description",
 *                     type="string"
 *                 ),
 *                 @OA\Property(
 *                     property="metadata",
 *                     type="object"
 *                 ),
 *                 required={"site","node"},
 *                 example={
 *                    "site": {
 *                      "name": "mysite"
 *                    },
 *                    "node": {
 *                      "id": null,
 *                      "title": "Cool post",
 *                      "location": null
 *                    },
 *                    "indent": null,
 *                    "order": null,
 *                    "parent": null,
 *                    "description": "An example description for the post",
 *                    "metadata": {"tags": "metadata,can,be,whatever,you,want","other":"stuff"}
 *                 }
 *             )
 *         )
 *     ),
 *    @OA\Response(
 *        response="200",
 *        description="object with full properties returned"
 *   )
 * )
 */
async function createNode(req, res) {
  let site = await HAXCMS.loadSite(req.body['site']['name'].toLowerCase());
  // get a new item prototype
  let item = new JSONOutlineSchemaItem();
  // set the title
  item['title'] = req.body['node']['title'].replace("\n", '');
  if ((req.body['node']['id']) && req.body['node']['id'] != '' && req.body['node']['id'] != null) {
      item.id = req.body['node']['id'];
  }
  let cleanTitle = HAXCMS.cleanTitle(item['title']);
  if ((req.body['node']['location']) && req.body['node']['location'] != '' && req.body['node']['location'] != null) {
    cleanTitle = HAXCMS.cleanTitle(req.body['node']['location']);
  }
  let slug = site.getUniqueSlugName(cleanTitle);
  // ensure this location doesn't exist already
  item['location'] =
      'pages/' + slug + '/index.html';
      item['slug'] = slug;
  if ((req.body['indent']) && req.body['indent'] != '' && req.body['indent'] != null) {
      item['indent'] = req.body['indent'];
  }
  if ((req.body['order']) && req.body['order'] != '' && req.body['order'] != null) {
      item['order'] = req.body['order'];
  }
  if ((req.body['parent']) && req.body['parent'] != '' && req.body['parent'] != null) {
      item['parent'] = req.body['parent'];
  } else {
      item['parent'] = null;
  }
  if ((req.body['description']) && req.body['description'] != '' && req.body['description'] != null) {
      item['description'] = req.body['description'].replace("\n", '');
  }
  item['metadata'] = {};
  if ((req.body['order']) && req.body['metadata'] != '' && req.body['metadata'] != null) {
      item['metadata'] = req.body['metadata'];
  }
  item.metadata.created = Date.now();
  item.metadata.updated = Date.now();
  // add the item back into the outline schema
  // @todo fix logic here to actually create the page based on 1 call
  // this logic should be cleaned up in addPage to allow for
  // passing in arguments
  await site.recurseCopy(
      HAXCMS.HAXCMS_ROOT + '/system/boilerplate/page/default',
      site.directory +
          '/' +
          site.manifest.metadata.site.name +
          '/' +
          item.location.replace('/index.html', '')
  );
  site.manifest.addItem(item);
  await site.manifest.save();
  await site.gitCommit('Page added:' + item.title + ' (' + item.id + ')');
  res.send(item);
}
module.exports = createNode;