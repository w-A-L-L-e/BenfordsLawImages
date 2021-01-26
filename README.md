# BenfordsLawImages

Watched this show on Netflix in the weekend called 'connected' which had all this mystery and wonder around Benford's law.
One part was about applying it to images. So I got curious and wrote a little program quick and dirty to do this check myself.
It can read jpeg and png images and prints out the benford results and an ascii graph.


# installing
On macOS just run make install_deps (you will need homebrew and xcode installed).

```
$ make install_deps
```

then compile it with make
```
make
```

You can install the binary by running
```
make install
```
And remove it with make uninstall.


# Runing
Running the created executable without arguments prints the usage:
```
$ USAGE: ./img2benford: <image|-random>
  an image file (jpg or png) as argument.
  -random to show the uniform random result of benford
```

Now run it first with random data:
```
./img2benford -random
Uniform random benford on a million values:

            #########   #########   #########   #########   #########   #########   #########   #########
#########   #########   #########   #########   #########   #########   #########   #########   #########
#########   #########   #########   #########   #########   #########   #########   #########   #########
#########   #########   #########   #########   #########   #########   #########   #########   #########
#########   #########   #########   #########   #########   #########   #########   #########   #########
#########   #########   #########   #########   #########   #########   #########   #########   #########
#########   #########   #########   #########   #########   #########   #########   #########   #########
#########   #########   #########   #########   #########   #########   #########   #########   #########
#########   #########   #########   #########   #########   #########   #########   #########   #########
#########   #########   #########   #########   #########   #########   #########   #########   #########
#########   #########   #########   #########   #########   #########   #########   #########   #########
  1 (10)      2 (11)      3 (11)      4 (11)      5 (11)      6 (11)      7 (11)      8 (11)      9 (11)

benford count 1 = 100440 percentage = 10
benford count 2 = 111447 percentage = 11
benford count 3 = 110810 percentage = 11
benford count 4 = 111213 percentage = 11
benford count 5 = 111111 percentage = 11
benford count 6 = 110529 percentage = 11
benford count 7 = 110797 percentage = 11
benford count 8 = 110183 percentage = 11
benford count 9 = 111302 percentage = 11
```

So that's what I expected pretty much each most significand digit is occuring about the same.

# Results
Now I took this random photo from facebook of a waterfall in nature. Ran the same test but now on an image. And 'no way', gotta
say that's pretty interesting as a result:

```
./img2benford tests/nature_image.jpg

#########
#########
#########
#########
#########   #########
#########   #########
#########   #########
#########   #########
#########   #########
#########   #########
#########   #########
#########   #########
#########   #########   #########
#########   #########   #########
#########   #########   #########
#########   #########   #########   #########
#########   #########   #########   #########
#########   #########   #########   #########   #########
#########   #########   #########   #########   #########
#########   #########   #########   #########   #########
#########   #########   #########   #########   #########   #########
#########   #########   #########   #########   #########   #########   #########
#########   #########   #########   #########   #########   #########   #########   #########   #########
#########   #########   #########   #########   #########   #########   #########   #########   #########
#########   #########   #########   #########   #########   #########   #########   #########   #########
  1 (25)      2 (21)      3 (13)      4 (10)      5 (8)       6 (5)       7 (4)       8 (3)       9 (3)

benford count 1 = 648313 percentage = 25
benford count 2 = 531042 percentage = 21
benford count 3 = 351602 percentage = 13
benford count 4 = 273866 percentage = 10
benford count 5 = 211944 percentage = 8
benford count 6 = 127823 percentage = 5
benford count 7 = 106355 percentage = 4
benford count 8 = 89524 percentage = 3
benford count 9 = 91162 percentage = 3

```

# Remarks
Wait, what? OMG!
However, then I proceeded to using other images on my pc and was kinda disappointed. Or rather it's not as good as the show 'connected' made us believe.
It works on this example but I can find plenty of 'real' photos that don't give this nice curve. 
Incidently the second test also is not that bad (./img2benford tests/connected_digits_screenshot.jpg). 
However take a photo in the city with buildings as a background and you get a totally deviating curve even though it wasn't manipulated.
So maybe Benford only works on 'natural' things, meh, who knows... It was still worth the little effort to try it out myself ;).

