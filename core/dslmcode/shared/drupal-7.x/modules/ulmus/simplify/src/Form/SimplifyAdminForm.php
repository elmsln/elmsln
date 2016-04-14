<?php

/**
 * @file
 * Contains \Drupal\simplify\Form\SimplifyAdminForm.
 */

namespace Drupal\simplify\Form;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Form\ConfigFormBase;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Drupal\Core\Extension\ModuleHandler;
use Drupal\Core\Form\FormStateInterface;

/**
 * Configure simplify global configurations.
 */
class SimplifyAdminForm extends ConfigFormBase {

  /**
   * The module handler service.
   *
   * @var \Drupal\Core\Extension\ModuleHandler
   */
  protected $moduleHandler;

  /**
   * Constructs a SimplifyAdminForm object.
   *
   * @param \Drupal\Core\Config\ConfigFactoryInterface $config_factory
   *   The factory for configuration objects.
   * @param \Drupal\Core\Extension\ModuleHandler $module_handler
   *   The module handler service.
   */
  public function __construct(ConfigFactoryInterface $config_factory, ModuleHandler $module_handler) {
    parent::__construct($config_factory);
    $this->moduleHandler =  $module_handler;
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container) {
    return new static(
      $container->get('config.factory'),
      $container->get('module_handler')
    );
  }

