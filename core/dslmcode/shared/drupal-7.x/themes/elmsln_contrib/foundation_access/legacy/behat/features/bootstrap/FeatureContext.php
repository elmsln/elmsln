<?php

use Drupal\DrupalExtension\Context\DrupalContext;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;
use Behat\Behat\Tester\Exception\PendingException;

class FeatureContext extends DrupalContext implements SnippetAcceptingContext {

  /**
   * @When /^I login with user "([^"]*)"$/
   */
  public function iLoginWithUser($name) {
    // @todo: Move password to YAML.
    $password = '1234';
    $this->loginUser($name, $password);
  }

  /**
   * Login a user to the site.
   *
   * @param $name
   *   The user name.
   * @param $password
   *   The use password.
   * @param bool $check_success
   *   Determines if we should check for the login to be successful.
   *
   * @throws \Exception
   */
  protected function loginUser($name, $password, $check_success = TRUE) {
    $this->getSession()->visit($this->locatePath('/#/logout'));
    // Reload to force refresh button of the browser. (ui-router reload the state.)
    $this->getSession()->reload();
    $this->iWaitForCssElement('#login-form', 'appear');
    $element = $this->getSession()->getPage();
    $element->fillField('username', $name);
    $element->fillField('password', $password);
    $submit = $element->findButton('Log in');

    if (empty($submit)) {
      throw new \Exception(sprintf("No submit button at %s", $this->getSession()->getCurrentUrl()));
    }

    // Log in.
    $submit->click();

    if ($check_success) {
      // Wait for the dashboard's menu to load, with the user accout information.
      $this->iWaitForCssElement('.menu-account', 'appear');
    }
  }

  /**
   * @When /^I login with bad credentials$/
   */
  public function iLoginWithBadCredentials() {
    return $this->loginUser('wrong-foo', 'wrong-bar', FALSE);
  }

  /**
   * @Then /^I should wait for the text "([^"]*)" to "([^"]*)"$/
   */
  public function iShouldWaitForTheTextTo($text, $appear) {
    $this->waitForXpathNode(".//*[contains(normalize-space(string(text())), \"$text\")]", $appear == 'appear');
  }

  /**
   * @Then /^I wait for css element "([^"]*)" to "([^"]*)"$/
   */
  public function iWaitForCssElement($element, $appear) {
    $xpath = $this->getSession()->getSelectorsHandler()->selectorToXpath('css', $element);
    $this->waitForXpathNode($xpath, $appear == 'appear');
  }

  /**
   * @Then I should see the login page
   */
  public function iShouldSeeTheLoginPage() {
    $this->iWaitForCssElement('#login-form', 'appear');
  }

  /**
   * @Then I should see the category active
   */
  public function iShouldSeeTheCategoryActive() {
    $this->iWaitForCssElement('.active-category', 'appear');
  }

  /**
   * @Then I should see :markers markers
   */
  public function iShouldSeeMarkers($markers, $equals = TRUE) {
    $this->waitFor(function($context) use ($markers, $equals) {
      try {
        $nodes = $context->getSession()->evaluateScript('angular.element(".leaflet-marker-icon").length');
        if ($nodes == (int)$markers) {
          return $equals;
        }
        return !$equals;
      }
      catch (WebDriver\Exception $e) {
        if ($e->getCode() == WebDriver\Exception::NO_SUCH_ELEMENT) {
          return !$equals;
        }
        throw $e;
      }
    });
  }

  /**
   * @Then I should see a marker selected
   */
  public function iShouldSeeAMarkerSelected($appear = TRUE) {
    $selected_src_image = '../images/marker-red.png';
    // check if exist and is selected.
    $this->waitFor(function($context) use ($selected_src_image, $appear) {
      try {
        // Get an array of string <img src="...">, filled with the value of the src attribute of the marker icon image.
        $marker_attr_src = $context->getSession()->evaluateScript('angular.element(".leaflet-marker-icon").map(function(index, element){ return angular.element(element).attr("src") });');
        if (in_array($selected_src_image, $marker_attr_src)) {
          return $appear;
        }
        return !$appear;
      }
      catch (WebDriver\Exception $e) {
        if ($e->getCode() == WebDriver\Exception::NO_SUCH_ELEMENT) {
          return !$appear;
        }
        throw $e;
      }
    });
  }

