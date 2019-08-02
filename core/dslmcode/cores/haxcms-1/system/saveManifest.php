<?php
include_once '../system/lib/bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';
// test if this is a valid user login
if ($HAXCMS->validateJWT()) {
    header('Content-Type: application/json');
    // load the site from name
    $site = $HAXCMS->loadSite($HAXCMS->safePost['siteName']);
    // standard form submit
    if (isset($_POST['manifest']->title)) {
        $site->manifest->title = filter_var(
            $_POST['manifest']->title,
            FILTER_SANITIZE_STRING
        );
        $site->manifest->description = filter_var(
            $_POST['manifest']->description,
            FILTER_SANITIZE_STRING
        );
        $site->manifest->metadata->image = filter_var(
            $_POST['manifest']->image,
            FILTER_SANITIZE_STRING
        );
        if (isset($_POST['manifest']->hexCode)) {
            $site->manifest->metadata->hexCode = filter_var(
                $_POST['manifest']->hexCode,
                FILTER_SANITIZE_STRING
            );
        }
        if (isset($_POST['manifest']->cssVariable)) {
            $site->manifest->metadata->cssVariable = filter_var(
            $_POST['manifest']->cssVariable,
            FILTER_SANITIZE_STRING
            );
        }
        // update these parts of the manifest to match POST
        if (isset($_POST['manifest']->icon)) {
            $site->manifest->metadata->icon = filter_var(
                $_POST['manifest']->icon,
                FILTER_SANITIZE_STRING
            );
        }
        if (isset($_POST['manifest']->domain)) {
            $domain = filter_var(
                $_POST['manifest']->domain,
                FILTER_SANITIZE_STRING
            );
            // support updating the domain CNAME value
            if ($site->manifest->metadata->domain != $domain) {
                $site->manifest->metadata->domain = $domain;
                @file_put_contents(
                    $site->directory .
                        '/' .
                        $site->manifest->siteName .
                        '/CNAME',
                    $domain
                );
            }
        }
        // look for a match so we can set the correct data
        foreach ($HAXCMS->getThemes() as $key => $theme) {
            if (
                filter_var($_POST['manifest']->theme, FILTER_SANITIZE_STRING) ==
                $key
            ) {
                $site->manifest->metadata->theme = $theme;
            }
        }
    }
    // advanced form submitted
    if (isset($_POST['manifest']->license)) {
        $site->manifest->license = filter_var(
            $_POST['manifest']->license,
            FILTER_SANITIZE_STRING
        );
        $site->manifest->author = filter_var(
            $_POST['manifest']->author,
            FILTER_SANITIZE_STRING
        );
    }
    if (isset($_POST['manifest']->pathauto)) {
        $site->manifest->metadata->pathauto = filter_var(
        $_POST['manifest']->pathauto,
        FILTER_VALIDATE_BOOLEAN
        );
    }
    // more importantly, this is where the field UI stuff is...
    if (isset($_POST['manifest']->fields)) {
        $fields = new stdClass();
        $fields->configure = array();
        $fields->advanced = array();
        // establish a fields block
        $site->manifest->metadata->fields = new stdClass();
        $site->manifest->metadata->fields->configure = array();
        $site->manifest->metadata->fields->advanced = array();
        foreach ($_POST['manifest']->fields as $key => $field) {
            // ensure formgroup isset, shouldn't be possible..
            if (!isset($field->formgroup)) {
                $field->formgroup = 'configure';
            }
            $fieldgroup = $field->formgroup;
            unset($field->formgroup);
            // another sanity check
            if ($fieldgroup == 'configure' || $fieldgroup == 'advanced') {
                array_push($fields->{$fieldgroup}, $field);
            }
        }
        if (count($fields->configure) > 0) {
            $site->manifest->metadata->fields->configure = $fields->configure;
        }
        if (count($fields->advanced) > 0) {
            $site->manifest->metadata->fields->advanced = $fields->advanced;
        }
    }
    $site->manifest->metadata->updated = time();
    $site->manifest->save(false);
    // now work on HAXCMS layer to match the saved / sanitized data
    $item = $site->manifest;
    // remove items list as we only need the item itself not the nesting
    unset($item->items);
    $HAXCMS->outlineSchema->updateItem($item, true);
    $site->gitCommit('Manifest updated');
    // check git remote if it came across as a possible setting
    if (isset($_POST['manifest']->git)) {
        if (
            filter_var($_POST['manifest']->git->url, FILTER_SANITIZE_STRING) &&
            (!isset($site->manifest->metadata->git->url) ||
                $site->manifest->metadata->git->url !=
                    filter_var(
                        $_POST['manifest']->git->url,
                        FILTER_SANITIZE_STRING
                    ))
        ) {
            $site->gitSetRemote(
                filter_var($_POST['manifest']->git->url, FILTER_SANITIZE_STRING)
            );
        }
    }
    header('Status: 200');
    print json_encode($site->manifest);
    exit();
}
?>
