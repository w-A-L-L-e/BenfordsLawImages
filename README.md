# BenfordsLawImages

Watched this show on Netflix in the weekend called 'Connected' which had all this mystery and wonder around Benford's law.
One part was about applying it to images. So I got curious and hacked together a little program to do this benford check myself.
It can read jpeg and png images and prints out the benford results and an ascii graph. And yes this is just a quick hack, surely
can be improved. But it was really funny to see the graph on a random image from facebook actually showing the same curve as
was advertised in the netflix show.


# Installing
On macOS just run make install_deps (you will need homebrew and xcode installed).

```
$ make install_deps
```

then compile it with make
```
make
```

Optional: You can install the binary in /usr/local/bin by running
```
make install
```
And remove it with make uninstall.


# Running
Running the created executable without arguments prints the usage:
```
$ USAGE: ./img2benford: <image|-random>
  an image file (jpg or png) as argument.
  -random to show the uniform random result of benford
```

Now run it first with random data:
```
./img2benford -random
Benford applied to one million random values:
                                                                                                            
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

benford count 1 = 100273 percentage = 10
benford count 2 = 110775 percentage = 11
benford count 3 = 110885 percentage = 11
benford count 4 = 110940 percentage = 11
benford count 5 = 110794 percentage = 11
benford count 6 = 111017 percentage = 11
benford count 7 = 111086 percentage = 11
benford count 8 = 110961 percentage = 11
benford count 9 = 111193 percentage = 11
```

So that's what I expected pretty much each most significand digit is occuring about the same. Also 0 isn't printed here
as it only counts actual 0 which doesn't happen much in images neither (r+g+b==0 is blackest of black not really acchieved in pictures).
It does however happen most likely enough in this pseudo-random test to offset the benford count for digit 1 and it is found here 2% of the time.

# Results
Being satisfied with this graph, quickly googled opening png and jpeg images.Found some stackoverflow code, adjusted it for what we needed.
Now I took this random photo from facebook of a waterfall in nature. Ran the same test but now on an image. And ... 'no way!'... gotta
say, that's pretty interesting as a first result:

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
However, then I proceeded to using other images on my pc and was kinda disappointed. Or rather it's not as good as the show 'connected' made us believe.
It works on this example but I can find plenty of 'real' photos that don't give this nice curve. 
Incidently the second test also is not that bad (./img2benford tests/connected_digits_screenshot.jpg). 
However take a photo in the city with buildings as a background and you get a totally deviating curve even though it wasn't manipulated.
So maybe Benford only works on 'natural' things, meh, who knows... It was still worth the little effort to try it out myself ;).

Now here comes the proof that it doesn't really work well for image manipulation detection. There's an edited image in tests/
and if you run it with our tool it should show a graph different (flatter) than the original. However it doesn't, it's even more close
to the benford curve than the original (normally the 1s are around 30%, in the original its 25%, in the edited image it's actually 27%).
```
./img2benford tests/nature_edited_red.jpg
```

Some more screenshots and an explanation of the algorithm is here https://walter.schreppers.com/hobby_project/benfords_law

Ow and last but definately not least: if you can find any mistakes or make improvements. Feel free to put them in an issue, comment or pull request.

# Credits
Jenke Goffa for taking that beautiful picture of a waterfall that also produces the nice benford curve. It's included in the
test cases tests/nature_image.jpg. And ofcourse the Connected TV series that inspired me to write this tool in the first place https://en.wikipedia.org/wiki/Connected_(2020_TV_series)

