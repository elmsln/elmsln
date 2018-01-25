<?php


namespace Drupal\xautoload\Phases;

use Drupal\xautoload\DrupalSystem\DrupalSystemInterface;
use Drupal\xautoload\CacheMissObserver\CacheMissObserverInterface;

/**
 * Records events during a Drupal request, and forwards them to the registered
 * observers after the first class loader cache miss.
 */
class DrupalPhaseControl implements CacheMissObserverInterface {

  /**
   * @var DrupalSystemInterface
   */
  private $system;

  /**
   * @var PhaseObserverInterface[]
   */
  private $observers;

  /**
   * @var bool
   *   TRUE, if the class finder is no longer the cached one..
   */
  private $awake = FALSE;

  /**
   * @var string[]|null
   *   Extension type by extension name.
   */
  private $extensions;

  /**
   * @var bool
   *   TRUE, if in main phase.
   */
  private $mainPhase = FALSE;

  /**
   * @var bool
   *   TRUE, if in of after boot phase.
   */
  private $bootPhase;

  /**
   * @param DrupalSystemInterface $system
   * @param PhaseObserverInterface[] $observers
   */
  public function __construct(DrupalSystemInterface $system, array $observers) {
    $this->system = $system;
    $this->observers = $observers;
  }

  /**
   * {@inheritdoc}
   */
  public function cacheMiss($finder) {
    $this->extensions = $this->system->getActiveExtensions();
    foreach ($this->observers as $observer) {
      $observer->wakeUp($finder, $this->extensions);
    }
    $this->awake = TRUE;
    if ($this->bootPhase) {
      // We slipped into boot phase while asleep. Need to catch up.
      foreach ($this->observers as $observer) {
        $observer->enterBootPhase();
      }
    }
    if ($this->mainPhase) {
      // We slipped into main phase while asleep. Need to catch up.
      foreach ($this->observers as $observer) {
        $observer->enterMainPhase();
      }
    }
  }

  public function enterBootPhase() {
    if ($this->bootPhase) {
      // We are already in the main phase. Nothing changes.
      return;
    }
    $this->bootPhase = TRUE;
    if (!$this->awake) {
      // The entire thing is not initialized yet.
      // Postpone until operateOnFinder()
      return;
    }
    foreach ($this->observers as $observer) {
      $observer->enterBootPhase();
    }
  }

  /**
   * Initiate the main phase.
   *
   * Called from
   * @see xautoload_custom_theme()
   * @see xautolaod_init()
   */
  public function enterMainPhase() {
    // Main phase implies boot phase.
    $this->enterBootPhase();
    if ($this->mainPhase) {
      // We are already in the main phase. Nothing changes.
      return;
    }
    $this->mainPhase = TRUE;
    if (!$this->awake) {
      // The entire thing is not initialized yet.
      // Postpone until operateOnFinder()
      return;
    }
    foreach ($this->observers as $observer) {
      $observer->enterMainPhase();
    }
  }

  /**
   * Checks if new extensions have been enabled, and registers them.
   *
   * This is called from xautoload_module_implements_alter(), which is called
   * whenever a new module is enabled, but also some calls we need to ignore.
   */
  public function checkNewExtensions() {
    if (!$this->awake) {
      // The entire thing is not initialized yet.
      // Postpone until operateOnFinder()
      return;
    }
    $activeExtensions = $this->system->getActiveExtensions();
    if ($activeExtensions === $this->extensions) {
      // Nothing actually changed. False alarm.
      return;
    }
    // Now check all extensions to find out if any of them is new.
    foreach ($activeExtensions as $name => $type) {
      if (!isset($this->extensions[$name])) {
        // This extension was freshly enabled.
        if ('xautoload' === $name) {
          // If xautoload is enabled in this request, then boot phase and main
          // phase are not properly initialized yet.
          $this->enterMainPhase();
        }
        // Notify observers about the new extension.
        foreach ($this->observers as $observer) {
          $observer->welcomeNewExtension($name, $type);
        }
      }
    }
  }

  /**
   * Called from @see xautoload_modules_enabled()
   *
   * @param $modules
   */
  public function modulesEnabled($modules) {
    if (!$this->awake) {
      // No need to postpone.
      // initMainPhase() will have these modules included.
      return;
    }
    foreach ($this->observers as $observer) {
      $observer->modulesEnabled($modules);
    }
  }
} 
