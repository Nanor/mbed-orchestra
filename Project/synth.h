void changeVolume(int amount);
int getVolume();
void incVoice();
void decVoice();
void synth_init();
void synth_clean();
void synth_tick();
void synth_note_on(int freq, float amp);
void synth_note_off();
int note_to_freq(int note);
float lerp(float a, float b, float t);
int clamp(int value, int min, int max);

#define MAXVOLUME 99
