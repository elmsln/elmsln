<?php
/**
 * Error Stack Implementation - E_STRICT compliant
 *
 * This is an incredibly simple implementation of a very complex error handling
 * facility.  It contains the ability
 * to track multiple errors from multiple packages simultaneously.  In addition,
 * it can track errors of many levels, save data along with the error, context
 * information such as the exact file, line number, class and function that
 * generated the error, and if necessary, it can raise a traditional PEAR_Error.
 * It has built-in support for PEAR::Log, to log errors as they occur
 * @author Greg Beaver <cellog@php.net>
 * @version 0.1alpha (E_STRICT)
 * @package PEAR_ErrorStack
 * @category Debugging
 * @license http://opensource.org/licenses/bsd-license.php New BSD License
 */

/**
 * PEAR_Exception is used by default
 */
require_once 'PEAR/Exception.php';

class PEAR_ErrorStack_Exception extends PEAR_Exception{}

/**#@+
 * One of four possible return values from the error Callback
 * @see PEAR_ErrorStack::_errorCallback()
 */
/**
 * If this is returned, then the error will be both pushed onto the stack
 * and logged.
 */
define('PEAR_ERRORSTACK_PUSHANDLOG', 1);
/**
 * If this is returned, then the error will only be pushed onto the stack,
 * and not logged.
 */
define('PEAR_ERRORSTACK_PUSH', 2);
/**
 * If this is returned, then the error will only be logged, but not pushed
 * onto the error stack.
 */
define('PEAR_ERRORSTACK_LOG', 3);
/**
 * If this is returned, then the error is completely ignored.
 */
define('PEAR_ERRORSTACK_IGNORE', 4);
/**#@-*/

/**
 * Error code for an attempt to instantiate a non-class as a PEAR_ErrorStack in
 * the singleton method.
 */
define('PEAR_ERRORSTACK_ERR_NONCLASS', 1);

/**
 * Error code for an attempt to pass an object into {@link PEAR_ErrorStack::getMessage()}
 * that has no __toString() method
 */
define('PEAR_ERRORSTACK_ERR_OBJTOSTRING', 2);
/**
 * Error Stack Implementation
 *
 * Usage:
 * <code>
 * // global error stack
 * $global_stack = &PEAR_ErrorStack::singleton('MyPackage');
 * // local error stack
 * $local_stack = new PEAR_ErrorStack('MyPackage');
 * </code>
 * @copyright 2004 Gregory Beaver <cellog@php.net>
 * @package PEAR_ErrorStack
 * @license http://opensource.org/licenses/bsd-license.php New BSD License
 */
class PEAR_ErrorStack {
    /**
     * Singleton storage
     *
     * Format:
     * <pre>
     * array(
     *  'package1' => PEAR_ErrorStack object,
     *  'package2' => PEAR_ErrorStack object,
     *  ...
     * )
     * </pre>
     */
    static protected $singleton;

    /**
     * Global error callback (default)
     *
     * This is only used if set to non-false.  * is the default callback for
     * all packages, whereas specific packages may set a default callback
     * for all instances, regardless of whether they are a singleton or not.
     *
     * To exclude non-singletons, only set the local callback for the singleton
     * @see PEAR_ErrorStack::setDefaultCallback()
     */
    static protected $globalcallback =
        array(
            '*' => false,
        );

    /**
     * Global Log object (default)
     *
     * This is only used if set to non-false.  Use to set a default log object for
     * all stacks, regardless of instantiation order or location
     * @see PEAR_ErrorStack::setDefaultLogger()
     */
    static protected $globallogger = false;

    /**
     * PEAR_Warning callback
     *
     * This is only used if set to non-false.  Use to set a default log object for
     * all stacks, regardless of instantiation order or location
     * @see PEAR_ErrorStack::setDefaultLogger()
     */
    static protected $pearwarningcallback = false;

