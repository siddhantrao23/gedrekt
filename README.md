# Levenshtein

Levenshtein distance algorithm is an algorithm to determine the edit distance metric (by insertions, deletions or substitutions of single characters) between two strings, often used in Natural Language Processing.

```
    levenshtein(“book”, “borg”) = 2
    levenshtein(“abc”, “ab”) = 1
```

The generic version of levenshtein distance would calculates the distance not just for strings, but also for any collection that provides a Forward Iterator. This extends the application to other types of data, such as genome sequences, encoded query plans etc.

Our implementation can calculate the levenshtein distance with any two data structures where their value types can be compared with equality.
