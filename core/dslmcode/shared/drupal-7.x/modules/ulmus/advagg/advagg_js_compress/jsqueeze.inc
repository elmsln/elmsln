<?php
// @codingStandardsIgnoreFile
// @ignore comment_docblock_file:file
// @ignore style_curly_braces:file
// @ignore style_string_spacing:file
// @ignore style_else_spacing:file
// @ignore comment_comment_docblock_missing:file
// @ignore comment_comment_eg:file
// @ignore production_code:file
// @ignore druplart_unary:file
// @ignore style_uppercase_constants:file
// @ignore comment_comment_space:file
// @ignore druplart_conditional_assignment:file
// @ignore style_paren_spacing:file
// @ignore style_no_tabs:file
// @ignore comment_docblock_comment:file
// @ignore comment_comment_indent:file
// @ignore style_comma_spacing:file
// @ignore style_elseif:file
// @ignore :file

/*
 * Copyright (C) 2015 Nicolas Grekas - p@tchwork.com
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the (at your option):
 * Apache License v2.0 (see provided LICENCE.ASL20 file), or
 * GNU General Public License v2.0 (see provided LICENCE.GPLv2 file).
 */

namespace Patchwork;

/*
*
* This class shrinks Javascript code
* (a process called minification nowadays)
*
* Should work with most valid Javascript code,
* even when semi-colons are missing.
*
* Features:
* - Removes comments and white spaces.
* - Renames every local vars, typically to a single character.
* - Renames also global vars, methods and properties, but only if they
*   are marked special by some naming convention. By default, special
*   var names begin with one or more "$", or with a single "_".
* - Renames also local/global vars found in strings,
*   but only if they are marked special.
* - Keep Microsoft's conditional comments.
* - Output is optimized for later HTTP compression.
*
* Notes:
* - Source code must be parse error free before processing.
* - In order to maximise later HTTP compression (deflate, gzip),
*   new variables names are chosen by considering closures,
*   variables' frequency and characters' frequency.
* - If you use with/eval then be careful.
*
* Bonus:
* - Replaces false/true by !1/!0
* - Replaces new Array/Object by []/{}
* - Merges consecutive "var" declarations with commas
* - Merges consecutive concatened strings
* - Fix a bug in Safari's parser (http://forums.asp.net/thread/1585609.aspx)
* - Can replace optional semi-colons by line feeds,
*   thus facilitating output debugging.
* - Keep important comments marked with /*!...
* - Treats three semi-colons ;;; like single-line comments
*   (http://dean.edwards.name/packer/2/usage/#triple-semi-colon).
* - Fix special catch scope across browsers
* - Work around buggy-handling of named function expressions in IE<=8
*
* TODO?
* - foo['bar'] => foo.bar
* - {'foo':'bar'} => {foo:'bar'}
* - Dead code removal (never used function)
* - Munge primitives: var WINDOW=window, etc.
*/

class JSqueeze
{
    const

    SPECIAL_VAR_PACKER = '(\$+[a-zA-Z_]|_[a-zA-Z0-9$])[a-zA-Z0-9_$]*';

    public

    $charFreq;

    protected

    $strings,
    $closures,
    $str0,
    $str1,
    $argFreq,
    $specialVarRx,
    $keepImportantComments,

    $varRx = '(?:[a-zA-Z_$])[a-zA-Z0-9_$]*',
    $reserved = array(
        'abstract','as','boolean','break','byte','case','catch','char','class',
        'const','continue','debugger','default','delete','do','double','else',
        'enum','export','extends','false','final','finally','float','for',
        'function','goto','if','implements','import','in','instanceof','int',
        'long','native','new','null','package','private','protected','public',
        'return','short','static','super','switch','synchronized','this',
        'throw','throws','transient','true','try','typeof','var','void',
        'while','with','yield','let','interface',
    );


    function __construct()
    {
        $this->reserved = array_flip($this->reserved);
        $this->charFreq = array_fill(0, 256, 0);
    }