    /**
     * Global Overriding Callback
     *
     * This callback will override any error callbacks that specific loggers have set.
     * Use with EXTREME caution
     * @see PEAR_ErrorStack::staticPushCallback()
     * @access private
     * @global array $GLOBALS['_PEAR_ERRORSTACK_DEFAULT_LOGGER']
     */
    static protected $overridecallback = array();

    /**
     * Errors are stored in the order that they are pushed on the stack.
     * @since 0.4alpha Errors are no longer organized by error level.
     * This renders pop() nearly unusable, and levels could be more easily
     * handled in a callback anyway
     * @var array
     */
    private $_errors = array();

    /**
     * Storage of errors by level.
     *
     * Allows easy retrieval and deletion of only errors from a particular level
     * @since PEAR 1.4.0dev
     * @var array
     */
    private $_errorsByLevel = array();

    /**
     * Package name this error stack represents
     * @var string
     */
    protected $_package;

    /**
     * Determines whether a PEAR_Error is thrown upon every error addition
     * @var boolean
     */
    private $_compat = false;

    /**
     * If set to a valid callback, this will be used to generate the error
     * message from the error code, otherwise the message passed in will be
     * used
     * @var false|string|array
     */
    private $_msgCallback = false;

    /**
     * If set to a valid callback, this will be used to generate the error
     * context for an error.  For PHP-related errors, this will be a file
     * and line number as retrieved from debug_backtrace(), but can be
     * customized for other purposes.  The error might actually be in a separate
     * configuration file, or in a database query.
     * @var false|string|array
     */
    public $contextCallback = false;

    /**
     * If set to a valid callback, this will be called every time an error
     * is pushed onto the stack.  The return value will be used to determine
     * whether to allow an error to be pushed or logged.
     *
     * The return value must be one an PEAR_ERRORSTACK_* constant
     * @see PEAR_ERRORSTACK_PUSHANDLOG, PEAR_ERRORSTACK_PUSH, PEAR_ERRORSTACK_LOG
     * @var false|string|array
     */
    protected $_errorCallback = array();

    /**
     * PEAR::Log object for logging errors
     * @var false|Log
     */
    protected $_logger = false;

    /**
     * Error messages - designed to be overridden
     * @var array
     * @abstract
     */
    protected $_errorMsgs = array();

    /**
     * Set up a new error stack
     *
     * @param string   $package name of the package this error stack represents
     * @param callback $msgCallback callback used for error message generation
     * @param callback $contextCallback callback used for context generation,
     *                 defaults to {@link getFileLine()}
     * @param boolean  $throwPEAR_Error (ignored)
     */
    public function PEAR_ErrorStack($package, $msgCallback = false, $contextCallback = false,
                                    $throwPEAR_Error = false)
    {
        $this->_package = $package;
        $this->setMessageCallback($msgCallback);
        $this->setContextCallback($contextCallback);
        $this->_compat = false;
    }

    /**
     * Return a single error stack for this package.
     *
     * Note that all parameters are ignored if the stack for package $package
     * has already been instantiated
     * @param string   $package name of the package this error stack represents
     * @param callback $msgCallback callback used for error message generation
     * @param callback $contextCallback callback used for context generation,
     *                 defaults to {@link getFileLine()}
     * @param boolean  $throwPEAR_Error
     * @param string   $exceptionClass exception class to instantiate if
     *                 in PHP 5
     * @param string   $stackClass class to instantiate
     * @static
     * @return PEAR_ErrorStack
     */
    static public function singleton($package, $msgCallback = false, $contextCallback = false,
                              $throwPEAR_Error = false, $stackClass = 'PEAR_ErrorStack')
    {
        if (isset(self::$singleton[$package])) {
            return self::$singleton[$package];
        }
        if (!class_exists($stackClass)) {
            throw PEAR_ErrorStack::staticPush('PEAR_ErrorStack', PEAR_ERRORSTACK_ERR_NONCLASS,
                'exception', array('stackclass' => $stackClass),
                'stack class "%stackclass%" is not a valid class name (should be like PEAR_ErrorStack)',
                false, $trace);
        }
        return self::$singleton[$package] =
            new $stackClass($package, $msgCallback, $contextCallback, $throwPEAR_Error);
    }


