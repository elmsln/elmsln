<?php
include_once '../system/lib/bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';
// test if this is a valid user login
if ($HAXCMS->validateJWT()) {
    header('Content-Type: application/json');
    if ($HAXCMS->validateRequestToken()) {
        header('Status: 200');
        $params = $HAXCMS->safePost;
        $domain = null;
        // woohoo we can edit this thing!
        if (isset($params['domain'])) {
            $domain = $params['domain'];
        }
        $site = $HAXCMS->loadSite(
            strtolower($params['siteName']),
            true,
            $domain
        );
        // now get a new item to reference this into the top level sites listing
        $schema = $HAXCMS->outlineSchema->newItem();
        $schema->id = $site->manifest->id;
        $schema->title = $params['siteName'];
        $schema->location =
            $HAXCMS->basePath .
            $HAXCMS->sitesDirectory .
            '/' .
            $site->manifest->metadata->siteName .
            '/index.html';
        $schema->metadata->siteName = $site->manifest->metadata->siteName;
        // look for a match so we can set the correct data
        foreach ($HAXCMS->getThemes() as $key => $theme) {
            if ($params['theme'] == $key) {
                $schema->metadata->theme = $theme;
            }
        }
        // description for an overview if desired
        if (isset($params['description'])) {
            $schema->description = $params['description'];
        }
        // background image / banner
        if (isset($params['image'])) {
            $schema->metadata->image = $params['image'];
        }
        // icon to express the concept / visually identify site
        if (isset($params['icon'])) {
            $schema->metadata->icon = $params['icon'];
        }
        // slightly style the site based on css vars and hexcode
        if (isset($params['hexCode'])) {
            $hex = $params['hexCode'];
        } else {
            $hex = '#aeff00';
        }
        $schema->metadata->hexCode = $hex;
        if (isset($params['cssVariable'])) {
            $cssvar = $params['cssVariable'];
        } else {
            $cssvar = '--simple-colors-default-theme-light-blue-7';
        }
        $schema->metadata->created = time();
        $schema->metadata->updated = time();
        $schema->metadata->cssVariable = $cssvar;
        // check for publishing settings being set globally in HAXCMS
        // this would allow them to fork off to different locations down stream
        $schema->metadata->publishing = new stdClass();
        if (isset($HAXCMS->config->publishing->git->vendor)) {
            $schema->metadata->publishing->git =
                $HAXCMS->config->publishing->git;
            unset($schema->metadata->publishing->git->keySet);
            unset($schema->metadata->publishing->git->email);
            unset($schema->metadata->publishing->git->user);
        }
        // mirror the metadata information into the site's info
        // this means that this info is available to the full site listing
        // as well as this individual site. saves on performance / calls
        // later on if we only need to hit 1 file each time to get all the
        // data we need.
        foreach ($schema->metadata as $key => $value) {
            $site->manifest->metadata->{$key} = $value;
        }
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
        "lrn-table": "@lrnwebcomponents/lrn-table/lrn-table.js",
        "lrn-vocab": "@lrnwebcomponents/lrn-vocab/lrn-vocab.js",
        "lrndesign-blockquote": "@lrnwebcomponents/lrndesign-blockquote/lrndesign-blockquote.js",
        "magazine-cover": "@lrnwebcomponents/magazine-cover/magazine-cover.js",
        "media-behaviors": "@lrnwebcomponents/media-behaviors/media-behaviors.js",
        "media-image": "@lrnwebcomponents/media-image/media-image.js",
        "meme-maker": "@lrnwebcomponents/meme-maker/meme-maker.js",
        "grid-plate": "@lrnwebcomponents/grid-plate/grid-plate.js",
        "md-block": "@lrnwebcomponents/md-block/md-block.js",
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
        "lrndesign-timeline": "@lrnwebcomponents\/lrndesign-timeline\/lrndesign-timeline.js",
        "html-block": "@lrnwebcomponents\/html-block\/html-block.js",
        "user-action": "@lrnwebcomponents\/user-action\/user-action.js",
        "rss-items": "@lrnwebcomponents/rss-items/rss-items.js"
      }');
        $site->manifest->description = $schema->description;
        // save the outline into the new site
        $site->manifest->save(false);
        // main site schema doesn't care about publishing settings
        unset($schema->metadata->publishing);
        $git = new Git();
        $repo = $git->open(
            $site->directory . '/' . $site->manifest->metadata->siteName
        );
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
            $repo->create_branch(
                $site->manifest->metadata->publishing->git->branch
            );
        }
        print json_encode($schema);
    } else {
        header('Status: 403');
    }
    exit();
}
?>
