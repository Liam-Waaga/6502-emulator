# 6502 emulator

I am restarting the 6502 emulator because honestly I think I could do better after what I learned starting the previous one. I also just got bored of the last one so I kinda forgot how the codebase worked and I want to make it more readable.

## OS Support
Only supporting Linux for now because this is meant to be so I can learn. This will not support Windows until I want to learn the win32 api.

## INI Parser
The INI parser is currently flawed, in that it assumes ASCII, and that it does very little validation that some values are sensible. IE it is currently possible to have the value for an INI field to have almost any ascii value, regardless of whether or not it is even a printable character.

## Configuration (Runtime)
The configuration is done through a configuration file called "6502.ini" (or whatever is specified in the command line). Here is a example configuration showing off all of the supported values.
```6502.ini

frequency = 1000000 # default value

[rom]
file          = rom.bin # required
begin_address = 32768   # required all begin address's are inclusive
end_address   = 65536   # required all end address's are exclusive
offset        = 0       # this is the default value

[ram]
begin_address = 0     # required
end_address   = 32768 # required

```


## TODO
- Write the headers so that things are "theoretically" functional
- Maybe migrate the logging library to c++ if I feel like it
- Actually validate the example config is valid, or more accurately, change the code so that it is valid because i did something wrong.