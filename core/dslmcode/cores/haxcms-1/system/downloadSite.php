<?php
include_once '../system/lib/bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';
// test if this is a valid user login
if ($HAXCMS->validateJWT()) {
    // load site
    $site = $HAXCMS->loadSite($HAXCMS->safePost['siteName']);
    // helpful boilerplate https://stackoverflow.com/questions/29873248/how-to-zip-a-whole-directory-and-download-using-php
    $dir = HAXCMS_ROOT . '/' . $HAXCMS->sitesDirectory . '/' . $site->name;
    // form a basic name
    $zip_file =
        HAXCMS_ROOT .
        '/' .
        $HAXCMS->publishedDirectory .
        '/' .
        $site->name .
        '.zip';
    // Get real path for our folder
    $rootPath = realpath($dir);
    // Initialize archive object
    $zip = new ZipArchive();
    $zip->open($zip_file, ZipArchive::CREATE | ZipArchive::OVERWRITE);
    // Create recursive directory iterator
    $directory = new RecursiveDirectoryIterator($rootPath);
    $filtered = new DirFilter($directory, array('node_modules'));
    $files = new RecursiveIteratorIterator($filtered);
    foreach ($files as $name => $file) {
        // Skip directories (they would be added automatically)
        if (!$file->isDir()) {
            // Get real and relative path for current file
            $filePath = $file->getRealPath();
            $relativePath = substr($filePath, strlen($rootPath) + 1);
            // Add current file to archive
            if ($filePath != '' && $relativePath != '') {
                $zip->addFile($filePath, $relativePath);
            }
        }
    }
    // Zip archive will be created only after closing object
    $zip->close();
    header('Content-Type: application/json');
    header('Status: 200');
    $return = array(
      'link' =>
        $HAXCMS->basePath .
        $HAXCMS->publishedDirectory .
        '/' .
        basename($zip_file),
      'name' => basename($zip_file)
    );
    print json_encode($return);
    exit();
}
?>
