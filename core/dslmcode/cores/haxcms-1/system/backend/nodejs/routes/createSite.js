const fs = require('fs-extra');
const path = require('path');
const HAXCMS = require('../lib/HAXCMS.js');
const { Git } = require('git-interface');
const JSONOutlineSchemaItem = require('../lib/JSONOutlineSchemaItem.js');

/**
   * @OA\Post(
   *    path="/createSite",
   *    tags={"cms","authenticated","site"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *     @OA\RequestBody(
   *        @OA\MediaType(
   *             mediaType="application/json",
   *             @OA\Schema(
   *                 @OA\Property(
   *                     property="site",
   *                     type="object"
   *                 ),
   *                 @OA\Property(
   *                     property="theme",
   *                     type="object"
   *                 ),
   *                 required={"site","node"},
   *                 example={
   *                    "site": {
   *                      "name": "mynewsite",
   *                      "domain": ""
   *                    },
   *                    "theme": {
   *                      "name": "learn-two-theme",
   *                      "variables": {
   *                        "image":"",
   *                        "icon":"",
   *                        "hexCode":"",
   *                        "cssVariable":"",
   *                        }                   
   *                    }
   *                 }
   *             )
   *         )
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Create a new site"
   *   )
   * )
   */
async function createSite(req, res) {
if (HAXCMS.validateRequestToken(null, null, req.body)) {
    let domain = null;
    // woohoo we can edit this thing!
    if (req.body['site']['domain'] && req.body['site']['domain'] != null && req.body['site']['domain'] != '') {
    domain = req.body['site']['domain'];
    }
    // sanitize name
    let name = HAXCMS.generateMachineName(req.body['site']['name']);
    let site = await HAXCMS.loadSite(
        name.toLowerCase(),
        true,
        domain
    );
    // now get a new item to reference this into the top level sites listing
    let schema = new JSONOutlineSchemaItem();
    schema.id = site.manifest.id;
    schema.title = name;
    schema.location =
        HAXCMS.basePath +
        HAXCMS.sitesDirectory +
        '/' +
        site.manifest.metadata.site.name +
        '/index.html';
    schema.metadata = {
        site: {},
        theme: {}
    }
    schema.metadata.site.name = site.manifest.metadata.site.name;
    let theme = HAXCMS.HAXCMS_DEFAULT_THEME;
    if (req.body['theme']['name'] && typeof req.body['theme']['name'] === "string") {
    theme = req.body['theme']['name'];
    }
    let themesAry = HAXCMS.getThemes();
    // look for a match so we can set the correct data
    for (var key in themesAry) {
        if (theme == key) {
            schema.metadata.theme = themesAry[key];
        }
    }
    schema.metadata.theme.variables = {};
    // description for an overview if desired
    if (req.body['site']['description'] && req.body['site']['description'] != '' && req.body['site']['description'] != null) {
        schema.description = req.body['site']['description'].replace(/<\/?[^>]+(>|$)/g, "");
    }

    schema.metadata.theme.variables.image = 'assets/banner.jpg';
    // icon to express the concept / visually identify site
    if (req.body['theme']['icon'] && req.body['theme']['icon'] != '' && req.body['theme']['icon'] != null) {
        schema.metadata.theme.variables.icon = req.body['theme']['icon'];
    }
    // slightly style the site based on css vars and hexcode
    let hex = HAXCMS.HAXCMS_FALLBACK_HEX;
    schema.metadata.theme.variables.hexCode = hex;
    let cssvar = '--simple-colors-default-theme-light-blue-7';
    if (req.body['theme']['color'] && req.body['theme']['color'] != '' && req.body['theme']['color'] != null) {
        cssvar = '--simple-colors-default-theme-' + req.body['theme']['color'] + '-7';
    }
    schema.metadata.theme.variables.cssVariable = cssvar;
    schema.metadata.site.created = Date.now();
    schema.metadata.site.updated = Date.now();
    // check for publishing settings being set globally in HAXCMS
    // this would allow them to fork off to different locations down stream
    schema.metadata.site.git = {};
    if (HAXCMS.config.site.git.vendor) {
        schema.metadata.site.git = HAXCMS.config.site.git;
        delete schema.metadata.site.git.keySet;
        delete schema.metadata.site.git.email;
        delete schema.metadata.site.git.user;
    }
    // mirror the metadata information into the site's info
    // this means that this info is available to the full site listing
    // as well as this individual site. saves on performance / calls
    // later on if we only need to hit 1 file each time to get all the
    // data we need.
    for (var key in schema.metadata) {
        site.manifest.metadata[key] = schema.metadata[key];
    }
    site.manifest.metadata.node = {};
    site.manifest.metadata.node.fields = {};
    site.manifest.description = schema.description;
    // save the outline into the new site
    await site.manifest.save(false);
    // main site schema doesn't care about publishing settings
    delete schema.metadata.site.git;

    const git = new Git({
        dir: site.directory + '/' + site.manifest.metadata.site.name
    });
    git.setDir(site.directory + '/' + site.manifest.metadata.site.name);
    await git.init();
    try {
        await git.add();
        await git.commit('A new journey begins: ' + site.manifest.title + ' (' + site.manifest.id + ')');
        // make a branch but dont use it
        if (site.manifest.metadata.site.git && site.manifest.metadata.site.git.staticBranch) {
            await git.createBranch(
                site.manifest.metadata.site.git.staticBranch
            );
        }
        if (site.manifest.metadata.site.git && site.manifest.metadata.site.git.branch) {
            await git.createBranch(
                site.manifest.metadata.site.git.branch
            );
        }
    }
    catch(e) {
        console.log(e);
    }
    
    res.send(schema);
}
else {
    res.send(403);
}
}
module.exports = createSite;