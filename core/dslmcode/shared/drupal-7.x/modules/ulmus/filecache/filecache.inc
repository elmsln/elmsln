<?php // -*- indent-tabs-mode:nil -*-

// Max filename length for cid. Doesn't include cache bin prefix.
// Must be at least 34 (see FILECACHE_CID_FILENAME_POS_BEFORE_MD5).
define('FILECACHE_CID_FILENAME_MAX', 200);

// Cut point between not MD5 encoded and MD5 encoded
// 34 is '%_' + 32 hexdigits for 128-bit MD5
define('FILECACHE_CID_FILENAME_POS_BEFORE_MD5', FILECACHE_CID_FILENAME_MAX - 34);


function filecache_directory() {
  $filecache_directory = variable_get('filecache_directory', FALSE);
  if ($filecache_directory === FALSE) {
    // Default directory for Apache only but if it already exists, use it
    // http://drupal.org/node/1337084 (Drush support)
    $filecache_directory = DRUPAL_ROOT . '/' . conf_path() . '/files/.ht.filecache';
    if (strpos($_SERVER['SERVER_SOFTWARE'], 'Apache') !== 0 &&
        !is_dir($filecache_directory)) {
      // Neither Apache, nor default directory exists
      $filecache_directory = FALSE;
    }
  }
  return $filecache_directory;
}

class DrupalFileCache implements DrupalCacheInterface {

  function __construct($bin) {
    $this->bin = $bin;
    $filecache_directory = filecache_directory();
    $t = get_t();

    // Check for problems with filecache_directory
    $hint = FALSE;
    if (empty($filecache_directory)) {
      $hint = t('Your web server is not Apache and so default filecache_directory cannot be used.');
    } else {
      if (!is_dir($filecache_directory)) {
        if (!file_exists($filecache_directory)) {
          // Directory does not exist. Try to create it.
          if (!mkdir($filecache_directory, 0777, TRUE)) {
            $hint = $t('%dir does not exist and <samp>filecache.inc</samp> was not able to create it probably due to permission problem.', array('%dir' => $filecache_directory));
          }
          if (!chmod($filecache_directory, 0777)) {
            // insist that $filecache_directory must have 777 access mode
            // or better not exist at all
            rmdir($filecache_directory);
            $hint = $t('%dir does not exist, <samp>filecache.inc</samp> successfully created it but chmod 777 failed.', array('%dir' => $filecache_directory));
          }
        } else {
          $hint = $t('%dir is not directory.', array('%dir' => $filecache_directory));
        }
      } elseif (!is_writable($filecache_directory)) {
        $hint = $t('%dir is directory but PHP cannot write to it.', array('%dir' => $filecache_directory));
      }
    }
    if ($hint) {
?>
<p><strong><?php print $t('Fatal error: filecache_directory is not configured correctly. Please read %readmetxt.', array('%readmetxt' => dirname(__FILE__) . '/README.txt')) ?></strong></p>

<p><?php print $t('Hint: @hint', array('@hint' => $hint)) ?></p>
<?php
      die();
    }

    //@todo Support custom prefix
    $this->directory = $filecache_directory;
    $this->prefix = $this->directory .'/'. $bin .'-';
  }

  function encode_cid($cid) {
    // Use urlencode(), but turn the
    // encoded ':' and '/' back into ordinary characters since they're used so
    // often. (Especially ':', but '/' is used in cache_menu.)
    // We can't turn them back into their own characters though; both are
    // considered unsafe in filenames. So turn : -> <space> and / -> ^
    $safe_cid = str_replace(array('%2F','%3A'), array('^',' '), urlencode($cid));
    if (strlen($safe_cid) > FILECACHE_CID_FILENAME_MAX) {
      $safe_cid =
        substr($safe_cid, 0, FILECACHE_CID_FILENAME_POS_BEFORE_MD5) .
        '%_' .
        md5(substr($safe_cid, FILECACHE_CID_FILENAME_POS_BEFORE_MD5));
    }

    return $safe_cid;
  }

