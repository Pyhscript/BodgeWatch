# BodgeWatch
arduino keypad controlled stopwatch/timer

I made this simple project during summer break with limited hardware I had with me (Arduino Uno, stepper motor, 4x4 keypad)

## Stopwatch mode

Activated by pressing S key followed by E key, motor will spin the handle(in my case wire I tied around the shaft) until X is pressed. If F is pressed after motor is stopped builtin LED will blink number of times equal to full revolutions of the handle.

## Timer mode

Activated by pressing T key followed by number of seconds you want handle to spin, followed by E. Timer can be stopped before given time elapses if X is pressed.

## Reset

If wrong key is pressed user can use R key to reset the input

## Keypad map


```
| 1 | 2 | 3 | 4 |
| 5 | 6 | 7 | 8 |
| 9 | 0 | R | X |
| F | S | T | E |

```
