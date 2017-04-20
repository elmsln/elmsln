<?php

/**
 * @file
 * Contains SearchApiPorterStemmer and SearchApiPorter2.
 */

/**
 * Stems words to their roots.
 */
class SearchApiPorterStemmer extends SearchApiAbstractProcessor {

  /**
   * Static cache for already generated stems.
   *
   * @var array
   */
  protected $stems = array();

  /**
   * {@inheritdoc}
   */
  public function configurationForm() {
    $form = parent::configurationForm();

    $args = array(
      '!algorithm' => url('https://github.com/markfullmer/porter2'),
      '!exclusions' => url('https://github.com/markfullmer/porter2#user-content-custom-exclusions'),
    );
    $form += array(
      'help' => array(
        '#markup' => '<p>' . t('Optionally, provide an exclusion list to override the stemmer algorithm. Read about the <a href="@algorithm">algorithm</a> and <a href="@exclusions">exclusions</a>.', $args) . '</p>',
      ),
      'exceptions' => array(
        '#type' => 'textarea',
        '#title' => t('Exceptions'),
        '#description' => t('Enter exceptions in the form of WORD=STEM, where "WORD" is the term entered and "STEM" is the resulting stem. List each exception on a separate line.'),
        '#default_value' => "texan=texa",
      ),
    );

    if (!empty($this->options['exceptions'])) {
      $form['exceptions']['#default_value'] = $this->options['exceptions'];
    }
    return $form;
  }

  /**
   * {@inheritdoc}
   */
  protected function process(&$value) {
    // Load custom exceptions.
    $exceptions = $this->getExceptions();

    $words = preg_split('/[^\p{L}\p{N}]+/u', $value, -1 , PREG_SPLIT_DELIM_CAPTURE);
    $stemmed = array();
    foreach ($words as $i => $word) {
      if ($i % 2 == 0 && strlen($word)) {
        if (!isset($this->stems[$word])) {
          $stem = new SearchApiPorter2($word, $exceptions);
          $this->stems[$word] = $stem->stem();
        }
        $stemmed[] = $this->stems[$word];
      }
      else {
        $stemmed[] = $word;
      }
    }
    $value = implode('', $stemmed);
  }

  /**
   * Retrieves the processor's configured exceptions.
   *
   * @return string[]
   *   An associative array of exceptions, with words as keys and stems as their
   *   replacements.
   */
  protected function getExceptions() {
    if (!empty($this->options['exceptions'])) {
      $exceptions = parse_ini_string($this->options['exceptions'], TRUE);
      return is_array($exceptions) ? $exceptions : array();
    }
    return array();
  }

}

/**
 * Implements the Porter2 stemming algorithm.
 *
 * @see https://github.com/markfullmer/porter2
 */
class SearchApiPorter2 {

  /**
   * The word being stemmed.
   *
   * @var string
   */
  protected $word;

  /**
   * The R1 of the word.
   *
   * @var int
   *
   * @see http://snowball.tartarus.org/texts/r1r2.html.
   */
  protected $r1;

  /**
   * The R2 of the word.
   *
   * @var int
   *
   * @see http://snowball.tartarus.org/texts/r1r2.html.
   */
  protected $r2;

  /**
   * List of exceptions to be used.
   *
   * @var string[]
   */
  protected $exceptions = array();

  /**
   * Constructs a SearchApiPorter2 object.
   *
   * @param string $word
   *   The word to stem.
   * @param string[] $custom_exceptions
   *   (optional) A custom list of exceptions.
   */
  public function __construct($word, $custom_exceptions = array()) {
    $this->word = $word;
    $this->exceptions = $custom_exceptions + array(
      'skis' => 'ski',
      'skies' => 'sky',
      'dying' => 'die',
      'lying' => 'lie',
      'tying' => 'tie',
      'idly' => 'idl',
      'gently' => 'gentl',
      'ugly' => 'ugli',
      'early' => 'earli',
      'only' => 'onli',
      'singly' => 'singl',
      'sky' => 'sky',
      'news' => 'news',
      'howe' => 'howe',
      'atlas' => 'atlas',
      'cosmos' => 'cosmos',
      'bias' => 'bias',
      'andes' => 'andes',
    );

    // Set initial y, or y after a vowel, to Y.
    $inc = 0;
    while ($inc <= $this->length()) {
      if (substr($this->word, $inc, 1) === 'y' && ($inc == 0 || $this->isVowel($inc - 1))) {
        $this->word = substr_replace($this->word, 'Y', $inc, 1);

      }
      $inc++;
    }
    // Establish the regions R1 and R2. See function R().
    $this->r1 = $this->R(1);
    $this->r2 = $this->R(2);
  }

