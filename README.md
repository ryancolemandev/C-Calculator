# C-Calculator
## C expression calculator using a simple recursive descent parser
It can evaluate expressions that contain positive and negative decimal numbers as well as the addition, subtraction, multiplication, division and parantheses functions.
This project introduced me to parsing, operator precedence and basic error handling which I hope to use on a compiler project. It also was good practice for fundamentals such as structs and pointers.

## How does it work?
The program reads an expression as a string and goes through it one part at a time. expression() handles addition and subtraction, term() handles multiplication and division, factor() handles numbers, negative numbers and parantheses. This gives three layers of precendence where multiplication and division are always calculated before addition and subtraction no matter what order the expression is given as. The errors that it handles are improper parantheses, diviaion by zero and invalid expressions or characters but it hasn't yet been tested exhaustively. 