    /**
     * Squeezes a JavaScript source code.
     *
     * Set $singleLine to false if you want optional
     * semi-colons to be replaced by line feeds.
     *
     * Set $keepImportantComments to false if you want /*! comments to be removed.
     *
     * $specialVarRx defines the regular expression of special variables names
     * for global vars, methods, properties and in string substitution.
     * Set it to false if you don't want any.
     *
     * If the analysed javascript source contains a single line comment like
     * this one, then the directive will overwrite $specialVarRx:
     *
     * // jsqueeze.specialVarRx = your_special_var_regexp_here
     *
     * Only the first directive is parsed, others are ignored. It is not possible
     * to redefine $specialVarRx in the middle of the javascript source.
     *
     * Example:
     * $parser = new JSqueeze;
     * $squeezed_js = $parser->squeeze($fat_js);
     */

    function squeeze($code, $singleLine = true, $keepImportantComments = true, $specialVarRx = false)
    {
        $code = trim($code);
        if ('' === $code) return '';

        $this->argFreq = array(-1 => 0);
        $this->specialVarRx = $specialVarRx;
        $this->keepImportantComments = !!$keepImportantComments;

        if (preg_match("#//[ \t]*jsqueeze\.specialVarRx[ \t]*=[ \t]*([\"']?)(.*)\1#i", $code, $key))
        {
            if (!$key[1])
            {
                $key[2] = trim($key[2]);
                $key[1] = strtolower($key[2]);
                $key[1] = $key[1] && $key[1] != 'false' && $key[1] != 'none' && $key[1] != 'off';
            }

            $this->specialVarRx = $key[1] ? $key[2] : false;
        }

        // Remove capturing parentheses
        $this->specialVarRx && $this->specialVarRx = preg_replace('/(?<!\\\\)((?:\\\\\\\\)*)\((?!\?)/', '(?:', $this->specialVarRx);

        false !== strpos($code, "\r"          ) && $code = strtr(str_replace("\r\n", "\n", $code), "\r", "\n");
        false !== strpos($code, "\xC2\x85"    ) && $code = str_replace("\xC2\x85"    , "\n", $code); // Next Line
        false !== strpos($code, "\xE2\x80\xA8") && $code = str_replace("\xE2\x80\xA8", "\n", $code); // Line Separator
        false !== strpos($code, "\xE2\x80\xA9") && $code = str_replace("\xE2\x80\xA9", "\n", $code); // Paragraph Separator

        list($code, $this->strings ) = $this->extractStrings( $code);
        list($code, $this->closures) = $this->extractClosures($code);

        $key = "//''\"\"#0'"; // This crap has a wonderful property: it can not happen in any valid javascript, even in strings
        $this->closures[$key] =& $code;

        $tree = array($key => array('parent' => false));
        $this->makeVars($code, $tree[$key], $key);
        $this->renameVars($tree[$key], true);

        $code = substr($tree[$key]['code'], 1);
        $code = preg_replace("'\breturn !'", 'return!', $code);
        $code = preg_replace("'\}(?=(else|while)[^\$.a-zA-Z0-9_])'", "}\r", $code);
        $code = str_replace(array_keys($this->strings), array_values($this->strings), $code);

        if ($singleLine) $code = strtr($code, "\n", ';');
        else $code = str_replace("\n", ";\n", $code);
        false !== strpos($code, "\r") && $code = strtr(trim($code), "\r", "\n");

        // Cleanup memory
        $this->charFreq = array_fill(0, 256, 0);
        $this->strings = $this->closures = $this->argFreq = array();
        $this->str0 = $this->str1 = '';

        return $code;
    }


