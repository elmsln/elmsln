<?php
include_once '../system/lib/bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';
// test if this is a valid user login
if ($HAXCMS->validateJWT()) {
    header('Content-Type: application/json');
    // load the site from name
    $site = $HAXCMS->loadSite($HAXCMS->safePost['siteName']);
    $original = $site->manifest->items;
    $items = $_POST['items'];
    $itemMap = array();
    // items from the POST
    foreach ($items as $key => $item) {
        // get a fake item
        if (!($page = $site->loadNode($item->id))) {
            $page = $HAXCMS->outlineSchema->newItem();
            $itemMap[$item->id] = $page->id;
        } else {
            $page->id = $item->id;
        }
        // set a crappy default title
        $page->title = $item->title;
        if ($item->parent == null) {
            $page->parent = null;
            $page->indent = 0;
        } else {
            // check the item map as backend dictates unique ID
            if (isset($itemMap[$item->parent])) {
                $page->parent = $itemMap[$item->parent];
            } else {
                // set to the parent id
                $page->parent = $item->parent;
            }
            // move it one indentation below the parent; this can be changed later if desired
            $page->indent = $item->indent;
        }
        if (isset($item->order)) {
            $page->order = $item->order;
        } else {
            $page->order = $key;
        }
        // keep location if we get one already
        if (isset($item->location) && $item->location != '') {
            // force location to be in the right place
            $cleanTitle = $HAXCMS->cleanTitle($item->location);
            $page->location = 'pages/' . $cleanTitle . '/index.html';
        } else {
            $cleanTitle = $HAXCMS->cleanTitle($page->title);
            // generate a logical page location
            $page->location = 'pages/' . $cleanTitle . '/index.html';
        }
        // verify this exists, front end could have set what they wanted
        // or it could have just been renamed
        $siteDirectory =
            $site->directory . '/' . $site->manifest->metadata->siteName;
        // if it doesn't exist currently make sure the name is unique
        if (!$site->loadNode($page->id)) {
            // ensure this location doesn't exist already
            $tmpTitle = $site->getUniqueLocationName($cleanTitle, $page);
            $page->location = 'pages/' . $tmpTitle . '/index.html';
            $site->recurseCopy(
                HAXCMS_ROOT . '/system/boilerplate/page',
                $siteDirectory . '/pages/' . $tmpTitle
            );
        }
        // this would imply existing item, lets see if it moved or needs moved
        else {
            $moved = false;
            foreach ($original as $key => $tmpItem) {
                // see if this is something moving as opposed to brand new
                if (
                    $tmpItem->id == $page->id &&
                    $tmpItem->location != ''
                ) {
                    // core support for automatically managing paths to make them nice
                    if (isset($site->manifest->metadata->pathauto) && $site->manifest->metadata->pathauto) {
                        $moved = true;
                        $new = 'pages/' . $site->getUniqueLocationName($HAXCMS->cleanTitle($page->title), $page) . '/index.html';
                        $site->renamePageLocation(
                            $page->location,
                            $new
                        );
                        $page->location = $new;
                    }
                    else if ($tmpItem->location != $page->location) {
                        $moved = true;
                        // @todo might want something to rebuild the path based on new parents
                        $site->renamePageLocation(
                            $tmpItem->location,
                            $page->location
                        );
                    }
                }
            }
            // it wasn't moved and it doesn't exist... let's fix that
            // this is beyond an edge case
            if (
                !$moved &&
                !file_exists($siteDirectory . '/' . $page->location)
            ) {
                // ensure this location doesn't exist already
                $tmpTitle = $site->getUniqueLocationName($cleanTitle, $page);
                $page->location = 'pages/' . $tmpTitle . '/index.html';
                $site->recurseCopy(
                    HAXCMS_ROOT . '/system/boilerplate/page',
                    $siteDirectory . '/pages/' . $tmpTitle
                );
            }
        }
        // check for any metadata keys that did come over
        foreach ($item->metadata as $key => $value) {
            $page->metadata->{$key} = $value;
        }
        // safety check for new things
        if (!isset($page->metadata->created)) {
            $page->metadata->created = time();
        }
        // always update at this time
        $page->metadata->updated = time();
        if ($site->loadNode($page->id)) {
            $site->updateNode($page);
        } else {
            $site->manifest->addItem($page);
        }
    }
    $site->manifest->metadata->updated = time();
    $site->manifest->save();
    $site->gitCommit('Outline updated in bulk');
    header('Status: 200');
    print json_encode($site->manifest->items);
    exit();
}
?>
