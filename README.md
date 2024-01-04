# tinyhttp

## Introduction
This is a tiny webserver using C++, very **simple, weak and vulnerable**. It's not for production but study!
With socket, thread, it can perform static webpages well. But without cgi, it's still not available to answer POST, so dynamic webpages(x). The original model is tinyhttp(https://tinyhttpd.sourceforge.net/)a lite httpserver written by James David in 1999.
This program is my first step to backend web programming, which I'm really interested and have written lots of frontend pages. The program also servers as my program design course's assignment (use C++ to create whatever you like, lines>=1500), though not the initial reason why I write this, it gives me the motivation to start. I have gained lots of knowledge in this program, and deeper my understanding of OOP. 


## Installation
Fork it, Donwload it in ZIP or whatever way you like.

I have only tested it on Windows, but there should be only minial changes to run it on Linux and Mac. 
1. The header files must be replaced since I'm using WinSock.
2. The function `ReadHeader::readheader()`in file `readheader.cpp` is using `S_IFDIR` and `S_IFMT`, which I'm not sure if goes well in other platform.
3. The original version `Source.cpp` uses thread that only support windows platform.


## Version History
The first version is `Source.cpp`. I write it following [these codes](https://tinyhttpd.sourceforge.net/) and [a teaching video](https://www.bilibili.com/video/BV1B24y1d7Vi/) in bilibili. It is using C but not C++.

The second version is all other files. [This article](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa) in medium and [this video](https://www.youtube.com/watch?v=YwHErWJIh6Y) in Youtube helped me a lot. It rewrites the first version in C++.



## Future Steps
There're some future steps I want to implement but I can't promise due to the lack of time.
1. Support POST method.
2. Log system.
3. Support thread. 