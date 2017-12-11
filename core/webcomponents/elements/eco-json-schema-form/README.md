eco-json-schema-form
===============

[Polymer 1.0 JSON Schema form builder](http://ecoutu.github.io/eco-json-schema-form)

## Description

This repository provides elements that take in a [JSON schema](http://json-schema.org/) and generates a DOM tree of inputs linked to the object described by the schema.

See the [component page](http://ecoutu.github.io/eco-json-schema-form) for more information.

## TODO:

* Being able to set an initial value (eg, providing an instance of the schema for modification) - currently only supports new instances
* Create an element that provides a single entry point, so there is no need to choose between `<eco-json-schema-object>` and `<eco-json-schema-array>`
* Specifying which fields to show

## Supported

### wizard:

Including eco-json-schema-wizard.html the first level objects will be treated as wizard pages, with a Next and Previous buttons

### type: number

- [x] multipleOf
- [x] maximum
- [x] exclusiveMaximum
- [x] minimum
- [x] exclusiveMinimum

### type: string

- [x] maxLength
- [x] minLength
- [x] pattern

### type: array

- [x] items - object
- [ ] items - array
- [ ] additionalItems - boolean
- [ ] additionalItems - object
- [ ] maxItems
- [ ] minItems
- [ ] uniqueItems

### type: object

- [ ] maxProperties
- [ ] minProperties
- [ ] required
- [ ] additionalProperties - boolean
- [ ] additionalProperties - object
- [x] properties
- [ ] patternProperties
- [ ] dependencies, value is an object
- [ ] dependencies, value is an array

### misc

- [ ] enum - number / integer
- [ ] enum - string
- [ ] enum - array
- [ ] enum - object
- [ ] allOf
- [ ] anyOf
- [ ] oneOf
- [ ] not
- [ ] definitions
- [x] title
- [ ] description
- [ ] default
- [x] format - date-time
- [x] format - email
- [ ] format - hostname
- [ ] format - ipv4
- [ ] format - ipv6
- [x] format - uri
