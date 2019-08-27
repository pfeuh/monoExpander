# monoExpander
Arduino's midi monophonic expander
Based on tone(freq) function.

Hardware:

Add a midi in (optocoupler + puulup) on TX.
Add a jack socket on gpio AUDIO_OUTPUT_PIN.
Add a button on gpio CALL_CONFIG_KEY.
Add (optional) a jack socket on gpio GATE_OUTPUT_PIN.

At the reboot, if the button is pressed, you can configure with a PC terminal.

