<?php
/**
 * @file
 * Load all interfaces and exception classes.
 */

// Interfaces.
require_once __DIR__ . '/../includes/AuthcacheP13nContentBuilderInterface.inc';
require_once __DIR__ . '/../includes/AuthcacheP13nContentEncoderInterface.inc';
require_once __DIR__ . '/../includes/AuthcacheP13nContextProviderInterface.inc';
require_once __DIR__ . '/../includes/AuthcacheP13nCoreServiceInterface.inc';
require_once __DIR__ . '/../includes/AuthcacheP13nFilterInterface.inc';
require_once __DIR__ . '/../includes/AuthcacheP13nFragmentAccessInterface.inc';
require_once __DIR__ . '/../includes/AuthcacheP13nFragmentInterface.inc';
require_once __DIR__ . '/../includes/AuthcacheP13nFragmentLoaderInterface.inc';
require_once __DIR__ . '/../includes/AuthcacheP13nFragmentValidatorInterface.inc';
require_once __DIR__ . '/../includes/AuthcacheP13nRequestHandlerInterface.inc';
require_once __DIR__ . '/../includes/AuthcacheP13nRequestRouterInterface.inc';
require_once __DIR__ . '/../includes/AuthcacheP13nRequestUrlGeneratorInterface.inc';
require_once __DIR__ . '/../includes/AuthcacheP13nRequestValidatorInterface.inc';
require_once __DIR__ . '/../includes/AuthcacheP13nSettingAccessInterface.inc';
require_once __DIR__ . '/../includes/AuthcacheP13nSettingInterface.inc';
require_once __DIR__ . '/../includes/AuthcacheP13nSettingValidatorInterface.inc';

// Exception classes.
require_once __DIR__ . '/../includes/AuthcacheP13nRequestException.inc';
require_once __DIR__ . '/../includes/AuthcacheP13nRequestAccessDenied.inc';
require_once __DIR__ . '/../includes/AuthcacheP13nRequestInvalidInput.inc';
require_once __DIR__ . '/../includes/AuthcacheP13nRequestNotFound.inc';
