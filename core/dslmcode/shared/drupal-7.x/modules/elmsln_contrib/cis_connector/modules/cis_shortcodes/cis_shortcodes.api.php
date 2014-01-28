<?php
/**
 * @file
 * Structure and example of shortcodes to generate.
 *
 * This is the basic structure of the Version 1 CIS shortcode.
 * This specification can be added to without much issue
 * hence it is versioned for when newer connotations of data
 * to abstract are required.  Below are some example codes.
 *
 * @param cis
 *   api version currently in use for this shortcode.
 * @param tool
 *   cis tool name
 * @param item
 *   tag or id
 * @param render
 *   (optional) iframe or link, defaults to iframe
 * @param item_type
 *   (optional) tag or id, defaults to id
 * @param section
 *   (optional) section to query, useful with tag, defaults to _user _context
 * @param entity_type
 *   (optional) entity type for the id, defaults to node
 * @param entity_bundle
 *   (optional) bundle for the id, default to NULL
 */

/**
 * Code 1 example
 *
 * API version 1
 * connect to the associated MOOC distribution
 * pull item (type assumed node) number 12
 * render assumed as iframe
 */
$code1 = '[cis=v1 tool=mooc item=12]';

/**
 * Code 2 example
 *
 * API version 1
 * connect to the associated CLE distribution
 * pull the (assumed node) item tagged as "cool Stuff"
 * render as a link to the item
 * Uses current user context to help calculate the node to deliver
 */
$code2 = '[cis=v1 tool=cle item="cool Stuff" item_type=tag render=link]';

/**
 * Other examples
 */
// default render style is iframe
$code3 = '[cis=v1 tool=media item=12]';
// request item, grab output and embed into content
// this is really only useful for images or non-responsive video
$code4 = '[cis=v1 tool=icor item=16 render=embed]';