    /**
     * Set up a PEAR::Log object for all error stacks that don't have one
     * @param Log $log
     * @static
     */
    static public function setDefaultLogger($log)
    {
        self::$globallogger = $log;
    }

    /**
     * Set up a PEAR::Log object for this error stack
     * @param Log $log
     */
    public function setLogger($log)
    {
        $this->_logger = $log;
    }

    /**
     * Set an error code => error message mapping callback
     *
     * This method sets the callback that can be used to generate error
     * messages for any instance
     * @param array|string Callback function/method
     */
    public function setMessageCallback($msgCallback)
    {
        if (!$msgCallback) {
            $this->_msgCallback = array($this, 'getErrorMessage');
        } else {
            if (is_callable($msgCallback)) {
                $this->_msgCallback = $msgCallback;
            }
        }
    }

    /**
     * Get an error code => error message mapping callback
     *
     * This method returns the current callback that can be used to generate error
     * messages
     * @return array|string|false Callback function/method or false if none
     */
    public function getMessageCallback()
    {
        return $this->_msgCallback;
    }

    /**
     * Sets a default callback to be used by all error stacks
     *
     * This method sets the callback that can be used to generate error
     * messages for a singleton
     * @param array|string Callback function/method
     * @param string Package name, or false for all packages
     */
    static public function setDefaultCallback($callback = false, $package = false)
    {
        if (!is_callable($callback)) {
            $callback = false;
        }
        $package = $package ? $package : '*';
        self::$globalcallback[$package] = $callback;
    }

    /**
     * Do not use
     * @access private
     */
    static public function setPEARWarningCallback($callback)
    {
        self::$pearwarningcallback = $callback;
    }

    /**
     * Set an error code => error message mapping callback
     *
     * This method sets the callback that can be used to generate context
     * information for an error.  Passing in NULL will disable context generation
     * and remove the expensive call to debug_backtrace()
     * @param array|string Callback function/method
     */
    public function setContextCallback($contextCallback)
    {
        if ($contextCallback === null) {
            return $this->contextCallback = false;
        }
        if (!$contextCallback) {
            $this->contextCallback = array($this, 'getFileLine');
        } else {
            if (is_callable($contextCallback)) {
                $this->contextCallback = $contextCallback;
            }
        }
    }

    /**
     * Set an error Callback
     * If set to a valid callback, this will be called every time an error
     * is pushed onto the stack.  The return value will be used to determine
     * whether to allow an error to be pushed or logged.
     *
     * The return value must be one of the ERRORSTACK_* constants.
     *
     * This functionality can be used to emulate PEAR's pushErrorHandling, and
     * the PEAR_ERROR_CALLBACK mode, without affecting the integrity of
     * the error stack or logging
     * @see PEAR_ERRORSTACK_PUSHANDLOG, PEAR_ERRORSTACK_PUSH, PEAR_ERRORSTACK_LOG
     * @see popCallback()
     * @param string|array $cb
     */
    public function pushCallback($cb)
    {
        array_push($this->_errorCallback, $cb);
    }

    /**
     * Remove a callback from the error callback stack
     * @see pushCallback()
     * @return array|string|false
     */
    public function popCallback()
    {
        if (!count($this->_errorCallback)) {
            return false;
        }
        return array_pop($this->_errorCallback);
    }

    /**
     * Set a temporary overriding error callback for every package error stack
     *
     * Use this to temporarily disable all existing callbacks (can be used
     * to emulate the @ operator, for instance)
     * @see PEAR_ERRORSTACK_PUSHANDLOG, PEAR_ERRORSTACK_PUSH, PEAR_ERRORSTACK_LOG
     * @see staticPopCallback(), pushCallback()
     * @param string|array $cb
     */
    static public function staticPushCallback($cb)
    {
        array_push(self::$overridecallback, $cb);
    }