  /**
   * @Then I should have :frequency as chart usage label
   */
  public function iShouldHaveAsChartUsageLabel($frequency) {
    $csspath = '#chart-usage > div:nth-child(1) > div > svg > g:nth-child(5) > g:nth-child(1) > text';
    $this->waitForTextNgElement($csspath, $frequency);
  }

  /**
   * @Then I should not see the filters
   */
  public function iShouldNotSeeTheFilters() {
    $csspath = "input.hide-meters-category";
    $this->iWaitForCssElement($csspath, FALSE);
  }

  /**
   * @AfterStep
   *
   * Take a screen shot after failed steps for Selenium drivers (e.g.
   * PhantomJs).
   */
  public function takeScreenshotAfterFailedStep($event) {
    if ($event->getTestResult()->isPassed()) {
      // Not a failed step.
      return;
    }

    if ($this->getSession()->getDriver() instanceof \Behat\Mink\Driver\Selenium2Driver) {
      $file_name = sys_get_temp_dir() . DIRECTORY_SEPARATOR . 'behat-failed-step.png';
      $screenshot = $this->getSession()->getDriver()->getScreenshot();
      file_put_contents($file_name, $screenshot);
      print "Screenshot for failed step created in $file_name";
    }
  }

  /**
   * @BeforeScenario
   *
   * Delete the RESTful tokens before every scenario, so user starts as
   * anonymous.
   */
  public function deleteRestfulTokens($event) {
    if (!module_exists('restful_token_auth')) {
      // Module is disabled.
      return;
    }
    if (!$entities = entity_load('restful_token_auth')) {
      // No tokens found.
      return;
    }
    // Delete from database.
    foreach ($entities as $entity) {
      $entity->delete();
    }
  }

  /**
   * @BeforeScenario
   *
   * Resize the view port.
   */
  public function resizeWindow() {
    if ($this->getSession()->getDriver() instanceof \Behat\Mink\Driver\Selenium2Driver) {
      $this->getSession()->resizeWindow(1440, 900, 'current');
    }
  }

  /**
   * Helper function; Execute a function until it return TRUE or timeouts.
   *
   * @param $fn
   *   A callable to invoke.
   * @param int $timeout
   *   The timeout period. Defaults to 30 seconds.
   *
   * @throws Exception
   */
  private function waitFor($fn, $timeout = 30000) {
    $start = microtime(true);
    $end = $start + $timeout / 1000.0;
    while (microtime(true) < $end) {
      if ($fn($this)) {
        return;
      }
    }
    throw new \Exception('waitFor timed out.');
  }

  /**
   * Wait for an element by its XPath to appear or disappear.
   *
   * @param string $xpath
   *   The XPath string.
   * @param bool $appear
   *   Determine if element should appear. Defaults to TRUE.
   *
   * @throws Exception
   */
  private function waitForXpathNode($xpath, $appear = TRUE) {
    $this->waitFor(function($context) use ($xpath, $appear) {
      try {
        $nodes = $context->getSession()->getDriver()->find($xpath);
        if (count($nodes) > 0) {
          $visible = $nodes[0]->isVisible();
          return $appear ? $visible : !$visible;
        }
        return !$appear;
      }
      catch (WebDriver\Exception $e) {
        if ($e->getCode() == WebDriver\Exception::NO_SUCH_ELEMENT) {
          return !$appear;
        }
        throw $e;
      }
    });
  }

  /**
   * Wait for appear or disappear text of an element, the search is done with CSSPath.
   *
   * @param string $csspath
   *   The CSSPath string.
   * @param bool $appear
   *   Determine if element should appear. Defaults to TRUE.
   *
   * @throws Exception
   */
  private function waitForTextNgElement($csspath, $text, $appear = TRUE) {
    $this->waitFor(function($context) use ($csspath, $text, $appear) {
      try {
        $element_text = $context->getSession()->evaluateScript('angular.element("' + $csspath + '").text();');
        if ($element_text == $text) {
          return $appear;
        }
        return !$appear;
      }
      catch (WebDriver\Exception $e) {
        if ($e->getCode() == WebDriver\Exception::NO_SUCH_ELEMENT) {
          return !$appear;
        }
        throw $e;
      }
    });
  }


}
