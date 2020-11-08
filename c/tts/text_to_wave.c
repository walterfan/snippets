#include <stdio.h>
#include <string.h>
#include "flite/flite.h"

void usenglish_init(cst_voice *v);
cst_lexicon *cmulex_init(void);

//usage: text2wave("hello", "hello.wav", "./voices")
int text2wave(const char* text, const char* outfile, const char *voice_pathname) {
    
    cst_voice *v;
    cst_wave *w;
    cst_utterance *u;
    const char *voice_pathname;

    /* Initialize Flite, and set up language and lexicon */
    flite_init();
    flite_add_lang("eng",usenglish_init,cmulex_init);
    flite_add_lang("usenglish",usenglish_init,cmulex_init);

    /* Load and select voice */
    v = flite_voice_select(voice_pathname);
    if (v == NULL)
    {
        fprintf(stderr,"failed to load voice: %s\n",voice_pathname);
        return 1;
    }

    u = flite_synth_text(text,v);
    w = utt_wave(u);

    /* Play the resulting wave, save it to a filename, or do none of these */
    cst_wave_save_riff(w,outfile);

    delete_utterance(u); /* will delete w too */

    return 0;
}
