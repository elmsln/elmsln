Feature: Login
  In order to be able to access content
  As an anonymous user
  We need to be able to login to the site and be authenticated

  @javascript
  Scenario: Login with bad credentials
    Given I am an anonymous user
    When I login with bad credentials
    Then I should wait for the text "Login name or password is incorrect." to "appear"