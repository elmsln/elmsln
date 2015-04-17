<?php
/**
 * @file
 * Stub classes for testing.
 */

/**
 * Simple invocation recorder class.
 */
class AuthcacheP13nTestStubObserver {
  protected $invocations;
  protected $returns;
  protected $objects;
  protected $classes;

  /**
   * Construct new stub observer instance.
   */
  public function __construct() {
    $this->classes = array();
    $this->objects = array();
    $this->invocations = array();
    $this->returns = array();
  }

  /**
   * Setup invocation verifier and return-value for a method.
   *
   * @return AuthcacheP13nTestStubVerifyer
   *   New invocation verifier instance.
   */
  public function method($object, $method, $return = NULL) {
    $name = $this->boundMethodName($object, $method);
    $this->returns[$name] = $return;
    $this->invocations[$name] = array();
    return new AuthcacheP13nTestStubVerifyer($name, $this);
  }

  /**
   * Record one method invocation.
   */
  public function record($object, $method, $arguments) {
    $name = $this->boundMethodName($object, $method);

    // Record invocation.
    $this->invocations[$name][] = $arguments;

    $result = isset($this->returns[$name]) ? $this->returns[$name] : NULL;
    if (is_object($result) && $result instanceof Exception) {
      throw $result;
    }

    // Return result.
    return $result;
  }

  /**
   * Return recorded invocations.
   */
  public function invocations($name) {
    return $this->invocations[$name];
  }

  /**
   * Compute the name for a bound method.
   */
  public function boundMethodName($object, $method) {
    $id = spl_object_hash($object);

    if (isset($this->objects[$id])) {
      $instance_name = $this->objects[$id]['name'];
    }
    else {
      $class_name = get_class($object);

      if (!isset($this->classes[$class_name])) {
        $this->classes[$class_name] = 0;
      }

      $instance_counter = $this->classes[$class_name]++;
      $instance_name = $class_name . '_' . $instance_counter;

      $this->objects[$id] = array(
        'instance' => $object,
        'name' => $instance_name,
      );
    }

    return $instance_name . '::' . $method;
  }
}

/**
 * Simple invocation verifier class.
 */
class AuthcacheP13nTestStubVerifyer {
  protected $name;
  protected $observer;
  protected $checks;

  /**
   * Construct new invocation verifier instance.
   *
   * Do not use directly, invocation verifier objects are returned by
   * AuthcacheP13nTestStubObserver::method().
   */
  public function __construct($name, $observer) {
    $this->name = $name;
    $this->observer = $observer;
    $this->checks = array();
  }

  /**
   * Add an expectation.
   */
  public function expect($checkfunc, $message = NULL) {
    $this->checks[] = $checkfunc;
    return $this;
  }

  /**
   * Test whether the the expectations are fullfilled.
   */
  public function verify(&$message) {
    $invocations = $this->observer->invocations($this->name);
    $checks = $this->checks;

    if (empty($checks)) {
      $checks = array(
        AuthcacheP13nTestStubVerifyer::once(),
      );
    }

    foreach ($checks as $checkfunc) {
      if (!$checkfunc($invocations, $this->name, $message)) {
        return FALSE;
      }
    }

    return TRUE;
  }

  /**
   * Invocation verifier ensuring that a method was never invoked.
   */
  public static function never() {
    return static::times(0);
  }

  /**
   * Invocation verifier testing whether a method was invoked exacly once.
   */
  public static function once() {
    return static::times(1);
  }

  /**
   * Invocation verifier testing the number of times a method was invoked.
   */
  public static function times($expected) {
    // Necessary until #1272900 lands
    // @ignore style_function_spacing
    return function($invocations, $name, &$message) use ($expected) {
      $actual = count($invocations);
      $message = format_plural($expected, '@name: Expecting one invocation, got @actual.', '@name: Expecting @expected invocations, got @actual.', array(
        '@name' => $name,
        '@expected' => $expected,
        '@actual' => $actual,
      ));
      return $expected === $actual;
    };
  }

  /**
   * Invocation verifier matching the arguments of a given invocation.
   */
  public static function args($args = array(), $invoc = 0) {
    // Necessary until #1272900 lands
    // @ignore style_function_spacing
    return function($invocations, $name, &$message) use ($args, $invoc) {
      $message = t('@name: On invocation number @invoc, expecting arguments @this and got @that.', array(
        '@name' => $name,
        '@invoc' => $invoc,
        '@this' => var_export($args, TRUE),
        '@that' => var_export($invocations[$invoc], TRUE),
      ));
      return $invocations[$invoc] === $args;
    };
  }
}

/**
 * Stub class for core services.
 */
class AuthcacheP13nTestCoreServiceStub implements AuthcacheP13nCoreServiceInterface {
  protected $observer;

  /**
   * Construct new stub class.
   */
  public function __construct($observer) {
    $this->observer = $observer;
  }

