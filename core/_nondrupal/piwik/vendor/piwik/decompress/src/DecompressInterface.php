<?php
/**
 * Piwik - free/libre analytics platform
 *
 * @link http://piwik.org
 * @license http://www.gnu.org/licenses/lgpl-3.0.html LGPL v3 or later
 */

namespace Piwik\Decompress;

/**
 * Interface of a class that can decompress files.
 */
interface DecompressInterface
{
    /**
     * Constructor
     *
     * @param string $filename Name of the archive
     */
    public function __construct($filename);

    /**
     * Extract files from the archive to the target directory
     *
     * @param string $pathExtracted Absolute path of target directory
     *
     * @return mixed Array of file names if successful; or 0 if an error occurred
     */
    public function extract($pathExtracted);

    /**
     * Get error description for the latest error
     *
     * @return string
     */
    public function errorInfo();
}