    /**
     * Remove a temporary overriding error callback
     * @see staticPushCallback()
     * @return array|string|false
     */
    static public function staticPopCallback()
    {
        $ret = array_pop(self::$overridecallback);
        if (!is_array(self::$overridecallback)) {
            self::$overridecallback = array();
        }
        return $ret;
    }

    /**
     * demote an exception to a non-fatal error (default is warning)
     * @param Exception
     * @param string
     */
    public function demoteException($e, $level = 'warning')
    {
        $this->push(get_class($e), $level, array(),
            $e->getMessage(), $e, $e->getTrace());
    }

    /**
     * promote a warning into a PEAR_Exception
     *
     * It is probably best to do this manually, to take advantage of the
     * use of exception classnames to categorize errors
     * @return PEAR_Exception
     */
    public function promoteWarning($warning, $exceptionclass = 'PEAR_Exception')
    {
        return new $exceptionclass($warning['message'],
            array($warning), $warning['code']);
    }

    /**
     * Add an error to the stack
     *
     * If the message generator exists, it is called with 2 parameters.
     *  - the current Error Stack object
     *  - an array that is in the same format as an error.  Available indices
     *    are 'code', 'package', 'time', 'params', 'level', and 'context'
     *
     * Next, if the error should contain context information, this is
     * handled by the context grabbing method.
     * Finally, the error is pushed onto the proper error stack
     * @param int    $code      Package-specific error code
     * @param string $level     Error level.  This is NOT spell-checked
     * @param array  $params    associative array of error parameters
     * @param string $msg       Error message, or a portion of it if the message
     *                          is to be generated
     * @param array  $repackage If this error re-packages an error pushed by
     *                          another package, place the array returned from
     *                          {@link pop()} in this parameter
     * @param array  $backtrace Protected parameter: use this to pass in the
     *                          {@link debug_backtrace()} that should be used
     *                          to find error context
     * @return PEAR_Error|array|Exception
     *                          if compatibility mode is on, a PEAR_Error is also
     *                          thrown.  If the class Exception exists, then one
     *                          is returned to allow code like:
     * <code>
     * throw ($stack->push(MY_ERROR_CODE, 'error', array('username' => 'grob')));
     * </code>
     *
     * The errorData property of the exception class will be set to the array
     * that would normally be returned.  If a PEAR_Error is returned, the userinfo
     * property is set to the array
     *
     * Otherwise, an array is returned in this format:
     * <code>
     * array(
     *    'code' => $code,
     *    'params' => $params,
     *    'package' => $this->_package,
     *    'level' => $level,
     *    'time' => time(),
     *    'context' => $context,
     *    'message' => $msg,
     * //['repackage' => $err] repackaged error array
     * );
     * </code>
     */
    public function push($code, $level = 'error', $params = array(), $msg = false,
                         $repackage = false, $backtrace = false)
    {
        $context = false;
        // grab error context
        if ($this->contextCallback) {
            if (!$backtrace) {
                $backtrace = debug_backtrace();
            }
            $context = call_user_func($this->contextCallback, $code, $params, $backtrace);
        }

        // save error
        $time = explode(' ', microtime());
        $time = $time[1] + $time[0];
        $err = array(
                'code' => $code,
                'params' => $params,
                'package' => $this->_package,
                'level' => $level,
                'time' => $time,
                'context' => $context,
                'message' => $msg,
               );

        // set up the error message, if necessary
        if ($this->_msgCallback) {
            $msg = call_user_func_array($this->_msgCallback,
                                        array($this, $err));
            $err['message'] = $msg;
        }


        if ($repackage) {
            $err['repackage'] = $repackage;
        }
        $push = $log = true;
        // try the overriding callback first
        $callback = $this->staticPopCallback();
        if ($callback) {
            $this->staticPushCallback($callback);
        }
        if (!is_callable($callback)) {
            // try the local callback next
            $callback = $this->popCallback();
            if (is_callable($callback)) {
                $this->pushCallback($callback);
            } else {
                // try the default callback
                $callback = isset(self::$globalcallback[$this->_package]) ?
                    self::$globalcallback[$this->_package] :
                    self::$globalcallback['*'];
            }
        }
        if (is_callable($callback)) {
            switch(call_user_func($callback, $err)){
            	case PEAR_ERRORSTACK_IGNORE:
            		return $err;
        		break;
            	case PEAR_ERRORSTACK_PUSH:
            		$log = false;
        		break;
            	case PEAR_ERRORSTACK_LOG:
            		$push = false;
        		break;
                // anything else returned has the same effect as pushandlog
            }
        }
        if ($push) {
            if (is_callable(self::$pearwarningcallback)) {
                call_user_func(self::$pearwarningcallback, $err);
            }
            array_unshift($this->_errors, $err);
            $this->_errorsByLevel[$err['level']][] = &$this->_errors[0];
        }
        if ($log) {
            if ($this->_logger || self::$globallogger) {
                $this->_log($err);
            }
        }
        return $err;
    }

