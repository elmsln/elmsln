<?php

namespace Behat\Gherkin\Keywords;

/*
 * This file is part of the Behat Gherkin.
 * (c) 2011 Konstantin Kudryashov <ever.zet@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

/**
 * Array initializable keywords holder.
 *
 * $keywords = new Behat\Gherkin\Keywords\ArrayKeywords(array(
 *     'en' => array(
 *         'feature'          => 'Feature',
 *         'background'       => 'Background',
 *         'scenario'         => 'Scenario',
 *         'scenario_outline' => 'Scenario Outline|Scenario Template',
 *         'examples'         => 'Examples|Scenarios',
 *         'given'            => 'Given',
 *         'when'             => 'When',
 *         'then'             => 'Then',
 *         'and'              => 'And',
 *         'but'              => 'But'
 *     ),
 *     'ru' => array(
 *         'feature'          => 'Функционал',
 *         'background'       => 'Предыстория',
 *         'scenario'         => 'Сценарий',
 *         'scenario_outline' => 'Структура сценария',
 *         'examples'         => 'Значения',
 *         'given'            => 'Допустим',
 *         'when'             => 'Если',
 *         'then'             => 'То',
 *         'and'              => 'И',
 *         'but'              => 'Но'
 *     )
 * ));
 *
 * @author Konstantin Kudryashov <ever.zet@gmail.com>
 */
class ArrayKeywords implements KeywordsInterface
{
    private $keywords = array();
    private $language;

    /**
     * Initializes holder with keywords.
     *
     * @param array $keywords Keywords array
     */
    public function __construct(array $keywords)
    {
        $this->keywords = $keywords;
    }

    /**
     * Sets keywords holder language.
     *
     * @param string $language Language name
     */
    public function setLanguage($language)
    {
        if (!isset($this->keywords[$language])) {
            $this->language = 'en';
        } else {
            $this->language = $language;
        }
    }

    /**
     * Returns Feature keywords (splitted by "|").
     *
     * @return string
     */
    public function getFeatureKeywords()
    {
        return $this->keywords[$this->language]['feature'];
    }

    /**
     * Returns Background keywords (splitted by "|").
     *
     * @return string
     */
    public function getBackgroundKeywords()
    {
        return $this->keywords[$this->language]['background'];
    }

    /**
     * Returns Scenario keywords (splitted by "|").
     *
     * @return string
     */
    public function getScenarioKeywords()
    {
        return $this->keywords[$this->language]['scenario'];
    }

    /**
     * Returns Scenario Outline keywords (splitted by "|").
     *
     * @return string
     */
    public function getOutlineKeywords()
    {
        return $this->keywords[$this->language]['scenario_outline'];
    }

    /**
     * Returns Examples keywords (splitted by "|").
     *
     * @return string
     */
    public function getExamplesKeywords()
    {
        return $this->keywords[$this->language]['examples'];
    }

    /**
     * Returns Given keywords (splitted by "|").
     *
     * @return string
     */
    public function getGivenKeywords()
    {
        return $this->keywords[$this->language]['given'];
    }

    /**
     * Returns When keywords (splitted by "|").
     *
     * @return string
     */
    public function getWhenKeywords()
    {
        return $this->keywords[$this->language]['when'];
    }

    /**
     * Returns Then keywords (splitted by "|").
     *
     * @return string
     */
    public function getThenKeywords()
    {
        return $this->keywords[$this->language]['then'];
    }

    /**
     * Returns And keywords (splitted by "|").
     *
     * @return string
     */
    public function getAndKeywords()
    {
        return $this->keywords[$this->language]['and'];
    }

    /**
     * Returns But keywords (splitted by "|").
     *
     * @return string
     */
    public function getButKeywords()
    {
        return $this->keywords[$this->language]['but'];
    }

    /**
     * Returns all step keywords (Given, When, Then, And, But).
     *
     * @return string
     */
    public function getStepKeywords()
    {
        return implode('|', array(
            $this->getGivenKeywords(),
            $this->getWhenKeywords(),
            $this->getThenKeywords(),
            $this->getAndKeywords(),
            $this->getButKeywords()
        ));
    }
}
