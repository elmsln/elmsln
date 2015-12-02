Feature: Homepage
  To have people accessing a working site
  As any user
  I should see the homepage

  Scenario: Homepage works
    When I go to the homepage
    Then I should get a "200" HTTP response