    protected function extractStrings($f)
    {
        if ($cc_on = false !== strpos($f, '@cc_on'))
        {
            // Protect conditional comments from being removed
            $f = str_replace('#', '##', $f);
            $f = str_replace('/*@', '1#@', $f);
            $f = preg_replace("'//@([^\n]+)'", '2#@$1@#3', $f);
            $f = str_replace('@*/', '@#1', $f);
        }

        $len = strlen($f);
        $code = str_repeat(' ', $len);
        $j = 0;

        $strings = array();
        $K = 0;

        $instr = false;

        $q = array(
            "'", '"',
            "'" => 0,
            '"' => 0,
        );

        // Extract strings, removes comments
        for ($i = 0; $i < $len; ++$i)
        {
            if ($instr)
            {
                if ('//' == $instr)
                {
                    if ("\n" == $f[$i])
                    {
                        $f[$i--] = ' ';
                        $instr = false;
                    }
                }
                else if ($f[$i] == $instr || ('/' == $f[$i] && "/'" == $instr))
                {
                    if ('!' == $instr) ;
                    else if ('*' == $instr)
                    {
                        if ('/' == $f[$i+1])
                        {
                            ++$i;
                            $instr = false;
                        }
                    }
                    else
                    {
                        if ("/'" == $instr)
                        {
                            while (isset ($f[$i+1]) && false !== strpos('gmi', $f[$i+1])) $s[] = $f[$i++];
                            $s[] = $f[$i];
                        }

                        $instr = false;
                    }
                }
                else if ('*' == $instr) ;
                else if ('!' == $instr)
                {
                    if ('*' == $f[$i] && '/' == $f[$i+1])
                    {
                        $s[] = "*/\r";
                        ++$i;
                        $instr = false;
                    }
                    else if ("\n" == $f[$i]) $s[] = "\r";
                    else $s[] = $f[$i];
                }
                else if ('\\' == $f[$i])
                {
                    ++$i;

                    if ("\n" != $f[$i])
                    {
                        isset($q[$f[$i]]) && ++$q[$f[$i]];
                        $s[] = '\\' . $f[$i];
                    }
                }
                else if ('[' == $f[$i] && "/'" == $instr)
                {
                    $instr = '/[';
                    $s[] = '[';
                }
                else if (']' == $f[$i] && '/[' == $instr)
                {
                    $instr = "/'";
                    $s[] = ']';
                }
                else if ("'" == $f[$i] || '"' == $f[$i])
                {
                    ++$q[$f[$i]];
                    $s[] = '\\' . $f[$i];
                }
                else $s[] = $f[$i];
            }
            else switch ($f[$i])
            {
            case ';':
                // Remove triple semi-colon
                if ($i>0 && ';' == $f[$i-1] && $i+1 < $len && ';' == $f[$i+1]) $f[$i] = $f[$i+1] = '/';
                else
                {
                    $code[++$j] = ';';
                    break;
                }

            case '/':
                if ('*' == $f[$i+1])
                {
                    ++$i;
                    $instr = '*';

                    if ($this->keepImportantComments && '!' == $f[$i+1])
                    {
                        ++$i;
                        // no break here
                    }
                    else break;
                }
                else if ('/' == $f[$i+1])
                {
                    ++$i;
                    $instr = '//';
                    break;
                }
                else
                {
                    $a = $j && ' ' == $code[$j] ? $code[$j-1] : $code[$j];
                    if (false !== strpos('-!%&;<=>~:^+|,(*?[{ ', $a)
                        || (false !== strpos('oenfd', $a)
                        && preg_match(
                            "'(?<![\$.a-zA-Z0-9_])(do|else|return|typeof|yield) ?$'",
                            substr($code, $j-7, 8)
                        )))
                    {
                        $key = "//''\"\"" . $K++ . $instr = "/'";
                        $a = $j;
                        $code .= $key;
                        while (isset($key[++$j-$a-1])) $code[$j] = $key[$j-$a-1]; --$j;
                        isset($s) && ($s = implode('', $s)) && $cc_on && $this->restoreCc($s);
                        $strings[$key] = array('/');
                        $s =& $strings[$key];
                    }
                    else $code[++$j] = '/';

                    break;
                }

            case "'":
            case '"':
                $instr = $f[$i];
                $key = "//''\"\"" . $K++ . ('!' == $instr ? ']' : "'");
                $a = $j;
                $code .= $key;
                while (isset($key[++$j-$a-1])) $code[$j] = $key[$j-$a-1]; --$j;
                isset($s) && ($s = implode('', $s)) && $cc_on && $this->restoreCc($s);
                $strings[$key] = array();
                $s =& $strings[$key];
                '!' == $instr && $s[] = "\r/*!";

                break;

            case "\n":
                if ($j > 5)
                {
                    ' ' == $code[$j] && --$j;

                    $code[++$j] =
                        false !== strpos('kend', $code[$j-1])
                            && preg_match(
                                "'(?<![\$.a-zA-Z0-9_])(break|continue|return|yield) ?$'",
                                substr($code, $j-8, 9)
                            )
                        ? ';' : ' ';

                    break;
                }

            case "\t": $f[$i] = ' ';
            case ' ':
                if (!$j || ' ' == $code[$j]) break;

            default:
                $code[++$j] = $f[$i];
            }
        }

        isset($s) && ($s = implode('', $s)) && $cc_on && $this->restoreCc($s);
        unset($s);

        $code = substr($code, 0, $j+1);
        $cc_on && $this->restoreCc($code, false);

        // Protect wanted spaces and remove unwanted ones
        $code = str_replace('- -', "-\x7F-", $code);
        $code = str_replace('+ +', "+\x7F+", $code);
        $code = preg_replace("'(\d)\s+\.\s*([a-zA-Z\$_[(])'", "$1\x7F.$2", $code);
        $code = preg_replace("# ([-!%&;<=>~:.^+|,()*?[\]{}/']+)#", '$1', $code);
        $code = preg_replace( "#([-!%&;<=>~:.^+|,()*?[\]{}/]+) #", '$1', $code);

        // Replace new Array/Object by []/{}
        false !== strpos($code, 'new Array' ) && $code = preg_replace( "'new Array(?:\(\)|([;\])},:]))'", '[]$1', $code);
        false !== strpos($code, 'new Object') && $code = preg_replace("'new Object(?:\(\)|([;\])},:]))'", '{}$1', $code);

        // Add missing semi-colons after curly braces
        // This adds more semi-colons than strictly needed,
        // but it seems that later gzipping is favorable to the repetition of "};"
        $code = preg_replace("'\}(?![:,;.()\[\]}\|&]|(else|catch|finally|while)[^\$.a-zA-Z0-9_])'", '};', $code);

        // Tag possible empty instruction for easy detection
        $code = preg_replace("'(?<![\$.a-zA-Z0-9_])if\('"   , '1#(', $code);
        $code = preg_replace("'(?<![\$.a-zA-Z0-9_])for\('"  , '2#(', $code);
        $code = preg_replace("'(?<![\$.a-zA-Z0-9_])while\('", '3#(', $code);

        $forPool = array();
        $instrPool = array();
        $s = 0;

        $f = array();
        $j = -1;

        // Remove as much semi-colon as possible
        $len = strlen($code);
        for ($i = 0; $i < $len; ++$i)
        {
            switch ($code[$i])
            {
            case '(':
                if ($j>=0 && "\n" == $f[$j]) $f[$j] = ';';

                ++$s;

                if ($i && '#' == $code[$i-1])
                {
                    $instrPool[$s - 1] = 1;
                    if ('2' == $code[$i-2]) $forPool[$s] = 1;
                }

                $f[++$j] = '(';
                break;

            case ']':
            case ')':
                if ($i+1 < $len && !isset($forPool[$s]) && !isset($instrPool[$s-1]) && preg_match("'[a-zA-Z0-9_\$]'", $code[$i+1]))
                {
                    $f[$j] .= $code[$i];
                    $f[++$j] = "\n";
                }
                else $f[++$j] = $code[$i];

                if (')' == $code[$i])
                {
                    unset($forPool[$s]);
                    --$s;
                }

                continue 2;

            case '}':
                if ("\n" == $f[$j]) $f[$j] = '}';
                else $f[++$j] = '}';
                break;

            case ';':
                if (isset($forPool[$s]) || isset($instrPool[$s])) $f[++$j] = ';';
                else if ($j>=0 && "\n" != $f[$j] && ';' != $f[$j]) $f[++$j] = "\n";

                break;

            case '#':
                switch ($f[$j])
                {
                case '1': $f[$j] = 'if';    break 2;
                case '2': $f[$j] = 'for';   break 2;
                case '3': $f[$j] = 'while'; break 2;
                }

            case '[';
                if ($j>=0 && "\n" == $f[$j]) $f[$j] = ';';

            default: $f[++$j] = $code[$i];
            }

            unset($instrPool[$s]);
        }

        $f = implode('', $f);
        $cc_on && $f = str_replace('@#3', "\n", $f);

        // Fix "else ;" empty instructions
        $f = preg_replace("'(?<![\$.a-zA-Z0-9_])else\n'", "\n", $f);

        $r1 = array( // keywords with a direct object
            'case','delete','do','else','function','in','instanceof','break',
            'new','return','throw','typeof','var','void','yield','let','if',
            'const',
        );

        $r2 = array( // keywords with a subject
            'in','instanceof',
        );

        // Fix missing semi-colons
        $f = preg_replace("'(?<!(?<![a-zA-Z0-9_\$])" . implode(')(?<!(?<![a-zA-Z0-9_\$])', $r1) . ") (?!(" . implode('|', $r2) . ")(?![a-zA-Z0-9_\$]))'", "\n", $f);
        $f = preg_replace("'(?<!(?<![a-zA-Z0-9_\$])do)(?<!(?<![a-zA-Z0-9_\$])else) if\('", "\nif(", $f);
        $f = preg_replace("'(?<=--|\+\+)(?<![a-zA-Z0-9_\$])(" . implode('|', $r1) . ")(?![a-zA-Z0-9_\$])'", "\n$1", $f);
        $f = preg_replace("'(?<![a-zA-Z0-9_\$])for\neach\('", 'for each(', $f);
        $f = preg_replace("'(?<![a-zA-Z0-9_\$])\n(" . implode('|', $r2) . ")(?![a-zA-Z0-9_\$])'", '$1', $f);

        // Merge strings
        if ($q["'"] > $q['"']) $q = array($q[1], $q[0]);
        $f = preg_replace("#//''\"\"[0-9]+'#", $q[0] . '$0' . $q[0], $f);
        strpos($f, $q[0] . '+' . $q[0]) && $f = str_replace($q[0] . '+' . $q[0], '', $f);
        $len = count($strings);
        foreach ($strings as $r1 => &$r2)
        {
            $r2 = "/'" == substr($r1, -2)
                ? str_replace(array("\\'", '\\"'), array("'", '"'), $r2)
                : str_replace('\\' . $q[1], $q[1], $r2);
        }

        // Restore wanted spaces
        $f = strtr($f, "\x7F", ' ');

        return array($f, $strings);
    }

