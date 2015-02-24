Feature: Router
  In order to check the router system
  As anonymous user
  We need to be able to ask the login.

  @javascript
  Scenario: Anonymous user have to see login page when set url "/"
    Given I am an anonymous user
    When I visit "/"
    Then I should see the login page
