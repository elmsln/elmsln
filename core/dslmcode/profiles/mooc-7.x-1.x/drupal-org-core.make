core = "7.x"
api = "2"

; Drupal Core
projects[drupal][type] = core
projects[drupal][version] = 7.28
; Patch to allow install profile enabling to enable dependencies correctly.
projects[drupal][patch][1093420] = http://drupal.org/files/1093420-22.patch

; specific to MOOC platform
; Patch to allow token insert entity to function correctly
projects[drupal][patch][365241] = "http://drupal.org/files/ac_select_event-365241-54.patch"
