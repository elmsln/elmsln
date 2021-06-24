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
        $size = false;
        $status = 0;
        $return = array();
        $name = $upload['name'];
        // check for a file upload; we block a few formats by design
        if (
            isset($upload['tmp_name']) &&
            is_uploaded_file($upload['tmp_name']) &&
            strpos($name, '.php') === FALSE &&
            strpos($name, '.sh') === FALSE &&
            strpos($name, '.js') === FALSE &&
            strpos($name, '.css') === FALSE
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
            // account for name possibly matching on file system already
            $actual_name = pathinfo($name, PATHINFO_FILENAME);
            $original_name = $actual_name;
            $extension = pathinfo($name, PATHINFO_EXTENSION);
            $i = 1;
            while (file_exists($path . $actual_name . "." . $extension)) {           
                $actual_name = (string)$original_name . $i;
                $i++;
            }
            $name = $actual_name . "." . $extension;
            $fullpath = $path . $name;
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
                        ->save($path . 'scale-50/' . $name)
                        ->crop(100, 100)
                        ->save($path . 'crop-sm/' . $name);*/
                    // fake the file object creation stuff from CMS land
                    $return = array(
                        'file' => array(
                            'path' => $path . $name,
                            'fullUrl' =>
                                $HAXCMS->basePath .
                                $pathPart .
                                $name,
                            'url' => 'files/' . $name,
                            'type' => mime_content_type($fullpath),
                            'name' => $name,
                            'size' => $size
                        )
                    );
                } else {
                    // fake the file object creation stuff from CMS land
                    $return = array(
                        'file' => array(
                            'path' => $path . $name,
                            'fullUrl' =>
                                $HAXCMS->basePath .
                                $pathPart .
                                $name,
                            'url' => 'files/' . $name,
                            'type' => mime_content_type($fullpath),
                            'name' => $name,
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
            $return = 'failed to write ' . $name;
        }
        return array(
            'status' => $status,
            'data' => $return
        );
    }
}
