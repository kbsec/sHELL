#include <windows.h>

BOOL s_fgets(HANDLE hFile, char *buffer, DWORD n) {
  if (hFile == INVALID_HANDLE_VALUE || buffer == NULL || n == 0) {
    return FALSE;
  }

  DWORD bytesRead;
  BOOL success;
  char ch;
  DWORD i = 0;
  BOOL crFound = FALSE;

  while (i < n - 1) {
    success = ReadFile(hFile, &ch, sizeof(char), &bytesRead, NULL);

    if (!success || bytesRead == 0) { // Error or EOF
      break;
    }

    // Check for CR+LF (Windows-style newline)
    if (ch == '\r') {
      crFound = TRUE;
      continue;
    } else if (crFound && ch == '\n') {
      buffer[i++] = '\n';
      break;
    }

    crFound = FALSE;
    buffer[i++] = ch;
  }

  buffer[i] = '\0'; // Null-terminate the string
  return i > 0;
}

BOOL s_fwgets(HANDLE hFile, wchar_t *buffer, DWORD n) {
  if (hFile == INVALID_HANDLE_VALUE || buffer == NULL || n == 0) {
    return FALSE;
  }

  DWORD bytesRead;
  BOOL success;
  wchar_t ch;
  DWORD i = 0;
  BOOL crFound = FALSE;

  while (i < n - 1) {
    success = ReadFile(hFile, &ch, sizeof(wchar_t), &bytesRead, NULL);

    if (!success || bytesRead == 0) { // Error or EOF
      break;
    }

    // Check for CR+LF (Windows-style newline)
    if (ch == L'\r') {
      crFound = TRUE;
      continue;
    } else if (crFound && ch == L'\n') {
      buffer[i++] = L'\n';
      break;
    }

    crFound = FALSE;
    buffer[i++] = ch;
  }

  buffer[i] = L'\0'; // double Null-terminate the string
  return i > 0;
}
