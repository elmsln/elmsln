<?php

namespace Icamys\SitemapGenerator;

use BadMethodCallException;
use DateTime;
use DOMDocument;
use InvalidArgumentException;
use LengthException;
use SimpleXMLElement;
use SplFixedArray;

class SitemapGenerator
{
    const MAX_FILE_SIZE = 10485760;
    const MAX_URLS_PER_SITEMAP = 50000;

    const URL_PARAM_LOC = 0;
    const URL_PARAM_LASTMOD = 1;
    const URL_PARAM_CHANGEFREQ = 2;
    const URL_PARAM_PRIORITY = 3;

    /**
     * Name of sitemap file
     * @var string
     * @access public
     */
    public $sitemapFileName = "sitemap.xml";

    /**
     * Name of sitemap index file
     * @var string
     * @access public
     */
    public $sitemapIndexFileName = "sitemap-index.xml";

    /**
     * Robots file name
     * @var string
     * @access public
     */
    public $robotsFileName = "robots.txt";

    /**
     * Quantity of URLs per single sitemap file.
     * According to specification max value is 50.000.
     * If Your links are very long, sitemap file can be bigger than 10MB,
     * in this case use smaller value.
     * @var int
     * @access public
     */
    public $maxURLsPerSitemap = self::MAX_URLS_PER_SITEMAP;

    /**
     * Quantity of sitemaps per index file.
     * According to specification max value is 50.000
     * If Your index file is very long, index file can be bigger than 10MB,
     * in this case use smaller value.
     * @see http://www.sitemaps.org/protocol.html
     * @var int
     * @access public
     */
    public $maxSitemaps = 50000;

    /**
     * If true, two sitemap files (.xml and .xml.gz) will be created and added to robots.txt.
     * If true, .gz file will be submitted to search engines.
     * If quantity of URLs will be bigger than 50.000, option will be ignored,
     * all sitemap files except sitemap index will be compressed.
     * @var bool
     * @access public
     */
    public $createGZipFile = false;

    /**
     * URL to Your site.
     * Script will use it to send sitemaps to search engines.
     * @var string
     * @access private
     */
    private $baseURL;

    /**
     * Base path. Relative to script location.
     * Use this if Your sitemap and robots files should be stored in other
     * directory then script.
     * @var string
     * @access private
     */
    private $basePath;

    /**
     * Version of this class
     * @var string
     * @access private
     */
    private $classVersion = "1.1.0";

    /**
     * Search engines URLs
     * @var array of strings
     * @access private
     */
    private $searchEngines = array(
        array(
            "http://search.yahooapis.com/SiteExplorerService/V1/updateNotification?appid=USERID&url=",
            "http://search.yahooapis.com/SiteExplorerService/V1/ping?sitemap="
        ),
        "http://www.google.com/webmasters/tools/ping?sitemap=",
        "http://submissions.ask.com/ping?sitemap=",
        "http://www.bing.com/webmaster/ping.aspx?siteMap="
    );

    /**
     * Array with urls
     * @var SplFixedArray of strings
     * @access private
     */
    private $urls;

    /**
     * Array with sitemap
     * @var array of strings
     * @access private
     */
    private $sitemaps;

    /**
     * Array with sitemap index
     * @var array of strings
     * @access private
     */
    private $sitemapIndex;

    /**
     * Current sitemap full URL
     * @var string
     * @access private
     */
    private $sitemapFullURL;

    /**
     * @var DOMDocument
     */
    private $document;

    /**
     * Constructor.
     * @param string $baseURL You site URL, with / at the end.
     * @param string|null $basePath Relative path where sitemap and robots should be stored.
     */
    public function __construct($baseURL, $basePath = "")
    {
        $this->urls = new SplFixedArray();
        $this->baseURL = $baseURL;
        $this->basePath = $basePath;
        $this->document = new DOMDocument("1.0");
        $this->document->preserveWhiteSpace = false;
        $this->document->formatOutput = true;
    }

    /**
     * Use this to add many URL at one time.
     * Each inside array can have 1 to 4 fields.
     * @param $urlsArray
     * @throws InvalidArgumentException
     */
    public function addUrls($urlsArray)
    {
        if (!is_array($urlsArray)) {
            throw new InvalidArgumentException("Array as argument should be given.");
        }
        foreach ($urlsArray as $url) {
            $this->addUrl(
                isset($url[0]) ? $url[0] : null,
                isset($url[1]) ? $url[1] : null,
                isset($url[2]) ? $url[2] : null,
                isset($url[3]) ? $url[3] : null
            );
        }
    }

