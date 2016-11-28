Custom Tools
===============

There are several ways using developer hooks to get custom tools to show up in the network flyout / system wide. The easiest way is to add your own custom topology files. A topology file tells elmsln about your custom thing you made or external system you want to provide links to.

create a topology file in `/var/www/elmsln/config/shared/drupal-7.x/tools/{name}/{name}.topology`. Here's an example topology file:
```
default_title="Custom Tool"
type="custom"
subdomain="custom"
group="Network"
icon_library="elmsln"
show_in_network="1"
weight="11"
icon="dino"
color="light-blue"
color_dark="darken-3"
color_light="lighten-3"
color_text="accessible-light-blue-text"
color_outline="light-blue-outline"
color_code="#03a9f4"
custom="1"
address="http://legacylms.edu"
```

You can create any number of topology files and have them lazy loaded into the elmsln keychain registry. This visually shows up in the Network flyout but also allows you to utilize elmsln's ability to simplify call structures to other systems (see `_cis_connector_request()` ).