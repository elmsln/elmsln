<?php
  // support ELMSLN config loading globally
  include_once '../../core/dslmcode/elmsln_environment/elmsln_environment.php';
  global $elmslncfg;
  // redirect top level back to CIS for the services
  header('Location: ' . $elmslncfg['protocol'] . '://online.' . $elmslncfg['address'] . '/');
  exit;
?>