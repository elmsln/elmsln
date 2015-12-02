Feature: Authentication
  In order to make sure Behaviour testing is working
  As a behat test user
  I want to make sure I can log in
  Scenario: Anonymous access
    Given I am on the homepage
    Then I should see "Login"

  @api
  Scenario: Log in as a regular user
    Given I am logged in as a user with the "authenticated user" role
    Then I should not see "Login"

  @api @javascript
  Scenario: Log in via selenium
    Given I am logged in as a user with the "authenticated user" role
    Then I should not see "Login"
