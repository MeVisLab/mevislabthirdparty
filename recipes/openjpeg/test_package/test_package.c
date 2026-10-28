#include <openjpeg.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    opj_cparameters_t parameters;
    opj_image_cmptparm_t component_parameters[3];
    opj_image_t *image;
    opj_codec_t *codec;
    int i;

    printf("OpenJPEG %s, opj_has_thread_support: %d, opj_get_num_cpus: %d\n", opj_version(), opj_has_thread_support(),
           opj_get_num_cpus());

    opj_set_default_encoder_parameters(&parameters);
    if (parameters.tcp_numlayers != 0 || parameters.numresolution != 6 || parameters.cp_disto_alloc != 0) {
        fprintf(stderr, "unexpected default encoder parameters\n");
        return EXIT_FAILURE;
    }
    parameters.tcp_numlayers = 1;
    parameters.tcp_rates[0] = 0;
    parameters.cp_disto_alloc = 1;
    parameters.numresolution = 2;

    memset(component_parameters, 0, sizeof(component_parameters));
    for (i = 0; i < 3; ++i) {
        component_parameters[i].prec = 8;
        component_parameters[i].sgnd = 0;
        component_parameters[i].dx = 1;
        component_parameters[i].dy = 1;
        component_parameters[i].w = 8;
        component_parameters[i].h = 8;
    }
    image = opj_image_create(3, component_parameters, OPJ_CLRSPC_SRGB);
    if (image == NULL) {
        fprintf(stderr, "opj_image_create failed\n");
        return EXIT_FAILURE;
    }
    image->x0 = 0;
    image->y0 = 0;
    image->x1 = 8;
    image->y1 = 8;

    codec = opj_create_compress(OPJ_CODEC_J2K);
    if (codec == NULL) {
        fprintf(stderr, "opj_create_compress failed\n");
        return EXIT_FAILURE;
    }
    if (!opj_setup_encoder(codec, &parameters, image)) {
        fprintf(stderr, "opj_setup_encoder failed\n");
        return EXIT_FAILURE;
    }

    opj_destroy_codec(codec);
    opj_image_destroy(image);
    printf("J2K encoder set up for a %ux%u image with %u components\n", 8, 8, 3);
    return EXIT_SUCCESS;
}
