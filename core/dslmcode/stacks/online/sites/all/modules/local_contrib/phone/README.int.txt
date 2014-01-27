About the International Phone Number format
===========================================

These rules have been formulated off of the E.123 (for display) and
E.164 (for input) specifications published by the ITU. In order to
prevent ambiguity, we have chosen to restrict some of the stipulations
these specifications give.

In summary, country calling codes are assigned by the ITU Telecommunication
Standardization Sector in E.164. We take an international phone number to
have the form +XX YYYYYYY where XX is the country code, and YYYYYYY to be
the subscriber's number, possibly with intervening spaces. The maximum
length for these phone numbers is 15.

Reference materials can be found here:
- http://www.itu.int/rec/T-REC-E.123/en
- http://www.itu.int/rec/T-REC-E.164/en

Modifications to E.123
----------------------

7.1: The international prefix symbol "+" MUST prefix international
phone numbers. All numbers missing this symbol will be assumed to be in
the default country code.

When reformatting numbers to a standard format, the following conventions
will be taken:

7.2: Parentheses will be normalized to spaces.

We do not support the multiple phone numbers as described by (7.4); users
can always specify that multiple values are allowed if this is desired.
The functionality specified by 7.5, 7.6 and 8 IS NOT implemented.

9.2 specifies that spacing SHALL OCCUR between the country code, the trunk
code and the subscriber number. As trunk codes are omitted by convention,
this means the only guaranteed separation will be between the country code
and subscriber number. Our implementation MAY treat hyphens, spaces and
parentheses as advisory indicators as to where spaces should be placed.
However, +1 7329060489 will stay as it was specified, while +1 (732) 906-0489
will be normalized to +1 732 906 0489. As a future feature, rules may
be implemented for country codes specifying these conventions, however,
I have deemed such functionality out of scope for now.

The Drupal task specifies that we should validate country codes, however,
due to the highly volatile nature of these codes, the author does not
believe that it is a good idea to maintain a list of valid country codes.
Thus, we only validate that the country code is three or less digits.

Modifications to E.164
----------------------

Our processing for NDD's will be similarly constrained. As per
7.3.2, we will treat 0 as a valid trunk code for all countries.
Other digits may be specified if the fall in the form of (X), where X is
a single digit that is 7 or 8.

Postscript
----------

Modifications to our implementation will occur as necessary by user bug
reports.