    /**
     * Static version of {@link push()}
     *
     * @param string $package   Package name this error belongs to
     * @param int    $code      Package-specific error code
     * @param string $level     Error level.  This is NOT spell-checked
     * @param array  $params    associative array of error parameters
     * @param string $msg       Error message, or a portion of it if the message
     *                          is to be generated
     * @param array  $repackage If this error re-packages an error pushed by
     *                          another package, place the array returned from
     *                          {@link pop()} in this parameter
     * @param array  $backtrace Protected parameter: use this to pass in the
     *                          {@link debug_backtrace()} that should be used
     *                          to find error context
     * @return PEAR_Error|null|Exception
     *                          if compatibility mode is on, a PEAR_Error is also
     *                          thrown.  If the class Exception exists, then one
     *                          is returned to allow code like:
     * <code>
     * throw ($stack->push(MY_ERROR_CODE, 'error', array('username' => 'grob')));
     * </code>
     * @static
     */
    static public function staticPush($package, $code, $level = 'error', $params = array(),
                        $msg = false, $repackage = false, $backtrace = false)
    {
        $s = PEAR_ErrorStack::singleton($package);
        if ($s->contextCallback) {
            if (!$backtrace) {
                $backtrace = debug_backtrace();
            }
        }
        return $s->push($code, $level, $params, $msg, $repackage, $backtrace);
    }

    /**
     * Log an error using PEAR::Log
     * @param array $err Error array
     * @param array $levels Error level => Log constant map
     * @access protected
     */
    protected function _log($err, $levels = array(
                'exception' => PEAR_LOG_CRIT,
                'alert' => PEAR_LOG_ALERT,
                'critical' => PEAR_LOG_CRIT,
                'error' => PEAR_LOG_ERR,
                'warning' => PEAR_LOG_WARNING,
                'notice' => PEAR_LOG_NOTICE,
                'info' => PEAR_LOG_INFO,
                'debug' => PEAR_LOG_DEBUG))
    {
        if (isset($levels[$err['level']])) {
            $level = $levels[$err['level']];
        } else {
            $level = PEAR_LOG_INFO;
        }
        if ($this->_logger) {
            $this->_logger->log($err['message'], $level, $err);
        } else {
            self::$globallogger->log($err['message'], $level, $err);
        }
    }


    /**
     * Pop an error off of the error stack
     *
     * @return false|array
     * @since 0.4alpha it is no longer possible to specify a specific error
     * level to return - the last error pushed will be returned, instead
     */
    public function pop()
    {
        return @array_shift($this->_errors);
    }

    /**
     * Determine whether there are any errors on the stack
     * @param string|array Level name.  Use to determine if any errors
     * of level (string), or levels (array) have been pushed
     * @return boolean
     */
    public function hasErrors($level = false)
    {
        if ($level) {
            return isset($this->_errorsByLevel[$level]);
        }
        return count($this->_errors);
    }