    protected function extractClosures($code)
    {
        $code = ';' . $code;

        $this->argFreq[-1] += substr_count($code, '}catch(');

        if ($this->argFreq[-1])
        {
            // Special catch scope handling

            // FIXME: this implementation doesn't work with nested catch scopes who need
            // access to their parent's caught variable (but who needs that?).

            $f = preg_split("@}catch\(({$this->varRx})@", $code, -1, PREG_SPLIT_DELIM_CAPTURE);

            $code = 'catch$scope$var' . mt_rand();
            $this->specialVarRx = $this->specialVarRx ? '(?:' . $this->specialVarRx . '|' . preg_quote($code) . ')' : preg_quote($code);
            $i = count($f) - 1;

            while ($i)
            {
                $c = 1;
                $j = 0;
                $l = strlen($f[$i]);

                while ($c && $j < $l)
                {
                    $s = $f[$i][$j++];
                    $c += '(' == $s ? 1 : (')' == $s ? -1 : 0);
                }

                if (!$c) do
                {
                    $s = $f[$i][$j++];
                    $c += '{' == $s ? 1 : ('}' == $s ? -1 : 0);
                }
                while ($c && $j < $l);

                $c = preg_quote($f[$i-1], '#');
                $f[$i-2] .= '}catch(' . preg_replace("#([.,{]?)(?<![a-zA-Z0-9_\$@]){$c}\\b#", '$1' . $code, $f[$i-1] . substr($f[$i], 0, $j)) . substr($f[$i], $j);

                unset($f[$i--], $f[$i--]);
            }

            $code = $f[0];
        }

        $f = preg_split("'(?<![a-zA-Z0-9_\$])(function[ (].*?\{)'", $code, -1, PREG_SPLIT_DELIM_CAPTURE);
        $i = count($f) - 1;
        $closures = array();

        while ($i)
        {
            $c = 1;
            $j = 0;
            $l = strlen($f[$i]);

            while ($c && $j < $l)
            {
                $s = $f[$i][$j++];
                $c += '{' == $s ? 1 : ('}' == $s ? -1 : 0);
            }

            switch (substr($f[$i-2], -1))
            {
            default: if (false !== $c = strpos($f[$i-1], ' ', 8)) break;
            case false: case "\n": case ';': case '{': case '}': case ')': case ']':
                $c = strpos($f[$i-1], '(', 8);
            }

            $l = "//''\"\"#$i'";
            $code = substr($f[$i-1], $c);
            $closures[$l] = $code . substr($f[$i], 0, $j);
            $f[$i-2] .= substr($f[$i-1], 0, $c) . $l . substr($f[$i], $j);

            if ('(){' !== $code)
            {
                $j = substr_count($code, ',');
                do isset($this->argFreq[$j]) ? ++$this->argFreq[$j] : $this->argFreq[$j] = 1;
                while ($j--);
            }

            $i -= 2;
        }

        return array($f[0], $closures);
    }

