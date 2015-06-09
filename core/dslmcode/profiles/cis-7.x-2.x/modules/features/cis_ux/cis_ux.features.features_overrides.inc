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
  $overrides["menu_links.menu-cis-toolkit_bulk-ops:cis/courses/bulk_ops.customized"] = 1;
  $overrides["menu_links.menu-cis-toolkit_bulk-ops:cis/courses/bulk_ops.has_children"] = 1;
  $overrides["menu_links.menu-cis-toolkit_bulk-ops:cis/courses/bulk_ops.options|identifier"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-cis-toolkit_bulk-ops:cis/courses/bulk_ops.weight"] = -47;
  $overrides["menu_links.menu-cis-toolkit_course-map:cis/courses/map.menu-cis-toolkit_course-map:cis/courses/map"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-cis-toolkit_course-map:cis/offerings/course-map.menu-cis-toolkit_course-map:cis/offerings/course-map"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-cis-toolkit_field-collection-admin:cis/admin/field-collections.menu-cis-toolkit_field-collection-admin:cis/admin/field-collections"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-cis-toolkit_offerings:cis/offerings.menu-cis-toolkit_offerings:cis/offerings"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-cis-toolkit_people:cis/admin/people.menu-cis-toolkit_people:cis/admin/people"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-cis-toolkit_resources:cis/resources.menu-cis-toolkit_resources:cis/resources"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-cis-toolkit_section-map:cis/offerings/section-map.menu-cis-toolkit_section-map:cis/offerings/section-map"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-cis-toolkit_semester-map:cis/offerings/semester-map.menu-cis-toolkit_semester-map:cis/offerings/semester-map"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-cis-toolkit_service-instances:cis/services/instances.menu-cis-toolkit_service-instances:cis/services/instances"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-cis-toolkit_service-map:cis/services/map.menu-cis-toolkit_service-map:cis/services/map"]["DELETED"] = TRUE;
  $overrides["menu_links.menu-cis-toolkit_services:cis/services.menu-cis-toolkit_services:cis/services"]["DELETED"] = TRUE;

 return $overrides;
}