  function decode_cid($filename) {
    return urldecode($filename);
  }

  function get($cid) {
    $filename = $this->prefix . $this->encode_cid($cid);

    // XXX should be in getMultiple() and get() to call getMultiple()
    $this->delete_flushed();

    // Use @ because cache entry may not exist
    $content = @file_get_contents($filename);
    if ($content === FALSE) {
      return FALSE;
    }
    $cache = @unserialize($content);
    if ($cache === FALSE) {
      // we are in the middle of cache_set
      $fh = fopen($filename, 'rb');
      if ($fh === FALSE) {
        return FALSE;
      }
      if (flock($fh, LOCK_SH) === FALSE) {
        fclose($fh);
        return FALSE;
      }
      $cache = @unserialize(@stream_get_contents($fh));
      if ($cache === FALSE ||
          flock($fh, LOCK_UN) === FALSE ||
          fclose($fh) === FALSE) {
        unlink($filename); // remove broken file
        flock($fh, LOCK_UN);
        fclose($fh);
        return FALSE;
      }
    }

    // XXX Should reproduce the cache_lifetime / cache_flush_$bin logic
    $cache_flush = variable_get('filecache_flush_'. $this->bin, 0);
    if ($cache->expire != CACHE_TEMPORARY && // XXX how to handle this?
        $cache->expire != CACHE_PERMANENT &&
        ($cache->expire < REQUEST_TIME ||
         ($cache_flush && $cache->created < $cache_flush))) {
      unlink($filename);
      return FALSE;
    }

    // Some systems don't update access time so we do it this way
    // XXX There's a chance that file no longer exists at this point
    // XXX but it's ok because we deal fine with broken cache entries
    // XXX should check only once in a page request if we have such
    // XXX filesystem and set $this->touch so that here we now what to do
    // XXX should be configurable
    //touch($filename);

    // XXX should assert($cache->cid == $cid)

    return $cache;
  }

  function getMultiple(&$cids) {
    $results = array();
    foreach ($cids as $cid) {
      $cache = $this->get($cid);
      if ($cache !== FALSE) {
        $results[$cid] = $cache;
        unset($cids[$cid]);
      }
    }
    return $results;
  }

  function set($cid, $data, $expire = CACHE_PERMANENT) {
    $filename = $this->prefix . $this->encode_cid($cid);

    // Open file for that entry, handling errors that may arise
    $fh = @fopen($filename, 'r+b');
    if ($fh === FALSE) {
      // If file doesn't exist, create it with a+w permissions
      $fh = fopen($filename, 'c+b');
      if ($fh !== FALSE) {
        if (!chmod($filename, 0777)) {
          watchdog('filecache', 'Cannot chmod %filename',
                   array('%filename' => $filename), WATCHDOG_CRITICAL);
          return;
        }
      } else {
        // most likely permission error - report it as critical error
        watchdog('filecache', 'Cannot open %filename',
                 array('%filename' => $filename), WATCHDOG_CRITICAL);
        return;
      }
    }

    // Our safeguard for simultaneous writing in the same file
    if (flock($fh, LOCK_EX) === FALSE) {
      fclose($fh);
      return;
    }

    $cache = new StdClass;
    $cache->cid = $cid;
    $cache->created = REQUEST_TIME;
    $cache->expire = $expire;
    $cache->data = $data;

    if (ftruncate($fh, 0) === FALSE ||
        fwrite($fh, serialize($cache)) === FALSE ||
        flock($fh, LOCK_UN) === FALSE ||
        fclose($fh) === FALSE) {
      // XXX should not happen -> cleanup
      unlink($filename);
      flock($fh, LOCK_UN);
      fclose($fh);
      return;
    }
  }

