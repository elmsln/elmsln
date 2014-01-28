core = "7.x"
api = "2"

; Drupal Core
projects[drupal][type] = "core"
projects[drupal][version] = "7.24”
; Patch to allow install profile enabling to enable dependencies correctly.
projects[drupal][patch][1093420] = "http://drupal.org/files/1093420-22.patch"
; Patch to correct block rebuilding performance issue
projects[drupal][patch][1693336] = "http://drupal.org/files/1693336_8.patch”

; specific to MOOC platform
; Patch to allow token insert entity to function correctly
projects[drupal][patch][365241] = "http://drupal.org/files/ac_select_event-365241-54.patch"