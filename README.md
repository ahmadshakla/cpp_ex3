cpp_ex3
ahmad.shakla
315294553
######

In this exercise we were asked to implement a hash map and a spam detector file.
first of all, the Hashmap.hpp file, in this file I implemented the hash map as a I was asked to
in the exercise's pdf. To store the elements, I used an array of vectors that changes it's size
according to the number of elements inside it. I created a 2 in 1 constructor, it can be used as
a default constructor, or can be supplied with the lower and upper load factors.
in the Hashmap's iterator, I stored a pointer to a Hashmap object and a pointer to the current pair
both these fields were supplied to the iterator's constructors as nullptr, the ++ operator was
implemented in the following way: starting from the first pair I find in the map, I checked if
there are more elements in the vector that the pair exists in,if there was such, I moved to that
pair,if there weren't any (meaning that the pair was the last element in the vector) then I move
to the vector below me, and so on, until I have no more pairs in the map.
in the SpamDetector.cpp I read from both the csv file and the text file in a similar way, I stored
each word and number in the csv file as keys and values in a Hashmap object that I created.
now for the message file I stored all its contents in one string, and used the find() method
to look for matches.
