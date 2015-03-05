<?php
/**
 * @file
 * Include file for fences hook implementations.
 */

/**
 * Implements hook_fences_suggestion_info().
 */
function fences_fences_suggestion_info() {
  // Suggestions for the "field" theme hook.
  $fences['field'] = array(
    'no_wrapper' => array(
      'label'       => t('no markup'),
      'element'     => '',
      'description' => t('No wrapping HTML'),
    ),
    'address' => array(
      'label'       => t('address'),
      'element'     => 'address',
      'description' => t('Contact information for a page or article element'),
      'groups'      => array(t('Sectioning')),
    ),
    'article' => array(
      'label'       => t('article'),
      'element'     => 'article',
      'description' => t('Self-contained syndicatable or reusable composition'),
      'groups'      => array(t('Sectioning')),
    ),
    'aside' => array(
      'label'       => t('aside'),
      'element'     => 'aside',
      'description' => t('Sidebar for tangentially related content'),
      'groups'      => array(t('Sectioning')),
    ),
    'b' => array(
      'label'       => t('bold'),
      'element'     => 'b',
      'description' => t('Keywords'),
      'groups'      => array(t('Phrasing')),
    ),
    'bdi' => array(
      'label'       => t('bidirectional text'),
      'element'     => 'bdi',
      'description' => t('Text directionality isolation'),
      'groups'      => array(t('Phrasing')),
    ),
    'blockquote' => array(
      'label'       => t('block quote'),
      'element'     => 'blockquote',
      'description' => t('A section quoted from another source'),
      'groups'      => array(t('Sectioning')),
    ),
    'cite' => array(
      'label'       => t('cite'),
      'element'     => 'cite',
      'description' => t('A citation or a reference to other sources'),
      'groups'      => array(t('Phrasing')),
    ),
    'code' => array(
      'label'       => t('code'),
      'element'     => 'code',
      'description' => t('Computer code'),
      'groups'      => array(t('Phrasing')),
    ),
    'dl' => array(
      'label'       => t('description list'),
      'element'     => 'dl',
      'description' => t('Association list consisting of name-value groups'),
      'groups'      => array(t('List')),
    ),
    'dt' => array(
      'label'       => t('description list’s term'),
      'element'     => 'dt',
      'description' => t('Legend for corresponding dd element(s)'),
      'groups'      => array(t('List')),
    ),
    'dd' => array(
      'label'       => t('description list’s definition'),
      'element'     => 'dd',
      'description' => t('Content for corresponding dt element(s)'),
      'groups'      => array(t('List')),
    ),
    'del' => array(
      'label'       => t('deletion'),
      'element'     => 'del',
      'description' => t('A removal from the document'),
      'groups'      => array(t('Phrasing')),
    ),
    'details' => array(
      'label'       => t('details'),
      'element'     => 'details',
      'description' => t('Disclosure control for hiding details'),
      'groups'      => array(t('Sectioning')),
    ),
    'div' => array(
      'label'       => t('division'),
      'element'     => 'div',
      'description' => t('Generic container; only use as a last resort'),
      'groups'      => array(t('Block-level')),
    ),
    'em' => array(
      'label'       => t('emphasis'),
      'element'     => 'em',
      'description' => t('Stress emphasis'),
      'groups'      => array(t('Phrasing')),
    ),
    'figcaption' => array(
      'label'       => t('figure caption'),
      'element'     => 'figcaption',
      'description' => t('Caption for figure'),
      'groups'      => array(t('Block-level')),
    ),
    'figure' => array(
      'label'       => t('figure'),
      'element'     => 'figure',
      'description' => t('Figure with optional caption'),
      'groups'      => array(t('Block-level')),
    ),
    'footer' => array(
      'label'       => t('footer'),
      'element'     => 'footer',
      'description' => t('Footer for a page or section'),
      'groups'      => array(t('Sectioning')),
    ),
    'h1' => array(
      'label'       => t('heading rank 1'),
      'element'     => 'h1',
      'description' => t('Section heading'),
      'groups'      => array(t('Sectioning')),
    ),
    'h2' => array(
      'label'       => t('heading rank 2'),
      'element'     => 'h2',
      'description' => t('Section heading'),
      'groups'      => array(t('Sectioning')),
    ),
    'h3' => array(
      'label'       => t('heading rank 3'),
      'element'     => 'h3',
      'description' => t('Section heading'),
      'groups'      => array(t('Sectioning')),
    ),
    'h4' => array(
      'label'       => t('heading rank 4'),
      'element'     => 'h4',
      'description' => t('Section heading'),
      'groups'      => array(t('Sectioning')),
    ),
    'h5' => array(
      'label'       => t('heading rank 5'),
      'element'     => 'h5',
      'description' => t('Section heading'),
      'groups'      => array(t('Sectioning')),
    ),
    'h6' => array(
      'label'       => t('heading rank 6'),
      'element'     => 'h6',
      'description' => t('Section heading'),
      'groups'      => array(t('Sectioning')),
    ),
    'header' => array(
      'label'       => t('header'),
      'element'     => 'header',
      'description' => t('Introductory or navigational aids for a page or section'),
      'groups'      => array(t('Sectioning')),
    ),
    'hgroup' => array(
      'label'       => t('heading group'),
      'element'     => 'hgroup',
      'description' => t('Heading group'),
      'groups'      => array(t('Sectioning')),
    ),
    'i' => array(
      'label'       => t('italic'),
      'element'     => 'i',
      'description' => t('Alternate voice'),
      'groups'      => array(t('Phrasing')),
    ),
    'ins' => array(
      'label'       => t('insertion'),
      'element'     => 'ins',
      'description' => t('An addition to the document'),
      'groups'      => array(t('Phrasing')),
    ),
    'kbd' => array(
      'label'       => t('keyboard'),
      'element'     => 'kbd',
      'description' => t('User input'),
      'groups'      => array(t('Phrasing')),
    ),
    'mark' => array(
      'label'       => t('mark'),
      'element'     => 'mark',
      'description' => t('Highlight'),
      'groups'      => array(t('Phrasing')),
    ),
    'menu' => array(
      'label'       => t('menu'),
      'element'     => 'menu',
      'description' => t('Menu of commands'),
      'groups'      => array(t('List')),
    ),
    'nav' => array(
      'label'       => t('navigation'),
      'element'     => 'nav',
      'description' => t('Section with navigational links'),
      'groups'      => array(t('Sectioning')),
    ),
    'ol' => array(
      'label'       => t('ordered list'),
      'element'     => 'ol',
      'description' => t('Ordered list'),
      'groups'      => array(t('List')),
    ),
    'p' => array(
      'label'       => t('paragraph'),
      'element'     => 'p',
      'description' => t('Paragraph'),
      'groups'      => array(t('Block-level')),
    ),
    'pre' => array(
      'label'       => t('preformatted text'),
      'element'     => 'pre',
      'description' => t('Block of preformatted text'),
      'groups'      => array(t('Block-level')),
    ),
    'pre_code' => array(
      'label'       => t('preformatted code'),
      'element'     => 'pre code',
      'description' => t('Block of preformatted code'),
      'groups'      => array(t('Block-level')),
    ),
    'q' => array(
      'label'       => t('quotation'),
      'element'     => 'q',
      'description' => t('Quotation'),
      'groups'      => array(t('Phrasing')),
    ),
    'ruby' => array(
      'label'       => t('ruby'),
      'element'     => 'ruby',
      'description' => t('Ruby annotation(s)'),
      'groups'      => array(t('Ruby')),
    ),
    'rp_rt' => array(
      'label'       => t('ruby text with parenthesis'),
      'element'     => 'rp rt',
      'description' => t('Ruby annotation text with surrounding parenthesis'),
      'groups'      => array(t('Ruby')),
    ),
    'rt' => array(
      'label'       => t('ruby text'),
      'element'     => 'rt',
      'description' => t('Ruby annotation text'),
      'groups'      => array(t('Ruby')),
    ),
    's' => array(
      'label'       => t('strikethrough'),
      'element'     => 's',
      'description' => t('Inaccurate text'),
      'groups'      => array(t('Phrasing')),
    ),
    'samp' => array(
      'label'       => t('sample output'),
      'element'     => 'samp',
      'description' => t('Computer output'),
      'groups'      => array(t('Phrasing')),
    ),
    'section' => array(
      'label'       => t('section'),
      'element'     => 'section',
      'description' => t('Generic document or application section'),
      'groups'      => array(t('Sectioning')),
    ),
    'small' => array(
      'label'       => t('small'),
      'element'     => 'small',
      'description' => t('Side comment'),
      'groups'      => array(t('Phrasing')),
    ),
    'span' => array(
      'label'       => t('span'),
      'element'     => 'span',
      'description' => t('Generic phrasing container'),
      'groups'      => array(t('Phrasing')),
    ),
    'strong' => array(
      'label'       => t('strong'),
      'element'     => 'strong',
      'description' => t('Importance'),
      'groups'      => array(t('Phrasing')),
    ),
    'sub' => array(
      'label'       => t('subscript'),
      'element'     => 'sub',
      'description' => t('Subscript'),
      'groups'      => array(t('Phrasing')),
    ),
    'summary' => array(
      'label'       => t('summary'),
      'element'     => 'summary',
      'description' => t('Caption for details'),
      'groups'      => array(t('Block-level')),
    ),
    'sup' => array(
      'label'       => t('superscript'),
      'element'     => 'sup',
      'description' => t('Superscript'),
      'groups'      => array(t('Phrasing')),
    ),
    'u' => array(
      'label'       => t('underline'),
      'element'     => 'u',
      'description' => t('Keywords'),
      'groups'      => array(t('Phrasing')),
    ),
    'ul' => array(
      'label'       => t('unordered list'),
      'element'     => 'ul',
      'description' => t('Unordered list'),
      'groups'      => array(t('List')),
    ),
    'var' => array(
      'label'       => t('variable'),
      'element'     => 'var',
      'description' => t('Variable'),
      'groups'      => array(t('Phrasing')),
    ),
  );
  return $fences;
}