    /**
     * Use this to add single URL to sitemap.
     * @param string $url URL
     * @param DateTime $lastModified When it was modified, use ISO8601-compatible format
     * @param string $changeFrequency How often search engines should revisit this URL
     * @param string $priority Priority of URL on You site
     * @see http://en.wikipedia.org/wiki/ISO_8601
     * @see http://php.net/manual/en/function.date.php
     * @throws InvalidArgumentException
     */
    public function addUrl($url, DateTime $lastModified = null, $changeFrequency = null, $priority = null)
    {
        if ($url == null) {
            throw new InvalidArgumentException("URL is mandatory. At least one argument should be given.");
        }
        $urlLength = extension_loaded('mbstring') ? mb_strlen($url) : strlen($url);
        if ($urlLength > 2048) {
            throw new InvalidArgumentException(
                "URL length can't be bigger than 2048 characters.
                Note, that precise url length check is guaranteed only using mb_string extension.
                Make sure Your server allow to use mbstring extension."
            );
        }
        $tmp = new SplFixedArray(1);

        $tmp[self::URL_PARAM_LOC] = $url;

        if (isset($lastModified)) {
            $tmp->setSize(2);
            $tmp[self::URL_PARAM_LASTMOD] = $lastModified->format(DateTime::ATOM);
        }

        if (isset($changeFrequency)) {
            $tmp->setSize(3);
            $tmp[self::URL_PARAM_CHANGEFREQ] = $changeFrequency;
        }

        if (isset($priority)) {
            $tmp->setSize(4);
            $tmp[self::URL_PARAM_PRIORITY] = $priority;
        }

        if ($this->urls->getSize() === 0) {
            $this->urls->setSize(1);
        } else {
            if ($this->urls->getSize() === $this->urls->key()) {
                $this->urls->setSize($this->urls->getSize() * 2);
            }
        }

        $this->urls[$this->urls->key()] = $tmp;
        $this->urls->next();
    }

    /**
     * @throws BadMethodCallException
     * @throws InvalidArgumentException
     * @throws LengthException
     */
    public function createSitemap()
    {
        if (!isset($this->urls)) {
            throw new BadMethodCallException("To create sitemap, call addUrl or addUrls function first.");
        }

        if ($this->maxURLsPerSitemap > self::MAX_URLS_PER_SITEMAP) {
            throw new InvalidArgumentException(
                "More than " . self::MAX_URLS_PER_SITEMAP . " URLs per single sitemap is not allowed."
            );
        }

        $generatorInfo = implode(PHP_EOL, [
            sprintf('<!-- generator-class="%s" -->', get_class($this)),
            sprintf('<!-- generator-version="%s" -->', $this->classVersion),
            sprintf('<!-- generated-on="%s" -->', date('c')),
        ]);

        $sitemapHeader = implode(PHP_EOL, [
            '<?xml version="1.0" encoding="UTF-8"?>',
            $generatorInfo,
            '<urlset',
            'xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"',
            'xsi:schemaLocation="http://www.sitemaps.org/schemas/sitemap/0.9 http://www.sitemaps.org/schemas/sitemap/0.9/sitemap.xsd"',
            'xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">',
            '</urlset>'
        ]);

        $sitemapIndexHeader = implode(PHP_EOL, [
            '<?xml version="1.0" encoding="UTF-8"?>',
            $generatorInfo,
            '<sitemapindex',
            'xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"',
            'xsi:schemaLocation="http://www.sitemaps.org/schemas/sitemap/0.9 http://www.sitemaps.org/schemas/sitemap/0.9/siteindex.xsd"',
            'xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">',
            '</sitemapindex>'
        ]);

        $nullUrls = 0;
        foreach ($this->urls as $url) {
            if (is_null($url)) {
                $nullUrls++;
            }
        }

        $nonEmptyUrls = $this->urls->getSize() - $nullUrls;

        $chunks = ceil($nonEmptyUrls / $this->maxURLsPerSitemap);

        for ($chunkCounter = 0; $chunkCounter < $chunks; $chunkCounter++) {
            $xml = new SimpleXMLElement($sitemapHeader);
            for ($urlCounter = $chunkCounter * $this->maxURLsPerSitemap;
                 $urlCounter < ($chunkCounter + 1) * $this->maxURLsPerSitemap && $urlCounter < $nonEmptyUrls;
                 $urlCounter++
            ) {
                $row = $xml->addChild('url');

                $row->addChild(
                    'loc',
                    htmlspecialchars($this->baseURL . $this->urls[$urlCounter][self::URL_PARAM_LOC], ENT_QUOTES, 'UTF-8')
                );

                if ($this->urls[$urlCounter]->getSize() > 1) {
                    $row->addChild('lastmod', $this->urls[$urlCounter][self::URL_PARAM_LASTMOD]);
                }
                if ($this->urls[$urlCounter]->getSize() > 2) {
                    $row->addChild('changefreq', $this->urls[$urlCounter][self::URL_PARAM_CHANGEFREQ]);
                }
                if ($this->urls[$urlCounter]->getSize() > 3) {
                    $row->addChild('priority', $this->urls[$urlCounter][self::URL_PARAM_PRIORITY]);
                }
            }
            if (strlen($xml->asXML()) > self::MAX_FILE_SIZE) {
                throw new LengthException(
                    "Sitemap size equals to " . strlen($xml->asXML())
                    . " bytes is more than 10MB (" . self::MAX_FILE_SIZE . " bytes),
                    please decrease maxURLsPerSitemap variable."
                );
            }
            $this->sitemaps[] = $xml->asXML();
        }
        if (count($this->sitemaps) > $this->maxSitemaps) {
            throw new LengthException(
                "Sitemap index can contain {$this->maxSitemaps} sitemaps.
                Perhaps You trying to submit too many maps."
            );
        }
        if (count($this->sitemaps) > 1) {
            for ($i = 0; $i < count($this->sitemaps); $i++) {
                $this->sitemaps[$i] = array(
                    str_replace(".xml", ($i + 1) . ".xml", $this->sitemapFileName),
                    $this->sitemaps[$i]
                );
            }
            $xml = new SimpleXMLElement($sitemapIndexHeader);
            foreach ($this->sitemaps as $sitemap) {
                $row = $xml->addChild('sitemap');
                $row->addChild('loc', $this->baseURL . "/" . $this->getSitemapFileName(htmlentities($sitemap[0])));
                $row->addChild('lastmod', date('c'));
            }
            $this->sitemapFullURL = $this->baseURL . "/" . $this->sitemapIndexFileName;
            $this->sitemapIndex = array(
                $this->sitemapIndexFileName,
                $xml->asXML()
            );
        } else {
            $this->sitemapFullURL = $this->baseURL . "/" . $this->getSitemapFileName();

            $this->sitemaps[0] = array(
                $this->sitemapFileName,
                $this->sitemaps[0]
            );
        }
    }

