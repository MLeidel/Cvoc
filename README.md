# Cvoc
### "command-line voice, c voice, curl voice"

Cvoc is a console binary that produces text-to-speech audio files.
It is written for Linux.  
It requires an OpenAI authorization key set to an environment
variable called __GPTKEY__.
Cvoc uses the OpenAI audio.speech API with several speech parameters
to convert text into speech in the form of an audio file. The quality
of the speech produced is more lifelike than that of previous 
text-to-speech technologies.

Explanation of the 
[API parameters](https://platform.openai.com/docs/api-reference/audio/createSpeech "openai audio.speech")

Cvoc uses the Linux utility '__play__' (SoX) to play back the audio file.  
Cvoc uses the '__curl__' utility to create/stream the audio file.  

## How to Use

Cvoc uses a required `cvoc.ini` file to hold default values for the  
text-to-speech parameters (`~/.config/cvoc.ini`). Edit this file to
change the defaults.  

example:
```bash
output=speech
voice=nova
format=mp3
speed=0.95
model=tts-1
```
Note: the output file name does not have its extension.  
This is because it will use the _format_ for its extention.


Two ways to execute `cvoc`:

```bash
cvoc
```
Executing without an argument prompts you for all of the parameters.
Press Enter to accept the default value of any parameter. The text
is the last parameter requested.

```bash
cvoc the cow jumped over the moon.
```
Executing with text produces an audio file based on default parameters (cvoc.ini).
