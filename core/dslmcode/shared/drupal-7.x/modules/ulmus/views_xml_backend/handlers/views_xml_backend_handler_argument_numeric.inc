<?php

class views_xml_backend_handler_argument_numeric extends views_xml_backend_handler_argument {

  function generate() {

    return $this->options['xpath_selector'] . ' = ' . $this->get_value();
  }
}
