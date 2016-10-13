Feature: Category
  In order to check markers filter by category
  As authenticated user
  We need to be able select a category and filter the markers.

  @javascript
  Scenario: Show category selected active
    Given I login with user "carlos"
    When I visit "/#/dashboard/1/category/5"
    Then I should see the category active

  @javascript
  Scenario: Show highlight the active category
    Given I login with user "carlos"
    When I visit "/#/dashboard/1/marker/6?categoryId=14"
    Then I should see the category active

  @javascript
  Scenario: Hide filter meters by categories
    Given I login with user "carlos"
    When I click "בטחון"
    Then I should not see the filters

  @javascript
  Scenario: Show filter meters by categories
    Given I login with user "carlos"
    When I visit "/#/dashboard/1"
    Then the "מבנה חינוך" checkbox should be checked

