#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <lzma.h>


static bool init_decoder(lzma_stream *strm)
{
	lzma_ret ret = lzma_stream_decoder(strm, UINT64_MAX, LZMA_CONCATENATED);
	if (ret == LZMA_OK)
		return true;

	const char *msg;
	switch (ret) {
	case LZMA_MEM_ERROR:
		msg = "Memory allocation failed";
		break;

	case LZMA_OPTIONS_ERROR:
		msg = "Unsupported decompressor flags";
		break;

	default:
		msg = "Unknown error, possibly a bug";
		break;
	}

	fprintf(stderr, "Error initializing the decoder: %s (error code %u)\n", msg, ret);
	return false;
}

static bool init_encoder(lzma_stream *strm)
{
	lzma_ret ret = lzma_easy_encoder(strm, LZMA_PRESET_EXTREME, LZMA_CHECK_CRC64);
	if (ret == LZMA_OK)
		return true;

	const char *msg;
	switch (ret) {
	case LZMA_MEM_ERROR:
		msg = "Memory allocation failed";
		break;

	case LZMA_OPTIONS_ERROR:
		msg = "Specified preset is not supported";
		break;

	case LZMA_UNSUPPORTED_CHECK:
		msg = "Specified integrity check is not supported";
		break;

	default:
		msg = "Unknown error, possibly a bug";
		break;
	}

	fprintf(stderr, "Error initializing the encoder: %s (error code %u)\n", msg, ret);
	return false;
}

static bool run_stream(lzma_stream *strm, const uint8_t *in, size_t in_size, uint8_t *out, size_t out_capacity, size_t *out_size)
{
	strm->next_in = in;
	strm->avail_in = in_size;
	strm->next_out = out;
	strm->avail_out = out_capacity;

	lzma_ret ret = lzma_code(strm, LZMA_FINISH);
	lzma_end(strm);
	if (ret != LZMA_STREAM_END) {
		fprintf(stderr, "lzma_code did not finish the stream (error code %u)\n", ret);
		return false;
	}

	*out_size = out_capacity - strm->avail_out;
	return true;
}

int main(void)
{
	uint8_t input[BUFSIZ];
	uint8_t compressed[BUFSIZ];
	uint8_t decompressed[BUFSIZ];
	size_t compressed_size = 0;
	size_t decompressed_size = 0;
	size_t i;

	for (i = 0; i < sizeof(input); ++i)
		input[i] = (uint8_t)("Conan Package Manager"[i % 21]);

	lzma_stream encoder = LZMA_STREAM_INIT;
	if (!init_encoder(&encoder))
		return EXIT_FAILURE;
	if (!run_stream(&encoder, input, sizeof(input), compressed, sizeof(compressed), &compressed_size))
		return EXIT_FAILURE;
	if (compressed_size == 0 || compressed_size >= sizeof(input)) {
		fprintf(stderr, "Unexpected compressed size %zu\n", compressed_size);
		return EXIT_FAILURE;
	}

	lzma_stream decoder = LZMA_STREAM_INIT;
	if (!init_decoder(&decoder))
		return EXIT_FAILURE;
	if (!run_stream(&decoder, compressed, compressed_size, decompressed, sizeof(decompressed), &decompressed_size))
		return EXIT_FAILURE;
	if (decompressed_size != sizeof(input) || memcmp(input, decompressed, sizeof(input)) != 0) {
		fprintf(stderr, "Decompressed data does not match input (%zu bytes)\n", decompressed_size);
		return EXIT_FAILURE;
	}

	printf("liblzma %s: %zu bytes -> %zu bytes -> %zu bytes\n", lzma_version_string(), sizeof(input), compressed_size, decompressed_size);
	return EXIT_SUCCESS;
}
