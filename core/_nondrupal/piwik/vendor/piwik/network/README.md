# Piwik/Network

Component providing Network tools.

[![Build Status](https://travis-ci.org/piwik/component-network.svg?branch=master)](https://travis-ci.org/piwik/component-network)
[![Coverage Status](https://coveralls.io/repos/piwik/component-network/badge.png?branch=master)](https://coveralls.io/r/piwik/component-network?branch=master)
[![Scrutinizer Code Quality](https://scrutinizer-ci.com/g/piwik/component-network/badges/quality-score.png?b=master)](https://scrutinizer-ci.com/g/piwik/component-network/?branch=master)

## Installation

With Composer:

```json
{
    "require": {
        "piwik/network": "*"
    }
}
```

## Usage

### IP

To manipulate an IP address, you can use the `Piwik\Network\IP` class:

```php
$ip = IP::fromStringIP('127.0.0.1');
// IPv6
$ip = IP::fromStringIP('::1');
// In binary format:
$ip = IP::fromBinaryIP("\x7F\x00\x00\x01");

echo $ip->toString(); // 127.0.0.1
echo $ip->toBinary();

// IPv4 & IPv6
if ($ip instanceof IPv4) {}
if ($ip instanceof IPv6) {}

// Hostname reverse lookup
echo $ip->getHostname();

if ($ip->isInRange('192.168.1.1/32')) {}
if ($ip->isInRange('192.168.*.*')) {}

// Anonymize an IP by setting X bytes to null bytes
$ip->anonymize(2);
```

The `Piwik\Network\IPUtils` class provides utility methods:

```php
echo IPUtils::binaryToStringIP("\x7F\x00\x00\x01");
echo IPUtils::stringToBinaryIP('127.0.0.1');

// Sanitization methods
$sanitizedIp = IPUtils::sanitizeIp($_GET['ip']);
$sanitizedIpRange = IPUtils::sanitizeIpRange($_GET['ipRange']);

// IP range
$bounds = IPUtils::getIPRangeBounds('192.168.1.*');
echo $bounds[0]; // 192.168.1.0
echo $bounds[1]; // 192.168.1.255
```

## License

The Network component is released under the [LGPL v3.0](http://choosealicense.com/licenses/lgpl-3.0/).
