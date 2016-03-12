<?php

/**
 * @file
 * Features Builder definitions.
 */

/**
 * Implements hook_features_builders_info().
 */
function features_builder_default_features_builders_info() {
  $builders = array(
    'features_builder_context' => array(
      'label' => t('Context'),
      'class' => 'ContextFeaturesBuilder',
    ),
    'features_builder_eck' => array(
      'label' => t('ECK'),
      'class' => 'EckFeaturesBuilder',
    ),
    'features_builder_entityqueue' => array(
      'label' => t('Entityqueue'),
      'class' => 'EntityqueueFeaturesBuilder',
    ),
    'features_builder_feeds' => array(
      'label' => t('Feeds'),
      'class' => 'FeedsFeaturesBuilder',
    ),
    'features_builder_field' => array(
      'label' => t('Fields'),
      'class' => 'FieldFeaturesBuilder',
    ),
    'features_builder_fieldable_panels_panes' => array(
      'label' => t('Fieldable Panels Panes'),
      'class' => 'FieldablePanelsPanesFeaturesBuilder',
    ),
    'features_builder_field_collection' => array(
      'label' => t('Field Collection'),
      'class' => 'FieldCollectionFeaturesBuilder',
    ),
    'features_builder_flag' => array(
      'label' => t('Flags'),
      'class' => 'FlagFeaturesBuilder',
    ),
    'features_builder_media' => array(
      'label' => t('Media'),
      'class' => 'MediaFeaturesBuilder',
    ),
    'features_builder_menu' => array(
      'label' => t('Menu'),
      'class' => 'MenuFeaturesBuilder',
    ),
    'features_builder_message' => array(
      'label' => t('Message'),
      'class' => 'MessageFeaturesBuilder',
    ),
    'features_builder_node' => array(
      'label' => t('Nodes'),
      'class' => 'NodeFeaturesBuilder',
    ),
    'features_builder_og' => array(
      'label' => t('Organic Groups'),
      'class' => 'OgFeaturesBuilder',
    ),
    'features_builder_panels' => array(
      'label' => t('Panels'),
      'class' => 'PanelsFeaturesBuilder',
    ),
    'features_builder_paragraphs' => array(
      'label' => t('Paragraphs'),
      'class' => 'ParagraphsFeaturesBuilder',
    ),
    'features_builder_profile2' => array(
      'label' => t('Profile2'),
      'class' => 'Profile2FeaturesBuilder',
    ),
    'features_builder_search_api' => array(
      'label' => t('Search'),
      'class' => 'SearchApiBuilder',
    ),
    'features_builder_seo' => array(
      'label' => t('SEO'),
      'class' => 'SeoFeaturesBuilder',
    ),
    'features_builder_site' => array(
      'label' => t('Site'),
      'class' => 'SiteFeaturesBuilder',
    ),
    'features_builder_taxonomy' => array(
      'label' => t('Taxonomy'),
      'class' => 'TaxonomyFeaturesBuilder',
    ),
    'features_builder_user' => array(
      'label' => t('Users'),
      'class' => 'UserFeaturesBuilder',
    ),
    'features_builder_views' => array(
      'label' => t('Views'),
      'class' => 'ViewsFeaturesBuilder',
    ),
  );
  return $builders;
}
