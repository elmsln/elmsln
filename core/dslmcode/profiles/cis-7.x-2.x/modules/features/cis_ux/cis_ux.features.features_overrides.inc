<?php
/**
 * @file
 * cis_ux.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function cis_ux_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: menu_links
  $overrides["menu_links.menu-elmsln-navigation_bulk-ops:cis/courses/bulk_ops.customized"] = 1;
  $overrides["menu_links.menu-elmsln-navigation_bulk-ops:cis/courses/bulk_ops.has_children"] = 1;
  $overrides["menu_links.menu-elmsln-navigation_bulk-ops:cis/courses/bulk_ops.options|identifier"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-elmsln-navigation_bulk-ops:cis/courses/bulk_ops.weight"] = -47;
  $overrides["menu_links.menu-elmsln-navigation_course-map:cis/courses/map.menu-elmsln-navigation_course-map:cis/courses/map"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-elmsln-navigation_course-map:cis/offerings/course-map.menu-elmsln-navigation_course-map:cis/offerings/course-map"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-elmsln-navigation_field-collection-admin:cis/admin/field-collections.menu-elmsln-navigation_field-collection-admin:cis/admin/field-collections"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-elmsln-navigation_offerings:cis/offerings.menu-elmsln-navigation_offerings:cis/offerings"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-elmsln-navigation_people:cis/admin/people.menu-elmsln-navigation_people:cis/admin/people"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-elmsln-navigation_section-map:cis/offerings/section-map.menu-elmsln-navigation_section-map:cis/offerings/section-map"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-elmsln-navigation_semester-map:cis/offerings/semester-map.menu-elmsln-navigation_semester-map:cis/offerings/semester-map"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-elmsln-navigation_service-instances:cis/services/instances.menu-elmsln-navigation_service-instances:cis/services/instances"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-elmsln-navigation_service-map:cis/services/map.menu-elmsln-navigation_service-map:cis/services/map"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-elmsln-navigation_services:cis/services.menu-elmsln-navigation_services:cis/services"]["DELETED"] = TRUE;

 return $overrides;
}
