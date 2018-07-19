# led-music-visualizer
The goal of this project is to create a small box that takes Aux input, uses FFT to analyze the audio signals, and produce led animations to match the music. Initially, the animations may be as simple as reacting to above average pulses in the music, but eventually I would like to add some sort of smart analysis of the music so that it can somewhat detect changes from verse->bridge->chorus etc... 

# Build
This project was built using an Arduino Uno, a SparkFun Spectrum Shield, various WS2812b LED strips, various wires and connectors, and a 3d printed case. I started by getting the values from the shield and analyzing them myself. I wanted to see which what the data looked like, and how I could extrapolate information from it. The next step, once I had learned what I could from the data, was to start with simple LED animations based on a very simple analysis of the data. I will gradually add more and more functionality into the algorithm until I reach a point that I am happy with the displays. 

# Goals
I eventually want to find a way for the system to be able to handle more leds without having to edit the code. Currently I have to hardcode the led count, but in the future I'd like to add buttons (or some other interface) to update the LED count.

# Demo
Once I have completed a fair portion of this project, I will upload a video to youtube of it working. 

# Images
//TODO add google photos link to the album
# Instructions
For those that are interested in re-creating this project, or improving it, I will add instructions below.
