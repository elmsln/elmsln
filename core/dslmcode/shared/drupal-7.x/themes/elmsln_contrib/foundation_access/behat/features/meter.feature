Feature: Meter
  In order to view the location of the meters
  As authenticated user
  We need to be able view the meters as markers on the map

  @javascript
  Scenario: Show all meters of the account
    Given I login with user "carlos"
    When I visit "/#/dashboard/1"
    Then I should see "3" markers

  @javascript
  Scenario: Show only meters of a selected
    Given I login with user "carlos"
    When I visit "/#/dashboard/1/marker/6"
    Then I should see a marker selected

  @javascript
  Scenario: Show only meters of a selected in a category
    Given I login with user "carlos"
    When I visit "/#/dashboard/1/marker/6?categoryId=14"
    Then I should see a marker selected

  @javascript
  Scenario: Show only meters of the category selected
    Given I login with user "carlos"
    When I visit "/#/dashboard/1/category/14"
    Then I should see "2" markers

  @javascript
  Scenario: Show only meters not filter in the category menu.
    Given I login with user "carlos"
    When I visit "/#/dashboard/1"
    Then I should see "3" markers
    Then I uncheck the box "מבנה חינוך"
    Then the "מבנה חינוך" checkbox should not be checked
    Then I should see "2" markers
    Then I uncheck the box "מקלט"
    Then the "מקלט" checkbox should not be checked
    Then I should see "1" markers