  /**
   * Computes the stem of the word.
   *
   * @return string
   *   The word's stem.
   */
  public function stem() {
    // Ignore exceptions & words that are two letters or less.
    if ($this->exceptions() || $this->length() <= 2) {
      return strtolower($this->word);
    }
    else {
      $this->step0();
      $this->step1a();
      $this->step1b();
      $this->step1c();
      $this->step2();
      $this->step3();
      $this->step4();
      $this->step5();
    }
    return strtolower($this->word);
  }

  /**
   * Determines whether the word is contained in our list of exceptions.
   *
   * If so, the $word property is changed to the stem listed in the exceptions.
   *
   * @return bool
   *   TRUE if the word was an exception, FALSE otherwise.
   */
  protected function exceptions() {
    if (isset($this->exceptions[$this->word])) {
      $this->word = $this->exceptions[$this->word];
      return TRUE;
    }
    return FALSE;
  }

  /**
   * Searches for the longest among the "s" suffixes and removes it.
   *
   * Implements step 0 of the Porter2 algorithm.
   */
  protected function step0() {
    $found = FALSE;
    $checks = array("'s'", "'s", "'");
    foreach ($checks as $check) {
      if (!$found && $this->hasEnding($check)) {
        $this->removeEnding($check);
        $found = TRUE;
      }
    }
  }

  /**
   * Handles various suffixes, of which the longest is replaced.
   *
   * Implements step 1a of the Porter2 algorithm.
   */
  protected function step1a() {
    $found = FALSE;
    if ($this->hasEnding('sses')) {
      $this->removeEnding('sses');
      $this->addEnding('ss');
      $found = TRUE;
    }
    $checks = array('ied', 'ies');
    foreach ($checks as $check) {
      if (!$found && $this->hasEnding($check)) {
        $length = $this->length();
        $this->removeEnding($check);
        if ($length > 4) {
          $this->addEnding('i');
        }
        else {
          $this->addEnding('ie');
        }
        $found = TRUE;
      }
    }
    if ($this->hasEnding('us') || $this->hasEnding('ss')) {
      $found = TRUE;
    }
    // Delete if preceding word part has a vowel not immediately before the s.
    if (!$found && $this->hasEnding('s') && $this->containsVowel(substr($this->word, 0, -2))) {
      $this->removeEnding('s');
    }
  }

  /**
   * Handles various suffixes, of which the longest is replaced.
   *
   * Implements step 1b of the Porter2 algorithm.
   */
  protected function step1b() {
    $exceptions = array(
      'inning',
      'outing',
      'canning',
      'herring',
      'earring',
      'proceed',
      'exceed',
      'succeed',
    );
    if (in_array($this->word, $exceptions)) {
      return;
    }
    $checks = array('eedly', 'eed');
    foreach ($checks as $check) {
      if ($this->hasEnding($check)) {
        if ($this->r1 !== $this->length()) {
          $this->removeEnding($check);
          $this->addEnding('ee');
        }
        return;
      }
    }
    $checks = array('ingly', 'edly', 'ing', 'ed');
    $second_endings = array('at', 'bl', 'iz');
    foreach ($checks as $check) {
      // If the ending is present and the previous part contains a vowel.
      if ($this->hasEnding($check) && $this->containsVowel(substr($this->word, 0, -strlen($check)))) {
        $this->removeEnding($check);
        foreach ($second_endings as $ending) {
          if ($this->hasEnding($ending)) {
            $this->addEnding('e');
            return;
          }
        }
        // If the word ends with a double, remove the last letter.
        $found = $this->removeDoubles();
        // If the word is short, add e (so hop -> hope).
        if (!$found && ($this->isShort())) {
          $this->addEnding('e');
        }
        return;
      }
    }
  }

  /**
   * Replaces suffix y or Y with i if after non-vowel not @ word begin.
   *
   * Implements step 1c of the Porter2 algorithm.
   */
  protected function step1c() {
    if (($this->hasEnding('y') || $this->hasEnding('Y')) && $this->length() > 2 && !($this->isVowel($this->length() - 2))) {
      $this->removeEnding('y');
      $this->addEnding('i');
    }
  }

  /**
   * Implements step 2 of the Porter2 algorithm.
   */
  protected function step2() {
    $checks = array(
      "ization" => "ize",
      "iveness" => "ive",
      "fulness" => "ful",
      "ational" => "ate",
      "ousness" => "ous",
      "biliti" => "ble",
      "tional" => "tion",
      "lessli" => "less",
      "fulli" => "ful",
      "entli" => "ent",
      "ation" => "ate",
      "aliti" => "al",
      "iviti" => "ive",
      "ousli" => "ous",
      "alism" => "al",
      "abli" => "able",
      "anci" => "ance",
      "alli" => "al",
      "izer" => "ize",
      "enci" => "ence",
      "ator" => "ate",
      "bli" => "ble",
      "ogi" => "og",
    );
    foreach ($checks as $find => $replace) {
      if ($this->hasEnding($find)) {
        if ($this->inR1($find)) {
          $this->removeEnding($find);
          $this->addEnding($replace);
        }
        return;
      }
    }
    if ($this->hasEnding('li')) {
      if ($this->length() > 4 && $this->validLi($this->charAt(-3))) {
        $this->removeEnding('li');
      }
    }
  }