  function clear($cid = NULL, $wildcard = FALSE) {
    global $user;

    // parts are shamelessy copied from includes/cache.inc

    if (empty($cid)) {
      if (variable_get('cache_lifetime', 0)) {
        // We store the time in the current user's $user->cache variable which
        // will be saved into the sessions bin by _drupal_session_write(). We then
        // simulate that the cache was flushed for this user by not returning
        // cached data that was cached before the timestamp.
        $user->cache = REQUEST_TIME;

        $cache_flush = variable_get('cache_flush_' . $this->bin, 0);
        if ($cache_flush == 0) {
          // This is the first request to clear the cache, start a timer.
          variable_set('cache_flush_' . $this->bin, REQUEST_TIME);
        }
        elseif (REQUEST_TIME > ($cache_flush + variable_get('cache_lifetime', 0))) {
          // Clear the cache for everyone, cache_lifetime seconds have
          // passed since the first request to clear the cache.
          $this->delete_expired();
          variable_set('cache_flush_' . $this->bin, 0);
        }
      }
      else {
        // No minimum cache lifetime, flush all temporary cache entries now.
        $this->delete_expired();
      }
    }
    else {
      if ($wildcard) {
        if ($cid == '*') {
          $this->delete_wildcard('');
        }
        else {
          $this->delete_wildcard($cid);
        }
      }
      elseif (is_array($cid)) {
        foreach ($cid as $one_cid) {
          $this->delete_one($one_cid);
        }
      }
      else {
        $this->delete_one($cid);
      }
    }
  }

  protected function delete_one($cid) {
    $filename = $this->prefix . $this->encode_cid($cid);
    @unlink($filename);
  }

  protected function all($cid_prefix = '') {
    $list = array();
    $filename_prefix = $this->bin . '-' . $this->encode_cid($cid_prefix);
    $filename_prefix_len = strlen($filename_prefix);
    $cwd = getcwd();
    chdir($this->directory);
    $dh = opendir('.');
    while (($filename = readdir($dh)) !== FALSE) {
      if (strncmp($filename, $filename_prefix, $filename_prefix_len) === 0) {
        $list[] = $filename;
      }
    }
    closedir($dh);
    chdir($cwd);
    return $list;
  }

  protected function delete_wildcard($cid_prefix) {
    foreach ($this->all($cid_prefix) as $filename) {
      @unlink ($this->directory . '/' . $filename);
    }
  }

  protected function delete_expired() {
    $cwd = getcwd();
    chdir($this->directory);
    foreach ($this->all() as $filename) {
      // XXX reads all entries XXX
      $content = @file_get_contents($filename);
      if ($content === FALSE) {
        continue;
      }
      $cache = @unserialize($content);
      if ($content === FALSE) {
        continue;
      }
      if ($cache->expire == CACHE_PERMANENT) {
        continue;
      }
      if ($cache->expire == CACHE_TEMPORARY ||
          $cache->expire < REQUEST_TIME) {
        @unlink($filename);
      }
    } // foreach $filename
    chdir($cwd);
  }

  protected function delete_flushed() {
    static $recursion = FALSE; // XXX how cache.inc survives this?
    if ($recursion) {
      return;
    }
    $recursion = TRUE;

    // Garbage collection necessary when enforcing a minimum cache lifetime.
    $cache_flush = variable_get('cache_flush_' . $this->bin, 0);
    if ($cache_flush && ($cache_flush + variable_get('cache_lifetime', 0) <= REQUEST_TIME)) {
      // Reset the variable immediately to prevent a meltdown in heavy load situations.
      variable_set('cache_flush_' . $this->bin, 0);
      // Time to flush old cache data
      $cwd = getcwd();
      chdir($this->directory);
      foreach ($this->all() as $filename) {
        // XXX reads all entries XXX
        $content = @file_get_contents($filename);
        if ($content === FALSE) {
          continue;
        }
        $cache = @unserialize($content);
        if ($content === FALSE) {
          continue;
        }
        if ($cache->expire != CACHE_PERMANENT &&
            $cache->expire <= $cache_flush) {
          @unlink($filename);
        }
      } // foreach $filename
      chdir($cwd);
    } // if $cache_flush

    $recursion = FALSE;
  }

  function isEmpty() {
    return count($this->all()) == 0;
  }

}

