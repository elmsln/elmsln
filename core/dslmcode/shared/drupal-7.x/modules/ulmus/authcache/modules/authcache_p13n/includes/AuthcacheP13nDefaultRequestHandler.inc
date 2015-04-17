<?php

/**
 * @file
 * Defines default request handler class
 */

/**
 * Default request handler class for personalized fragments.
 *
 * This class is responsible for handling a request and returning the result
 * along with appropriate HTTP headers back to the client.
 */
class AuthcacheP13nDefaultRequestHandler implements AuthcacheP13nRequestHandlerInterface {
  /**
   * @var AuthcacheP13nCoreService
   */
  protected $coreService;

  /**
   * @var AuthcacheP13nRequestValidator
   */
  protected $requestValidator;

  /**
   * @var AuthcacheP13nContentBuilder
   */
  protected $contentBuilder;

  /**
   * @var AuthcacheP13nContentEncoder
   */
  protected $contentEncoder;

  /**
   * Associative array of filter chains.
   *
   * Map of event type => array of filter objects. Currently supported event
   * types contain:
   * - request: Decoded parameters, runs before validation.
   * - response: Encoded result, runs just before content is sent to the
   *   browser.
   */
  protected $filters;

  /**
   * Associative array of context providers.
   *
   * Map of target context key => array of context provider objects.
   */
  protected $contextProviders;

  /**
   * Construct a new instance.
   */
  public function __construct(
    AuthcacheP13nCoreServiceInterface $core_service,
    AuthcacheP13nRequestValidatorInterface $request_validator,
    AuthcacheP13nContentBuilderInterface $content_builder,
    AuthcacheP13nContentEncoderInterface $content_encoder,
    array $filters,
    array $context_providers
  ) {
    $this->coreService = $core_service;
    $this->requestValidator = $request_validator;
    $this->contentBuilder = $content_builder;
    $this->contentEncoder = $content_encoder;
    $this->filters = $filters;
    $this->contextProviders = $context_providers;
  }

  /**
   * {@inheritdoc}
   */
  public function handle($params) {
    $params = $this->filter('request', $params);
    $input = $this->validate($params);
    $context = $this->getContext($input);
    $result = $this->build($input, $context);
    $response = $this->encode($result);
    print $this->filter('response', $response);
  }

  /**
   * Perform chain of filters for a given event.
   */
  protected function filter($event, $input) {
    $output = $input;

    if (!empty($this->filters[$event])) {
      foreach ($this->filters[$event] as $filter) {
        $output = $filter->filter($event, $output);
      }
    }

    return $output;
  }

  /**
   * Return validated input parameters.
   *
   * @throws: AuthcacheP13nRequestInvalidInput
   */
  protected function validate($params) {
    return $this->requestValidator ? $this->requestValidator->validate($params) : $params;
  }

  /**
   * Collect context.
   *
   * @return array
   *   An array of key-value pairs gathered from the registered context
   *   providers.
   */
  protected function getContext($params) {
    $context = array();

    if (!empty($this->contextProviders)) {
      foreach ($this->contextProviders as $target => $context_provider) {
        $context[$target] = $context_provider->get($params);
      }
    }

    return $context;
  }

  /**
   * Construct response from the validated input.
   */
  protected function build($input, $context) {
    return $this->contentBuilder->build($input, $context);
  }

  /**
   * Encode the result returned by ::build().
   */
  protected function encode($result) {
    $this->coreService->drupalAddHttpHeader('Content-Type', $this->contentEncoder->contentType());
    return $this->contentEncoder->encode($result);
  }
}