  /**
   * Implements step 3 of the Porter2 algorithm.
   */
  protected function step3() {
    $checks = array(
      'ational' => 'ate',
      'tional' => 'tion',
      'alize' => 'al',
      'icate' => 'ic',
      'iciti' => 'ic',
      'ical' => 'ic',
      'ness' => '',
      'ful' => '',
    );
    foreach ($checks as $find => $replace) {
      if ($this->hasEnding($find)) {
        if ($this->inR1($find)) {
          $this->removeEnding($find);
          $this->addEnding($replace);
        }
        return;
      }
    }
    if ($this->hasEnding('ative')) {
      if ($this->inR2('ative')) {
        $this->removeEnding('ative');
      }
    }
  }

  /**
   * Implements step 4 of the Porter2 algorithm.
   */
  protected function step4() {
    $checks = array(
      'ement',
      'ment',
      'ance',
      'ence',
      'able',
      'ible',
      'ant',
      'ent',
      'ion',
      'ism',
      'ate',
      'iti',
      'ous',
      'ive',
      'ize',
      'al',
      'er',
      'ic',
    );
    foreach ($checks as $check) {
      // Among the suffixes, if found and in R2, delete.
      if ($this->hasEnding($check)) {
        if ($this->inR2($check)) {
          if ($check !== 'ion' || in_array($this->charAt(-4), array('s', 't'))) {
            $this->removeEnding($check);
          }
        }
        return;
      }
    }
  }

  /**
   * Implements step 5 of the Porter2 algorithm.
   */
  protected function step5() {
    if ($this->hasEnding('e')) {
      // Delete if in R2, or in R1 and not preceded by a short syllable.
      if ($this->inR2('e') || ($this->inR1('e') && !$this->isShortSyllable($this->length() - 3))) {
        $this->removeEnding('e');
      }
      return;
    }
    if ($this->hasEnding('l')) {
      // Delete if in R2 and preceded by l.
      if ($this->inR2('l') && $this->charAt(-2) == 'l') {
        $this->removeEnding('l');
      }
    }
  }

  /**
   * Removes certain double consonants from the word's end.
   *
   * @return bool
   *   TRUE if a match was found and removed, FALSE otherwise.
   */
  protected function removeDoubles() {
    $found = FALSE;
    $doubles = array('bb', 'dd', 'ff', 'gg', 'mm', 'nn', 'pp', 'rr', 'tt');
    foreach ($doubles as $double) {
      if (substr($this->word, -2) == $double) {
        $this->word = substr($this->word, 0, -1);
        $found = TRUE;
        break;
      }
    }
    return $found;
  }

  /**
   * Checks whether a character is a vowel.
   *
   * @param int $position
   *   The character's position.
   * @param string|null $word
   *   (optional) The word in which to check. Defaults to $this->word.
   * @param string[] $additional
   *   (optional) Additional characters that should count as vowels.
   *
   * @return bool
   *   TRUE if the character is a vowel, FALSE otherwise.
   */
  protected function isVowel($position, $word = NULL, $additional = array()) {
    if ($word === NULL) {
      $word = $this->word;
    }
    $vowels = array_merge(array('a', 'e', 'i', 'o', 'u', 'y'), $additional);
    return in_array($this->charAt($position, $word), $vowels);
  }

  /**
   * Retrieves the character at the given position.
   *
   * @param int $position
   *   The 0-based index of the character. If a negative number is given, the
   *   position is counted from the end of the string.
   * @param string|null $word
   *   (optional) The word from which to retrieve the character. Defaults to
   *   $this->word.
   *
   * @return string
   *   The character at the given position, or an empty string if the given
   *   position was illegal.
   */
  protected function charAt($position, $word = NULL) {
    if ($word === NULL) {
      $word = $this->word;
    }
    $length = strlen($word);
    if (abs($position) >= $length) {
      return '';
    }
    if ($position < 0) {
      $position += $length;
    }
    return $word[$position];
  }

