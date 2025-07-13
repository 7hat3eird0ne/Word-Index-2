# About
## Credits

Here are the two libraries (I guess you can call it? I am new to C++ so I dunno) I used with the link to their GitHub repository, both are in the include folder:
- BigInt.hpp - https://github.com/faheel/BigInt
- json.hpp - https://github.com/nlohmann/json

## Basic info
**Since this version acts pretty much exact same the original, I reuse the same README**

Hello, currrently, this repository allows users to assign a unique index to any string, with the index scaling up with the length of the string

For example, lets make our character set, which is pretty much a json file with all settings and order of characters, we don't have to care about the setting that much, lets just say the characters are only lowercase english alphabet letters in the same order as in alphabet

The first few indexes of our character set would be:

- 0\. ""
- 1\. "a"
- 2\. "b"
- 3\. "c"
- ...
- 26\. "z"
- 27\. "aa"
- 28\. "ba"
- ...

and so on...

I would like to note that I made this just for fun + this is very messy and very unprofessional :D

## The math behind it

The way the number is actualy computed and the math behind it is pretty simple:

1. First we convert every individual character in the string to a digit from 0 to N-1 where N is the amount of characters in character set, we can just say that it is the index of the character in the list
1. Then we put them together and convert the number represenation to the decimal base
    - For example, string "code" in our alphabet character set could be written as 
    4(e) 3(d) 14(o) 2(c), which converted to decimal ends up becoming 72698
1. Because adding "a" or any character which is first in character set ends up adding 0 to it, it is hard to know if the index refferences to version with or without additional a's, we can fix that by adding N**L, where ** is exponation and L is length of string (for "code", L is 4)
1. Because of the additional N**L, the formula now leaves out few indexes, the two strings (in their numerical represenation) in between which are the skipped indexes always look like this (where M = N-1):
    - 1MM and 1000 (add additional M's and 0's to reflect any length)
    - if we change the forms into their decimal ones:
        - 1MM = 2N**(L-1)
        - 1000 = N**(L)
    - and take difference between them, and subtract 1, we can get the value we should have to remove the additional index:
        - N**(L) - 2N**(L-1)
    - Now we gotta take summation of it from 0 to L, but because 0 gives wrong value instead of 1, we just manualy subtract 1 manualy and make the summation starts at 1, this gives us our final formula which we add to numerical representation instead of just alone N**l:
        - N\*\*L - sum(N\*\*(j)-2N\*\*(j-1), where j = 1 -> L) - 1
1. We can simplify the summation though
    - first we change the inside of summation to a multiplication 
        - (1-2/N) \* (N\*\*j) 
    - then we can take out the (1 - 2/N) bit out of the summation
    - then we can add one to j everywhere so that the bounds get lowered by one
        - sum(N\*\*(j+1), where j = 0 -> L-1)
    - then we can multiply the inner summation bit by (N-1) and divide by it the entire summation
    - then we can simplify the summation so that it is:
        - N**(L+1) - 1
    - we can also multiply the thing by N so we can get rid of the (+1) in the exponent, and simplify the (1 - 2/N)
    - now the correction factor is N\*\*L - (N-2)\*(N\*\*L-1)/(N-1) - 1

1. We can simplify the correction factor more though
    - First we regroup it a bit
        - (N\*\*L-1) - (N-2)\*(N\*\*L-1)/(N-1)
    - Then we put N\*\*-1 into the fraction
        - ((N-1)\*(N\*\*L-1)-(N-2)\*(N\*\*L-1))/(N-1)
    - We can group the (N\*\*L-1) terms into one
        - ((N-1)-(N-2))\*(N\*\*L-1)/(N-1)
    - Simplifying the two terms ends up equalling 1, being useless, which results in our final correction formula
        - (N\*\*L-1)/(N-1)

1. Then we add it to our numerical representation and we get our result formula:
    - index = numRepres + (N\*\*L-1)/(N-1)

## How to use

There are few commands you can use to use it, as seen using the 'h' command:
- h
    - Prints help
- q
    - Quits the program
- r
    - Changes the character set
- f
    - Translates a string into an index
- b
    - Finds a string using an index

## Customisation

We can customise the calculator a bit, by copying the json file and changing the following:
- The 'order' array defines in which order do the characters go, every element has to be a string of length 1, duplicates can be there but can make the indexes inaccurate so I don't recomend them.
- The 'caseSensitive' bool says whatever it should be case sensitive or not, if it is set to false, it will just turn everything lowercase.
- The 'reverseAppend' bool says whatever the append should be reversed, for example "code" will normaly be 4 3 14 2, but with reverse append it will be reversed.
- The 'minLen' integer says what should be the minimal length avaible, this just subtracts the final index by the smallest index of the minimal length, for example if we make minLen = 2, it will make "aa" turn into 0, instead of being 27.

## Algorithms intended to be done by human

(If a step results in some decimal number, round it down)

### String to Index:

1. Let R = 0, M = 1, N = amount of characters in character set
1. Take the first character, or next unused one
1. Find the characters index in the character set (starting with 0 going up to N-1)
1. Multiply index of the character by M and add it to R
1. Multiply M by N
1. If there are more characters, go to step 2, else continue to step 7
1. Let S = (M-1)/(N-1)
1. Add S to R
1. Output R

### Index to String

1. Let L = 0, T = 1, I = index, N = amount of characters in character set
1. Multiply T by N
1. Add 1 to L
1. Let C = (T-1)/(N-1)
1. If C > I, go to step 6, else if C = I, go to step 8, else go to step 2
1. Divide T by N
1. Subtract 1 from L 
1. Let S = (T-1)/(N-1), if C = I, then let S = C
1. Let X = I - S
1. Divide X by N, let R = remainder
1. Find the character corresponding to the remainder as an index in the character set
1. Append the character to the end of the result string
1. Subtract 1 from L
1. If L = 0, go to step 15, else go to step 10
1. Output the result string

This is most probably everything for now. Feel free to use it if it can be remotely usable in your case

Thank you for reading!