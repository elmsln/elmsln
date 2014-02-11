<?php

/**
 * @file
 * Dummy template file for Display Suite views fields.
 */

$url = url('admin/structure/ds/vd', array('absolute' => TRUE));
$link_url = l($url, $url, array('alias' => TRUE));
print t('The layout selection and positioning of fields happens at !url.', array('!url' => $link_url));