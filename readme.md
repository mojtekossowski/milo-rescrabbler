# Rescrabbler
This Rescrabbler program finds the longest matching anagram transition on dictionary written in pure C++ (STL).

### Anagram transition / derivation
An anagram derivation is a N-letter word derived from a N-1 letter word by adding a letter and rearranging. For example, here is a derivation of "aliens":

`ail + s = sail + n = nails + e = aliens`

### Algorithm
Rescrabler algorithm can be divided into 3 parts:

1. Creation of dictionary of matching words to the beginning word (each record is stored in a multimap of (int, DictionaryWord). DictionaryWord contains a map of occuring letters (LettersStack) - which contains a count of each letter occurance.

2. Iteration through the multimap (int, DictionaryWord) in descending order (longest word first). If the solution for the currently longest word was not found, algorithm will reset the result stack and continue once again for previous longest word (reverse iterator).

3. Recursive call of findAnnagrams searches the dictionary with specified depth and substract all obtained elements from dictionary word argument. If there's a possible transition (exists a transit letter between two elements) the word is pushed to the result list. If not - its poped out. When the base word was found in dictionary, the 'anagram_found_exception' is raised.

If number of letters of beginning word matches currently processing word, the algorithm is stopped.
Then, to obtain the result, just reverse iteration over result records should be performed.

I tried to use smartpointers instead of const references / references / raw pointers, but it has negative impact on benchmark result (ca ~1.5s)

### Build
```
$ qmake milo-rescrabler.pro
$ make
$ make install
```

### Benchmark
For beginning 'ail' and unix built-in /usr/share/dict (american-english, ~100k records) algorithm takes ~1.64 (previously 5.9 - in cause of bug) to find the longest annagram transition (derivation).
Result for 'ail' and unix dict:

`ail + n = lain + e = alien + r = linear + o = aileron + t = oriental + a = rationale + t = alteration + i = retaliation + l = alliteration + s = alliterations + ' = alliteration's`

### Usage
* Commands:
```
--dict <filepath>  loads file
--default          uses default dictionary (from task)
--base             sets begin word (prompt)
```

* Mix of commands will also work. ex. `--dict --default` will look
    for 'ail' in ./assets/words (unix dictionary from /usr/share/dict).
* All necessary info is provided by command prompt (including benchmark from `std::chrono`).