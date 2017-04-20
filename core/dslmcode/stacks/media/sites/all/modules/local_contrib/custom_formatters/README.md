# Custom Formatters
-------------------

The Custom Formatters module allows users to easily create custom Field
Formatters without the need to write a custom module. Custom Formatters can then
be exported as CTools Exportables, Features or Drupal API Field Formatters.



## Features
-----------

* Pluggable editor/renderer engines:
    * **Formatter presets** _(default)_  
      Create simple formatters from existing formatters with preset formatter
      settings.
    
    * **HTML + Tokens** _(default)_  
      A HTML based editor with Token support.
    
    * **PHP** _(default)_  
      A PHP based editor with support for multiple fields and multiple values.
    
    * **[Twig](https://drupal.org/project/twig_filter)**  
      A Twig based editor provided by the Twig filter module.
    
* Supports for all fieldable entities, including but not limited to:
    * Drupal core - Comment, Node, Taxonomy term and User entities.
    * Field collection module - Field-collection item entity.
    * Media module - Media entity.
    
* Exportable as:
    * Drupal API formatter via:
        * Custom Formatters export interface.
    * CTools exportable via:
        * Custom Formatters export interface.
        * CTools Bulk Export module.
        * Features module.
        
* Live preview using real entities or Devel Generate.

* Integrates with:
    * **Coder Review**  
      Review your Custom Formatter code for Drupal coding standards and more.
      
    * **Contextual links** _(Drupal core)_  
      Adds a hover link for quick editing of Custom Formatters.
      
    * **Display Suite**  
      Format Display Suite fields.
      
    * **Entity tokens**  
      Leverages entity tokens for Field token support.
      
    * **Features**  
      Adds dependent Custom Formatters (from Views or Content types) to Feature.
      
    * **Form Builder**  
      Drag'n'Drop interface for builder Formatter Settings forms.
      
    * **Insert**  
      Exposes Custom Formatters to the Insert module.
      
    * **Libraries API and the EditArea javascript library**  
      Adds real-time syntax highlighting.
      
    * **Token**  
      Adds the Token tree browser to the HTML + Tokens engine.



## Required Modules
-------------------

* [Chaos tool suite](http://drupal.org/project/ctools)



## Recommended Modules
----------------------

* Coder Review (via [Coder](http://drupal.org/project/coder)) 
* Devel Generate (via [Devel](http://drupal.org/project/devel))
* Entity tokens (via [Entity API](http://drupal.org/project/entity))
* [Field tokens](http://drupal.org/project/field_tokens)
* [Form Builder](http://drupal.org/project/form_builder)
* [Libraries API](http://drupal.org/project/libraries)
* [Token](http://drupal.org/project/token)



## Usage/Configuration
----------------------

Read the manual at: [drupal.org/node/2514412](https://www.drupal.org/node/2514412)



## EditArea - Real-time syntax highlighting
-------------------------------------------

The EditArea javascript library adds real-time syntax highlighting, to install
it follow these steps:

1. Download and install the [Libraries API](http://drupal.org/project/libraries)
   module.

2. Download the [EditArea](http://sourceforge.net/projects/editarea/files/EditArea/EditArea%200.8.2/editarea_0_8_2.zip/downloa)
   library and extract and move it into your libraries folder as 'editarea'
   (e.g., sites/all/libraries/editarea).



## Makefile entries
-------------------

For easy downloading of Custom Formatters and it's required/recommended modules
and/or libraries, you can use the following entries in your makefile:


      projects[] = coder

      projects[] = ctools

      projects[] = custom_formatters

      projects[] = devel

      projects[] = entity

      projects[] = field_tokens

      projects[] = form_builder

      projects[] = libraries

      projects[] = options_element

      projects[] = token

      libraries[editarea][download][type] = get
      libraries[editarea][download][url] = http://downloads.sourceforge.net/project/editarea/EditArea/EditArea%200.8.2/editarea_0_8_2.zip?r=&ts=1334742944&use_mirror=internode


**Note:** It is highly recommended to specify the version of your projects, the
above format is only for the sake of simplicity.
