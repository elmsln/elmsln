Feature: Drupal.org search
	In order to find modules on D.O.
	As a Drupal User
	I need to use D.O search

	Scenario: Searching for "behat"
		Given I go to "http://drupal.org"
		When I fill in "Search …" with "behat"
		And I press "Search"
		Then I should see "Behat Drupal Extension"