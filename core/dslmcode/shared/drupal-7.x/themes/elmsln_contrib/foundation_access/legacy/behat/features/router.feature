Feature: Router
  In order to check the router system
  As authenticated user
  We need to be able navigate between states.

  @javascript
  Scenario: Authenticate user have to see homepage when set url "/"
    Given I login with user "carlos"
    When I visit "/"
    Then I should see "3" markers

  @javascript
  Scenario: Set default chart frequency monthly
    Given I login with user "carlos"
    When I visit "/#/dashboard/1"
    Then I should have "חודש" as chart usage label

  @javascript
  Scenario: Keep chart frequency monthly at category selection
    Given I login with user "carlos"
    When I visit "/#/dashboard/1"
    Then I click "בטחון"
    Then I should have "חודש" as chart usage label
