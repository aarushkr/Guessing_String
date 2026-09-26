# Guessing_String 

A small implementation of a genetic algorithm in C++ that evolves a randomly generated string toward a target string using methods such as crossover and mutation. This program can guess a long string in minutes whereas a brute force approach could take years in the worst case

## How it works

The program maintains a population of randomly generated strings. Each string is given a fitness based on how many characters match the target at the correct positions. A mating pool is created and populated with that many copies of the string as its fitness times 100 (fitness is normalized to be a value between 0 and 1 inclusive). Thus the fittest individuals are more likely to be selected as parents. New strings are created through crossover and can undergo mutation. The process continues until the target string is generated.

## Note

I learned the concepts behind genetic algorithms from [The Nature of Code](https://natureofcode.com/) by Daniel Shiffman (in which code is written in p5.js) and implemented the algorithm myself in C++.
