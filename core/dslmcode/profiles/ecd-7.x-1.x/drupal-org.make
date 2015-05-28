; ecd make file for d.o. usage
core = "7.x"
api = "2"

; ----------
; Ulmus Sub-distro
; ----------
projects[ulmus][type] = "module"
projects[ulmus][destination] = "modules/contrib"
projects[ulmus][subdir] = "contrib"
projects[ulmus][download][type] = "git"
projects[ulmus][download][branch] = "7.x-1.x"

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