  /**
   * {@inheritdoc}
   */
  public function drupalAddHttpHeader($name, $value, $append = FALSE) {
    return $this->observer->record($this, __FUNCTION__, func_get_args());
  }

  /**
   * {@inheritdoc}
   */
  public function drupalBootstrap($phase = NULL, $new_phase = TRUE) {
    return $this->observer->record($this, __FUNCTION__, func_get_args());
  }
}

/**
 * Stub class for request validator.
 */
class AuthcacheP13nTestRequestValidatorStub implements AuthcacheP13nRequestValidatorInterface {
  protected $observer;

  /**
   * Construct new stub class.
   */
  public function __construct($observer) {
    $this->observer = $observer;
  }

  /**
   * {@inheritdoc}
   */
  public function validate($params) {
    return $this->observer->record($this, __FUNCTION__, func_get_args());
  }
}

/**
 * Stub class for content builder.
 */
class AuthcacheP13nTestContentBuilderStub implements AuthcacheP13nContentBuilderInterface {
  protected $observer;

  /**
   * Construct new stub class.
   */
  public function __construct($observer) {
    $this->observer = $observer;
  }

  /**
   * {@inheritdoc}
   */
  public function build($input, $context) {
    return $this->observer->record($this, __FUNCTION__, func_get_args());
  }
}

/**
 * Stub class for content encoder.
 */
class AuthcacheP13nTestContentEncoderStub implements AuthcacheP13nContentEncoderInterface {
  protected $observer;

  /**
   * Construct new stub class.
   */
  public function __construct($observer) {
    $this->observer = $observer;
  }

  /**
   * {@inheritdoc}
   */
  public function contentType() {
    return $this->observer->record($this, __FUNCTION__, func_get_args());
  }

  /**
   * {@inheritdoc}
   */
  public function encode($result) {
    return $this->observer->record($this, __FUNCTION__, func_get_args());
  }
}

/**
 * Stub context provider.
 */
class AuthcacheP13nTestContextProviderStub implements AuthcacheP13nContextProviderInterface {
  protected $observer;

  /**
   * Construct new stub class.
   */
  public function __construct($observer) {
    $this->observer = $observer;
  }

  /**
   * {@inheritdoc}
   */
  public function get($params) {
    return $this->observer->record($this, __FUNCTION__, func_get_args());
  }
}

/**
 * Stub class for content builder.
 */
class AuthcacheP13nTestFilterStub implements AuthcacheP13nFilterInterface {
  protected $observer;

  /**
   * Construct new stub class.
   */
  public function __construct($observer) {
    $this->observer = $observer;
  }

  /**
   * {@inheritdoc}
   */
  public function filter($event, $input) {
    return $this->observer->record($this, __FUNCTION__, func_get_args());
  }
}

/**
 * Stub fragment.
 */
class AuthcacheP13nTestFragmentStub implements AuthcacheP13nFragmentInterface {
  protected $observer;

  /**
   * Construct new stub class.
   */
  public function __construct($observer) {
    $this->observer = $observer;
  }

  /**
   * {@inheritdoc}
   */
  public function render($key, $subject, $context) {
    return $this->observer->record($this, __FUNCTION__, func_get_args());
  }
}

/**
 * Stub fragment validator.
 */
class AuthcacheP13nTestFragmentValidatorStub implements AuthcacheP13nFragmentValidatorInterface {
  protected $observer;

  /**
   * Construct new stub class.
   */
  public function __construct($observer) {
    $this->observer = $observer;
  }

  /**
   * {@inheritdoc}
   */
  public function validate($keys) {
    return $this->observer->record($this, __FUNCTION__, func_get_args());
  }
}

/**
 * Stub fragment loader.
 */
class AuthcacheP13nTestFragmentLoaderStub implements AuthcacheP13nFragmentLoaderInterface {
  protected $observer;

  /**
   * Construct new stub class.
   */
  public function __construct($observer) {
    $this->observer = $observer;
  }

  /**
   * {@inheritdoc}
   */
  public function load($keys, $context) {
    return $this->observer->record($this, __FUNCTION__, func_get_args());
  }
}

/**
 * Stub fragment access checker.
 */
class AuthcacheP13nTestFragmentAccessStub implements AuthcacheP13nFragmentAccessInterface {
  protected $observer;

  /**
   * Construct new stub class.
   */
  public function __construct($observer) {
    $this->observer = $observer;
  }

  /**
   * {@inheritdoc}
   */
  public function check($account, $key, $subject, $context) {
    return $this->observer->record($this, __FUNCTION__, func_get_args());
  }
}


/**
 * Stub fragment.
 */
class AuthcacheP13nTestEchoFragment implements AuthcacheP13nFragmentInterface {
  /**
   * {@inheritdoc}
   */
  public function render($key, $subject, $context) {
    return serialize(array('key' => $key, 'subject' => $subject));
  }
}


/**
 * Stub class for fragment request validator.
 */
