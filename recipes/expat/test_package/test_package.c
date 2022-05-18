#include <stdio.h>
#include "expat.h"

#ifdef XML_LARGE_SIZE
#if defined(XML_USE_MSC_EXTENSIONS) && _MSC_VER < 1400
#define XML_FMT_INT_MOD "I64"
#else
#define XML_FMT_INT_MOD "ll"
#endif
#else
#define XML_FMT_INT_MOD "l"
#endif

static void XMLCALL startElement(void *userData, const char *name, const char **atts)
{
  (void)atts;
  int i;
  int *depthPtr = (int *)userData;

  for (i = 0; i < *depthPtr; i++)  putchar('\t');
  puts(name);
  *depthPtr += 1;
}

static void XMLCALL endElement(void *userData, const char *name)
{
  (void)name;
  int *depthPtr = (int *)userData;
  *depthPtr -= 1;
}

int main(int argc, char *argv[])
{
  XML_Parser parser = XML_ParserCreate(NULL);
  int depth = 0;
  (void)argc;
  (void)argv;

  XML_SetUserData(parser, &depth);
  XML_SetElementHandler(parser, startElement, endElement);
  XML_ParserFree(parser);
  printf("Test application successfully!\n");
  return 0;
}