    protected function makeVars($closure, &$tree, $key)
    {
        $tree['code'] =& $closure;
        $tree['nfe'] = false;
        $tree['used'] = array();
        $tree['local'] = array();

        // Replace multiple "var" declarations by a single one
        $closure = preg_replace_callback("'(?<=[\n\{\}])var [^\n\{\}]+(?:\nvar [^\n\{\}]+)+'", array(&$this, 'mergeVarDeclarations'), $closure);

        // Get all local vars (functions, arguments and "var" prefixed)

        $vars =& $tree['local'];

        if (preg_match("'^( [^(]*)?\((.*?)\)\{'", $closure, $v))
        {
            if ($v[1])
            {
                $vars[$tree['nfe'] = substr($v[1], 1)] = -1;
                $tree['parent']['local'][';' . $key] =& $vars[$tree['nfe']];
            }

            if ($v[2])
            {
                $i = 0;
                $v = explode(',', $v[2]);
                foreach ($v as $w) $vars[$w] = $this->argFreq[$i++] - 1; // Give a bonus to argument variables
            }
        }

        $v = preg_split("'(?<![\$.a-zA-Z0-9_])var '", $closure);
        if ($i = count($v) - 1)
        {
            $w = array();

            while ($i)
            {
                $j = $c = 0;
                $l = strlen($v[$i]);

                while ($j < $l)
                {
                    switch ($v[$i][$j])
                    {
                    case '(': case '[': case '{':
                        ++$c;
                        break;

                    case ')': case ']': case '}':
                        if ($c-- <= 0) break 2;
                        break;

                    case ';': case "\n":
                        if (!$c) break 2;

                    default:
                        $c || $w[] = $v[$i][$j];
                    }

                    ++$j;
                }

                $w[] = ',';
                --$i;
            }

            $v = explode(',', implode('', $w));
            foreach ($v as $w) if (preg_match("'^{$this->varRx}'", $w, $v)) isset($vars[$v[0]]) || $vars[$v[0]] = 0;
        }

        if (preg_match_all("@function ({$this->varRx})//''\"\"#@", $closure, $v))
        {
            foreach ($v[1] as $w) isset($vars[$w]) || $vars[$w] = 0;
        }

        if ($this->argFreq[-1] && preg_match_all("@}catch\(({$this->varRx})@", $closure, $v))
        {
            $v[0] = array();
            foreach ($v[1] as $w) isset($v[0][$w]) ? ++$v[0][$w] : $v[0][$w] = 1;
            foreach ($v[0] as $w => $v) $vars[$w] = $this->argFreq[-1] - $v;
        }

        // Get all used vars, local and non-local

        $vars =& $tree['used'];

        if (preg_match_all("#([.,{]?)(?<![a-zA-Z0-9_\$])({$this->varRx})(:?)#", $closure, $w, PREG_SET_ORDER))
        {
            foreach ($w as $k)
            {
                if (',' === $k[1] || '{' === $k[1])
                {
                    if (':' === substr($k[3], -1)) $k = '.' . $k[2];
                    else $k = $k[2];
                }
                else $k = $k[1] . $k[2];

                isset($vars[$k]) ? ++$vars[$k] : $vars[$k] = 1;
            }
        }

        if (preg_match_all("#//''\"\"[0-9]+(?:['!]|/')#", $closure, $w)) foreach ($w[0] as $a)
        {
            $v = "'" === substr($a, -1) && "/'" !== substr($a, -2) && $this->specialVarRx
                ? preg_split("#([.,{]?(?<![a-zA-Z0-9_\$@]){$this->specialVarRx}:?)#", $this->strings[$a], -1, PREG_SPLIT_DELIM_CAPTURE)
                : array($this->strings[$a]);
            $a = count($v);

            for ($i = 0; $i < $a; ++$i)
            {
                $k = $v[$i];

                if (1 === $i%2)
                {
                    if (',' === $k[0] || '{' === $k[0])
                    {
                        if (':' === substr($k, -1)) $k = '.' . substr($k, 1, -1);
                        else $k = substr($k, 1);
                    }
                    else if (':' === substr($k, -1)) $k = substr($k, 0, -1);

                    $w =& $tree;

                    while (isset($w['parent']) && !(isset($w['used'][$k]) || isset($w['local'][$k]))) $w =& $w['parent'];

                    (isset($w['used'][$k]) || isset($w['local'][$k])) && (isset($vars[$k]) ? ++$vars[$k] : $vars[$k] = 1);

                    unset($w);
                }

                if (0 === $i%2 || !isset($vars[$k])) foreach (count_chars($v[$i], 1) as $k => $w) $this->charFreq[$k] += $w;
            }
        }

        // Propagate the usage number to parents

        foreach ($vars as $w => $a)
        {
            $k =& $tree;
            $chain = array();
            do
            {
                $vars =& $k['local'];
                $chain[] =& $k;
                if (isset($vars[$w]))
                {
                    unset($k['used'][$w]);
                    if (isset($vars[$w])) $vars[$w] += $a;
                    else $vars[$w] = $a;
                    $a = false;
                    break;
                }
            }
            while ($k['parent'] && $k =& $k['parent']);

            if ($a && !$k['parent'])
            {
                if (isset($vars[$w])) $vars[$w] += $a;
                else $vars[$w] = $a;
            }

            if (isset($tree['used'][$w]) && isset($vars[$w])) foreach ($chain as &$b)
            {
                isset($b['local'][$w]) || $b['used'][$w] =& $vars[$w];
            }
        }

        // Analyse childs

        $tree['childs'] = array();
        $vars =& $tree['childs'];

        if (preg_match_all("@//''\"\"#[0-9]+'@", $closure, $w))
        {
            foreach ($w[0] as $a)
            {
                $vars[$a] = array('parent' => &$tree);
                $this->makeVars($this->closures[$a], $vars[$a], $a);
            }
        }
    }