class AuthcacheP13nTestEchoFragmentValidator implements AuthcacheP13nFragmentValidatorInterface {
  /**
   * {@inheritdoc}
   */
  public function validate($keys) {
    $valid = !isset($keys['invalid']);
    if (!$valid) {
      throw new AuthcacheP13nRequestInvalidInput();
    }
    return $keys;
  }
}


/**
 * Stub class for fragment request loader.
 */
class AuthcacheP13nTestEchoFragmentLoader implements AuthcacheP13nFragmentLoaderInterface {
  /**
   * {@inheritdoc}
   */
  public function load($keys, $context) {
    if (isset($keys['load'])) {
      $keys['load'] = 'loaded';
    }
    if (isset($keys['load missing'])) {
      throw new AuthcacheP13nRequestNotFound();
    }
    return $keys;
  }
}


/**
 * Stub class for fragment access checker
 */
class AuthcacheP13nTestEchoFragmentAccess implements AuthcacheP13nFragmentAccessInterface {
  /**
   * {@inheritdoc}
   */
  public function check($account, $key, $subject, $context) {
    return $key !== 'account' || $subject == $account;
  }
}

/**
 * Stub partial.
 */
class AuthcacheP13nTestEchoPartial implements AuthcacheP13nFragmentInterface {
  /**
   * {@inheritdoc}
   */
  public function render($key, $subject, $context) {
    return array('key' => $key, 'subject' => $subject);
  }
}

/**
 * Stub class for setting renderer
 */
class AuthcacheP13nTestEchoSetting implements AuthcacheP13nSettingInterface {
  /**
   * {@inheritdoc}
   */
  public function get($params, $context) {
    return array('params' => $params);
  }
}

/**
 * Stub class for setting request validator.
 */
class AuthcacheP13nTestEchoSettingValidator implements AuthcacheP13nSettingValidatorInterface {
  /**
   * {@inheritdoc}
   */
  public function validate($params) {
    $valid = !isset($params['valid']) || $params['valid'];
    if (!$valid) {
      throw new AuthcacheP13nRequestInvalidInput();
    }
    return array('validated' => TRUE) + $params;
  }
}

/**
 * Stub class for setting access checker
 */
class AuthcacheP13nTestEchoSettingAccess implements AuthcacheP13nSettingAccessInterface {
  /**
   * {@inheritdoc}
   */
  public function check($account, $params, $context) {
    return !isset($params['account']) || $params['account'] == $account;
  }
}

/**
 * Stub router.
 */
class AuthcacheP13nTestRequestRouterStub implements AuthcacheP13nRequestRouterInterface {
  /**
   * {@inheritdoc}
   */
  public function getRoutes() {
    return array(
      'test/good',
      'test/bad',
    );
  }

  /**
   * {@inheritdoc}
   */
  public function getHandler($route_id) {
    switch ($route_id) {
      case 'test/good':
        return new AuthcacheP13nTestRequestHandlerStub();

      case 'test/bad':
        return new AuthcacheP13nTestRequestHandlerBadStub();

      default:
        return FALSE;
    }
  }

  /**
   * {@inheritdoc}
   */
  public function generateURL($route_id, $arg = NULL) {
    if ($route_id === 'test/bad') {
      return FALSE;
    }
    else {
      return array(
        'path' => 'http://example.com/authcache.php',
        'options' => array(
          'query' => array(
            'r' => $route_id,
            'a' => $arg ?: '',
          ),
        ),
      );
    }
  }

  /**
   * {@inheritdoc}
   */
  public function rebuild() {
  }
}

/**
 * Stub request handler.
 */
class AuthcacheP13nTestRequestHandlerStub implements AuthcacheP13nRequestHandlerInterface {
  /**
   * {@inheritdoc}
   */
  public function handle($params) {
    print serialize($params);
  }
}

/**
 * Stub request handler.
 */
class AuthcacheP13nTestRequestHandlerBadStub implements AuthcacheP13nRequestHandlerInterface {
  /**
   * {@inheritdoc}
   */
  public function handle($params) {
    print 'this line is expected to be discarded';
    switch ($params['error']) {
      case 'not_found':
        throw new AuthcacheP13nRequestNotFound();

      case 'invalid_input':
        throw new AuthcacheP13nRequestInvalidInput();

      case 'access_denied':
        throw new AuthcacheP13nRequestAccessDenied();

      case 'server_error':
        throw new AuthcacheP13nRequestException();

      case 'redirect':
        drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
        drupal_goto('');

      default:
        throw new Exception();
    }
  }
}

/**
 * Stub URL generator.
 */
class AuthcacheP13nTestRequestUrlGeneratorStub implements AuthcacheP13nRequestUrlGeneratorInterface {
  /**
   * {@inheritdoc}
   */
  public function url($route_id, $arg = NULL) {
    if ($route_id === 'test/bad') {
      return FALSE;
    }
    else {
      return array(
        'path' => 'http://example.com/authcache.php',
        'options' => array(
          'query' => array(
            'r' => $route_id,
            'a' => $arg ?: '',
          ),
        ),
      );
    }
  }
}
