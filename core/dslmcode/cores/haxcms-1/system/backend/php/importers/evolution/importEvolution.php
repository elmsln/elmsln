<?php

include_once '../../bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';

// now let's work against the XML structure
$source = __DIR__ . '/e_data/content.xml';
$name = "wccourse";
// parse the file
$xmlfile = file_get_contents($source);
$ob = simplexml_load_string($xmlfile);
$json = json_encode($ob);
$configData = json_decode($json, true);
// test if this is a valid user login
header('Content-Type: application/json');
header('Status: 200');
// woohoo we can edit this thing!
$site = $HAXCMS->loadSite(strtolower($name), true);
// now get a new item to reference this into the top level sites listing
$schema = $HAXCMS->outlineSchema->newItem();
$schema->id = $site->manifest->id;
$schema->title = $name;
$schema->location =
    $HAXCMS->basePath .
    $HAXCMS->sitesDirectory .
    '/' .
    $site->manifest->metadata->site->name .
    '/index.html';
$schema->metadata->site = new stdClass();
$schema->metadata->site->name = $site->manifest->metadata->site->name;
$schema->metadata->theme = new stdClass();
$schema->metadata->theme->variables = new stdClass();
$schema->metadata->theme->element = "outline-player";
$schema->metadata->theme->path =
    "@haxtheweb/outline-player/outline-player.js";
$schema->metadata->theme->name = "Outline player";
$schema->metadata->theme->variables->hexCode = '#aeff00';
$schema->metadata->site->created = time();
$schema->metadata->site->updated = time();
$schema->metadata->theme->variables->cssVariable = '--simple-colors-default-theme-light-blue-7';
// check for publishing settings being set globally in HAXCMS
// this would allow them to fork off to different locations down stream
if (isset($HAXCMS->config->site->git->vendor)) {
    $schema->metadata->site->git = $HAXCMS->config->site->git;
    unset($schema->metadata->site->git->keySet);
    unset($schema->metadata->site->git->email);
    unset($schema->metadata->site->git->user);
}
$schema->metadata->node = new stdClass();
$schema->metadata->node->fields = new stdClass();
// mirror the metadata information into the site's info
// this means that this info is available to the full site listing
// as well as this individual site. saves on performance / calls
// later on if we only need to hit 1 file each time to get all the
// data we need.
$site->manifest->metadata = $schema->metadata;
// save the outline into the new site
$site->manifest->save(false);
// main site schema doesn't care about publishing settings
unset($schema->metadata->publishing);
// save it back to the system outline so we can review on the big board
$HAXCMS->outlineSchema->addItem($schema);
$HAXCMS->outlineSchema->save();
$git = new GitRepo();
$repo = Git::open($site->directory . '/' . $site->manifest->metadata->site->name);
$repo->add('.');
$site->gitCommit(
    'A new journey begins: ' .
        $site->manifest->title .
        ' (' .
        $site->manifest->id .
        ')'
);
// make a branch but dont use it
if (isset($site->manifest->metadata->site->git->branch)) {
  $repo->create_branch($site->manifest->metadata->site->git->branch);
}
$item = array_pop($site->manifest->items);
$siteDirectory = $site->directory . '/' . $site->manifest->metadata->site->name;
unlink($siteDirectory . '/' . $item->location);
rmdir($siteDirectory . '/pages/' . $item->id);

unlink($siteDirectory . '/files/.gitkeep');
rmdir($siteDirectory . '/files');
$site->recurseCopy(__DIR__ . '/content', $siteDirectory . '/files');
// load lessons
$lessons = $configData['courseContent']['lesson'];
foreach ($lessons as $key => $lesson) {
    $page = $HAXCMS->outlineSchema->newItem();
    $page->title = $lesson['@attributes']['title'];
    $body = "<p><br/></p>";
    $page->parent = null;
    $page->indent = 0;
    $page->order = $key;
    $parent = $page->id;
    $cleanTitleParent = $lesson['@attributes']['directory'];
    $page->location = 'pages/' . $cleanTitleParent . '/index.html';
    $page->slug = $cleanTitleParent;
    $site->recurseCopy(
        HAXCMS_ROOT . '/system/boilerplate/page/default',
        $siteDirectory . '/pages/' . $cleanTitleParent
    );
    $page->writeLocation(
        $body,
        HAXCMS_ROOT . '/' . $HAXCMS->sitesDirectory . '/' . $site->name . '/'
    );
    $page->metadata->created = time();
    $page->metadata->updated = time();
    $site->manifest->addItem($page);
    if (isset($lesson['page'])) {
        foreach ($lesson['page'] as $key2 => $item) {
            if (isset($item['title'])) {
                // get a fake item
                $page = $HAXCMS->outlineSchema->newItem();
                $page->title = $item['title'];
                if (isset($item['pagecontent'])) {
                    $body = html_entity_decode($item['pagecontent']);
                    $body = str_replace(
                        ' src="./images/',
                        ' src="files/' . $cleanTitleParent . '/images/',
                        $body
                    );
                    $body = str_replace(
                        ' src="./corefiles/',
                        ' src="files/' . $cleanTitleParent . '/corefiles/',
                        $body
                    );
                    $body = str_replace(
                        ' href="./corefiles/',
                        ' href="files/' . $cleanTitleParent . '/corefiles/',
                        $body
                    );
                    $body = str_replace(
                        ' src="images/',
                        ' src="files/' . $cleanTitleParent . '/images/',
                        $body
                    );
                    $body = str_replace(
                        ' src="corefiles/',
                        ' src="files/' . $cleanTitleParent . '/corefiles/',
                        $body
                    );
                    $body = str_replace(
                        ' href="corefiles/',
                        ' href="files/' . $cleanTitleParent . '/corefiles/',
                        $body
                    );
                    $page->description = str_replace(
                        "\n",
                        '',
                        substr(strip_tags($body), 0, 200)
                    );
                } else {
                    $body = "<p><br/></p>";
                }
                $page->parent = $parent;
                $page->indent = 1;
                $page->order = $key2;
                // ensure this location doesn't exist already
                $loop = 0;
                $cleanTitle = str_replace(
                    '.html',
                    '',
                    $item['@attributes']['filename']
                );
                $page->location =
                    'pages/' .
                    $cleanTitleParent .
                    '/' .
                    $cleanTitle .
                    '/index.html';
                $site->recurseCopy(
                    HAXCMS_ROOT . '/system/boilerplate/page/default',
                    $siteDirectory .
                        '/pages/' .
                        $cleanTitleParent .
                        '/' .
                        $cleanTitle
                );
                $page->writeLocation(
                    $body,
                    HAXCMS_ROOT .
                        '/' .
                        $HAXCMS->sitesDirectory .
                        '/' .
                        $site->name .
                        '/'
                );
                $page->metadata->created = time();
                $page->metadata->updated = time();
                $site->manifest->addItem($page);
            }
        }
    }
}
$site->manifest->metadata->site->updated = time();
$site->manifest->save();
$site->gitCommit('Outline updated in bulk');
print json_encode($schema);
?>
