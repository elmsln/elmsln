const fs = require('fs-extra');
const HAXCMS = require('../lib/HAXCMS.js');
const explode = require('locutus/php/strings/explode');
const base64_encode = require('locutus/php/url/base64_encode');
const parse_url = require('locutus/php/url/parse_url');
const strtr = require('locutus/php/strings/strtr');

/**
   * @OA\Post(
   *    path="/publishSite",
   *    tags={"cms","authenticated","git","site"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\RequestBody(
   *        @OA\MediaType(
   *             mediaType="application/json",
   *             @OA\Schema(
   *                 @OA\Property(
   *                     property="site",
   *                     type="object"
   *                 ),
   *                 required={"site"},
   *                 example={
   *                    "site": {
   *                      "name": "mynewsite"
   *                    },
   *                 }
   *             )
   *         )
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Publishes the site to a remote source using git settings from site.json for details "
   *   )
   * )
   */
  function publishSite(req, res) {
    let site = site = HAXCMS.loadSite(req.body['site']['name']);
    // ensure we have something we can load and ship back out the door
    if (site) {
        // local publishing options, then defer to system, then make some up...
        if ((site.manifest.metadata.site.git)) {
            gitSettings = site.manifest.metadata.site.git;
        } else if ((HAXCMS.config.site.git)) {
            gitSettings = HAXCMS.config.site.git;
        } else {
            gitSettings = {};
            gitSettings.vendor = 'github';
            gitSettings.branch = 'master';
            gitSettings.staticBranch = 'gh-pages';
            gitSettings.url = '';
        }
        if ((gitSettings)) {
            let git = new Git();
            let siteDirectoryPath =
                site.directory + '/' + site.manifest.metadata.site.name;
            repo = git.open(siteDirectoryPath, true);
            // ensure we're on master and everything is added
            repo.checkout('master');
            // Try to build a reasonable "domain" value
            if (
                (gitSettings.url) &&
                gitSettings.url != '' &&
                gitSettings.url != false &&
                gitSettings.url !=
                    '/' + site.manifest.metadata.site.name + '.git'
            ) {
                domain = gitSettings.url;
                if (
                    (site.manifest.metadata.site.domain) &&
                    site.manifest.metadata.site.domain != ''
                ) {
                    domain = site.manifest.metadata.site.domain;
                } else {
                    // support blowing up github addresses correctly
                    parts = explode(
                        '/',
                        domain.replace(
                            'git@github.com:',
                            '').replace('.git', '')
                    );
                    if (parts.length === 2) {
                        domain =
                            'https://' + parts[0] + '.github.io/' + parts[1];
                    }
                }
            }
            // implies the domain is actually on the system locally
            else {
                domain =
                    HAXCMS.basePath +
                    HAXCMS.publishedDirectory +
                    '/' +
                    site.manifest.metadata.site.name +
                    '/';
            }
            // ensure we have the latest dynamic element loader since it may have improved from
            // when we first launched this site, HAX would have these definitions as well but
            // when in production, appstore isn't around so the user may have added custom
            // things that they care about but now magically in a published state its gone
            site.manifest.metadata.node.dynamicElementLoader = HAXCMS.config.node.dynamicElementLoader;
            // set last published time to now
            if (!(site.manifest.metadata.site.static)) {
              site.manifest.metadata.site.static = {};
            }
            site.manifest.metadata.site.static.lastPublished = Date.now();
            site.manifest.metadata.site.static.publishedLocation = domain;
            site.manifest.save(false);
            // just to be safe in case the push isn't successful
            try {
                repo.add('.');
                repo.commit('Clean up pre-publishing..');
                repo.push('origin', 'master');
            } catch (e) {
                // do nothing, we might be offline or something
                // @tood when we get into logging this would be worth logging
            }
            // now check out the publishing branch, it can't be master or our file will get mixed up
            // rather rapidly..
            if (gitSettings.staticBranch != 'master') {
                // try to check it out, if not then we need to create it
                try {
                    repo.checkout(gitSettings.staticBranch);
                    // on that branch now we need to forcibly get the master branch over top of this
                    repo.reset(gitSettings.branch, 'origin');
                    // now we can merge safely because we've already got the files over top
                    // as if they originated here
                    repo.merge(gitSettings.branch);
                } catch (e) {
                    repo.create_branch(gitSettings.staticBranch);
                    repo.checkout(gitSettings.staticBranch);
                }
            }
            // werid looking I know but if we have a CDN then we need to "rewrite" this file
            if ((site.manifest.metadata.site.static.cdn)) {
                cdn = site.manifest.metadata.site.static.cdn;
            } else {
                cdn = 'custom';
            }
            // sanity check
            if (
                fs.lstatSync(
                    HAXCMS.HAXCMS_ROOT + '/system/boilerplate/cdns/' + cdn + '.html'
                ).isFile()
            ) {
                // move the index.html and fs.unlink the symlinks otherwise we'll get build failures
                if (fs.lstat(siteDirectoryPath + '/build').isSymbolicLink()) {
                    fs.unlink(siteDirectoryPath + '/build');
                }
                if (fs.lstat(siteDirectoryPath + '/dist').isSymbolicLink()) {
                    fs.unlink(siteDirectoryPath + '/dist');
                }
                if (fs.lstat(siteDirectoryPath + '/node_modules').isSymbolicLink()) {
                    fs.unlink(siteDirectoryPath + '/node_modules');
                }
                if (fs.lstat(siteDirectoryPath + '/assets/babel-top.js').isSymbolicLink()) {
                    fs.unlink(siteDirectoryPath + '/assets/babel-top.js');
                }
                if (fs.lstat(siteDirectoryPath + '/assets/babel-bottom.js').isSymbolicLink()) {
                    fs.unlink(siteDirectoryPath + '/assets/babel-bottom.js');
                }
                // copy these things because we have a local routine
                if (cdn == 'custom') {
                    fs.copy(
                        HAXCMS.HAXCMS_ROOT + '/babel/babel-top.js',
                        siteDirectoryPath + '/assets/babel-top.js'
                    );
                    fs.copy(
                        HAXCMS.HAXCMS_ROOT + '/babel/babel-bottom.js',
                        siteDirectoryPath + '/assets/babel-bottom.js'
                    );
                    fs.mirror(
                        HAXCMS.HAXCMS_ROOT + '/build',
                        siteDirectoryPath + '/build'
                    );
                }
                // additional files to move to ensure we don't screw things up
                templates = site.getManagedTemplateFiles();
                // support for index as that comes from a CDN defining what to do
                // remove current index, then pull a new one
                // this ensures that the php file won't be in the published copy while it is in master
                fs.unlink([siteDirectoryPath + '/index.html', siteDirectoryPath + '/index.php']);
                fs.copy(HAXCMS.HAXCMS_ROOT + '/system/boilerplate/cdns/' + cdn + '.html', siteDirectoryPath + '/index.html');
                // process twig variables for static publishing
                licenseData = site.getLicenseData('all');
                licenseLink = '';
                licenseName = '';
                if ((site.manifest.license) && (licenseData[site.manifest.license])) {
                  licenseLink = licenseData[site.manifest.license]['link'];
                  licenseName = 'License: ' + licenseData[site.manifest.license]['name'];
                }
                let templateVars = {
                    'hexCode': HAXCMS_FALLBACK_HEX,
                    'version': HAXCMS.getHAXCMSVersion(),
                    'basePath':
                        '/' + site.manifest.metadata.site.name + '/',
                    'title': site.manifest.title,
                    'short': site.manifest.metadata.site.name,
                    'description': site.manifest.description,
                    'forceUpgrade' : site.getForceUpgrade(),
                    'swhash' : [],
                    'ghPagesURLParamCount' : 1,
                    'licenseLink' : licenseLink,
                    'licenseName' : licenseName,
                    'serviceWorkerScript' : site.getServiceWorkerScript('/' + site.manifest.metadata.site.name + '/', TRUE),
                    'bodyAttrs' : site.getSitePageAttributes(),
                };
                // custom isn't a regex by design
                if (cdn != 'custom') {
                  // special fallback for HAXtheWeb since it cheats in order to demo the solution
                  if (cdn == 'haxtheweb.org') {
                    templateVars['cdn'] = 'cdn.waxam.io';
                  }
                  else {
                    templateVars['cdn'] = cdn;
                  }
                  templateVars['metadata'] = site.getSiteMetadata(NULL, domain, 'https://' + templateVars['cdn']);
                  // build a regex so that we can do fully offline sites and cache the cdn requests even
                  templateVars['cdnRegex'] =
                    "(https?:\/\/" +    
                    templateVars['cdn'].replace('.', '\.') +
                    `(\/[A-Za-z0-9\-\._~:\/\?#\[\]@!$&'\(\)\*\+,;\=]*)?)`;
                  // support for disabling regex via offline setting
                  if ((site.manifest.metadata.site.static.offline) && !site.manifest.metadata.site.static.offline) {
                    delete templateVars['cdnRegex'];
                  }
                }
                // if we have a custom domain, try and engineer the base path
                // correctly for the manifest / service worker
                // @todo need to support domains that have subdomains in them
                if (
                    (site.manifest.metadata.site.domain) &&
                    site.manifest.metadata.site.domain != ''
                ) {
                    parts = parse_url(site.manifest.metadata.site.domain);
                    templateVars['basePath'] = '/';
                    if ((parts['base'])) {
                        templateVars['basePath'] = parts['base'];
                    }
                    if (templateVars['basePath'] == '/') {
                        templateVars['ghPagesURLParamCount'] = 0;
                    }
                    // now we need to update the SW to match
                    templateVars['serviceWorkerScript'] = site.getServiceWorkerScript(templateVars['basePath'], TRUE);
                }
                if ((site.manifest.metadata.theme.variables.hexCode)) {
                    templateVars['hexCode'] =
                        site.manifest.metadata.theme.variables.hexCode;
                }
                let swItems = site.manifest.items;
                // the core files you need in every SW manifest
                coreFiles = [
                    'index.html',
                    'manifest.json',
                    'site.json',
                    site.getLogoSize('512','512'),
                    site.getLogoSize('310','310'),
                    site.getLogoSize('192','192'),
                    site.getLogoSize('150','150'),
                    site.getLogoSize('144','144'),
                    site.getLogoSize('96','96'),
                    site.getLogoSize('72','72'),
                    site.getLogoSize('70','70'),
                    site.getLogoSize('48','48'),
                    site.getLogoSize('36','36'),
                    site.getLogoSize('16','16'),
                    '404.html',
                ];
                // loop through files directory so we can cache those things too
                let handle = opendir(siteDirectoryPath + '/files');
                if (handle) {
                    while (false !== (file = readdir(handle))) {
                        if (
                            file != "." &&
                            file != ".." &&
                            file != '.gitkeep' &&
                            file != '.DS_Store'
                        ) {
                            // ensure this is a file
                            if (
                                fs.lstatSync(siteDirectoryPath + '/files/' + file).isFile()
                            ) {
                                coreFiles.push('files/' + file);
                            } else {
                                // @todo maybe step into directories?
                            }
                        }
                    }
                    closedir(handle);
                }
                for(var key in coreFiles) {
                    let itemLocation = coreFiles[key];
                    let coreItem = {};
                    coreItem.location = itemLocation;
                    swItems.push(coreItem);
                }
                // generate a legit hash value that's the same for each file name + file size
                for(var key in swItems) {
                    let item = swItems[key];
                    if (
                        item.location === '' ||
                        item.location === templateVars['basePath']
                    ) {
                        filesize = filesize(
                            siteDirectoryPath + '/index.html'
                        );
                    } else if (
                        fs.lstatSync(siteDirectoryPath + '/' + item.location).isFile()
                    ) {
                        filesize = filesize(
                            siteDirectoryPath + '/' + item.location
                        );
                    } else {
                        // ?? file referenced but doesn't exist
                        filesize = 0;
                    }
                    if (filesize !== 0) {
                        templateVars['swhash'].push([
                            item.location,
                            strtr(
                                base64_encode(HAXCMS.hmacBase64(
                                         item.location + filesize,
                                         'haxcmsswhash'
                                    )
                                ),
                                    {
                                    '+' : '',
                                    '/' : '',
                                    '=' : '',
                                    '-' : ''
                                    }
                            )
                                ]);
                    }
                }
                // put the twig written output into the file
                // @todo need to fix a twig library
                /*loader = new \Twig\Loader\FilesystemLoader(siteDirectoryPath);
                twig = new \Twig\Environment(loader);
                for (var key in templates) {
                    let location = templates[key];
                  if (fs.lstatSync(siteDirectoryPath + '/' + location).isFile()) {
                    fs.writeFile(
                        siteDirectoryPath + '/' + location,
                        twig.render(location, templateVars)
                    );
                  }
                }*/
                try {
                    repo.add('.');
                    repo.commit('Published using CDN: ' + cdn);
                } catch (e) {
                    // do nothing, maybe there was nothing to commit
                }
            }
            // mirror over to the publishing directory
            // @todo need to make a way of doing this in a variable fashion
            // this way we could publish to multiple locations or intentionally to a location
            // which will be important when allowing for open, closed, or other server level configurations
            // that happen automatically as opposed to when the user hits publish
            // also for delivery of the "click to access site" link
            fs.mirror(
                siteDirectoryPath,
                HAXCMS.configDirectory + '/../_published/' + site.manifest.metadata.site.name
            );
            // remove the .git version control from this, it's not needed
            fs.rmdir(
                HAXCMS.configDirectory + '/../_published/' + site.manifest.metadata.site.name + '/.git'
            );
            // rewrite the base path to ensure it is accurate based on a local build publish vs web
            let index = fs.readFileSync(
                HAXCMS.configDirectory + '/../_published/' +
                    site.manifest.metadata.site.name +
                    '/index.html'
            );
            // replace if it was publishing with the name in it
            index = index.replace(
                '<base href="/' + site.manifest.metadata.site.name + '/"',
                '<base href="' + HAXCMS.basePath + '_published/' +
                    site.manifest.metadata.site.name +
                    '/"'
            );
            // replace if it has a vanity domain
            index = index.replace(
                '<base href="/"',
                '<base href="' + HAXCMS.basePath + '_published/' +
                    site.manifest.metadata.site.name +
                    '/"'
            );
            // rewrite the file
            fs.writeFile(
                HAXCMS.configDirectory + '/../_published/' +
                    site.manifest.metadata.site.name +
                    '/index.html',
                index
            );
            // tag, attempt to push, and set things up for next time
            repo.add_tag(
                'version-' + site.manifest.metadata.site.static.lastPublished
            );
            repo.push(
                'origin',
                'version-' + site.manifest.metadata.site.static.lastPublished,
                "--force"
            );
            if (gitSettings.staticBranch != 'master') {
                repo.push('origin', gitSettings.staticBranch, "--force");
                // now put it back plz... and master shouldn't notice any source changes
                repo.checkout(gitSettings.branch);
            }
            // restore these silly things if we need to
            if (!fs.lstatSync(siteDirectoryPath + '/dist').isSymbolicLink()) {
                fs.symlink('../../dist', siteDirectoryPath + '/dist');
            }
            if (!fs.lstatSync(siteDirectoryPath + '/node_modules').isSymbolicLink()) {
                fs.symlink(
                    '../../node_modules',
                    siteDirectoryPath + '/node_modules'
                );
            }
            if (fs.lstatSync(siteDirectoryPath + '/assets/babel-top.js').isSymbolicLink()) {
                fs.unlink(siteDirectoryPath + '/assets/babel-top.js');
            }
            if (fs.lstatSync(siteDirectoryPath + '/assets/babel-bottom.js').isSymbolicLink()) {
                fs.unlink(siteDirectoryPath + '/assets/babel-bottom.js');
            }
            if (fs.lstatSync(siteDirectoryPath + '/build').isSymbolicLink()) {
                fs.unlink(siteDirectoryPath + '/build');
            }
            else {
                fs.rmdir([siteDirectoryPath + '/build']);
            }

            fs.symlink(
                '../../../babel/babel-top.js',
                siteDirectoryPath + '/assets/babel-top.js'
            );
            fs.symlink(
                '../../../babel/babel-bottom.js',
                siteDirectoryPath + '/assets/babel-bottom.js'
            );
            fs.symlink('../../build', siteDirectoryPath + '/build');
            // reset the templated file for the index.html
            // since the "CDN" cleaned up how this worked most likely at run time
            fs.unlink([siteDirectoryPath + '/index.html']);
            fs.copy(HAXCMS.HAXCMS_ROOT + '/system/boilerplate/site/index.html', siteDirectoryPath + '/index.html');
            // this ensures that the php file wasn't in version control for the published copy
            fs.copy(HAXCMS.HAXCMS_ROOT + '/system/boilerplate/site/index.php', siteDirectoryPath + '/index.php');
            res.send({
                'status' : 200,
                'url' : domain,
                'label' : 'Click to access ' + site.manifest.title,
                'response' : 'Site published!',
                'output' : 'Site published successfully if no errors!'
            });
        }
    } else {
      res.send(500);
    }
  }
  module.exports = publishSite;