// **InsertLicense** code

#include <windows.h>
#include <stdio.h>

FILE *
fopen_utf8(const char *filename, const char *mode)
{
  FILE *file = NULL;
  WCHAR wMode[32];
  WCHAR wFileName[MAX_PATH];

  // convert the mode from ascii to ucs2
  MultiByteToWideChar(CP_ACP, 0, mode, static_cast<int>(strlen(mode)+1), wMode, 32);
  
  // convert the filename from utf8 to ucs2
  int r = MultiByteToWideChar(CP_UTF8, 0, filename,
                              static_cast<int>(strlen(filename)+1), wFileName, MAX_PATH);
  if (r!=0) {
    file = _wfopen(wFileName, wMode);
  }
  return file;
}