    protected function mergeVarDeclarations($m)
    {
        return str_replace("\nvar ", ',', $m[0]);
    }

    protected function renameVars(&$tree, $root)
    {
        if ($root)
        {
            $tree['local'] += $tree['used'];
            $tree['used'] = array();

            foreach ($tree['local'] as $k => $v)
            {
                if ('.' == $k[0]) $k = substr($k, 1);

                if ('true' === $k) $this->charFreq[48] += $v;
                else if ('false' === $k) $this->charFreq[49] += $v;
                else if (!$this->specialVarRx || !preg_match("#^{$this->specialVarRx}$#", $k))
                {
                    foreach (count_chars($k, 1) as $k => $w) $this->charFreq[$k] += $w * $v;
                }
                else if (2 == strlen($k)) $tree['used'][] = $k[1];
            }

            arsort($this->charFreq);

            $this->str0 = '';
            $this->str1 = '';

            foreach ($this->charFreq as $k => $v)
            {
                if (!$v) break;

                $v = chr($k);

                if ((64 < $k && $k < 91) || (96 < $k && $k < 123)) // A-Z a-z
                {
                    $this->str0 .= $v;
                    $this->str1 .= $v;
                }
                else if (47 < $k && $k < 58) // 0-9
                {
                    $this->str1 .= $v;
                }
            }

            if ('' === $this->str0)
            {
                $this->str0 = 'claspemitdbfrugnjvhowkxqyzCLASPEMITDBFRUGNJVHOWKXQYZ';
                $this->str1 = $this->str0 . '0123456789';
            }

            foreach ($tree['local'] as $var => $root)
            {
                if ('.' != substr($var, 0, 1) && isset($tree['local'][".{$var}"])) $tree['local'][$var] += $tree['local'][".{$var}"];
            }

            foreach ($tree['local'] as $var => $root)
            {
                if ('.' == substr($var, 0, 1) && isset($tree['local'][substr($var, 1)])) $tree['local'][$var] = $tree['local'][substr($var, 1)];
            }

            arsort($tree['local']);

            foreach ($tree['local'] as $var => $root) switch (substr($var, 0, 1))
            {
            case '.':
                if (!isset($tree['local'][substr($var, 1)]))
                {
                    $tree['local'][$var] = '#' . ($this->specialVarRx && 3 < strlen($var) && preg_match("'^\.{$this->specialVarRx}$'", $var) ? $this->getNextName($tree) . '$' : substr($var, 1));
                }
                break;

            case ';': $tree['local'][$var] = 0 === $root ? '' : $this->getNextName($tree);
            case '#': break;

            default:
                $root = $this->specialVarRx && 2 < strlen($var) && preg_match("'^{$this->specialVarRx}$'", $var) ? $this->getNextName($tree) . '$' : $var;
                $tree['local'][$var] = $root;
                if (isset($tree['local'][".{$var}"])) $tree['local'][".{$var}"] = '#' . $root;
            }

            foreach ($tree['local'] as $var => $root) $tree['local'][$var] = preg_replace("'^#'", '.', $tree['local'][$var]);
        }
        else
        {
            arsort($tree['local']);
            if (false !== $tree['nfe']) $tree['used'][] = $tree['local'][$tree['nfe']];

            foreach ($tree['local'] as $var => $root)
                if ($tree['nfe'] !== $var)
                    $tree['local'][$var] = 0 === $root ? '' : $this->getNextName($tree);
        }

        $this->local_tree =& $tree['local'];
        $this->used_tree  =& $tree['used'];

        $tree['code'] = preg_replace_callback("#[.,{ ]?(?<![a-zA-Z0-9_\$@]){$this->varRx}:?#", array(&$this, 'getNewName'), $tree['code']);
        $this->specialVarRx && $tree['code'] = preg_replace_callback("#//''\"\"[0-9]+'#", array(&$this, 'renameInString'), $tree['code']);

        foreach ($tree['childs'] as $a => &$b)
        {
            $this->renameVars($b, false);
            $tree['code'] = str_replace($a, $b['code'], $tree['code']);
            unset($tree['childs'][$a]);
        }
    }

