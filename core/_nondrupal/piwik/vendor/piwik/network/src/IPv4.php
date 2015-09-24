<?php
/**
 * Piwik - free/libre analytics platform
 *
 * @link http://piwik.org
 * @license http://www.gnu.org/licenses/gpl-3.0.html GPL v3 or later
 */

namespace Piwik\Network;

/**
 * IP v4 address.
 *
 * This class is immutable, i.e. once created it can't be changed. Methods that modify it
 * will always return a new instance.
 */
class IPv4 extends IP
{
    /**
     * {@inheritdoc}
     */
    public function toIPv4String()
    {
        return $this->toString();
    }

    /**
     * {@inheritdoc}
     */
    public function anonymize($byteCount)
    {
        $newBinaryIp = $this->ip;

        $i = strlen($newBinaryIp);
        if ($byteCount > $i) {
            $byteCount = $i;
        }

        while ($byteCount-- > 0) {
            $newBinaryIp[--$i] = chr(0);
        }

        return self::fromBinaryIP($newBinaryIp);
    }
}
