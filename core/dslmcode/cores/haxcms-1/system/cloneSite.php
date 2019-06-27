<?php
include_once '../system/lib/bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';
// test if this is a valid user login
if ($HAXCMS->validateJWT()) {
    // load site
    $site = $HAXCMS->loadSite($HAXCMS->safePost['siteName']);
    global $fileSystem;
    $siteDirectoryPath = $site->directory . '/' . $site->manifest->metadata->siteName;
    $cloneName = $GLOBALS['HAXCMS']->getUniqueName($site->name);
    // ensure the path to the new folder is valid
    $fileSystem->mirror(
        HAXCMS_ROOT . '/' . $HAXCMS->sitesDirectory . '/' . $site->name,
        HAXCMS_ROOT . '/' . $HAXCMS->sitesDirectory . '/' . $cloneName
    );
    // we need to then load and rewrite the siteName variable or it will conflict given the name change
    $site = $HAXCMS->loadSite($cloneName);
    $site->manifest->metadata->siteName = $cloneName;
    $site->save();
    header('Content-Type: application/json');
    header('Status: 200');
    $return = array(
      'link' =>
        $HAXCMS->basePath .
        $HAXCMS->sitesDirectory .
        '/' .
        $cloneName,
      'name' => $cloneName
    );
    print json_encode($return);
    exit();
}
?>
