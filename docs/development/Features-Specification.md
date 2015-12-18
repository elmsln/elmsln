## Features Specification
This is a Drupal specific connotation of how one should name and structure information when building out applications within elmsln. There are a four general layers to all distributions utilized in ELMSLN's many tools.
They are:
- Drupal core
- Drupal.org / ELMSLN Contributed modules
- Stack specific modules
- Distribution specific modules

### Drupal Core
We run a modified version of Drupal core for performance. This is not to be modified unless you are an ELMSLN core developer / submitting a patch.

### Drupal.org / ELMSLN Contrib
These modules come from Drupal.org, with several having been produced by ELMSLN core developers and released into general contrib as well. It is recommended to add projects here when incorporating generalizable contributed modules into ELMSLN's core package.

### Stack specific modules
These are contributed modules that are too specific to be included across all systems. Things like an Epub Exporter would only really make sense in the context of the MOOC/courses system for example.

### Distribution specific modules
These are modules, features and themes produced specifically for use with one application. These have no use (generally speaking) outside the context of that assembled product.

## Creating new functionality
When creating a distribution for ELMSLN it should attempt to maximize flexibility by capturing configuration in such a way that it can be easily updated / reverted to original state after the fact. Generally you should name things like this for an example new system called Idea Engine (ie).

profile path: `profiles/ie-7.x-1.x/`
- Content Types that are core to the system: `modules/features/ie_types`
- Views: `modules/features/ie_displays`
- Contexts / blocks: `modules/features/ie_ux`
- Contexts / blocks in regions specific to foundation access / ELMSLN: `modules/features/ie_cis_ux`
- Permissions: `modules/features/ie_perms`
- Custom code needed to make it run: `modules/ie_custom/ie_helper`
- Custom theme (sub-theme of Foundation Access): `themes/ie_foundation_access`
- Additional functionality (should include all views,contexts, types, etc): `modules/ie_extras/ie_tight_scope`

### Note on Permissions
Generally we treat permissions as a starting point and try to put them in their own feature using the defaultconfig module to capture them. This allows someone to import them as a starting point but then this won't get reverted down the road when we apply upgrades.

If the permissions are critical to the application working correctly (Like students NOT being allowed to submit a section node for example) then section's permissions should be bundled with it as Features based configuration (which can be reverted). If it's a student wiki type (something more floaty / flexible) then defaultconfig is recommended.