    /**
     * Returns created sitemaps as array of strings.
     * Use it You want to work with sitemap without saving it as files.
     * @return array of strings
     * @access public
     */
    public function toArray()
    {
        if (isset($this->sitemapIndex)) {
            return array_merge(array($this->sitemapIndex), $this->sitemaps);
        } else {
            return $this->sitemaps;
        }
    }

    /**
     * Will write sitemaps as files.
     * @access public
     * @throws BadMethodCallException
     */
    public function writeSitemap()
    {
        if (!isset($this->sitemaps)) {
            throw new BadMethodCallException("To write sitemap, call createSitemap function first.");
        }
        if (isset($this->sitemapIndex)) {
            $this->document->loadXML($this->sitemapIndex[1]);
            $this->writeFile($this->document->saveXML(), $this->basePath, $this->sitemapIndex[0], true);
            foreach ($this->sitemaps as $sitemap) {
                $this->writeFile($sitemap[1], $this->basePath, $sitemap[0]);
            }
        } else {
            $this->document->loadXML($this->sitemaps[0][1]);
            $this->writeFile($this->document->saveXML(), $this->basePath, $this->sitemaps[0][0], true);
            $this->writeFile($this->sitemaps[0][1], $this->basePath, $this->sitemaps[0][0]);
        }
    }

    private function getSitemapFileName($name = null)
    {
        if (!$name) {
            $name = $this->sitemapFileName;
        }
        if ($this->createGZipFile) {
            $name .= ".gz";
        }
        return $name;
    }

    /**
     * Save file.
     * @param string $content
     * @param string $filePath
     * @param string $fileName
     * @param bool $noGzip
     * @return bool
     * @access private
     */
    private function writeFile($content, $filePath, $fileName, $noGzip = false)
    {
        if (!$noGzip && $this->createGZipFile) {
            return $this->writeGZipFile($content, $filePath, $fileName);
        }
        $file = fopen($filePath . $fileName, 'w');
        fwrite($file, $content);
        return fclose($file);
    }

    /**
     * Save GZipped file.
     * @param string $content
     * @param string $filePath
     * @param string $fileName
     * @return bool
     * @access private
     */
    private function writeGZipFile($content, $filePath, $fileName)
    {
        $fileName .= '.gz';
        $file = gzopen($filePath . $fileName, 'w');
        gzwrite($file, $content);
        return gzclose($file);
    }

