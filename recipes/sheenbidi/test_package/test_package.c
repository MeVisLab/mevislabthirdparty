#include <SheenBidi/SheenBidi.h>

#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    const char *text = "Hello";
    SBCodepointSequence sequence = {SBStringEncodingUTF8, (void *)text, strlen(text)};

    SBAlgorithmRef algorithm = SBAlgorithmCreate(&sequence);
    if (!algorithm) {
        return 1;
    }

    SBParagraphRef paragraph = SBAlgorithmCreateParagraph(algorithm, 0, INT32_MAX, SBLevelDefaultLTR);
    if (!paragraph) {
        SBAlgorithmRelease(algorithm);
        return 1;
    }

    printf("base level: %u\n", (unsigned)SBParagraphGetBaseLevel(paragraph));

    SBParagraphRelease(paragraph);
    SBAlgorithmRelease(algorithm);
    return 0;
}
