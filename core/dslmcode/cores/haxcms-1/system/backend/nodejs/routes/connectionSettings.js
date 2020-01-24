const fs = require('fs-extra');
const path = require('path');
const HAXCMS = require('../lib/HAXCMS.js');

/**
 * @OA\Get(
 *    path="/connectionSettings",
 *    tags={"cms"},
 *    @OA\Response(
 *        response="200",
 *        description="Generate the connection settings dynamically for implying we have a backend"
 *   )
 * )
 */
function connectionSettings(req, res) {
  res.setHeader('Content-Type', 'application/javascript');
  const themes = JSON.parse(fs.readFileSync(path.join(HAXCMS.coreConfigPath, "themes.json"), 'utf8'));
  const baseAPIPath = HAXCMS.basePath + HAXCMS.apiBase;
  const returnData = JSON.stringify({
    getFormToken: HAXCMS.getRequestToken('form'),
    appStore: { 
      url: `${baseAPIPath}generateAppStore?app-store-token=${HAXCMS.getRequestToken('appstore')}`
    },
    themes: themes,
    login: `${baseAPIPath}login`,
    refreshUrl: `${baseAPIPath}refreshAccessToken`,
    logout: `${baseAPIPath}logout`,
    redirectUrl: HAXCMS.basePath,
    saveNodePath: `${baseAPIPath}saveNode`,
    saveManifestPath: `${baseAPIPath}saveManifest`,
    saveOutlinePath: `${baseAPIPath}saveOutline`,
    publishSitePath: `${baseAPIPath}publishSite`,
    syncSitePath: `${baseAPIPath}syncSite`,
    setConfigPath:`${baseAPIPath}setConfig`,
    getConfigPath: `${baseAPIPath}getConfig`,
    getNodeFieldsPath: `${baseAPIPath}getNodeFields`,
    getSiteFieldsPath: `${baseAPIPath}formLoad?haxcms_form_id=siteSettings`,
    revertSitePath: `${baseAPIPath}revertCommit`,
    createNodePath: `${baseAPIPath}createNode`,
    getUserDataPath: `${baseAPIPath}getUserData`,
    setUserPhotoPath: `${baseAPIPath}setUserPhoto`,
    deleteNodePath: `${baseAPIPath}deleteNode`,
    createNewSitePath: `${baseAPIPath}createSite`,
    gitImportSitePath: `${baseAPIPath}gitImportSite`,
    downloadSitePath: `${baseAPIPath}downloadSite`,
    archiveSitePath: `${baseAPIPath}archiveSite`,
    cloneSitePath: `${baseAPIPath}cloneSite`,
  });
  res.send(`window.appSettings =${returnData};`);
}

module.exports = connectionSettings;