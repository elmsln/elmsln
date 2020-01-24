<?php
include_once dirname(__FILE__) . "/../vendor/autoload.php";
use \Gumlet\ImageResize;

// a site object
class HAXCMSFIle
{
    /**
     * Save file into this site, optionally updating reference inside the page
     */
    public function save($upload, $site, $page = null, $imageOps = null)
    {
        global $HAXCMS;
        global $fileSystem;
        // check for a file upload
        if (
            isset($upload['tmp_name']) &&
            is_uploaded_file($upload['tmp_name'])
        ) {
            // get contents of the file if it was uploaded into a variable
            $filedata = file_get_contents($upload['tmp_name']);
            // attempt to save the file either to site or system level
            if ($site == 'system/user/files') {
              $pathPart = str_replace(HAXCMS_ROOT . '/', '', $HAXCMS->configDirectory) . '/user/files/';
            }
            else if ($site == 'system/tmp') {
              $pathPart = str_replace(HAXCMS_ROOT . '/', '', $HAXCMS->configDirectory) . '/tmp/';
            }
            else {
              $pathPart = $HAXCMS->sitesDirectory . '/' . $site->name . '/files/';
            }
            $path = HAXCMS_ROOT . '/' . $pathPart;
            // ensure this path exists
            $fileSystem->mkdir($path);
            $fullpath = $path . $upload['name'];
            if ($size = @file_put_contents($fullpath, $filedata)) {
                //@todo make a way of defining these as returns as well as number to take
                // specialized support for images to do scale and crop stuff automatically
                if (
                    in_array(mime_content_type($fullpath), array(
                        'image/png',
                        'image/jpeg',
                        'image/gif'
                    ))
                ) {
                    // ensure folders exist
                    // @todo comment this all in once we have a better way of doing it
                    // front end should dictate stuff like this happening and probably
                    // can actually accomplish much of it on its own
                    /*try {
                        $fileSystem->mkdir($path . 'scale-50');
                        $fileSystem->mkdir($path . 'crop-sm');
                    } catch (IOExceptionInterface $exception) {
                        echo "An error occurred while creating your directory at " .
                            $exception->getPath();
                    }
                    $image = new ImageResize($fullpath);
                    $image
                        ->scale(50)
                        ->save($path . 'scale-50/' . $upload['name'])
                        ->crop(100, 100)
                        ->save($path . 'crop-sm/' . $upload['name']);*/
                    // fake the file object creation stuff from CMS land
                    $return = array(
                        'file' => array(
                            'path' => $path . $upload['name'],
                            'fullUrl' =>
                                $HAXCMS->basePath .
                                $pathPart .
                                $upload['name'],
                            'url' => 'files/' . $upload['name'],
                            'type' => mime_content_type($fullpath),
                            'name' => $upload['name'],
                            'size' => $size
                        )
                    );
                } else {
                    // fake the file object creation stuff from CMS land
                    $return = array(
                        'file' => array(
                            'path' => $path . $upload['name'],
                            'fullUrl' =>
                                $HAXCMS->basePath .
                                $pathPart .
                                $upload['name'],
                            'url' => 'files/' . $upload['name'],
                            'type' => mime_content_type($fullpath),
                            'name' => $upload['name'],
                            'size' => $size
                        )
                    );
                }
                // perform page level reference saving if available
                if ($page != null) {
                    // now update the page's metadata to suggest it uses this file. FTW!
                    if (!isset($page->metadata->files)) {
                        $page->metadata->files = array();
                    }
                    $page->metadata->files[] = $return['file'];
                    $site->updateNode($page);
                }
                // perform scale / crop operations if requested
                if ($imageOps != null) {
                  $image = new ImageResize($fullpath);
                  switch ($imageOps) {
                    case 'thumbnail':
                    $image
                      ->scale(75)
                      ->crop(250, 250)
                      ->save($fullpath);
                    break;
                  }
                }
                $status = 200;
            }
        }
        if ($size === false) {
            $status = 500;
            $return = 'failed to write';
        }
        return array(
            'status' => $status,
            'data' => $return
        );
    }
}