    /**
     * If robots.txt file exist, will update information about newly created sitemaps.
     * If there is no robots.txt will, create one and put into it information about sitemaps.
     * @access public
     * @throws BadMethodCallException
     */
    public function updateRobots()
    {
        if (!isset($this->sitemaps)) {
            throw new BadMethodCallException("To update robots.txt, call createSitemap function first.");
        }
        $sampleRobotsFile = "User-agent: *\nAllow: /";
        if (file_exists($this->basePath . $this->robotsFileName)) {
            $robotsFile = explode("\n", file_get_contents($this->basePath . $this->robotsFileName));
            $robotsFileContent = "";
            foreach ($robotsFile as $key => $value) {
                if (substr($value, 0, 8) == 'Sitemap:') {
                    unset($robotsFile[$key]);
                } else {
                    $robotsFileContent .= $value . "\n";
                }
            }
            $robotsFileContent .= "Sitemap: $this->sitemapFullURL";
            if (!isset($this->sitemapIndex)) {
                $robotsFileContent .= "\nSitemap: " . $this->getSitemapFileName($this->sitemapFullURL);
            }
            file_put_contents($this->basePath . $this->robotsFileName, $robotsFileContent);
        } else {
            $sampleRobotsFile = $sampleRobotsFile . "\n\nSitemap: " . $this->sitemapFullURL;
            if (!isset($this->sitemapIndex)) {
                $sampleRobotsFile .= "\nSitemap: " . $this->getSitemapFileName($this->sitemapFullURL);
            }
            file_put_contents($this->basePath . $this->robotsFileName, $sampleRobotsFile);
        }
    }

    /**
     * Will inform search engines about newly created sitemaps.
     * Google, Ask, Bing and Yahoo will be noticed.
     * If You don't pass yahooAppId, Yahoo still will be informed,
     * but this method can be used once per day. If You will do this often,
     * message that limit was exceeded  will be returned from Yahoo.
     * @param string $yahooAppId Your site Yahoo appid.
     * @return array of messages and http codes from each search engine
     * @access public
     * @throws BadMethodCallException
     */
    public function submitSitemap($yahooAppId = null)
    {
        if (!isset($this->sitemaps)) {
            throw new BadMethodCallException("To submit sitemap, call createSitemap function first.");
        }
        if (!extension_loaded('curl')) {
            throw new BadMethodCallException("cURL library is needed to do submission.");
        }
        $searchEngines = $this->searchEngines;
        $searchEngines[0] = isset($yahooAppId) ?
            str_replace("USERID", $yahooAppId, $searchEngines[0][0]) :
            $searchEngines[0][1];
        $result = array();
        for ($i = 0; $i < count($searchEngines); $i++) {
            $submitSite = curl_init($searchEngines[$i] . htmlspecialchars($this->sitemapFullURL, ENT_QUOTES, 'UTF-8'));
            curl_setopt($submitSite, CURLOPT_RETURNTRANSFER, true);
            $responseContent = curl_exec($submitSite);
            $response = curl_getinfo($submitSite);
            $submitSiteShort = array_reverse(explode(".", parse_url($searchEngines[$i], PHP_URL_HOST)));
            $result[] = array(
                "site" => $submitSiteShort[1] . "." . $submitSiteShort[0],
                "fullsite" => $searchEngines[$i] . htmlspecialchars($this->sitemapFullURL, ENT_QUOTES, 'UTF-8'),
                "http_code" => $response['http_code'],
                "message" => str_replace("\n", " ", strip_tags($responseContent))
            );
        }
        return $result;
    }

    /**
     * Returns array of URLs
     *
     * Converts internal SplFixedArray to array
     * @return array
     */
    public function getUrls()
    {
        $urls = $this->urls->toArray();

        /**
         * @var int $key
         * @var SplFixedArray $urlSplArr
         */
        foreach ($urls as $key => $urlSplArr) {
            if (!is_null($urlSplArr)) {
                $urlArr = $urlSplArr->toArray();
                $url = [];
                foreach ($urlArr as $paramIndex => $paramValue) {
                    switch ($paramIndex) {
                        case static::URL_PARAM_LOC:
                            $url['loc'] = $paramValue;
                            break;
                        case static::URL_PARAM_CHANGEFREQ:
                            $url['changefreq'] = $paramValue;
                            break;
                        case static::URL_PARAM_LASTMOD:
                            $url['lastmod'] = $paramValue;
                            break;
                        case static::URL_PARAM_PRIORITY:
                            $url['priority'] = $paramValue;
                            break;
                        default:
                            break;
                    }
                }
                $urls[$key] = $url;
            }
        }

        return $urls;
    }

    public function countUrls()
    {
        return $this->urls->getSize();
    }
}