  /**
   * {@inheritdoc}
   */
  protected function getEditableConfigNames() {
    return ['simplify.global'];
  }

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'simplify_admin_form';
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state) {

    // Admin user permission.
    $form['simplify_admin'] = array(
      '#type' => 'checkbox',
      '#title' => $this->t('Hide fields from admin users.'),
      '#description' => $this->t("By default, Drupal gives User 1 and admin users <em>all</em> permissions (including Simplify's <em>View hidden fields</em> permission). This means that those users will always be able to view all hidden fields (and is by design).<br>Check this box to override this functionality and hide fields from any users. NOTE: As this option overrides default Drupal behaviour, it should be used sparingly and only when you fully understand the consequences."),
      '#default_value' => _simplify_get_config_value('simplify_admin', FALSE),
    );

    // Nodes.
    if ($this->moduleHandler->moduleExists('node')) {
      $form['nodes'] = array(
        '#type' => 'details',
        '#title' => $this->t('Nodes'),
        '#description' => $this->t("These fields will be hidden from <em>all</em> node forms. Alternatively, to hide fields from node forms of a particular content type, edit the content type and configure the hidden fields there."),
        '#open' => TRUE,
      );
      $form['nodes']['simplify_nodes_global'] = array(
        '#type' => 'checkboxes',
        '#title' => $this->t('Simplify the following options'),
        '#options' => simplify_get_fields('nodes'),
        '#default_value' => _simplify_get_config_value('simplify_nodes_global'),
      );
    }

    // Users.
    if ($this->moduleHandler->moduleExists('user')) {
      $form['users'] = array(
        '#type' => 'details',
        '#title' => $this->t('Users'),
        '#description' => $this->t("These fields will be hidden from all user account forms."),
        '#open' => TRUE,
      );
      $form['users']['simplify_users_global'] = array(
        '#type' => 'checkboxes',
        '#title' => $this->t('Simplify the following options'),
        '#options' => simplify_get_fields('users'),
        '#default_value' => _simplify_get_config_value('simplify_users_global'),
      );
    }

    // Comments.
    if ($this->moduleHandler->moduleExists('comment')) {
      $form['comments'] = array(
        '#type' => 'details',
        '#title' => $this->t('Comments'),
        '#description' => $this->t("These fields will be hidden from <em>all</em> comment forms. Alternatively, to hide fields from comment forms for comments of a particular comment type, edit the comment type and configure the hidden fields there."),
        '#open' => TRUE,
      );
      $form['comments']['simplify_comments_global'] = array(
        '#type' => 'checkboxes',
        '#title' => $this->t('Simplify the following options'),
        '#options' => simplify_get_fields('comments'),
        '#default_value' => _simplify_get_config_value('simplify_comments_global'),
      );
    }

    // Taxonomy.
    if ($this->moduleHandler->moduleExists('taxonomy')) {
      $form['taxonomy'] = array(
        '#type' => 'details',
        '#title' => $this->t('Taxonomy'),
        '#description' => $this->t("These fields will be hidden from <em>all</em> taxonomy term forms. Alternatively, to hide fields from taxonomy term forms for a particular vocabulary, edit the vocabulary and configure the hidden fields there."),
        '#open' => TRUE,
      );
      $form['taxonomy']['simplify_taxonomies_global'] = array(
        '#type' => 'checkboxes',
        '#title' => $this->t('Simplify the following options'),
        '#options' => simplify_get_fields('taxonomy'),
        '#default_value' => _simplify_get_config_value('simplify_taxonomies_global'),
      );
    }

    // Blocks.
    if ($this->moduleHandler->moduleExists('block')) {
      $form['blocks'] = array(
        '#type' => 'details',
        '#title' => $this->t('Blocks'),
        '#description' => $this->t("These fields will be hidden from <em>all</em> blocks forms. Alternatively, to hide fields from block forms of a particular block type, edit the block type and configure the hidden fields there."),
        '#open' => TRUE,
      );
      $form['blocks']['simplify_blocks_global'] = array(
        '#type' => 'checkboxes',
        '#title' => $this->t('Simplify the following options'),
        '#options' => simplify_get_fields('blocks'),
        '#default_value' => _simplify_get_config_value('simplify_blocks_global'),
      );
    }

    // Profiles.
    if ($this->moduleHandler->moduleExists('profile2_page')) {
      $form['profiles'] = array(
        '#type' => 'details',
        '#title' => $this->t('Profiles'),
        '#description' => $this->t("These fields will be hidden from all profile forms."),
        '#open' => TRUE,
      );
      $form['profiles']['simplify_profiles_global'] = array(
        '#type' => 'checkboxes',
        '#title' => $this->t('Simplify the following options'),
        '#options' => simplify_get_fields('profiles'),
        '#default_value' => _simplify_get_config_value('simplify_profiles_global'),
      );
    }

    // Remove empty values from saved variables.
    // (see: http://drupal.org/node/61760#comment-402631)
    $form['array_filter'] = array(
      '#type' => 'hidden',
    );

    return parent::buildForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function validateForm(array &$form, FormStateInterface $form_state) {
    parent::validateForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
    \Drupal::configFactory()->getEditable('simplify.global')
      ->set('simplify_admin', $form_state->getValue('simplify_admin'))
      ->set('simplify_nodes_global', $this->getFormValue($form_state, 'simplify_nodes_global'))
      ->set('simplify_users_global', $this->getFormValue($form_state, 'simplify_users_global'))
      ->set('simplify_comments_global', $this->getFormValue($form_state, 'simplify_comments_global'))
      ->set('simplify_taxonomies_global', $this->getFormValue($form_state, 'simplify_taxonomies_global'))
      ->set('simplify_blocks_global', $this->getFormValue($form_state, 'simplify_blocks_global'))
      ->set('simplify_profiles_global', $this->getFormValue($form_state, 'simplify_profiles_global'))
      ->save();

    parent::submitForm($form, $form_state);
  }

  /**
   * Gets an array representing the configuration form values or empty array
   * is empty or not applicable.
   *
   * @param string $form_state
   *   The form state array.
   * @param string $config_name
   *   The configuration name to be retrieved.
   *
   * @return array
   *   An array representing the configuration or empty array if the
   *   configuration is not applicable.
   */
  protected function getFormValue(FormStateInterface $form_state, $config_name) {
    $value = $form_state->getValue($config_name);
    return !empty($value) ? $value : array();
  }

}
