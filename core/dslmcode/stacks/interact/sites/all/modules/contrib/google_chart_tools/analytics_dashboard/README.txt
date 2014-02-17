Analystic Dashboard - Drupal module.
Creates a default site usage data charts page, with time frame filtering.

The page path is /admin/reports/analytics-dashboard
Or by menu Reports -> analytics.

The admin page to select which chart will be visible can be found
in the path /admin/config/analytics-dashboard.
Or by menu Configuration -> Analytics dashboard configuration.

You can add your custom charts to the analytics page by imlements hook_analytics_dashboard().
Please see analytics_dashboard.api.php.
Check analytics_dashboard.charts.inc as example using the hook_analytics_dashboard().
Note you can add weight attribute to the chart array.

Then You'll have your custom charts checkboxs in the admin page, 
and by check them, your charts will by display in the Analytics Dashboard page.

You can also use the 'Google Chart Tools' module's hook_draw_chart_alter()
(see google_chart_tools.api.php). To alter any existing chart.


