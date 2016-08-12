# Rescrabbler
This Rescrabbler program finds the longest matching anagram transition on dictionary written in pure C++ (STL).

### Anagram transition / derivation
An anagram derivation is a N-letter word derived from a N-1 letter word by adding a letter and rearranging. For example, here is a derivation of "aliens":

`ail + s = sail + n = nails + e = aliens`

### Algorithm
Rescrabler algorithm can be divided into 3 parts:

1. Creation of dictionary of matching words to the beginning word (each record is stored in a multimap of (int, WordDictionary). WordDictionary conains a map of occuring letters (LettersStack), which contains a number of each letter occurance.

2. Iteration through the multimap in descending order (longest word first). If the solution for the largest number of letters was not found, algorithm will reset the result stack and will begin to iterate.

3. Recursive call of findAnnagrams method with descending depth. Each item's letter stack is compared with the adjacent one. If there's possibility to transit (all letters are covered), the overloaded substraction operators returns the letter which will be removed to obtain the deeper word (with less letters).

If number of letters of beginning word matches currently processing word, the algorithm is stopped.

I tried to use smartpointers instead of const references / references / raw pointers, but it has negative impact on benchmark result (ca ~1s)

### Benchmark
For beginning 'ail' and unix built-in /usr/share/dict (american-english, ~100k records) algorithm takes ~5.4s to find the longest annagram transition.
Result for 'ail' and unix dict:

`ail + d = dial + e = ailed + n = alined + h = inhaled + r = hardline + g = heralding + H = Highlander + s = Highlanders + ' = Highlander's`

### Usage
* Commands:
        --dict <filepath>  loads file
        --default          uses default dictionary (from task)
        --begin <word>     sets begin world
* Mix of commands will also work. ex. --dict --default will look
    for 'ail' in ./assets/words (unix dictionary from /usr/share/dict).
* All necessary info is provided by command prompt (including benchmark from std::chrono).
