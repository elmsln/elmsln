<?php
include_once '../../lib/bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';
// test if this is a valid user login
if ($HAXCMS->validateJWT()) {
    header('Content-Type: application/json');
    if ($HAXCMS->validateRequestToken()) {
        $params = $HAXCMS->safePost;
        // woohoo we can edit this thing!
        // try to load this thing
        $gitRepo = new GitRepo();
        $path =
            HAXCMS_ROOT .
            '/' .
            $HAXCMS->sitesDirectory .
            strtolower($params['siteName']);
        @$gitRepo->create_new($path, $params['gitRepo'], $path);
        // validate the repo is a legit json outline schema backed haxcms site
        // @todo should do additional validation but this is smell test for now
        if (is_dir($path) && file_exists($path . '/site.json')) {
            header('Status: 200');
            // now the git repo should exist
            $site = $HAXCMS->loadSite(strtolower($params['siteName']));
            $schema = $site->manifest;
            unset($schema->items);
            // main site schema doesn't care about publishing settings
            unset($schema->metadata->publishing);
            // save it back to the system outline so we can review on the big board
            $HAXCMS->outlineSchema->addItem($schema);
            $HAXCMS->outlineSchema->save();
            print json_encode($schema);
        } else {
            header('Status: 500');
            print 'GIT REPO COULD NOT BE ESTABLISHED';
        }
    } else {
        header('Status: 403');
    }
    exit();
}
?>
