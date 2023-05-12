# StrHash: tool to partially reversibly hash alphanumeric strings

**Standard disclaimer:** _this is some code of mine that was created for some very specific purpose and might not work as intended. However it may still be useful to someone so here it is._

**Description:** Micccy's standard for hashing (ASCII) (alphanumeric) strings in 4bits per character.  
The pourpose is to make reverse engineering of hashed sequences fairly easy when done by the same user that originally created them.  
  
E.g.: This utility could be used to generate IPs to assign to a host from its (short) name.  
If the user forgets the host name, they can simply see which letters correspond to each nibble,  
since the user will only have ever messed with a limited set of host names, this should be enough for them to remember it.  
  
Only the lower 8bits matter if char is bigger than int8\_t  
ASCII control codes (<0x20) are ignored  
Non-alphanumeric values have their nibbles xored to get a single 4 bit figure  
Multiple consecutive non-alphanumeric values are added together and treated as a single one  
Nibbles replace alphanumeric values using the rules written below  
  
0 is reserved as the NUL character  
1-9 and (case insensitive) A-F map to the corresponding hexadecimal figure  
Remaining characters are then mapped starting from 1  
Since there are 36 characters and only 15 slots, 9 slots will have 2 characters mapped while the 6 remaining slots will have 3  
The 5 of the 6 characters that have been chosen to be the 3rd ones are JKWXY, and they have been put in a group containing a similar sound  
The character '0' has been put in group A, following 9 to make it easirer for users using decimal notation to reverse engineer numbers they hashed  
The groups are listed below  
  
HASH	CHAR  
0  
1	1GJ  
2	2HX  
3	3IY  
4	4L  
5	5M  
6	6N  
7	7O  
8	8P  
9	9Q  
A	AR0  
B	BS  
C	CTK  
D	DUW  
E	EV  
F	FZ  
  
The resulting hashed sequence can never have identical consecutive nibbles  
Nibbles are grouped into uint8\_t,uint16\_t,uint16\_t and uint64\_t little endian sequences  
Each sequence has all of its elements xored together to give an even smaller hash  
  
 E.G.: pizza = 83FA = 0x38,0xAF (xor:0x97) = 0xAF38  




**Status:** _Functional - should be expanded upon_
