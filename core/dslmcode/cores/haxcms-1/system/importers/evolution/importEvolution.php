<?php

include_once '../../lib/bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';

// now let's work against the XML structure
$source = __DIR__ . '/e_data/content.xml';
$siteName = "wccourse";
// parse the file
$xmlfile = file_get_contents($source);
$ob = simplexml_load_string($xmlfile);
$json = json_encode($ob);
$configData = json_decode($json, true);
// test if this is a valid user login
header('Content-Type: application/json');
header('Status: 200');
// woohoo we can edit this thing!
$site = $HAXCMS->loadSite(strtolower($siteName), true);
// now get a new item to reference this into the top level sites listing
$schema = $HAXCMS->outlineSchema->newItem();
$schema->id = $site->manifest->id;
$schema->title = $siteName;
$schema->location =
    $HAXCMS->basePath .
    $HAXCMS->sitesDirectory .
    '/' .
    $site->manifest->metadata->siteName .
    '/index.html';
$schema->metadata->siteName = $site->manifest->metadata->siteName;
$schema->metadata->theme = new stdClass();
$schema->metadata->theme->element = "outline-player";
$schema->metadata->theme->path =
    "@lrnwebcomponents/outline-player/outline-player.js";
$schema->metadata->theme->name = "Outline player";
$schema->metadata->hexCode = '#aeff00';
$schema->metadata->created = time();
$schema->metadata->updated = time();
$schema->metadata->cssVariable = '--simple-colors-default-theme-light-blue-7';
// check for publishing settings being set globally in HAXCMS
// this would allow them to fork off to different locations down stream
$schema->metadata->publishing = new stdClass();
if (isset($HAXCMS->config->publishing->git->vendor)) {
    $schema->metadata->publishing->git = $HAXCMS->config->publishing->git;
    unset($schema->metadata->publishing->git->keySet);
    unset($schema->metadata->publishing->git->email);
    unset($schema->metadata->publishing->git->user);
}
// mirror the metadata information into the site's info
// this means that this info is available to the full site listing
// as well as this individual site. saves on performance / calls
// later on if we only need to hit 1 file each time to get all the
// data we need.
$site->manifest->metadata = $schema->metadata;
// @todo support injecting this with out things via PHP
$site->manifest->metadata->dynamicElementLoader = json_decode('{
  "a11y-gif-player": "@lrnwebcomponents/a11y-gif-player/a11y-gif-player.js",
  "code-sample": "@lrnwebcomponents/code-sample/code-sample.js",
  "citation-element": "@lrnwebcomponents/citation-element/citation-element.js",
  "hero-banner": "@lrnwebcomponents/hero-banner/hero-banner.js",
  "image-compare-slider": "@lrnwebcomponents/image-compare-slider/image-compare-slider.js",
  "license-element": "@lrnwebcomponents/license-element/license-element.js",
  "lrn-aside": "@lrnwebcomponents/lrn-aside/lrn-aside.js",
  "lrn-calendar": "@lrnwebcomponents/lrn-calendar/lrn-calendar.js",
  "lrn-math": "@lrnwebcomponents/lrn-math/lrn-math.js",
  "grid-plate": "@lrnwebcomponents/grid-plate/grid-plate.js",
  "md-block": "@lrnwebcomponents/md-block/md-block.js",
  "lrn-table": "@lrnwebcomponents/lrn-table/lrn-table.js",
  "lrn-vocab": "@lrnwebcomponents/lrn-vocab/lrn-vocab.js",
  "lrndesign-blockquote": "@lrnwebcomponents/lrndesign-blockquote/lrndesign-blockquote.js",
  "magazine-cover": "@lrnwebcomponents/magazine-cover/magazine-cover.js",
  "media-behaviors": "@lrnwebcomponents/media-behaviors/media-behaviors.js",
  "media-image": "@lrnwebcomponents/media-image/media-image.js",
  "meme-maker": "@lrnwebcomponents/meme-maker/meme-maker.js",
  "multiple-choice": "@lrnwebcomponents/multiple-choice/multiple-choice.js",
  "paper-audio-player": "@lrnwebcomponents/paper-audio-player/paper-audio-player.js",
  "person-testimonial": "@lrnwebcomponents/person-testimonial/person-testimonial.js",
  "place-holder": "@lrnwebcomponents/place-holder/place-holder.js",
  "q-r": "@lrnwebcomponents/q-r/q-r.js",
  "full-width-image": "@lrnwebcomponents/full-width-image/full-width-image.js",
  "self-check": "@lrnwebcomponents/self-check/self-check.js",
  "simple-concept-network": "@lrnwebcomponents/simple-concept-network/simple-concept-network.js",
  "stop-note": "@lrnwebcomponents/stop-note/stop-note.js",
  "tab-list": "@lrnwebcomponents/tab-list/tab-list.js",
  "task-list": "@lrnwebcomponents/task-list/task-list.js",
  "video-player": "@lrnwebcomponents/video-player/video-player.js",
  "wave-player": "@lrnwebcomponents/wave-player/wave-player.js",
  "wikipedia-query": "@lrnwebcomponents/wikipedia-query/wikipedia-query.js",
  "lrndesign-gallery": "@lrnwebcomponents\/lrndesign-gallery\/lrndesign-gallery.js",
  "lrndesign-timeline": "@lrnwebcomponents\/lrndesign-timeline\/lrndesign-timeline.js"
  }');
// save the outline into the new site
$site->manifest->save(false);
// main site schema doesn't care about publishing settings
unset($schema->metadata->publishing);
// save it back to the system outline so we can review on the big board
$HAXCMS->outlineSchema->addItem($schema);
$HAXCMS->outlineSchema->save();
$git = new GitRepo();
$repo = Git::open($site->directory . '/' . $site->manifest->metadata->siteName);
$repo->add('.');
$site->gitCommit(
    'A new journey begins: ' .
        $site->manifest->title .
        ' (' .
        $site->manifest->id .
        ')'
);
// make a branch but dont use it
if (isset($site->manifest->metadata->publishing->git->branch)) {
    $repo->create_branch($site->manifest->metadata->publishing->git->branch);
}
$item = array_pop($site->manifest->items);
$siteDirectory = $site->directory . '/' . $site->manifest->metadata->siteName;
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
    $site->recurseCopy(
        HAXCMS_ROOT . '/system/boilerplate/page',
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
                    HAXCMS_ROOT . '/system/boilerplate/page',
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
$site->manifest->metadata->updated = time();
$site->manifest->save();
$site->gitCommit('Outline updated in bulk');
print json_encode($schema);
?>
