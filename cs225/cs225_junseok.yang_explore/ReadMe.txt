*How to build your program

1. Spread a CMD window.
2. Enter c++ main.cpp or g++ main.cpp
3. Run the created .exe file in the cmd window.
4. You can see the difference in the running speed of std::endl and '\n' by looking at the result.

*How to interact with your program

You can change the LINE_NUM value in the #define.
The more you increase the LINE_NUM value, the better the speed difference between STD::ENDL and "\N".
Changing the ++i in the "for" iterative statement to i++ will change the speed at which it moves.

*What you learned from creating the demo

I found out that std::endl was slow in making this demo. 
I also found out that Chrono was a very good header to check the time.