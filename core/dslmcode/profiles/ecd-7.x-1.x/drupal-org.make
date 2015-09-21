; ecd make file for d.o. usage
core = "7.x"
api = "2"

; ----------
; Ulmus Sub-distro
; ----------
projects[ulmus_core][version] = "1.x-dev"
projects[ulmus_core][subdir] = "contrib"

; ----------
; ECD Dependencies
; ----------
; Date/Time
projects[date][version] = "2.8"
projects[date][subdir] = "contrib"
; Entityforms
projects[entityform][version] = "2.0-rc1"
projects[entityform][subdir] = "contrib"
; Fields
projects[field_hidden][version] = "1.7"
projects[field_hidden][subdir] = "contrib"
projects[select_or_other][version] = "2.22"
projects[select_or_other][subdir] = "contrib"
; Other
projects[imagefield_focus][version] = "1.x-dev"
projects[imagefield_focus][subdir] = "contrib"
; Views
projects[editableviews][version] = "1.x-dev"
projects[editableviews][subdir] = "contrib"
projects[eva][version] = "1.x-dev"
projects[eva][subdir] = "contrib"

