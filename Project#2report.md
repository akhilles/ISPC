### Research on Hash and Password Cracking

#### Hash Function and Properties

A **hash function** is basically a function that maps an arbitrary size of data to a fixed size of data, which are strings or characters in terms of password. It is designed to act as a "one-way function". One data structure that implements hash function is hash table, which is widely used for rapid data lookup. Hash tables map the search key to a list of data. 

**A good hash function** will

- always generate the same hash value for a given input key, 
- map the expected inputs as evenly as possible over its output range
- have a defined output range

> Such hashing is commonly used to accelerate data searches.[[5\]](https://en.wikipedia.org/wiki/Hash_function#cite_note-algorithms_in_java-5) On the other hand, cryptographic hash functions produce much larger hash values, in order to ensure the computational complexity of brute-force inversion.[[2\]](https://en.wikipedia.org/wiki/Hash_function#cite_note-handbook_of_applied_cryptography-2) For example, [SHA-1](https://en.wikipedia.org/wiki/SHA-1), one of the most widely used cryptographic hash functions, produces a 160-bit value. 
>
> Producing fixed-length output from variable length input can be accomplished by breaking the input data into chunks of specific size. Hash functions used for data searches use some arithmetic expression which iteratively processes chunks of the input (such as the characters in a string) to produce the hash value.[[5\]](https://en.wikipedia.org/wiki/Hash_function#cite_note-algorithms_in_java-5) In cryptographic hash functions, these chunks are processed by a [one-way compression function](https://en.wikipedia.org/wiki/One-way_compression_function), with the last chunk being padded if necessary. In this case, their size, which is called *block size*, is much bigger than the size of the hash value.[[2\]](https://en.wikipedia.org/wiki/Hash_function#cite_note-handbook_of_applied_cryptography-2) For example, in [SHA-1](https://en.wikipedia.org/wiki/SHA-1), the hash value is 160 bits and the block size 512 bits.
>
> from [Wikipedia](https://en.wikipedia.org/wiki/Hash_function)

- change hash values for each run of the program
- have data normalization features such as ignoring case differences of letters
- have a continuous data
- be not invertible

#### Password Hash Generation

###### Cryptographic Algorithms (public-key cryptography)

- **AES**
  - has become one of the most popular algorithm
  - is fast
- **SHA1**
  - one of the most secure hash algorithm
- **DES**
  - is no longer secure as it uses 56-bit key
  - is easy to be cracked
- **RSA**
  - asymmetric cryptography, ensures security with public key open
  - is slow and can only handle limited amount of data
- **MD5**
  - is used to check for data integrity 

Public-key cryptography, also known as *asymmetric cryptography*, is a type of cryptographic algorithm. In such algorithm, there is a pair of a public key and a private key. Those two keys are involved in Math. Data encrypted by one key, can only be decoded using the other key. Just by knowing one of the keys, the adversary cannot work out the other one. Therefore, making one of the key public will not compromise the secrecy of the other one. 

#### Adversary's Approach to the given Password Hash

The adversary can guess the hash function by looking at the pattern. One way to investigate **which hash function is used** is to take take all different algorithms and hash/encode your plain text and see which of the output matches. 

However, the given hash could be hashed from a **salted** password, meaning that extra strings or characters are inserted to password before it gets hashed. One way is to still use brute force to crack and at the end, try to exclude the salts.

#### Dictionary attack vs. Rainbow Table attack 

###### Dictionary attack 

- A guessing attack which uses precompiled list of options
- Resource requirement
  - based on knowing key information about a particular target such as family member names, birthday (involved social engineering), or based on patterns seen acorss a large number of users and known passwords.
  - requires pre-generation of dictionary first
  - requires more analysis time, as it compares hashes between the given hash and all those in the dictionary entries, so it is basically batch cracking

###### Rainbow Table attack

- A ranbow table is a precomputed table for reversing cryptographic hash functions with hash of a plain-text password up to a certain length consisting of a limited set of characters. It is an example of space/time trade off.
- Resource requirement
  - more storage and less computer processing time than brute-force attack.
  - requires pre-computation of hash chains.
  - requires less analysis time, as it just compares values in the table with the given hash
- Cannot crack salted passwords

###### When to use Dictionary attack vs. Rainbow Table attck? 

If the password is salted and the adversary knows the salt, it should use dictionary attack. A rainbow table is generally an offline-only attack. In a brute force attack or dictionary attack, you need to spend time either sending your guess to the real system to running through the algorithm offline. Given a slow hashing or encryption algorithm, this wastes time. Also, the work being done cannot be reused. Therefore, if the adversary would like to reuse a table to break multiple passwords, it is better to use rainbow table to save time. However, if it is one-time, rainbow table attack might wastes time on creating password candidates, and a brute-force/dictionary attack is prefered.



