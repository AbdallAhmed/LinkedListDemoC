# LinkedListDemoC

The program take a text file as an input argument.

The format of the text file is as follows:

<char>  <int>

The valid characters are 'i' and 'd'

If the current line has an 'i' the program should insert the value following the 'i' into the list in ascending order.

That is to say if we have a list that is:
2 -> 7 -> 10 -> null
and our line is 'i' 8
our list after should be
2 -> 7 -> 8 -> 10 -> null

*Duplicates are ignored.*

If the current line has a 'd' the program should delete the from the linked list.

That is to say if we have a list that is:
2 -> 7 -> 10 -> null
and our line is 'd' 10
our list after should be: 
2 -> 7 -> null

*Ignores deletion of non existing numbers*
