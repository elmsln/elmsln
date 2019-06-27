<?php
include_once '../system/lib/bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';
// test if this is a valid user login
if ($HAXCMS->validateJWT()) {
    header('Content-Type: application/json');
    $site = $HAXCMS->loadSite($HAXCMS->safePost['siteName']);
    // update the page's content, using manifest to find it
    // this ensures that writing is always to what the file system
    // determines to be the correct page
    if ($page = $site->loadNode($HAXCMS->safePost['nodeId'])) {
        if ($site->deleteNode($page) === false) {
            header('Status: 500');
            print 'failed to delete';
        } else {
            $site->gitCommit(
                'Page deleted: ' . $page->title . ' (' . $page->id . ')'
            );
            header('Status: 200');
            print json_encode($page);
        }
        exit();
    } else {
        header('Status: 500');
        print 'failed to load page';
    }
}
?>
