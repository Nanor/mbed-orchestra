void synth_init();
void synth_tick();
void synth_note_on(int freq, float amp);
void synth_note_off();
int note_to_freq(int note);
float lerp(float a, float b, float t);