    /**
     * Retrieve all errors since last purge
     *
     * @param boolean set in order to empty the error stack
     * @param string level name, to return only errors of a particular severity
     * @return array
     */
    public function getErrors($purge = false, $level = false)
    {
        if (!$purge) {
            if ($level) {
                if (!isset($this->_errorsByLevel[$level])) {
                    return array();
                } else {
                    return $this->_errorsByLevel[$level];
                }
            } else {
                return $this->_errors;
            }
        }
        if ($level) {
            $ret = $this->_errorsByLevel[$level];
            foreach ($this->_errorsByLevel[$level] as $i => $unused) {
                // entries are references to the $_errors array
                $this->_errorsByLevel[$level][$i] = false;
            }
            // array_filter removes all entries === false
            $this->_errors = array_filter($this->_errors);
            unset($this->_errorsByLevel[$level]);
            return $ret;
        }
        $ret = $this->_errors;
        $this->_errors = array();
        $this->_errorsByLevel = array();
        return $ret;
    }

    /**
     * Determine whether there are any errors on a single error stack, or on any error stack
     *
     * The optional parameter can be used to test the existence of any errors without the need of
     * singleton instantiation
     * @param string|false Package name to check for errors
     * @param string Level name to check for a particular severity
     * @return boolean
     */
    static public function staticHasErrors($package = false, $level = false)
    {
        if ($package) {
            if (!isset(self::$singleton[$package])) {
                return false;
            }
            return self::$singleton[$package]->hasErrors($level);
        }
        foreach (self::$singleton as $package => $obj) {
            if ($obj->hasErrors($level)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Get a list of all errors since last purge, organized by package
     * @since PEAR 1.4.0dev BC break! $level is now in the place $merge used to be
     * @param boolean $clearStack Set to purge the error stack of existing errors
     * @param string  $level Set to a level name in order to retrieve only errors of a particular level
     * @param boolean $merge Set to return a flat array, not organized by package
     * @param array   $sortfunc Function used to sort a merged array - default
     *        sorts by time, and should be good for most cases
     * @return array
     */
    static public function staticGetErrors($purge = false, $level = false, $merge = false, $sortfunc = array('PEAR_ErrorStack', '_sortErrors'))
    {
        $ret = array();
        if (!is_callable($sortfunc)) {
            $sortfunc = array('PEAR_ErrorStack', '_sortErrors');
        }
        foreach (self::$singleton as $package => $obj) {
            $test = self::$singleton[$package]->getErrors($purge, $level);
            if ($test) {
                if ($merge) {
                    $ret = array_merge($ret, $test);
                } else {
                    $ret[$package] = $test;
                }
            }
        }
        if ($merge) {
            usort($ret, $sortfunc);
        }
        return $ret;
    }

    /**
     * Error sorting function, sorts by time
     * @access private
     */
    function _sortErrors($a, $b)
    {
        if ($a['time'] == $b['time']) {
            return 0;
        }
        if ($a['time'] < $b['time']) {
            return 1;
        }
        return -1;
    }

    /**
     * Standard file/line number/function/class context callback
     *
     * This function uses a backtrace generated from {@link debug_backtrace()}
     * and so will not work at all in PHP < 4.3.0.  The frame should
     * reference the frame that contains the source of the error.
     * @return array|false either array('file' => file, 'line' => line,
     *         'function' => function name, 'class' => class name) or
     *         if this doesn't work, then false
     * @param unused
     * @param integer backtrace frame.
     * @param array Results of debug_backtrace()
     */
    static public function getFileLine($code, $params, $backtrace = null)
    {
        if ($backtrace === null) {
            return false;
        }
        $frame = 0;
        $functionframe = 1;
        if (!isset($backtrace[1])) {
            $functionframe = 0;
        } else {
            while (isset($backtrace[$functionframe]['function']) &&
                  $backtrace[$functionframe]['function'] == 'eval' &&
                  isset($backtrace[$functionframe + 1])) {
                $functionframe++;
            }
        }
        if (isset($backtrace[$frame])) {
            if (!isset($backtrace[$frame]['file'])) {
                $frame++;
            }
            $funcbacktrace = $backtrace[$functionframe];
            $filebacktrace = $backtrace[$frame];
            $ret = array('file' => $filebacktrace['file'],
                         'line' => $filebacktrace['line']);
            // rearrange for eval'd code or create function errors
            if (strpos($filebacktrace['file'], '(') &&
            	  preg_match(';^(.*?)\((\d+)\) : (.*?)\\z;', $filebacktrace['file'],
                  $matches)) {
                $ret['file'] = $matches[1];
                $ret['line'] = $matches[2] + 0;
            }
            if (isset($funcbacktrace['function']) && isset($backtrace[1])) {
                if ($funcbacktrace['function'] != 'eval') {
                    if ($funcbacktrace['function'] == '__lambda_func') {
                        $ret['function'] = 'create_function() code';
                    } else {
                        $ret['function'] = $funcbacktrace['function'];
                    }
                }
            }
            if (isset($funcbacktrace['class']) && isset($backtrace[1])) {
                $ret['class'] = $funcbacktrace['class'];
            }
            return $ret;
        }
        return false;
    }

    /**
     * Standard error message generation callback
     *
     * This method may also be called by a custom error message generator
     * to fill in template values from the params array, simply
     * set the third parameter to the error message template string to use
     *
     * The special variable %__msg% is reserved: use it only to specify
     * where a message passed in by the user should be placed in the template,
     * like so:
     *
     * Error message: %msg% - internal error
     *
     * If the message passed like so:
     *
     * <code>
     * $stack->push(ERROR_CODE, 'error', array(), 'server error 500');
     * </code>
     *
     * The returned error message will be "Error message: server error 500 -
     * internal error"
     * @param PEAR_ErrorStack
     * @param array
     * @param string|false Pre-generated error message template
     * @static
     * @return string
     */
    public function getErrorMessage(&$stack, $err, $template = false)
    {
        if ($template) {
            $mainmsg = $template;
        } else {
            $mainmsg = $stack->getErrorMessageTemplate($err['code']);
        }
        $mainmsg = str_replace('%__msg%', $err['message'], $mainmsg);
        if (count($err['params'])) {
            foreach ($err['params'] as $name => $val) {
                if (is_array($val)) {
                    // @ is needed in case $val is a multi-dimensional array
                    $val = @implode(', ', $val);
                }
                if (is_object($val)) {
                    if (method_exists($val, '__toString')) {
                        $val = $val->__toString();
                    } else {
                        throw PEAR_ErrorStack::staticPush('PEAR_ErrorStack', PEAR_ERRORSTACK_ERR_OBJTOSTRING,
                            'warning', array('obj' => get_class($val)),
                            'object %obj% passed into getErrorMessage, but has no __toString() method');
                        $val = 'Object';
                    }
                }
                $mainmsg = str_replace('%' . $name . '%', $val, $mainmsg);
            }
        }
        return $mainmsg;
    }

    /**
     * Standard Error Message Template generator from code
     * @return string
     */
    public function getErrorMessageTemplate($code)
    {
        if (!isset($this->_errorMsgs[$code])) {
            return '%__msg%';
        }
        return $this->_errorMsgs[$code];
    }

    /**
     * Set the Error Message Template array
     *
     * The array format must be:
     * <pre>
     * array(error code => 'message template',...)
     * </pre>
     *
     * Error message parameters passed into {@link push()} will be used as input
     * for the error message.  If the template is 'message %foo% was %bar%', and the
     * parameters are array('foo' => 'one', 'bar' => 'six'), the error message returned will
     * be 'message one was six'
     * @return string
     */
    public function setErrorMessageTemplate($template)
    {
        $this->_errorMsgs = $template;
    }
}
PEAR_ErrorStack::singleton('PEAR_ErrorStack', false, null, false, 'PEAR_ErrorStack_Exception');
?>