  /**
   * Determines whether the word ends in a "vowel-consonant" suffix.
   *
   * Unless the word is only two characters long, it also checks that the
   * third-last character is neither "w", "x" nor "Y".
   *
   * @param int|null $position
   *   (optional) If given, do not check the end of the word, but the character
   *   at the given position, and the next one.
   *
   * @return bool
   *   TRUE if the word has the described suffix, FALSE otherwise.
   */
  protected function isShortSyllable($position = NULL) {
    if ($position === NULL) {
      $position = $this->length() - 2;
    }
    // A vowel at the beginning of the word followed by a non-vowel.
    if ($position === 0) {
      return $this->isVowel(0) && !$this->isVowel(1);
    }
    // Vowel followed by non-vowel other than w, x, Y and preceded by
    // non-vowel.
    $additional = array('w', 'x', 'Y');
    return !$this->isVowel($position - 1) && $this->isVowel($position) && !$this->isVowel($position + 1, NULL, $additional);
  }

  /**
   * Determines whether the word is short.
   *
   * A word is called short if it ends in a short syllable and if R1 is null.
   *
   * @return bool
   *   TRUE if the word is short, FALSE otherwise.
   */
  protected function isShort() {
    return $this->isShortSyllable() && $this->r1 == $this->length();
  }

  /**
   * Determines the start of a certain "R" region.
   *
   * R is a region after the first non-vowel following a vowel, or end of word.
   *
   * @param int $type
   *   (optional) 1 or 2. If 2, then calculate the R after the R1.
   *
   * @return int
   *   The R position.
   */
  protected function R($type = 1) {
    $inc = 1;
    if ($type === 2) {
      $inc = $this->r1;
    }
    elseif ($this->length() > 5) {
      $prefix_5 = substr($this->word, 0, 5);
      if ($prefix_5 === 'gener' || $prefix_5 === 'arsen') {
        return 5;
      }
      if ($this->length() > 6 && substr($this->word, 0, 6) === 'commun') {
        return 6;
      }
    }

    while ($inc <= $this->length()) {
      if (!$this->isVowel($inc) && $this->isVowel($inc - 1)) {
        $position = $inc;
        break;
      }
      $inc++;
    }
    if (!isset($position)) {
      $position = $this->length();
    }
    else {
      // We add one, as this is the position AFTER the first non-vowel.
      $position++;
    }
    return $position;
  }

  /**
   * Checks whether the given string is contained in R1.
   *
   * @param string $string
   *   The string.
   *
   * @return bool
   *   TRUE if the string is in R1, FALSE otherwise.
   */
  protected function inR1($string) {
    $r1 = substr($this->word, $this->r1);
    return strpos($r1, $string) !== FALSE;
  }

  /**
   * Checks whether the given string is contained in R2.
   *
   * @param string $string
   *   The string.
   *
   * @return bool
   *   TRUE if the string is in R2, FALSE otherwise.
   */
  protected function inR2($string) {
    $r2 = substr($this->word, $this->r2);
    return strpos($r2, $string) !== FALSE;
  }

  /**
   * Determines the string length of the current word.
   *
   * @return int
   *   The string length of the current word.
   */
  protected function length() {
    return strlen($this->word);
  }

  /**
   * Checks whether the word ends with the given string.
   *
   * @param string $string
   *   The string.
   *
   * @return bool
   *   TRUE if the word ends with the given string, FALSE otherwise.
   */
  protected function hasEnding($string) {
    $length = strlen($string);
    if ($length > $this->length()) {
      return FALSE;
    }
    return (substr_compare($this->word, $string, -1 * $length, $length) === 0);
  }

  /**
   * Appends a given string to the current word.
   *
   * @param string $string
   *   The ending to append.
   */
  protected function addEnding($string) {
    $this->word = $this->word . $string;
  }

  /**
   * Removes a given string from the end of the current word.
   *
   * Does not check whether the ending is actually there.
   *
   * @param string $string
   *   The ending to remove.
   */
  protected function removeEnding($string) {
    $this->word = substr($this->word, 0, -strlen($string));
  }

  /**
   * Checks whether the given string contains a vowel.
   *
   * @param string $string
   *   The string to check.
   *
   * @return bool
   *   TRUE if the string contains a vowel, FALSE otherwise.
   */
  protected function containsVowel($string) {
    $inc = 0;
    $return = FALSE;
    while ($inc < strlen($string)) {
      if ($this->isVowel($inc, $string)) {
        $return = TRUE;
        break;
      }
      $inc++;
    }
    return $return;
  }

  /**
   * Checks whether the given string is a valid -li prefix.
   *
   * @param string $string
   *   The string to check.
   *
   * @return bool
   *   TRUE if the given string is a valid -li prefix, FALSE otherwise.
   */
  protected function validLi($string) {
    return in_array($string, array(
      'c',
      'd',
      'e',
      'g',
      'h',
      'k',
      'm',
      'n',
      'r',
      't',
    ));
  }

}
