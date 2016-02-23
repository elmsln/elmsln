<?php

/**
 * @file
 * Adminimal Menu Update file 7100.
 */

// Define Adminimal Menu path.
$module_path = drupal_get_path('module', 'adminimal_admin_menu');

// Delete the "adminimal_admin_menu.js" file.
file_unmanaged_delete($module_path . '/adminimal_admin_menu.js');

// Empty the "slicknav" folder.
file_unmanaged_delete_recursive($module_path . '/slicknav');

// Delete the "slicknav" folder.
drupal_rmdir($module_path . '/slicknav');