    protected function renameInString($a)
    {
        $b =& $this->strings[$a[0]];
        unset($this->strings[$a[0]]);

        return preg_replace_callback(
            "#[.,{]?(?<![a-zA-Z0-9_\$@]){$this->specialVarRx}:?#",
            array(&$this, 'getNewName'),
            $b
        );
    }

    protected function getNewName($m)
    {
        $m = $m[0];

        $pre = '.' === $m[0] ? '.' : '';
        $post = '';

        if (',' === $m[0] || '{' === $m[0] || ' ' === $m[0])
        {
            $pre = $m[0];

            if (':' === substr($m, -1))
            {
                $post = ':';
                $m = (' ' !== $m[0] ? '.' : '') . substr($m, 1, -1);
            }
            else $m = substr($m, 1);
        }
        else if (':' === substr($m, -1))
        {
            $post = ':';
            $m = substr($m, 0, -1);
        }

        $post = (isset($this->reserved[$m])
            ? ('true' === $m ? '!0' : ('false' === $m ? '!1': $m))
            : (
                  isset($this->local_tree[$m])
                ? $this->local_tree[$m]
                : (
                      isset($this->used_tree[$m])
                    ? $this->used_tree[$m]
                    : $m
                )
            )
        ) . $post;

        return '' === $post ? '' : ($pre . ('.' === $post[0] ? substr($post, 1) : $post));
    }

    protected function getNextName(&$tree = array(), &$counter = false)
    {
        if (false === $counter)
        {
            $counter =& $tree['counter'];
            isset($counter) || $counter = -1;
            $exclude = array_flip($tree['used']);
        }
        else $exclude = $tree;

        ++$counter;

        $len0 = strlen($this->str0);
        $len1 = strlen($this->str0);

        $name = $this->str0[$counter % $len0];

        $i = intval($counter / $len0) - 1;
        while ($i>=0)
        {
            $name .= $this->str1[ $i % $len1 ];
            $i = intval($i / $len1) - 1;
        }

        return !(isset($this->reserved[$name]) || isset($exclude[$name])) ? $name : $this->getNextName($exclude, $counter);
    }

    protected function restoreCc(&$s, $lf = true)
    {
        $lf && $s = str_replace('@#3', '', $s);

        $s = str_replace('@#1', '@*/', $s);
        $s = str_replace('2#@', '//@', $s);
        $s = str_replace('1#@', '/*@', $s);
        $s = str_replace('##', '#', $s);
    }
}
