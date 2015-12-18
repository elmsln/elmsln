## User Roles
There are a standard set of roles in ELMSLN that are automatically created in every system. These can be built upon though it is recommended to make sure that these new roles
- don't change names after creation (unique IDs are built automatically off of these names as a hash)
- Are loaded up in CIS via `hook_cis_service_instance_options_alter` so that all other systems produced have consistent roles (unless this role is a one-off)

The standard roles are (in order of escalation, generally speaking):
- anonymous user
- authenticated user
- guest
- past student
- student
- teaching assistant
- instructor
- staff
- SERVICE ACCOUNT
- administrator


### Scope of role
Role scope is per authority / service instance. For example, I might have the administrator role in the `media.elmsln` address, be an instructor in courses.elmsln/sing100 but a staff member in studio.elmsln/sing100. This is because all 3 of these systems are different drupal sites, allowing for maximal role delegation.

This also ensures that permissions are containerized. In this way, the `access content` or `create page content` permissions could be different from one site to the next. This could be useful if you wanted to modify what `instructor` role can do in Sing100 while keeping it at the baseline in Progress 101.

It is recommended that you capture any permission changes you make via `features` or some other configuration management mechanism when you change the connotation of what someone can do. For example, if students can create group content in a Art 100 because you added a wiki content type and they need edit rights on it, then make sure to capture this new innovation in order to share it with others, but also so you don't lose configuration during upgrades.
